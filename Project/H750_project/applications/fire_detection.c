/*
 * @Author: lebhoryi@gmail.com
 * @Date: 2021-06-30 16:52:58
 * @LastEditors: lebhoryi@gmail.com
 * @LastEditTime: 2021-07-01 19:36:20
 * @Version: V0.0.1
 * @FilePath: /art_pi/applications/fire_detection.c
 * @Description: fire detection demo app
 */
#include <rtthread.h>
#include "drv_common.h"
#include <rtdevice.h>
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports
#include "drv_dcmi.h"

/* fire detection */
#include <rt_ai_fire_model.h>
#include <rt_ai.h>
#include <rt_ai_log.h>
#include <backend_cubeai.h>
#include <logo.h>
#include "user_ui/ui.h"

#define LED_PIN GET_PIN(I, 8)


static rt_thread_t fire_th = RT_NULL;
struct rt_event ov2640_event;
rt_ai_buffer_t ai_flag = 0;
static int show_ui_flag = 0;


void ai_run_complete(void *arg){
    *(int*)arg = 1;
}

void ai_camera();
void bilinera_interpolation(rt_uint8_t *in_array, short height, short width,
                            rt_uint8_t *out_array, short out_height, short out_width);

//static void show_ui_timer_out(void* parameter)
//{
//     show_ui_flag = 1;
//}


int fire_app(void){
	int flame_flag = 0;
    /* init spi data notify event */
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);

    struct drv_lcd_device *lcd;
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, 240};
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

    lcd_show_image(0, 0, 320, 240, LOGO);
    lcd_show_string(90, 140, 16, "Hello RT-Thread!");
    lcd_show_string(90, 156, 16, "Demo: Fire Detection");
    rt_thread_mdelay(1000);

    rt_err_t result = RT_EOK;
    int ai_run_complete_flag = 0;

    /* find a registered model handle */
    static rt_ai_t model = NULL;
    model = rt_ai_find(RT_AI_FIRE_MODEL_NAME);
    if(!model) {rt_kprintf("ai model find err\r\n"); return -1;}

    // allocate input memory
    rt_ai_buffer_t *input_image = rt_malloc(RT_AI_FIRE_IN_1_SIZE_BYTES);
    if (!input_image) {rt_kprintf("malloc err\n"); return -1;}

    // allocate calculate memory
    rt_ai_buffer_t *work_buf = rt_malloc(RT_AI_FIRE_WORK_BUFFER_BYTES);
    if (!work_buf) {rt_kprintf("malloc err\n"); return -1;}

    // allocate output memory
    rt_ai_buffer_t *_out = rt_malloc(RT_AI_FIRE_OUT_1_SIZE_BYTES);
    if (!_out) {rt_kprintf("malloc err\n"); return -1;}

    // ai model init
    rt_ai_buffer_t model_init = rt_ai_init(model, work_buf);
    if (model_init != 0) {rt_kprintf("ai init err\n"); return -1;}
    rt_ai_config(model, CFG_INPUT_0_ADDR, input_image);
    rt_ai_config(model, CFG_OUTPUT_0_ADDR, _out);

    ai_camera();


//    rt_timer_t show_ui_timer = rt_timer_create("show_ui_timer", show_ui_timer_out,RT_NULL,  RT_TICK_PER_SECOND * 10,RT_TIMER_FLAG_ONE_SHOT);
//    rt_timer_start(show_ui_timer);

    while(1)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_event_recv(&ov2640_event,
                            1,
                            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER,
                            RT_NULL);
        rt_pin_write(LED_PIN, PIN_HIGH);
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        if (ai_flag > 0)
        {
            // resize
            bilinera_interpolation(lcd->lcd_info.framebuffer, 240, 320, input_image, 64, 64);
            rt_ai_run(model, NULL, NULL);
            uint8_t *out = (uint8_t *)rt_ai_output(model, 0);
            rt_kprintf("pred: %d %d\n", out[0], out[1]);
            if (out[0] >= 255 && out[1] < 50)
			{
				lcd_show_string(20, 20, 16, "Fire");
				flame_flag++;
			}
            else
			{
				lcd_show_string(20, 20, 16, "No Fire");
				flame_flag--;
			}

			if(flame_flag == 10)
			{
				flame_flag = 0;
				rt_kprintf("Detected the fire!\n");
			}
			else if(flame_flag < 0)
			{
				flame_flag = 0;
			}
        }
        DCMI_Start();

        rt_thread_mdelay(70);
//        if(show_ui_flag)
//        {
//            ui_init();
//            for(int i=0;i!=100 ;i++) rt_thread_mdelay(600);
//            close_lvgl_show();
//            rt_timer_start(show_ui_timer);
//        }
    }
    rt_free(input_image);
    rt_free(work_buf);
    rt_free(_out);

    return 0;
}
//MSH_CMD_EXPORT(fire_app,fire demo);
//INIT_COMPONENT_EXPORT(fire_app);



void fire_detec_thread(void)
{
    close_lvgl_show();
    rt_uint32_t stack_size = 8192;
    rt_uint8_t  priority = 21;
    rt_uint32_t tick = 5000;
    static int thread_create_flag = 0;

    if(thread_create_flag == 0)
    {
        fire_th = rt_thread_create("fire_detec", fire_app, RT_NULL, stack_size, priority, tick);
        thread_create_flag = 1;
    }
    if(fire_th == RT_NULL)
    {
        rt_kprintf("fire_th create failed!\n");
    }
    rt_thread_startup(fire_th);
}

void fire_detec_thread_stop()
{
    rt_thread_delete(fire_th);
    ui_init();
}
MSH_CMD_EXPORT(fire_detec_thread,fire_detec_thread);
MSH_CMD_EXPORT(fire_detec_thread_stop,fire_detec_thread_stop);

void ai_camera()
{
    rt_gc0328c_init();
    ai_flag = 1;
    DCMI_Start();
}


int is_in_array(short x, short y, short height, short width)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return 1;
    else
        return 0;
}


void bilinera_interpolation(rt_uint8_t* in_array, short height, short width,
                            rt_uint8_t* out_array, short out_height, short out_width)
{
    double h_times = (double)out_height / (double)height,
           w_times = (double)out_width / (double)width;
    short  x1, y1, x2, y2, f11, f12, f21, f22;
    double x, y;

    for (int i = 0; i < out_height; i++){
        for (int j = 0; j < out_width*3; j=j+3){
            for (int k =0; k <3; k++){
                x = j / w_times + k;
                y = i / h_times;

                x1 = (short)(x - 3);
                x2 = (short)(x + 3);
                y1 = (short)(y + 1);
                y2 = (short)(y - 1);
                f11 = is_in_array(x1, y1, height, width*3) ? in_array[y1*width*3+x1] : 0;
                f12 = is_in_array(x1, y2, height, width*3) ? in_array[y2*width*3+x1] : 0;
                f21 = is_in_array(x2, y1, height, width*3) ? in_array[y1*width*3+x2] : 0;
                f22 = is_in_array(x2, y2, height, width*3) ? in_array[y2*width*3+x2] : 0;
                out_array[i*out_width*3+j+k] = (rt_uint8_t)(((f11 * (x2 - x) * (y2 - y)) +
                                           (f21 * (x - x1) * (y2 - y)) +
                                           (f12 * (x2 - x) * (y - y1)) +
                                           (f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
            }
        }
    }
}

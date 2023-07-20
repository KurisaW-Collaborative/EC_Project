#include "ui.h"
static lv_obj_t *ui_Screen_start;
static lv_obj_t * bar ;

LV_FONT_DECLARE(normal_font);

void ui_screen_start_init(void)
{
    ui_Screen_start = lv_obj_create(NULL, NULL);

    lv_obj_set_style_local_bg_color(ui_Screen_start,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLACK);


    bar = lv_bar_create(ui_Screen_start,NULL);
    lv_obj_remove_style(bar,LV_OBJ_PART_ALL,NULL);  /*To have a clean start*/
    lv_obj_set_size(bar, 200, 20);
    lv_obj_set_x(bar, 70);
    lv_obj_set_y(bar, 250);
    lv_bar_set_start_value(bar, 0, LV_ANIM_OFF);

    lv_obj_t *loading_text = lv_label_create(ui_Screen_start, NULL);
    lv_label_set_recolor(loading_text, true);
    lv_obj_set_style_local_text_font(loading_text, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
    lv_obj_set_width(loading_text, 200);  /// 1
    lv_obj_set_height(loading_text, 150); /// 1
    lv_obj_set_x(loading_text, 90);
    lv_obj_set_y(loading_text, 200-32);
    lv_label_set_text(loading_text, "#226E93 Loading...#");
}

void show_start_ui()
{
    lv_disp_load_scr(ui_Screen_start);

    lv_bar_set_anim_time(bar,1000*5);
    lv_bar_set_value(bar, 80, LV_ANIM_ON);
    lv_bar_set_anim_time(bar,1000*1);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);
    rt_thread_mdelay(1000);
    show_main_ui();
}
MSH_CMD_EXPORT(show_start_ui, show start screen);

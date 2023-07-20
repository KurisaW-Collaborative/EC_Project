/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-14     瓜子的皮       the first version
 */
#include "data_communication.h"

static rt_device_t serial;
static struct rt_semaphore usart_rx_sem;
static int lvgl_rsmg = 0;
static char* g_uart_name = "uart1";
static rt_thread_t thread;

static int char_to_int(char* str)
{
    int ret = 0;
    int i =0;
    for(;str[i] != '\0';i++)
    {
        ret *=10;
        ret += str[i] - '0';
    }
    return ret;
}

//static double char_to_double(char* str)
//{
//    double ret = 0;
//    int i =0;
//    for(;str[i] != '.';i++)
//    {
//        ret *=10;
//        ret += str[i] - '0';
//    }
//    i++;
//
//    int len = 1;
//    double decimals = 0;
//    for(;str[i] != '\0';i++)
//    {
//        len = len *10;
//        decimals *=10;
//        decimals += str[i] - '0';
//    }
//    decimals = decimals / len;
//    ret += decimals;
//    return ret;
//}

static void parse_communication(char* str)
{
    //命令格式 $[type],[value]
    //需要确保传入数据合法
    int str_index = 1;

    char communication_type[COMMUNICAtION_MAX_DATA_LEN];
    rt_memset(communication_type,0,sizeof(communication_type));
   // double  communication_value = 0;
    char char_communication_value[COMMUNICAtION_MAX_DATA_LEN];
    rt_memset(char_communication_value,0,sizeof(char_communication_value));
    //解析命令类型
    int i =0;
    for(i = 0; str[str_index] != ',' && str[str_index] != '\0' ;)
    {
        communication_type[i++] = str[str_index ++];
    }
    str_index ++;
    communication_type[i] = '\0';
    rt_kprintf("communication_type:%s \n",communication_type);

    //解析命令值
    for(i =0 ; str[str_index] != '\0';)
    {
        char_communication_value[i++] = str[str_index++];
    }
    char_communication_value[i] = '\0';
    rt_kprintf("char_communication_value:%s \n",char_communication_value);
  //  communication_value = char_to_double(char_communication_value);

    if(!rt_strcmp(TEMPERATURE_TYPE,communication_type))
    {
        //收到温度数据后的触发
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_deteciton_abnormal_temperature(char_communication_value);
            set_deteciton_temperature(char_communication_value);
            set_temperature(char_communication_value);
        }
    } else if(!rt_strcmp(HUMIDITY_TYPE,communication_type)){
        //收到湿度数据后的触发
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_deteciton_abnormal_humidity(char_communication_value);
            set_deteciton_humidity(char_communication_value);
            set_humidity(char_communication_value);
        }

    } else if(!rt_strcmp(AIR_PRESSURE_TYPE,communication_type)){
        //收到气压数据后的触发
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_deteciton_pressure(char_communication_value);
            set_deteciton_abnormal_pressure(char_communication_value);
            set_pressure(char_communication_value);
        }
    } else if(!rt_strcmp(ILLNUMINATION_TYPE,communication_type)){
        //收到空气质量后的触发
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_deteciton_abnormal_illumination(char_communication_value);
            set_deteciton_illumination(char_communication_value);
        }
    } else if(!rt_strcmp(TIME_TYPE_HOUR,communication_type)){
        rt_kprintf("recv hour \n");
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_time(char_to_int(char_communication_value), -1, -1, -1);
        }
    } else if(!rt_strcmp(TIME_TYPE_MINUTE,communication_type)){
        rt_kprintf("recv min \n");
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_time(-1, char_to_int(char_communication_value), -1, -1);
        }
    }   else if(!rt_strcmp(TIME_TYPE_SECOND,communication_type)){
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_time(-1, -1, char_to_int(char_communication_value), -1);
        }
    } else if(!rt_strcmp(TIME_TYPE_WDAY,communication_type)){
        rt_kprintf("recv wday \n");
        if(lvgl_rsmg)//关于lvgl的触发
        {
            set_time(-1, -1, -1, char_to_int(char_communication_value));
        }
    }


}

void communication_recv()
{
    char ch;
    char communication_ss[64];
    rt_memset(communication_ss,0,sizeof(communication_ss));
    int  communication_ss_index = 0;
    int flag = 0;

    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(&usart_rx_sem, RT_WAITING_FOREVER);
        }


        if(ch == '$') flag =1;
        if(!flag) continue;//如果收到帧头则继续往下执行

        if(ch == '\0')//发送信息没有带有\n作为数据结尾
        {//错误数据格式 直接丢弃
            rt_memset(communication_ss,0,sizeof(communication_ss));
            communication_ss_index = 0;
            flag = 0;
        //    rt_kprintf("ch == '\\0':%s \n",communication_ss);
            continue;
        }

        if(ch != '\n')
        {
            communication_ss[communication_ss_index++] = ch;
           // rt_kprintf("ch != '\\n':%s \n",communication_ss);
            if(communication_ss_index > 63)//过长数据为错误数据 丢弃数据
            {
                flag = 0;
                rt_memset(communication_ss,0,sizeof (communication_ss));
                communication_ss_index = 0;
            }
        }else {
            communication_ss[communication_ss_index] = '\0';
        //    rt_kprintf("%s \n",communication_ss);
            parse_communication(communication_ss);

            flag = 0;
            rt_memset(communication_ss,0,sizeof (communication_ss));
            communication_ss_index = 0;
        }

     }
}

void communication_send(char* str)
{

    char ch;
    for(int i =0 ; i != rt_strlen(str);i++)
    {
        ch = str[i];
        if(serial != RT_NULL) rt_device_write(serial, 0, &ch, 1);
    }
}

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&usart_rx_sem);

    return RT_EOK;
}


static void communication_init()
{
    /* 初始化信号量 */
    static int sem_falg = 0;
    if(sem_falg++ == 0) rt_sem_init(&usart_rx_sem, "usart_rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* 以中断接收及轮询发送模式打开串口设备 */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);

    thread = rt_thread_create("communication_recv", communication_recv, RT_NULL, 1024, 25, 10);
        /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}

void set_communication_uart(char* uart_name)
{
    rt_device_t t_serial = rt_device_find(uart_name);
     if (!t_serial)
     {
         rt_kprintf("find %s failed!\n", uart_name);
         return ;
     }
    //对原先串口存留的数据进行清理
     if(serial !=RT_NULL) rt_device_close(serial);//关闭旧的串口
     if(thread !=RT_NULL)rt_thread_detach(thread);
     usart_rx_sem.value = 0;
    //使用新的串口
    g_uart_name = uart_name;
    serial = t_serial;
    communication_init();
}

MSH_CMD_EXPORT(set_communication_uart,set_communication_uart);

void communication_send_test(int argc,char* argv[])
{
    char str[64];
    int str_index = 0;

    rt_memset(str,0,sizeof (str));
    for(int i =0 ;i != rt_strlen(argv[1]) ;i++)
    {
        str[str_index++] = argv[1][i];
    }
    str[str_index++] = '\n';
    str[str_index] = '\0';
    char ch;
    for(int i =0 ; i != rt_strlen(str);i++)
    {
        ch = str[i];
        rt_device_write(serial, 0, &ch, 1);
    }
}
MSH_CMD_EXPORT(communication_send_test,communication_send_test);
void enable_lvgl_rsmg()
{
    lvgl_rsmg = 1;
}

void disable_lvgl_rsmg()
{
    lvgl_rsmg = 0;
}


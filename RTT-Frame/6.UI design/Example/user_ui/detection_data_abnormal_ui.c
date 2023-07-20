/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-13     瓜子的皮       the first version
 */

#include "ui.h"
lv_obj_t *ui_deteciton_abnormal;
static lv_obj_t* table;
//static char* Mark_in_red(char * str)
//{
//    int str_len=strlen(str);//测量字符串的长度
//    char* ss = "#0000ff";
//
//    int i = 0,j = 7;
//    for(;i<str_len&&j<64;i++,j++)
//    {
//        ss[j] = str[i];
//    }
//    ss[j] = ' ';
//    ss[j+1] = '#';
//    ss[j+2] = '\0';
//
//    return  ss;
//}

void set_deteciton_abnormal_temperature(char* num)
{
    lv_table_set_cell_value(table, 1, 1, num);

}
void set_deteciton_abnormal_pressure(char* pressure_numint )
{
 lv_table_set_cell_value(table, 2, 1, pressure_numint);

}
void set_deteciton_abnormal_humidity(char* humidity_numint )
{
    lv_table_set_cell_value(table, 3, 1, humidity_numint);

}

void set_deteciton_abnormal_illumination(char* illumination_stringint )
{
    lv_table_set_cell_value(table, 4, 1, illumination_stringint);

}

void  detection_data_abnormal_ui_init()
{
    ui_deteciton_abnormal = lv_obj_create(NULL, NULL);

    table = lv_table_create(ui_deteciton_abnormal,NULL);
    lv_table_set_col_width(table, 0,160);  /// 1
    lv_table_set_col_width(table, 1,160);  /// 1
    lv_obj_set_height(table, 300); /// 1

    lv_table_set_row_cnt(table,6);
    lv_table_set_col_cnt(table,2);
   // lv_obj_set_style_local_text_font(table, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
    //lv_label_set_recolor(table, true);

    lv_obj_set_x(table, 0);
    lv_obj_set_y(table, 90);
               /*Fill the first column*/
    lv_table_set_cell_value(table, 0, 0, "Environment");
    lv_table_set_cell_value(table, 1, 0, "Temperature");
    lv_table_set_cell_value(table, 2, 0, "Humidity");
    lv_table_set_cell_value(table, 3, 0, "Pressure");
    lv_table_set_cell_value(table, 4, 0, "illumination");
    lv_table_set_cell_value(table, 5, 0, "Noise");

    lv_table_set_cell_value(table, 0, 1, "Value");
    lv_table_set_cell_value(table, 1, 1, "$7");
    lv_table_set_cell_value(table, 2, 1, "$4");
    lv_table_set_cell_value(table, 3, 1, "$6");
    lv_table_set_cell_value(table, 4, 1, "$2");
    lv_table_set_cell_value(table, 5, 1, " $8 ");

}
void show_deteciton_abnormal_ui()
{
    lv_disp_load_scr(ui_deteciton_abnormal);
}
MSH_CMD_EXPORT(show_deteciton_abnormal_ui, show_deteciton_abnormal_ui);

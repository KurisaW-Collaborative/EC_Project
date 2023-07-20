#include "ui.h"


lv_obj_t *ui_deteciton;
static lv_obj_t *time_minute;
static lv_obj_t *time_sketchy;
static lv_obj_t *github;
static lv_obj_t *temperature;
static lv_obj_t *pressure;
static lv_obj_t *humidity;
static lv_obj_t *illumination;
static lv_obj_t *table;
LV_FONT_DECLARE(small_font);
LV_FONT_DECLARE(normal_font);
LV_FONT_DECLARE(kinestate_background);

LV_FONT_DECLARE(atmospheric_pressure);
LV_FONT_DECLARE(temperature_photo);
LV_FONT_DECLARE(humidness_photo);
//LV_FONT_DECLARE(illumination);
LV_FONT_DECLARE(air_quality_photo);
void set_deteciton_temperature(char* num)
{

    lv_label_set_text(temperature, num);
  //  lv_label_ins_text(temperature, LV_LABEL_POS_LAST, num);
    return;
}

void set_deteciton_pressure(char* pressure_num)
{
    lv_label_set_text(pressure, pressure_num);
    //lv_label_ins_text(pressure, LV_LABEL_POS_LAST, pressure_num);
}

void set_deteciton_humidity(char* humidity_num)
{
    lv_label_set_text(humidity, humidity_num);
 //   lv_label_ins_text(humidity, LV_LABEL_POS_LAST, "%");
}

void set_deteciton_illumination(char* illumination)
{
    lv_label_set_text(illumination, illumination);
    //lv_label_ins_text(illumination, LV_LABEL_POS_LAST, air_string);
}


//void ui_screen_detection_init(void)
//{
////背景
//    ui_deteciton = lv_obj_create(NULL, NULL);
//    lv_obj_t *background = lv_img_create(ui_deteciton, NULL);
//    lv_img_set_src(background, &kinestate_background);
//    lv_img_set_zoom(background,545);
//    lv_obj_set_width(background, 480);
//    lv_obj_set_height(background, 320);
//
//    lv_obj_set_x(background, 0);
//    lv_obj_set_y(background, 0);
//    lv_img_set_pivot(background, 0, 0); /*Rotate around the top left corner*/
////其他
//    github = lv_label_create(ui_deteciton, NULL);
//    lv_obj_set_style_local_text_font(github, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &small_font);
//    lv_label_set_long_mode(github, LV_LABEL_LONG_SROLL_CIRC);
//    lv_label_set_text(github, "Project code:https://github.com/KurisaW-Collaborative/EC_Project/     ");
//    lv_obj_set_width(github, 450);
//    lv_obj_set_x(github, 0);
//    lv_obj_set_y(github, 0);
//
//    time_minute = lv_label_create(ui_deteciton, NULL);
//    lv_label_set_recolor(time_minute, true);
//    lv_obj_set_style_local_text_font(time_minute, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//    lv_obj_set_x(time_minute, 200);
//    lv_obj_set_y(time_minute, 20);
//
//    time_sketchy = lv_label_create(ui_deteciton, NULL);
//    lv_label_set_recolor(time_sketchy, true);
//    lv_obj_set_style_local_text_font(time_sketchy, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//    lv_obj_set_x(time_sketchy, 0);
//    lv_obj_set_y(time_sketchy, 20);
////字符
//    temperature = lv_label_create(ui_deteciton, NULL);
//       lv_label_set_recolor(temperature, true);
//       lv_obj_set_style_local_text_font(temperature, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//       lv_obj_set_width(temperature, 200);  /// 1
//       lv_obj_set_height(temperature, 150); /// 1
//       lv_obj_set_x(temperature, 0);
//       lv_obj_set_y(temperature, 42);
//       set_deteciton_temperature("Collecting...");
//
//       humidity = lv_label_create(ui_deteciton, NULL);
//       lv_label_set_recolor(humidity, true);
//       lv_obj_set_style_local_text_font(humidity, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//       lv_obj_set_width(humidity, 200);  /// 1
//       lv_obj_set_height(humidity, 150); /// 1
//       lv_obj_set_x(humidity, 0);
//       lv_obj_set_y(humidity, 62);
//       set_deteciton_humidity("Collecting...");
//
//       pressure = lv_label_create(ui_deteciton, NULL);
//       lv_label_set_recolor(pressure, true);
//       lv_obj_set_style_local_text_font(pressure, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//       lv_obj_set_width(pressure, 200);  /// 1
//       lv_obj_set_height(pressure, 150); /// 1
//       lv_obj_set_x(pressure, 0);
//       lv_obj_set_y(pressure, 82);
//       set_deteciton_pressure("Collecting...");
//
//       illumination = lv_label_create(ui_deteciton, NULL);
//       lv_label_set_recolor(illumination, true);
//       lv_obj_set_style_local_text_font(illumination, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
//       lv_obj_set_width(illumination, 200);  /// 1
//       lv_obj_set_height(illumination, 150); /// 1
//       lv_obj_set_x(illumination, 0);
//       lv_obj_set_y(illumination, 102);
//       set_deteciton_air("Collecting...");
//}

void ui_screen_detection_init(void)
{
    ////背景
        ui_deteciton = lv_obj_create(NULL, NULL);
        lv_obj_t *background = lv_img_create(ui_deteciton, NULL);
        lv_img_set_src(background, &kinestate_background);
        lv_img_set_zoom(background,545);
        lv_obj_set_width(background, 480);
        lv_obj_set_height(background, 320);

        lv_obj_set_x(background, 0);
        lv_obj_set_y(background, 0);
        lv_img_set_pivot(background, 0, 0); /*Rotate around the top left corner*/
    //其他
        github = lv_label_create(ui_deteciton , NULL);
        lv_obj_set_style_local_text_font(github, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &small_font);
        lv_label_set_long_mode(github, LV_LABEL_LONG_SROLL_CIRC);
        lv_label_set_text(github, "Project code:https://github.com/KurisaW-Collaborative/EC_Project/     ");
        lv_obj_set_width(github, 450);
        lv_obj_set_x(github, 0);
        lv_obj_set_y(github, 0);

        time_minute = lv_label_create(ui_deteciton, NULL);
        lv_label_set_recolor(time_minute, true);
        lv_obj_set_style_local_text_font(time_minute, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
        lv_obj_set_x(time_minute, 200);
        lv_obj_set_y(time_minute, 20);

        time_sketchy = lv_label_create(ui_deteciton, NULL);
        lv_label_set_recolor(time_sketchy, true);
        lv_obj_set_style_local_text_font(time_sketchy, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
        lv_obj_set_x(time_sketchy, 0);
        lv_obj_set_y(time_sketchy, 20);
    //字符
//        LV_FONT_DECLARE(atmospheric_pressure);
//        LV_FONT_DECLARE(temperature_photo);
//        LV_FONT_DECLARE(humidness_photo);
//        LV_FONT_DECLARE(illumination);
        lv_obj_t *atmospheric_pressure_img = lv_img_create(ui_deteciton, NULL);
        lv_img_set_src(atmospheric_pressure_img, &atmospheric_pressure);
        lv_img_set_zoom(atmospheric_pressure_img,   64);
        lv_obj_set_width(atmospheric_pressure_img,  200);
        lv_obj_set_height(atmospheric_pressure_img, 200);

        lv_obj_set_x(atmospheric_pressure_img, 30-15);
        lv_obj_set_y(atmospheric_pressure_img, 150);
        lv_img_set_pivot(atmospheric_pressure_img, 0, 0); /*Rotate around the top left corner*/

        lv_obj_t *temperature_photo_p = lv_img_create(ui_deteciton, NULL);
        lv_img_set_src(temperature_photo_p, &temperature_photo);
        lv_img_set_zoom(temperature_photo_p,64);
        lv_obj_set_width(temperature_photo_p, 200);
        lv_obj_set_height(temperature_photo_p, 200);

        lv_obj_set_x(temperature_photo_p, 110-15);
        lv_obj_set_y(temperature_photo_p, 150);
        lv_img_set_pivot(temperature_photo_p, 0, 0); /*Rotate around the top left corner*/

        lv_obj_t *humidness_photo_p = lv_img_create(ui_deteciton, NULL);
        lv_img_set_src(humidness_photo_p, &humidness_photo);
        lv_img_set_zoom(humidness_photo_p,64);
        lv_obj_set_width(humidness_photo_p, 200);
        lv_obj_set_height(humidness_photo_p, 200);

        lv_obj_set_x(humidness_photo_p, 190-15);
        lv_obj_set_y(humidness_photo_p, 150);
        lv_img_set_pivot(humidness_photo_p, 0, 0); /*Rotate around the top left corner*/

        lv_obj_t *air_quality_img = lv_img_create(ui_deteciton, NULL);
        lv_img_set_src(air_quality_img, &air_quality_photo);
        lv_img_set_zoom(air_quality_img,64);
        lv_obj_set_width(air_quality_img, 200);
        lv_obj_set_height(air_quality_img, 200);

        lv_obj_set_x(air_quality_img, 270-15);
        lv_obj_set_y(air_quality_img, 150);
        lv_img_set_pivot(air_quality_img, 0, 0); /*Rotate around the top left corner*/

        temperature = lv_label_create(ui_deteciton, NULL);
           lv_label_set_recolor(temperature, true);
           lv_obj_set_style_local_text_font(temperature, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(temperature, 200);  /// 1
           lv_obj_set_height(temperature, 150); /// 1
           lv_obj_set_x(temperature,110-15);
           lv_obj_set_y(temperature, 210);
           set_deteciton_temperature("18.3");

           humidity = lv_label_create(ui_deteciton, NULL);
           lv_label_set_recolor(humidity, true);
           lv_obj_set_style_local_text_font(humidity, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(humidity, 200);  /// 1
           lv_obj_set_height(humidity, 150); /// 1
           lv_obj_set_x(humidity,  190-15);
           lv_obj_set_y(humidity, 210);
           set_deteciton_humidity("18.5");

           pressure = lv_label_create(ui_deteciton, NULL);
           lv_label_set_recolor(pressure, true);
           lv_obj_set_style_local_text_font(pressure, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(pressure, 200);  /// 1
           lv_obj_set_height(pressure, 150); /// 1
           lv_obj_set_x(pressure, 30-15);
           lv_obj_set_y(pressure, 210);
           set_deteciton_pressure("18.6");

           illumination = lv_label_create(ui_deteciton, NULL);
           lv_label_set_recolor(illumination, true);
           lv_obj_set_style_local_text_font(illumination, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(illumination, 200);  /// 1
           lv_obj_set_height(illumination, 150); /// 1
           lv_obj_set_x(illumination, 270-15);
           lv_obj_set_y(illumination, 210);
           set_deteciton_illumination("18.7");
}

void show_deteciton_ui()
{
    lv_disp_load_scr(ui_deteciton);
    now_show_ui.screen = ui_deteciton;
    now_show_ui.time_minute = time_minute;
    now_show_ui.time_sketchy = time_sketchy;
}

MSH_CMD_EXPORT(show_deteciton_ui, show deteciton ui);

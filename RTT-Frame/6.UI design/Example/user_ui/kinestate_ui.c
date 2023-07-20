#include "ui.h"

lv_obj_t *ui_kinestate;
static lv_obj_t *time_minute;
static lv_obj_t *time_sketchy;
static lv_obj_t *github;
static lv_obj_t *longitude;
static lv_obj_t *latitude;
static lv_obj_t *travel_time;
static lv_obj_t *travel_distance;
static lv_obj_t * exercise_status;
static lv_obj_t *speed;
static lv_obj_t *direction;

LV_FONT_DECLARE(small_font);
LV_FONT_DECLARE(normal_font);
LV_FONT_DECLARE(kinestate_background);
LV_FONT_DECLARE(kinestate_font);


void set_longitude(char * longitude_nub)
{
    lv_label_set_text(longitude, "#0000ff Longitude: #");
    lv_label_ins_text(longitude, LV_LABEL_POS_LAST, longitude_nub);
    return;
}

void set_latitude(char * latitude_nub)
{
    lv_label_set_text(latitude, "#0000ff Latitude: #");
    lv_label_ins_text(latitude, LV_LABEL_POS_LAST, latitude_nub);
    return;
}

void set_exercise_status(char * exercise_status_string)
{
    lv_label_set_text(exercise_status, "#0000ff Exercise Status: #");
    lv_label_ins_text(exercise_status, LV_LABEL_POS_LAST, exercise_status_string);
    return;
}

void set_speed(char* speed_string)
{
    lv_label_set_text(speed, "#0000ff Speed: #");
    lv_label_ins_text(speed, LV_LABEL_POS_LAST, speed_string);
    return;
}

void set_direction(char* direction_string)
{
    lv_label_set_text(direction, "#0000ff Directon: #");
    lv_label_ins_text(direction, LV_LABEL_POS_LAST, direction_string);
    return;
}

void set_travel_time(char* travel_time_string)
{
    lv_label_set_text(travel_time, "#0000ff Travel Time: #");
    lv_label_ins_text(travel_time, LV_LABEL_POS_LAST, travel_time_string);
    return;
}

void set_travel_distance(char* travel_distance_string)
{
    lv_label_set_text(travel_distance, "#0000ff Travel Distance: #");
    lv_label_ins_text(travel_distance, LV_LABEL_POS_LAST, travel_distance_string);
    return;
}


void ui_screen_kinestate_init(void)
{
//背景
    ui_kinestate = lv_obj_create(NULL, NULL);
    lv_obj_t *background = lv_img_create(ui_kinestate, NULL);
    lv_img_set_src(background, &kinestate_background);
    lv_img_set_zoom(background,545);
    lv_obj_set_width(background, 480);
    lv_obj_set_height(background, 320);

    lv_obj_set_x(background, 0);
    lv_obj_set_y(background, 0);
    lv_img_set_pivot(background, 0, 0); /*Rotate around the top left corner*/
//其他
    github = lv_label_create(ui_kinestate, NULL);
    lv_obj_set_style_local_text_font(github, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &small_font);
    lv_label_set_long_mode(github, LV_LABEL_LONG_SROLL_CIRC);
    lv_label_set_text(github, "Project code:https://github.com/KurisaW-Collaborative/EC_Project/     ");
    lv_obj_set_width(github, 450);
    lv_obj_set_x(github, 0);
    lv_obj_set_y(github, 0);

    time_minute = lv_label_create(ui_kinestate, NULL);
    lv_label_set_recolor(time_minute, true);
    lv_obj_set_style_local_text_font(time_minute, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
    lv_obj_set_x(time_minute, 200);
    lv_obj_set_y(time_minute, 20);

    time_sketchy = lv_label_create(ui_kinestate, NULL);
    lv_label_set_recolor(time_sketchy, true);
    lv_obj_set_style_local_text_font(time_sketchy, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
    lv_obj_set_x(time_sketchy, 0);
    lv_obj_set_y(time_sketchy, 20);
//字符
    exercise_status = lv_label_create(ui_kinestate, NULL);
    lv_label_set_recolor(exercise_status, true);
    lv_obj_set_style_local_text_font(exercise_status, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
    lv_obj_set_width(exercise_status, 200);  /// 1
    lv_obj_set_height(exercise_status, 150); /// 1
    lv_obj_set_x(exercise_status, 0);
    lv_obj_set_y(exercise_status, 42);
    set_exercise_status("Stopping");

    longitude = lv_label_create(ui_kinestate, NULL);
            lv_label_set_recolor(longitude, true);
            lv_obj_set_style_local_text_font(longitude, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
            lv_obj_set_x(longitude, 0);
           lv_obj_set_y(longitude, 62);
           set_longitude("18.32");

       latitude = lv_label_create(ui_kinestate, NULL);
       lv_label_set_recolor(latitude, true);
       lv_obj_set_style_local_text_font(latitude, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
       lv_obj_set_width(latitude, 200);  /// 1
       lv_obj_set_height(latitude, 150); /// 1
       lv_obj_set_x(latitude, 0);
       lv_obj_set_y(latitude, 82);
       set_latitude("1548");



       speed = lv_label_create(ui_kinestate, NULL);
           lv_label_set_recolor(speed, true);
           lv_obj_set_style_local_text_font(speed, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(speed, 200);  /// 1
           lv_obj_set_height(speed, 150); /// 1
           lv_obj_set_x(speed, 0);
           lv_obj_set_y(speed, 102);
           set_speed("19.25");

           direction = lv_label_create(ui_kinestate, NULL);
           lv_label_set_recolor(direction, true);
           lv_obj_set_style_local_text_font(direction, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(direction, 200);  /// 1
           lv_obj_set_height(direction, 150); /// 1
           lv_obj_set_x(direction, 0);
           lv_obj_set_y(direction, 122);
           set_direction("north");

           travel_time = lv_label_create(ui_kinestate, NULL);
                lv_label_set_recolor(travel_time, true);
                lv_obj_set_style_local_text_font(travel_time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
                lv_obj_set_x(travel_time, 0);
               lv_obj_set_y(travel_time, 142);
               set_travel_time("1111");

           travel_distance = lv_label_create(ui_kinestate, NULL);
           lv_label_set_recolor(travel_distance, true);
           lv_obj_set_style_local_text_font(travel_distance, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &normal_font);
           lv_obj_set_width(travel_distance, 200);  /// 1
           lv_obj_set_height(travel_distance, 150); /// 1
           lv_obj_set_x(travel_distance, 0);
           lv_obj_set_y(travel_distance, 162);
           set_travel_distance("182");

}

void show_kinestate_ui()
{
    lv_disp_load_scr(ui_kinestate);
    now_show_ui.screen = ui_kinestate;
    now_show_ui.time_minute = time_minute;
    now_show_ui.time_sketchy = time_sketchy;
}
MSH_CMD_EXPORT(show_kinestate_ui, show kinestate ui);

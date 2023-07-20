/*******************************************************************************
 * Size: 10 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef SMALL_FONT
#define SMALL_FONT 1
#endif

#if SMALL_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+002D "-" */
    0x7c, 0x0,

    /* U+002E "." */
    0x34, 0xd0,

    /* U+002F "/" */
    0x5, 0x8, 0xc, 0xc, 0x18, 0x24, 0x30, 0x30,
    0x60, 0x90, 0x40,

    /* U+003A ":" */
    0x34, 0xd0, 0x0, 0x34, 0xd0,

    /* U+0043 "C" */
    0xb, 0xd0, 0xb5, 0x83, 0x40, 0x1c, 0x0, 0x70,
    0x0, 0xd0, 0x2, 0xd7, 0x2, 0xf4,

    /* U+0045 "E" */
    0x3f, 0xd3, 0x94, 0x34, 0x3, 0xfc, 0x38, 0x3,
    0x40, 0x39, 0x43, 0xfe,

    /* U+004B "K" */
    0x34, 0x70, 0xd3, 0x43, 0x78, 0xf, 0xd0, 0x3f,
    0xc0, 0xe3, 0x83, 0x4b, 0xd, 0xe,

    /* U+0050 "P" */
    0x3f, 0xd0, 0xe6, 0xc3, 0x47, 0xd, 0x2c, 0x3f,
    0xd0, 0xe0, 0x3, 0x40, 0xd, 0x0,

    /* U+0057 "W" */
    0xb0, 0xd2, 0xec, 0x78, 0xa7, 0x2f, 0x38, 0xce,
    0xcd, 0x37, 0x37, 0xe, 0xce, 0xc2, 0xe2, 0xf0,
    0x78, 0x78,

    /* U+005F "_" */
    0xff, 0xd0,

    /* U+0061 "a" */
    0x2f, 0x42, 0x6c, 0xb, 0xc3, 0x9c, 0x76, 0xc2,
    0xec,

    /* U+0062 "b" */
    0x30, 0x3, 0x0, 0x3b, 0xc3, 0x9e, 0x30, 0xb3,
    0xb, 0x39, 0xe3, 0xb8,

    /* U+0063 "c" */
    0x1f, 0x8e, 0x57, 0x1, 0xc0, 0x39, 0x47, 0xe0,

    /* U+0064 "d" */
    0x0, 0xe0, 0xe, 0x1f, 0xe3, 0x9e, 0x70, 0xe7,
    0xe, 0x39, 0xe2, 0xfa,

    /* U+0065 "e" */
    0x1f, 0x43, 0x5c, 0x7f, 0xd7, 0x0, 0x39, 0x41,
    0xf8,

    /* U+0067 "g" */
    0x2f, 0xe7, 0x6c, 0x71, 0xc3, 0xf4, 0x34, 0x3,
    0xfe, 0x70, 0xe3, 0xf8,

    /* U+0068 "h" */
    0x30, 0x3, 0x0, 0x3b, 0xc3, 0x9e, 0x30, 0xe3,
    0xe, 0x30, 0xe3, 0xe,

    /* U+0069 "i" */
    0x30, 0x83, 0xc, 0x30, 0xc3, 0xc,

    /* U+006A "j" */
    0xc, 0x8, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd,
    0x2c, 0x78,

    /* U+006C "l" */
    0x30, 0xc3, 0xc, 0x30, 0xc3, 0x4b,

    /* U+006D "m" */
    0x37, 0xcf, 0x4e, 0x7d, 0xf3, 0xe, 0x2c, 0xc3,
    0x8b, 0x30, 0xe2, 0xcc, 0x38, 0xb0,

    /* U+006F "o" */
    0x1f, 0x83, 0x9d, 0x70, 0xe7, 0xe, 0x39, 0xd1,
    0xf8,

    /* U+0070 "p" */
    0x3b, 0xc3, 0x9e, 0x30, 0xb3, 0xb, 0x39, 0xe3,
    0xb8, 0x30, 0x3, 0x0,

    /* U+0072 "r" */
    0x37, 0x4f, 0x43, 0x40, 0xc0, 0x30, 0xc, 0x0,

    /* U+0073 "s" */
    0x2f, 0x1c, 0x43, 0xd0, 0x2d, 0x13, 0x9f, 0xc0,

    /* U+0074 "t" */
    0x10, 0xd, 0xf, 0xf0, 0xe0, 0x34, 0xd, 0x3,
    0x80, 0x7c,

    /* U+0075 "u" */
    0x70, 0xe7, 0xe, 0x70, 0xe7, 0xe, 0x3a, 0xe2,
    0xea,

    /* U+0076 "v" */
    0xb0, 0xd7, 0xc, 0x35, 0xc2, 0xa8, 0x1f, 0x0,
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 36, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 59, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 2, .adv_w = 52, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 62, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 15, .adv_w = 52, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 91, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 94, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 156, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 49, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 184, .adv_w = 50, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 154, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 225, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 79, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 67, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 102, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe, 0xf, 0x1a, 0x23, 0x25, 0x2b,
    0x30, 0x37, 0x3f, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x47, 0x48, 0x49, 0x4a, 0x4c, 0x4d, 0x4f, 0x50,
    0x52, 0x53, 0x54, 0x55, 0x56
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 87, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 29, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 0, 10, 11, 12, 0,
    13, 14, 0, 0, 0, 15, 0, 11,
    11, 16, 17, 18, 0, 19
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 3, 4, 5, 0,
    0, 0, 6, 0, 7, 0, 8, 8,
    8, 9, 0, 10, 11, 0, 0, 8,
    0, 0, 12, 13, 14, 15
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, -4, 0, -3, 0,
    0, 0, 0, 0, -7, 0, -2, 0,
    0, 6, 0, -11, 0, -10, 0, 0,
    0, 0, -2, 0, -5, -4, -2, 2,
    2, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, -6, 0, 0, 0,
    -6, -1, 0, 0, -4, 0, 0, 0,
    -6, -2, -3, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, -5,
    0, -2, -8, 0, 0, 0, -5, -2,
    0, -3, 0, 0, -2, 0, -9, -2,
    -6, -5, -23, -10, 0, 0, 0, -7,
    -4, -4, 0, 0, -2, 0, 0, 0,
    -2, -7, -3, 0, 0, 0, -2, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, -2,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, -1, -4, 0, -1, -6, 0, 0,
    0, 0, 0, -2, -5, -2, 0, 0,
    0, -2, 0, 0, 2, 0, 0, 0,
    0, -2, -2, 0, -2, 0, 0, 0,
    -2, 0, -1, 0, 0, 6, 0, 0,
    0, -3, -3, 0, 0, 8, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 0, 0, 0,
    0, -5, -14, -5, 2, 0, 0, -5,
    -2, -2, 0, 0, -1, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, -6,
    -1, 0, 1, 0, 0, -4, -3, -2,
    0, 0, -2, -4, 0, 0, -3, -10,
    -4, 0, 0, 0, -4, -1, 0, 0,
    -2, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 19,
    .right_class_cnt     = 15,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t small_font = {
#else
lv_font_t small_font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SMALL_FONT*/


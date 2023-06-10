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

#ifndef SMALL_MYFONT
#define SMALL_MYFONT 1
#endif

#if SMALL_MYFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x38, 0xe3, 0x49, 0x24, 0x3, 0x8e,

    /* U+0022 "\"" */
    0x36, 0xcd, 0xb3, 0x18, 0x81,

    /* U+0023 "#" */
    0x8, 0xc1, 0x88, 0x7f, 0xe2, 0x58, 0x25, 0x4b,
    0xfd, 0x32, 0x3, 0x30,

    /* U+0024 "$" */
    0x9, 0x1, 0xf4, 0x3a, 0x83, 0x80, 0x1f, 0x0,
    0x3c, 0x1, 0xc7, 0x6c, 0x2f, 0x0, 0x90,

    /* U+0025 "%" */
    0x3d, 0xc, 0xa, 0x71, 0x80, 0x93, 0x30, 0xa,
    0x76, 0x74, 0x2c, 0xcc, 0xc0, 0x15, 0xcd, 0x3,
    0xc, 0xc0, 0x50, 0xb8,

    /* U+0026 "&" */
    0xf, 0x40, 0x29, 0xc0, 0x2a, 0x80, 0x1e, 0x4,
    0x3f, 0x28, 0xb3, 0xf0, 0xb5, 0xf8, 0x2f, 0x5c,

    /* U+0027 "'" */
    0x34, 0xd3, 0x8,

    /* U+0028 "(" */
    0x4, 0xc, 0x28, 0x34, 0x30, 0x30, 0x30, 0x34,
    0x24, 0x1c, 0xc, 0x0,

    /* U+0029 ")" */
    0x10, 0xc3, 0x4a, 0x1c, 0x71, 0xc6, 0x28, 0xc6,
    0x0,

    /* U+002A "*" */
    0xc, 0x1b, 0x92, 0xe0, 0x9c, 0x0, 0x0,

    /* U+002B "+" */
    0x5, 0x0, 0x90, 0x9, 0xb, 0xfd, 0xa, 0x0,
    0x90,

    /* U+002C "," */
    0x24, 0xe1, 0x5c, 0x0,

    /* U+002D "-" */
    0x7c, 0x0,

    /* U+002E "." */
    0x34, 0xd0,

    /* U+002F "/" */
    0x5, 0x8, 0xc, 0xc, 0x18, 0x24, 0x30, 0x30,
    0x60, 0x90, 0x40,

    /* U+0030 "0" */
    0x1f, 0x43, 0x6c, 0x70, 0xdb, 0xd, 0xb0, 0xd7,
    0xd, 0x36, 0xc1, 0xf4,

    /* U+0031 "1" */
    0x1f, 0x2, 0xf0, 0xb, 0x0, 0xb0, 0xb, 0x0,
    0xb0, 0xb, 0x3, 0xfd,

    /* U+0032 "2" */
    0x2f, 0x6, 0x7c, 0x1, 0xc0, 0x2c, 0x3, 0x40,
    0xe0, 0x3d, 0x4b, 0xfd,

    /* U+0033 "3" */
    0x2f, 0x42, 0x6c, 0x2, 0xc0, 0xf0, 0x2, 0xc0,
    0xd, 0x66, 0xc2, 0xf4,

    /* U+0034 "4" */
    0x7, 0x80, 0xf8, 0x1e, 0x83, 0x68, 0x72, 0x8f,
    0xfe, 0x2, 0xc0, 0x28,

    /* U+0035 "5" */
    0x3f, 0xc3, 0x94, 0x30, 0x3, 0xf4, 0x12, 0xc0,
    0xd, 0x66, 0xc2, 0xf4,

    /* U+0036 "6" */
    0xf, 0x83, 0x98, 0x70, 0x7, 0xb8, 0x75, 0xd7,
    0xd, 0x39, 0xc1, 0xf4,

    /* U+0037 "7" */
    0x7f, 0xd1, 0x6c, 0x3, 0x40, 0x70, 0xa, 0x0,
    0xe0, 0xd, 0x0, 0xd0,

    /* U+0038 "8" */
    0x1f, 0x43, 0x5c, 0x34, 0xc2, 0xf8, 0x3b, 0xc7,
    0xd, 0x75, 0xd2, 0xf8,

    /* U+0039 "9" */
    0x2f, 0x7, 0x6c, 0xb0, 0xc7, 0x1d, 0x3e, 0xd0,
    0xc, 0x27, 0xc2, 0xe0,

    /* U+003A ":" */
    0x34, 0xd0, 0x0, 0x34, 0xd0,

    /* U+003B ";" */
    0x34, 0xd0, 0x0, 0x24, 0xe1, 0x5c, 0x0,

    /* U+003C "<" */
    0x0, 0x0, 0x6d, 0x7d, 0x7, 0x90, 0x7, 0xd0,
    0x5,

    /* U+003D "=" */
    0xbf, 0xe0, 0x0, 0x0, 0xb, 0xfd, 0x0, 0x0,

    /* U+003E ">" */
    0x40, 0xb, 0x90, 0x7, 0xd0, 0x6d, 0x7d, 0x4,
    0x0,

    /* U+003F "?" */
    0x2e, 0x9, 0xe0, 0x34, 0x2c, 0xc, 0x0, 0x1,
    0xc0, 0x70,

    /* U+0040 "@" */
    0x1, 0xfe, 0x0, 0xe0, 0x28, 0x28, 0x0, 0xc3,
    0xf, 0xc9, 0x63, 0x5c, 0x96, 0x32, 0x8c, 0x62,
    0xdf, 0x43, 0x0, 0x0, 0x1d, 0x4, 0x0, 0x6f,
    0x80,

    /* U+0041 "A" */
    0x3, 0xc0, 0x3, 0xe0, 0x7, 0xb0, 0xa, 0x70,
    0xd, 0x34, 0x1f, 0xf8, 0x2c, 0x2c, 0x38, 0xd,

    /* U+0042 "B" */
    0x3f, 0xd0, 0xe2, 0xc3, 0x4b, 0xf, 0xf4, 0x34,
    0xb0, 0xd0, 0xd3, 0x8b, 0xf, 0xf4,

    /* U+0043 "C" */
    0xb, 0xd0, 0xb5, 0x83, 0x40, 0x1c, 0x0, 0x70,
    0x0, 0xd0, 0x2, 0xd7, 0x2, 0xf4,

    /* U+0044 "D" */
    0x3f, 0x80, 0xe7, 0xc3, 0x43, 0x4d, 0xe, 0x34,
    0x38, 0xd0, 0xd3, 0x9f, 0xf, 0xe0,

    /* U+0045 "E" */
    0x3f, 0xd3, 0x94, 0x34, 0x3, 0xfc, 0x38, 0x3,
    0x40, 0x39, 0x43, 0xfe,

    /* U+0046 "F" */
    0x3f, 0xd3, 0x94, 0x34, 0x3, 0x40, 0x3f, 0xc3,
    0x80, 0x34, 0x3, 0x40,

    /* U+0047 "G" */
    0xb, 0xe0, 0xb5, 0xc3, 0x40, 0x1c, 0x0, 0x70,
    0xf4, 0xd0, 0xd2, 0xd7, 0x42, 0xf8,

    /* U+0048 "H" */
    0x34, 0x38, 0xd0, 0xe3, 0x43, 0x8f, 0xfe, 0x39,
    0x78, 0xd0, 0xe3, 0x43, 0x8d, 0xe,

    /* U+0049 "I" */
    0x34, 0xd3, 0x4d, 0x34, 0xd3, 0x4d,

    /* U+004A "J" */
    0x2, 0xc0, 0xb0, 0x2c, 0xb, 0x2, 0xc0, 0xb7,
    0x78, 0xb8,

    /* U+004B "K" */
    0x34, 0x70, 0xd3, 0x43, 0x78, 0xf, 0xd0, 0x3f,
    0xc0, 0xe3, 0x83, 0x4b, 0xd, 0xe,

    /* U+004C "L" */
    0x34, 0x3, 0x40, 0x34, 0x3, 0x40, 0x34, 0x3,
    0x40, 0x39, 0x43, 0xfd,

    /* U+004D "M" */
    0x38, 0xe, 0x3c, 0x2e, 0x3d, 0x3e, 0x3a, 0x3a,
    0x37, 0xaa, 0x33, 0xda, 0x31, 0xca, 0x30, 0xa,

    /* U+004E "N" */
    0x38, 0x38, 0xf0, 0xe3, 0xe3, 0x8d, 0xce, 0x36,
    0xa8, 0xd3, 0xe3, 0x4b, 0x8d, 0xe,

    /* U+004F "O" */
    0xb, 0xd0, 0x3d, 0xb4, 0x34, 0x2c, 0x70, 0x1c,
    0x70, 0x1c, 0x34, 0x2c, 0x3d, 0xb4, 0xb, 0xd0,

    /* U+0050 "P" */
    0x3f, 0xd0, 0xe6, 0xc3, 0x47, 0xd, 0x2c, 0x3f,
    0xd0, 0xe0, 0x3, 0x40, 0xd, 0x0,

    /* U+0051 "Q" */
    0xb, 0xd0, 0x3d, 0xb4, 0x34, 0x2c, 0x70, 0x1c,
    0x70, 0x1c, 0x34, 0x2c, 0x3d, 0x74, 0xb, 0xe0,
    0x1, 0xd4, 0x0, 0x7d,

    /* U+0052 "R" */
    0x3f, 0xd0, 0xe6, 0xc3, 0x47, 0xd, 0x2c, 0x3f,
    0xd0, 0xe7, 0x3, 0x4e, 0xd, 0x1d,

    /* U+0053 "S" */
    0x1f, 0x83, 0x98, 0x34, 0x2, 0xf4, 0x7, 0xd0,
    0xf, 0x75, 0xe2, 0xf8,

    /* U+0054 "T" */
    0xbf, 0xf1, 0xb5, 0xb, 0x0, 0xb0, 0xb, 0x0,
    0xb0, 0xb, 0x0, 0xb0,

    /* U+0055 "U" */
    0x34, 0x38, 0xd0, 0xe3, 0x43, 0x8d, 0xe, 0x34,
    0x38, 0xd0, 0xd2, 0xdb, 0x2, 0xf4,

    /* U+0056 "V" */
    0x38, 0x1c, 0x2c, 0x2c, 0x1c, 0x38, 0xd, 0x30,
    0xe, 0x70, 0x7, 0xa0, 0x3, 0xd0, 0x3, 0xc0,

    /* U+0057 "W" */
    0xb0, 0xd2, 0xec, 0x78, 0xa7, 0x2f, 0x38, 0xce,
    0xcd, 0x37, 0x37, 0xe, 0xce, 0xc2, 0xe2, 0xf0,
    0x78, 0x78,

    /* U+0058 "X" */
    0x70, 0xf0, 0xe3, 0x41, 0xec, 0x3, 0xd0, 0xf,
    0x40, 0xbb, 0x3, 0x4d, 0x2c, 0x3c,

    /* U+0059 "Y" */
    0x38, 0x38, 0x70, 0xc0, 0xdb, 0x2, 0xf4, 0x3,
    0xc0, 0xe, 0x0, 0x38, 0x0, 0xe0,

    /* U+005A "Z" */
    0x3f, 0xe1, 0x6d, 0x3, 0x80, 0x70, 0xe, 0x2,
    0xc0, 0x39, 0x4b, 0xfe,

    /* U+005B "[" */
    0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xd0,

    /* U+005C "\\" */
    0x90, 0x60, 0x30, 0x30, 0x24, 0x18, 0xc, 0xc,
    0x9, 0x5, 0x1,

    /* U+005D "]" */
    0x7c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1d, 0xe0,

    /* U+005E "^" */
    0x5, 0x0, 0xf0, 0x1b, 0x43, 0x58, 0x30, 0xc0,

    /* U+005F "_" */
    0xff, 0xd0,

    /* U+0060 "`" */
    0x2, 0xc2, 0x80,

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

    /* U+0066 "f" */
    0x1f, 0xe, 0xb, 0xe0, 0xe0, 0x38, 0xe, 0x3,
    0x80, 0xe0,

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

    /* U+006B "k" */
    0x30, 0x3, 0x0, 0x30, 0xd3, 0x78, 0x3f, 0x3,
    0xf4, 0x35, 0xc3, 0xe,

    /* U+006C "l" */
    0x30, 0xc3, 0xc, 0x30, 0xc3, 0x4b,

    /* U+006D "m" */
    0x37, 0xcf, 0x4e, 0x7d, 0xf3, 0xe, 0x2c, 0xc3,
    0x8b, 0x30, 0xe2, 0xcc, 0x38, 0xb0,

    /* U+006E "n" */
    0x37, 0xc3, 0x9e, 0x30, 0xe3, 0xe, 0x30, 0xe3,
    0xe,

    /* U+006F "o" */
    0x1f, 0x83, 0x9d, 0x70, 0xe7, 0xe, 0x39, 0xd1,
    0xf8,

    /* U+0070 "p" */
    0x3b, 0xc3, 0x9e, 0x30, 0xb3, 0xb, 0x39, 0xe3,
    0xb8, 0x30, 0x3, 0x0,

    /* U+0071 "q" */
    0x1f, 0xe3, 0x8e, 0x70, 0xe7, 0xe, 0x39, 0xe2,
    0xfe, 0x0, 0xe0, 0xe,

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
    0xf0,

    /* U+0077 "w" */
    0xb1, 0xc3, 0x1c, 0xb5, 0xc3, 0x3a, 0xb0, 0xed,
    0xe8, 0x2e, 0x3d, 0x7, 0x8f, 0x0,

    /* U+0078 "x" */
    0x71, 0xc3, 0xb8, 0x1f, 0x1, 0xf0, 0x37, 0x8b,
    0x1c,

    /* U+0079 "y" */
    0xb0, 0xd7, 0xc, 0x36, 0xc1, 0xf4, 0xf, 0x0,
    0xe0, 0x1d, 0x7, 0x80,

    /* U+007A "z" */
    0x7f, 0x81, 0xd0, 0xe0, 0xb0, 0x38, 0x2f, 0xf0,

    /* U+007B "{" */
    0x1c, 0x24, 0x24, 0x24, 0x34, 0xb0, 0x34, 0x24,
    0x24, 0x1d,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0x70, 0x28, 0x28, 0x24, 0x28, 0xd, 0x28, 0x24,
    0x28, 0x70,

    /* U+007E "~" */
    0x38, 0x45, 0x7c, 0x0, 0x0,

    /* U+5730 "地" */
    0x0, 0x0, 0x0, 0xc0, 0xd0, 0x1c, 0x9e, 0x87,
    0xfa, 0xfd, 0xd, 0xfd, 0xd0, 0xcd, 0xdd, 0x1f,
    0x9e, 0xc7, 0xd9, 0x90, 0x10, 0xa0, 0xa0, 0x7,
    0xfd,

    /* U+5740 "址" */
    0x0, 0x0, 0x1, 0xc0, 0x70, 0x1c, 0x7, 0xb,
    0xfa, 0x70, 0x1c, 0xa7, 0xf1, 0xca, 0x70, 0x2f,
    0xa7, 0x7, 0x4a, 0x70, 0x2, 0xff, 0xf0, 0x5,
    0x55,

    /* U+6E90 "源" */
    0x10, 0x0, 0x3, 0xbf, 0xfd, 0x3, 0x4d, 0x5,
    0x3b, 0xfc, 0x73, 0xba, 0xc0, 0x3a, 0x5c, 0x17,
    0x7f, 0xc3, 0xb5, 0xd8, 0x7a, 0xcd, 0xd5, 0x82,
    0xc0, 0x0, 0x0, 0x0,

    /* U+76EE "目" */
    0x7f, 0xff, 0x70, 0x7, 0x7f, 0xff, 0x75, 0x5b,
    0x70, 0x7, 0x7f, 0xff, 0x70, 0x7, 0x7f, 0xff,
    0x70, 0x7,

    /* U+7801 "码" */
    0x7f, 0xbf, 0xc2, 0x81, 0x18, 0x34, 0x32, 0x83,
    0xe3, 0x28, 0xb7, 0x7f, 0xe7, 0x70, 0x9, 0x37,
    0xbf, 0xd3, 0xf0, 0xc, 0x10, 0x7, 0x80, 0x0,
    0x0,

    /* U+9879 "项" */
    0x15, 0xff, 0xf7, 0xf1, 0xd0, 0xc, 0xff, 0xd0,
    0xcd, 0x8d, 0xc, 0xdd, 0xd1, 0xed, 0xdd, 0x79,
    0x9c, 0x80, 0x7, 0xac, 0x1, 0xd0, 0x60, 0x0,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 36, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 59, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 11, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 94, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 38, .adv_w = 154, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 118, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 52, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 77, .adv_w = 60, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 89, .adv_w = 60, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 98, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 105, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 114, .adv_w = 52, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 118, .adv_w = 59, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 120, .adv_w = 52, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 62, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 133, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 52, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 52, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 265, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 274, .adv_w = 94, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 282, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 291, .adv_w = 82, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 161, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 326, .adv_w = 103, .box_w = 8, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 53, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 91, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 123, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 558, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 99, .box_w = 8, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 100, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 93, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 60, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 692, .adv_w = 62, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 703, .adv_w = 60, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 711, .adv_w = 94, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 719, .adv_w = 91, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 721, .adv_w = 100, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 724, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 60, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 796, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 49, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 824, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 50, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 842, .adv_w = 154, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 103, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 874, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 886, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 898, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 906, .adv_w = 79, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 67, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 102, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 138, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 965, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 977, .adv_w = 82, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 985, .adv_w = 60, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 995, .adv_w = 47, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 998, .adv_w = 60, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1008, .adv_w = 94, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1013, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1038, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1063, .adv_w = 160, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1091, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1109, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1134, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x10, 0x1760, 0x1fbe, 0x20d1, 0x4149
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 22320, .range_length = 16714, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 6, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 0, 0, 0, 3, 4, 3,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 6, 6, 0, 0, 0,
    0, 0, 7, 8, 9, 10, 11, 12,
    13, 0, 0, 14, 15, 16, 0, 0,
    10, 17, 10, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 2, 27, 0, 0,
    0, 0, 28, 29, 30, 0, 31, 32,
    33, 34, 0, 0, 35, 36, 34, 34,
    29, 29, 37, 38, 39, 40, 37, 41,
    42, 43, 44, 45, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 0, 0, 0,
    2, 0, 3, 4, 0, 5, 6, 7,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 10, 0, 0, 0,
    11, 0, 12, 0, 13, 0, 0, 0,
    13, 0, 0, 14, 0, 0, 0, 0,
    13, 0, 13, 0, 15, 16, 17, 18,
    19, 20, 21, 22, 0, 23, 3, 0,
    0, 0, 24, 0, 25, 25, 25, 26,
    27, 0, 28, 29, 0, 0, 30, 30,
    25, 30, 25, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, -23, 0, -23, 0,
    0, 0, 0, -12, 0, -20, -2, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 15, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -22, 0, -29,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -18, -5, -13, -7, 0,
    -19, 0, 0, 0, -2, 0, 0, 0,
    6, 0, 0, -11, 0, -10, -6, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -4, -10, 0, -4, -2, -6, -13, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -3, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, -2, -15, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -4, 0, -2, 2, 2, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -12, 0, -16,
    0, 0, 0, 0, 0, 0, -6, 0,
    -2, 0, 0, -12, -2, -3, 0, -1,
    -3, -1, -7, 3, 0, -2, 0, 0,
    0, 0, 3, -3, 0, -3, -1, -1,
    -3, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -3, -5, 0, -2, -1, -1, -3, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -3, -2, -2, -3, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, -6, -2, -5, -3,
    -3, -1, -1, -1, -3, -2, 0, 0,
    0, 0, -4, 0, 0, 0, 0, -6,
    -2, -3, -2, 0, -3, 0, 0, 0,
    0, -5, 0, 0, 0, -3, 0, 0,
    0, -2, 0, -9, 0, -5, 0, -2,
    0, -4, -4, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, -5, 0, -2, 0, -7,
    -2, 0, 0, 0, 0, 0, -16, 0,
    -16, -10, 0, 0, 0, -7, -2, -24,
    -5, 0, 0, -1, -1, -5, -2, -5,
    0, -7, -3, 0, -5, 0, 0, -4,
    -5, -2, -3, -6, -4, -6, -4, -8,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, -4,
    0, -3, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, -5, 0, 0, 0,
    0, 0, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -7,
    0, -8, 0, 0, 0, 0, -3, -2,
    -5, 0, -3, -4, -3, -3, -2, 0,
    -4, 0, 0, 0, -3, 0, 0, 0,
    -2, 0, 0, -9, -2, -6, -4, -4,
    -6, -3, 0, -23, 0, -30, 0, -8,
    0, 0, 0, 0, -8, -1, -6, 0,
    -5, -22, -6, -14, -11, 0, -15, 0,
    -15, 0, -2, -3, -1, 0, 0, 0,
    0, -5, -2, -9, -7, 0, -9, 0,
    0, 0, 0, 0, -23, -5, -23, -10,
    0, 0, 0, -9, 0, -26, -2, -3,
    0, 0, 0, -5, -2, -11, 0, -7,
    -4, 0, -4, 0, 0, 0, -2, 0,
    0, 0, 0, -3, 0, -4, 0, 0,
    0, -2, 0, -6, 0, 0, 0, 0,
    0, -1, 0, -3, -3, -3, 0, -1,
    0, -1, -2, -2, 0, -1, -2, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -3, 0, 0, 0, -2,
    0, 3, 0, 0, 0, 0, 0, 0,
    0, -3, -3, -4, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, -21, -12,
    -21, -13, -4, -4, 0, -7, -5, -22,
    -5, 0, 0, 0, 0, -4, -3, -8,
    0, -12, -13, -3, -12, 0, 0, -8,
    -11, -3, -8, -5, -5, -5, -5, -12,
    0, 0, 0, 0, -4, 0, -4, -4,
    0, 0, 0, -2, 0, -10, -2, 0,
    0, -1, 0, -2, -3, 0, 0, -1,
    0, 0, -2, 0, 0, 0, -1, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, -13, -4, -13, -6, 0, 0,
    0, -3, -2, -12, -2, 0, -2, 2,
    0, 0, 0, -4, 0, -6, -3, 0,
    -4, 0, 0, -4, -3, 0, -5, -2,
    -2, -3, -2, -4, 0, 0, 0, 0,
    -7, -2, -7, -3, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -2, 0, -2, 0, -6,
    0, 0, 0, 0, 0, -1, -4, -2,
    -3, -4, -2, 0, 0, 0, 0, 0,
    0, -2, -3, -4, 0, 0, 0, 0,
    0, -4, -2, -4, -3, -2, -4, -3,
    0, 0, 0, 0, -19, -13, -19, -10,
    -6, -6, -3, -3, -3, -18, -3, -3,
    -2, 0, 0, 0, 0, -4, 0, -13,
    -9, 0, -11, 0, 0, -7, -9, -8,
    -7, -3, -5, -7, -3, -10, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, -4, -5, -5, 0, -2, 0,
    0, 0, -3, -2, 0, -2, -3, -4,
    -2, 0, 0, 0, 0, -3, -3, -2,
    -2, -5, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -13, -4, -8, -4, 0,
    -12, 0, 0, 0, 0, 0, 5, 0,
    12, 0, 0, 0, 0, -4, -2, 0,
    1, 0, 0, 0, 0, -8, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, -5, 0, -4, -1, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -2, -2, 0, -2, 0,
    0, 0, -5, 0, 0, 0, 0, -11,
    0, -4, 0, -1, -10, 0, -6, -2,
    0, -1, 0, 0, 0, 0, -1, -4,
    0, -1, -1, -4, -1, -2, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -3,
    0, 0, -5, 0, 0, -2, -5, 0,
    -2, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 2, 0, 0, 0, 0, -3, 0,
    0, -4, -4, -5, 0, -4, -2, 0,
    -6, 0, -6, -2, 0, -1, -2, 0,
    0, 0, 0, -2, 0, -1, -1, -3,
    -1, -1, 1, 7, 7, 0, -11, -3,
    -11, -1, 0, 0, 4, 0, 0, 0,
    0, 8, 0, 11, 8, 5, 9, 0,
    7, -4, -2, 0, -2, 0, -2, 0,
    -1, 0, 0, 1, 0, -1, 0, -3,
    0, 0, 1, -5, 0, 0, 0, 6,
    0, 0, -8, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -3, 0, 0, -3,
    -3, 0, 0, 0, 8, 0, 0, 0,
    0, -1, -1, 0, 1, -3, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, -5, 0, -2,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    1, -13, 1, 0, 1, 1, -5, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    -3, 0, 0, -2, -5, 0, -2, 0,
    -2, 0, 0, -6, -3, 0, 0, -3,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -3, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -14, -5, -14, -5, 2, 2,
    0, -3, 0, -12, 0, 0, 0, 0,
    0, 0, 0, -2, 1, -5, -2, 0,
    -2, 0, 0, 0, -1, 0, 0, 2,
    2, 0, 2, -1, 0, 0, 0, -6,
    0, 2, 0, 0, 0, 0, -4, 0,
    0, 0, 0, -5, 0, -2, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -6,
    -1, 0, 1, 1, -6, 0, 0, 0,
    0, -3, 0, 0, 0, 0, -1, 0,
    0, -4, -3, 0, -2, 0, 0, 0,
    -2, -4, 0, 0, 0, -2, 0, 0,
    0, 0, 0, -2, -10, -3, -10, -4,
    0, 0, 0, -2, 0, -7, 0, -4,
    0, -2, 0, 0, -3, -2, 0, -4,
    -1, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, -2, -13, 0, -13, -1, 0, 0,
    0, -1, 0, -5, 0, -5, 0, -2,
    0, -3, -5, 0, 0, -2, -1, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, 0, 0, -4,
    3, -3, -3, 0, 0, 3, 0, 0,
    -2, 0, -1, -5, 0, -3, 0, -2,
    -7, 0, 0, -2, -4, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, -10, 0,
    -10, -1, 0, 0, 0, 0, 0, -7,
    0, -4, 0, -1, 0, -1, -3, 0,
    0, -4, -1, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, -3, 0, -5,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, -4, 0, 0, -3,
    -2, 0, 0, 0, 0, 0, 0, 0,
    -2, -1, 0, 0, -1, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 45,
    .right_class_cnt     = 38,
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
    .cmap_num = 2,
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
const lv_font_t small_myfont = {
#else
lv_font_t small_myfont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
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



#endif /*#if SMALL_MYFONT*/


/**
  ******************************************************************************
  * @file    fire.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Jul 12 17:09:05 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "fire.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_fire
 
#undef AI_FIRE_MODEL_SIGNATURE
#define AI_FIRE_MODEL_SIGNATURE     "94bfc7ebc380f4d03705b010797421c2"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Jul 12 17:09:05 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_FIRE_N_BATCHES
#define AI_FIRE_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_5_scratch1_array;   /* Array #0 */
AI_STATIC ai_array conv2d_5_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv2d_3_scratch1_array;   /* Array #2 */
AI_STATIC ai_array conv2d_3_scratch0_array;   /* Array #3 */
AI_STATIC ai_array conv2d_1_scratch1_array;   /* Array #4 */
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #5 */
AI_STATIC ai_array dense_10_bias_array;   /* Array #6 */
AI_STATIC ai_array dense_10_weights_array;   /* Array #7 */
AI_STATIC ai_array dense_9_bias_array;   /* Array #8 */
AI_STATIC ai_array dense_9_weights_array;   /* Array #9 */
AI_STATIC ai_array dense_8_bias_array;   /* Array #10 */
AI_STATIC ai_array dense_8_weights_array;   /* Array #11 */
AI_STATIC ai_array conv2d_5_bias_array;   /* Array #12 */
AI_STATIC ai_array conv2d_5_weights_array;   /* Array #13 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #14 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #15 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #16 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #17 */
AI_STATIC ai_array conv2d_input_output_array;   /* Array #18 */
AI_STATIC ai_array conversion_0_output_array;   /* Array #19 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #20 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #21 */
AI_STATIC ai_array conv2d_5_output_array;   /* Array #22 */
AI_STATIC ai_array dense_8_output_array;   /* Array #23 */
AI_STATIC ai_array dense_9_output_array;   /* Array #24 */
AI_STATIC ai_array dense_10_output_array;   /* Array #25 */
AI_STATIC ai_array dense_10_fmt_output_array;   /* Array #26 */
AI_STATIC ai_array nl_11_output_array;   /* Array #27 */
AI_STATIC ai_array nl_11_fmt_output_array;   /* Array #28 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_5_scratch1;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_5_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_3_scratch1;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_3_scratch0;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_1_scratch1;   /* Tensor #4 */
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #5 */
AI_STATIC ai_tensor dense_10_bias;   /* Tensor #6 */
AI_STATIC ai_tensor dense_10_weights;   /* Tensor #7 */
AI_STATIC ai_tensor dense_9_bias;   /* Tensor #8 */
AI_STATIC ai_tensor dense_9_weights;   /* Tensor #9 */
AI_STATIC ai_tensor dense_8_bias;   /* Tensor #10 */
AI_STATIC ai_tensor dense_8_weights;   /* Tensor #11 */
AI_STATIC ai_tensor conv2d_5_bias;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_5_weights;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_input_output;   /* Tensor #18 */
AI_STATIC ai_tensor conversion_0_output;   /* Tensor #19 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #20 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #21 */
AI_STATIC ai_tensor conv2d_5_output;   /* Tensor #22 */
AI_STATIC ai_tensor conv2d_5_output0;   /* Tensor #23 */
AI_STATIC ai_tensor dense_8_output;   /* Tensor #24 */
AI_STATIC ai_tensor dense_9_output;   /* Tensor #25 */
AI_STATIC ai_tensor dense_10_output;   /* Tensor #26 */
AI_STATIC ai_tensor dense_10_fmt_output;   /* Tensor #27 */
AI_STATIC ai_tensor nl_11_output;   /* Tensor #28 */
AI_STATIC ai_tensor nl_11_fmt_output;   /* Tensor #29 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conversion_0_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain conv2d_5_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_8_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_9_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_10_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain dense_10_fmt_chain;   /* Chain #7 */
AI_STATIC_CONST ai_tensor_chain nl_11_chain;   /* Chain #8 */
AI_STATIC_CONST ai_tensor_chain nl_11_fmt_chain;   /* Chain #9 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_nl conversion_0_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_3_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_5_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_8_layer; /* Layer #4 */
AI_STATIC ai_layer_dense dense_9_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_10_layer; /* Layer #6 */
AI_STATIC ai_layer_nl dense_10_fmt_layer; /* Layer #7 */
AI_STATIC ai_layer_nl nl_11_layer; /* Layer #8 */
AI_STATIC ai_layer_nl nl_11_fmt_layer; /* Layer #9 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1536, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7168, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1856, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1984, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1196, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 2, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 128, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32768, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 256, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 589824, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 18432, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4608, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 432, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_input_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 12288, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12288, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 15376, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6272, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2304, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_fmt_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  nl_11_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  nl_11_fmt_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.025017669424414635f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008345992304384708f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004633603151887655f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0003961397451348603f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0026359420735388994f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00037432118551805615f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0046121892519295216f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0001451573334634304f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005802192725241184f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(3.60687990905717e-05f, 1.574822272232268e-05f, 2.7067490009358153e-05f, 3.224518877686933e-05f, 2.8792594093829393e-05f, 1.964554758160375e-05f, 2.8559763450175524e-05f, 2.8805316105717793e-05f, 3.5419816413195804e-05f, 3.1075687729753554e-05f, 1.0309005119779613e-05f, 1.462078853364801e-05f, 2.7223049983149394e-05f, 3.267345164204016e-05f, 3.922616087947972e-05f, 3.6625882785301656e-05f, 1.6358733773813583e-05f, 2.2193587938090786e-05f, 2.660104291862808e-05f, 3.297662624390796e-05f, 3.690067387651652e-05f, 3.183583976351656e-05f, 9.747488547873218e-06f, 3.274250775575638e-05f, 3.1580013455823064e-05f, 3.0183746275724843e-05f, 4.076398181496188e-05f, 2.61549557762919e-05f, 3.413828744669445e-05f, 3.0490362405544147e-05f, 1.6394556951127015e-05f, 2.909199429268483e-05f, 2.4802959160297178e-05f, 2.9085742426104844e-05f, 3.6980065488023683e-05f, 3.546221705619246e-05f, 3.609087798395194e-05f, 1.1323011676722672e-05f, 2.479811701050494e-05f, 3.064377960981801e-05f, 3.61449783667922e-05f, 3.284026388428174e-05f, 2.5254797947127372e-05f, 2.8170696168672293e-05f, 3.516507422318682e-05f, 2.840606430254411e-05f, 1.9899598555639386e-05f, 3.610306157497689e-05f, 2.3811655410099775e-05f, 3.6364894185680896e-05f, 3.5556902730604634e-05f, 4.000169792561792e-05f, 2.7160944227944128e-05f, 3.21239058393985e-05f, 3.173240475007333e-05f, 3.740208921954036e-05f, 3.728398951352574e-05f, 3.3365260605933145e-05f, 3.707225187099539e-05f, 3.730441676452756e-05f, 2.5746741812326945e-05f, 3.028526043635793e-05f, 2.3817699911887757e-05f, 8.818309652269818e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0043216911144554615f, 0.0018869203049689531f, 0.003243172075599432f, 0.0038635535165667534f, 0.003449870739132166f, 0.0023538898676633835f, 0.0034219734370708466f, 0.003451395081356168f, 0.004243931267410517f, 0.003723426256328821f, 0.0012352042831480503f, 0.0017518334789201617f, 0.003261811099946499f, 0.00391486706212163f, 0.004699999466538429f, 0.00438843946903944f, 0.0019600705709308386f, 0.002659191144630313f, 0.003187283407896757f, 0.003951192833483219f, 0.004421364516019821f, 0.003814506344497204f, 0.0011679244926199317f, 0.003923141397535801f, 0.003783853491768241f, 0.0036165558267384768f, 0.0048842583782970905f, 0.003133834106847644f, 0.004090380854904652f, 0.003653293941169977f, 0.0019643628038465977f, 0.003485744120553136f, 0.0029718405567109585f, 0.0034849951043725014f, 0.004430877044796944f, 0.004249011632055044f, 0.004324336536228657f, 0.0013567004352807999f, 0.0029712605755776167f, 0.003671676153317094f, 0.0043308185413479805f, 0.0039348541758954525f, 0.003025979036465287f, 0.0033753560855984688f, 0.004213408567011356f, 0.0034035574644804f, 0.0023843299131840467f, 0.0043257963843643665f, 0.002853064564988017f, 0.004357168450951576f, 0.004260356537997723f, 0.004792923107743263f, 0.0032543695997446775f, 0.0038490216247737408f, 0.0038021127693355083f, 0.004481443203985691f, 0.0044672926887869835f, 0.003997758496552706f, 0.004441922530531883f, 0.004469740204513073f, 0.0030849226750433445f, 0.003628718899562955f, 0.0028537889011204243f, 0.0010565920965746045f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(2.578665043984074e-05f, 1.7971518900594674e-05f, 2.3442076781066135e-05f, 1.5578953025396913e-05f, 1.721731314319186e-05f, 2.7725283871404827e-05f, 2.3191978471004404e-05f, 2.420080272713676e-05f, 2.026600850513205e-05f, 1.694976890576072e-05f, 2.1307607312337495e-05f, 2.184984987252392e-05f, 2.1477104382938705e-05f, 3.49487345374655e-05f, 2.059263533737976e-05f, 2.1882413420826197e-05f, 1.4907085642335005e-05f, 1.477118712500669e-05f, 2.2832151444163173e-05f, 1.607421836524736e-05f, 2.8588110581040382e-05f, 2.2187919967109337e-05f, 1.9974433598690666e-05f, 1.7401052900822833e-05f, 1.5429684935952537e-05f, 1.8368413293501362e-05f, 1.9396939023863524e-05f, 1.9222132323193364e-05f, 2.094780938932672e-05f, 1.4298490896180738e-05f, 2.3565697119920515e-05f, 3.96265386370942e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005565139930695295f, 0.003878519171848893f, 0.005059146322309971f, 0.0033621680922806263f, 0.003715750528499484f, 0.005983525887131691f, 0.005005171522498131f, 0.00522289052605629f, 0.004373704083263874f, 0.0036580106243491173f, 0.0045984964817762375f, 0.0047155204229056835f, 0.004635076504200697f, 0.007542452774941921f, 0.004444194957613945f, 0.004722548183053732f, 0.003217169316485524f, 0.003187840338796377f, 0.004927515517920256f, 0.003469053888693452f, 0.006169736385345459f, 0.004788480699062347f, 0.004310777876526117f, 0.0037554041482508183f, 0.0033299538772553205f, 0.003964175004512072f, 0.0041861459612846375f, 0.004148419946432114f, 0.004520846530795097f, 0.003085825592279434f, 0.005085825454443693f, 0.00855199247598648f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(7.185173217294505e-06f, 1.1362453733454458e-05f, 1.0740299330791458e-05f, 1.3996595953358337e-05f, 1.1913640264538117e-05f, 7.173473477450898e-06f, 8.903331945475657e-06f, 9.81969333224697e-06f, 9.312178917753045e-06f, 9.759086424310226e-06f, 9.169280019705184e-06f, 9.645819773140829e-06f, 8.975559467216954e-06f, 8.301650268549565e-06f, 1.3451836821332108e-05f, 8.99798033060506e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.001832219073548913f, 0.002897425554692745f, 0.0027387761510908604f, 0.0035691317170858383f, 0.003037978196516633f, 0.0018292355816811323f, 0.002270349534228444f, 0.002504021627828479f, 0.0023746055085211992f, 0.0024885667953640223f, 0.0023381663486361504f, 0.002459683921188116f, 0.0022887676022946835f, 0.0021169206593185663f, 0.0034302182029932737f, 0.0022944847587496042f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_input_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_UINTQ_ZP(0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004633603151887655f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008345992304384708f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.025017669424414635f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08115911483764648f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.15028393268585205f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.3290609121322632f),
    AI_PACK_INTQ_ZP(-11)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_11_fmt_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_UINTQ_ZP(0)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 12, 2), AI_STRIDE_INIT(4, 1, 1, 64, 768),
  1, &conv2d_5_scratch1_array, &conv2d_5_scratch1_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7168, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7168, 7168),
  1, &conv2d_5_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 29, 2), AI_STRIDE_INIT(4, 1, 1, 32, 928),
  1, &conv2d_3_scratch1_array, &conv2d_3_scratch1_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 6144, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6144, 6144),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 62, 2), AI_STRIDE_INIT(4, 1, 1, 16, 992),
  1, &conv2d_1_scratch1_array, &conv2d_1_scratch1_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1196, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1196, 1196),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_10_bias_array, &dense_10_bias_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 128, 2, 1, 1), AI_STRIDE_INIT(4, 1, 128, 256, 256),
  1, &dense_10_weights_array, &dense_10_weights_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &dense_9_bias_array, &dense_9_bias_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 256, 128, 1, 1), AI_STRIDE_INIT(4, 1, 256, 32768, 32768),
  1, &dense_9_weights_array, &dense_9_weights_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &dense_8_bias_array, &dense_8_bias_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 2304, 256, 1, 1), AI_STRIDE_INIT(4, 1, 2304, 589824, 589824),
  1, &dense_8_weights_array, &dense_8_weights_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_5_bias_array, &conv2d_5_bias_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 1, 32, 96, 288),
  1, &conv2d_5_weights_array, &conv2d_5_weights_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_3_bias_array, &conv2d_3_bias_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 1, 16, 48, 144),
  1, &conv2d_3_weights_array, &conv2d_3_weights_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_1_bias_array, &conv2d_1_bias_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 16), AI_STRIDE_INIT(4, 1, 3, 9, 27),
  1, &conv2d_1_weights_array, &conv2d_1_weights_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_input_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conv2d_input_output_array, &conv2d_input_output_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conversion_0_output_array, &conversion_0_output_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 31, 31), AI_STRIDE_INIT(4, 1, 1, 16, 496),
  1, &conv2d_1_output_array, &conv2d_1_output_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 14, 14), AI_STRIDE_INIT(4, 1, 1, 32, 448),
  1, &conv2d_3_output_array, &conv2d_3_output_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 6, 6), AI_STRIDE_INIT(4, 1, 1, 64, 384),
  1, &conv2d_5_output_array, &conv2d_5_output_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2304, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2304, 2304),
  1, &conv2d_5_output_array, &conv2d_5_output_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 1, 1, 256, 256),
  1, &dense_8_output_array, &dense_8_output_intq)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 1, 1, 128, 128),
  1, &dense_9_output_array, &dense_9_output_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &dense_10_output_array, &dense_10_output_intq)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_10_fmt_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  nl_11_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &nl_11_output_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  nl_11_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &nl_11_fmt_output_array, &nl_11_fmt_output_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE,
  nl, node_convert_integer,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conversion_0_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_scratch0, &conv2d_1_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, &conv2d_3_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_5_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_scratch0, &conv2d_5_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_5_layer, 5,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &dense_8_layer, AI_STATIC,
  .tensors = &conv2d_5_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_8_weights, &dense_8_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_8_layer, 8,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_9_layer, AI_STATIC,
  .tensors = &dense_8_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_9_weights, &dense_9_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_9_layer, 9,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_10_layer, AI_STATIC,
  .tensors = &dense_9_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_10_weights, &dense_10_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_10_layer, 10,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_10_fmt_layer, AI_STATIC,
  .tensors = &dense_10_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_10_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_10_fmt_layer, 10,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_11_layer, AI_STATIC,
  .tensors = &dense_10_fmt_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_fmt_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_11_layer, 11,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &nl_11_fmt_layer, AI_STATIC,
  .tensors = &nl_11_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_11_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_11_fmt_layer, 11,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_11_fmt_layer, AI_STATIC,
  .tensors = &nl_11_fmt_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 648312, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 23856, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FIRE_IN_NUM, &conv2d_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_FIRE_OUT_NUM, &nl_11_fmt_output),
  &conversion_0_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool fire_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_FIRE_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_5_scratch1_array.data = AI_PTR(activations + 13440);
    conv2d_5_scratch1_array.data_start = AI_PTR(activations + 13440);
    conv2d_5_scratch0_array.data = AI_PTR(activations + 6272);
    conv2d_5_scratch0_array.data_start = AI_PTR(activations + 6272);
    conv2d_3_scratch1_array.data = AI_PTR(activations + 22000);
    conv2d_3_scratch1_array.data_start = AI_PTR(activations + 22000);
    conv2d_3_scratch0_array.data = AI_PTR(activations + 15856);
    conv2d_3_scratch0_array.data_start = AI_PTR(activations + 15856);
    conv2d_1_scratch1_array.data = AI_PTR(activations + 17564);
    conv2d_1_scratch1_array.data_start = AI_PTR(activations + 17564);
    conv2d_1_scratch0_array.data = AI_PTR(activations + 16368);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 16368);
    conv2d_input_output_array.data = AI_PTR(NULL);
    conv2d_input_output_array.data_start = AI_PTR(NULL);
    conversion_0_output_array.data = AI_PTR(activations + 4080);
    conversion_0_output_array.data_start = AI_PTR(activations + 4080);
    conv2d_1_output_array.data = AI_PTR(activations + 480);
    conv2d_1_output_array.data_start = AI_PTR(activations + 480);
    conv2d_3_output_array.data = AI_PTR(activations + 0);
    conv2d_3_output_array.data_start = AI_PTR(activations + 0);
    conv2d_5_output_array.data = AI_PTR(activations + 14976);
    conv2d_5_output_array.data_start = AI_PTR(activations + 14976);
    dense_8_output_array.data = AI_PTR(activations + 0);
    dense_8_output_array.data_start = AI_PTR(activations + 0);
    dense_9_output_array.data = AI_PTR(activations + 256);
    dense_9_output_array.data_start = AI_PTR(activations + 256);
    dense_10_output_array.data = AI_PTR(activations + 0);
    dense_10_output_array.data_start = AI_PTR(activations + 0);
    dense_10_fmt_output_array.data = AI_PTR(activations + 4);
    dense_10_fmt_output_array.data_start = AI_PTR(activations + 4);
    nl_11_output_array.data = AI_PTR(activations + 12);
    nl_11_output_array.data_start = AI_PTR(activations + 12);
    nl_11_fmt_output_array.data = AI_PTR(NULL);
    nl_11_fmt_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool fire_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_10_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_10_bias_array.data = AI_PTR(weights + 648304);
    dense_10_bias_array.data_start = AI_PTR(weights + 648304);
    dense_10_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_10_weights_array.data = AI_PTR(weights + 648048);
    dense_10_weights_array.data_start = AI_PTR(weights + 648048);
    dense_9_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_9_bias_array.data = AI_PTR(weights + 647536);
    dense_9_bias_array.data_start = AI_PTR(weights + 647536);
    dense_9_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_9_weights_array.data = AI_PTR(weights + 614768);
    dense_9_weights_array.data_start = AI_PTR(weights + 614768);
    dense_8_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_8_bias_array.data = AI_PTR(weights + 613744);
    dense_8_bias_array.data_start = AI_PTR(weights + 613744);
    dense_8_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_8_weights_array.data = AI_PTR(weights + 23920);
    dense_8_weights_array.data_start = AI_PTR(weights + 23920);
    conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_bias_array.data = AI_PTR(weights + 23664);
    conv2d_5_bias_array.data_start = AI_PTR(weights + 23664);
    conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_weights_array.data = AI_PTR(weights + 5232);
    conv2d_5_weights_array.data_start = AI_PTR(weights + 5232);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 5104);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 5104);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 496);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 496);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 432);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 432);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 0);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_fire_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_FIRE_MODEL_NAME,
      .model_signature   = AI_FIRE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 8933526,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_fire_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_fire_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_fire_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_fire_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= fire_configure_weights(net_ctx, &params->params);
  ok &= fire_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_fire_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_fire_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_FIRE_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME


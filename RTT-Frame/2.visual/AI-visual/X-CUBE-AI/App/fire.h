/**
  ******************************************************************************
  * @file    fire.h
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

#ifndef __AI_FIRE_H__
#define __AI_FIRE_H__
#pragma once

#include "ai_platform.h"
#include "ai_platform_interface.h"

#define AI_FIRE_MODEL_NAME          "fire"

#define AI_FIRE_ACTIVATIONS_ALIGNMENT   (4)

#define AI_FIRE_IN_NUM       (1)
#define AI_FIRE_IN { \
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8, 64, 64, 3, 1, NULL), \
}
#define AI_FIRE_IN_SIZE { \
  (64 * 64 * 3), \
}
#define AI_FIRE_IN_1_SIZE  (64 * 64 * 3)
#define AI_FIRE_IN_1_SIZE_BYTES  ((64 * 64 * 3) * 1)





#define AI_FIRE_OUT_NUM      (1)
#define AI_FIRE_OUT { \
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8, 1, 1, 2, 1, NULL), \
}
#define AI_FIRE_OUT_SIZE { \
  (1 * 1 * 2), \
}
#define AI_FIRE_OUT_1_SIZE  (1 * 1 * 2)
#define AI_FIRE_OUT_1_SIZE_BYTES  ((1 * 1 * 2) * 1)

#define AI_FIRE_N_NODES (10)

AI_API_DECLARE_BEGIN

/*!
 * @defgroup fire
 * @brief Public neural network APIs
 * @details This is the header for the network public APIs declarations
 * for interfacing a generated network model.
 * @details The public neural network APIs hide the structure of the network
 * and offer a set of interfaces to create, initialize, query, configure, 
 * run and destroy a network instance.
 * To handle this, an opaque handler to the network context is provided 
 * on creation.
 * The APIs are meant as stadard interfaces for the calling code; depending on
 * the supported platforms and the models, different implementations could be
 * available.
 */

/******************************************************************************/
/*! Public API Functions Declarations */

/*!
 * @brief Get network library info as a datastruct.
 * @ingroup fire
 * @param[out] report a pointer to the report struct where to
 * store network info. See @ref ai_network_report struct for details
 * @return a boolean reporting the exit status of the API
 */
AI_API_ENTRY
ai_bool ai_fire_get_info(
  ai_handle network, ai_network_report* report);

/*!
 * @brief Get first network error code.
 * @ingroup fire
 * @details Get an error code related to the 1st error generated during
 * network processing. The error code is structure containing an 
 * error type indicating the type of error with an associated error code
 * Note: after this call the error code is internally reset to AI_ERROR_NONE
 * @param network an opaque handle to the network context
 * @return an error type/code pair indicating both the error type and code
 * see @ref ai_error for struct definition
 */
AI_API_ENTRY
ai_error ai_fire_get_error(ai_handle network);

/*!
 * @brief Create a neural network.
 * @ingroup fire
 * @details Instantiate a network and returns an object to handle it;
 * @param network an opaque handle to the network context
 * @param network_config a pointer to the network configuration info coded as a 
 * buffer
 * @return an error code reporting the status of the API on exit
 */
AI_API_ENTRY
ai_error ai_fire_create(
  ai_handle* network, const ai_buffer* network_config);

/*!
 * @brief Destroy a neural network and frees the allocated memory.
 * @ingroup fire
 * @details Destroys the network and frees its memory. The network handle is returned;
 * if the handle is not NULL, the unloading has not been successful.
 * @param network an opaque handle to the network context
 * @return an object handle : AI_HANDLE_NULL if network was destroyed
 * correctly. The same input network handle if destroy failed.
 */
AI_API_ENTRY
ai_handle ai_fire_destroy(ai_handle network);

/*!
 * @brief Initialize the data structures of the network.
 * @ingroup fire
 * @details This API initialized the network after a successfull
 * @ref ai_fire_create. Both the activations memory buffer 
 * and params (i.e. weights) need to be provided by caller application
 * 
 * @param network an opaque handle to the network context
 * @param params the parameters of the network (required). 
 * see @ref ai_network_params struct for details
 * @return true if the network was correctly initialized, false otherwise
 * in case of error the error type could be queried by 
 * using @ref ai_fire_get_error
 */
AI_API_ENTRY
ai_bool ai_fire_init(
  ai_handle network, const ai_network_params* params);


/*!
 * @brief Run the network and return the output
 * @ingroup fire
 *
 * @details Runs the network on the inputs and returns the corresponding output.
 * The size of the input and output buffers is stored in this
 * header generated by the code generation tool. See AI_FIRE_*
 * defines into file @ref fire.h for all network sizes defines
 *
 * @param network an opaque handle to the network context
 * @param[in] input buffer with the input data
 * @param[out] output buffer with the output data
 * @return the number of input batches processed (default 1) or <= 0 if it fails
 * in case of error the error type could be queried by 
 * using @ref ai_fire_get_error
 */
AI_API_ENTRY
ai_i32 ai_fire_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output);

/*!
 * @brief Runs the network on the inputs.
 * @ingroup fire
 *
 * @details Differently from @ref ai_network_run, no output is returned, e.g. for
 * temporal models with a fixed step size.
 *
 * @param network the network to be run
 * @param[in] input buffer with the input data
 * @return the number of input batches processed (usually 1) or <= 0 if it fails
 * in case of error the error type could be queried by 
 * using @ref ai_fire_get_error
 */
AI_API_ENTRY
ai_i32 ai_fire_forward(
  ai_handle network, const ai_buffer* input);

AI_API_DECLARE_END

#endif /*__AI_FIRE_H__*/

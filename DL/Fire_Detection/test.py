from paddle.fluid.contrib import quantize

with fluid.dygraph.guard():
    # Load the trained model
    model_dict, _ = fluid.load_dygraph("./fire_detection_model")

    # Quantize the model to INT8
    place = fluid.CPUPlace()
    quant_program = fluid.Program()
    startup_program = fluid.Program()
    with fluid.program_guard(quant_program, startup_program):
        input_clip_tensor = fluid.data(name="input_clip", shape=[None, 3, 224, 224], dtype='float32')
        model = FireDetectionModel()
        out = model(input_clip_tensor)
    quantize.quantize(quant_program, place, quantize_to=int8, save_quantized_model_path="./fire_detection_model_int8", \
                      input_quantize_type=InputType.FP32, weight_quantize_type=WeightType.INT8, activation_quantize_type=ActivationType.INT8, \
                      bias_quantize_type=BiasType.INT32, optimize_mode=OptimizeMode.LITE_FP16_ALGO_FOR_INT8, \
                      save_combined_model=False, model_filename=None)

    # Save the quantized model
    fluid.save_dygraph(model.state_dict(), "./fire_detection_model_int8/quantized_model")


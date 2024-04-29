CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m4)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "D:/compile/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_ASM_COMPILER "D:/compile/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -Wall -O0 -gdwarf-2 -g")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "D:/compile/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-g++.exe")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -Wall -O0 -gdwarf-2 -g")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "D:/compile/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe")
SET(CMAKE_SIZE "D:/compile/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-size.exe")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/link.lds")

SET(CMAKE_CXX_STANDARD 14)
PROJECT(rtthread C CXX ASM)
INCLUDE_DIRECTORIES(
	packages/aht10-latest
	applications
	rt-thread/components/net/at/include
	rt-thread/components/net/at/at_socket
	packages/at_device-latest/inc
	packages/at_device-latest/class/esp8266
	packages/cJSON-latest
	rt-thread/components/libc/compilers/common/include
	rt-thread/components/libc/compilers/newlib
	rt-thread/libcpu/arm/common
	rt-thread/libcpu/arm/cortex-m4
	rt-thread/components/drivers/include
	rt-thread/components/drivers/sensor
	board
	board/CubeMX_Config/Inc
	libraries/HAL_Drivers
	libraries/HAL_Drivers/config
	libraries/HAL_Drivers/CMSIS/Include
	rt-thread/components/dfs/dfs_v1/include
	rt-thread/components/dfs/dfs_v1/filesystems/devfs
	rt-thread/components/finsh
	.
	rt-thread/include
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Inc
	libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Include
	packages/onenet-latest/inc
	packages/pahomqtt-latest/MQTTPacket/src
	packages/pahomqtt-latest/MQTTClient-RT
	rt-thread/components/libc/posix/io/poll
	rt-thread/components/libc/posix/io/stdio
	rt-thread/components/libc/posix/ipc
	rt-thread/components/net/netdev/include
	rt-thread/components/net/sal/include
	rt-thread/components/net/sal/include/socket
	rt-thread/components/net/sal/impl
	rt-thread/components/net/sal/include/dfs_net
	rt-thread/components/net/sal/include/socket/sys_socket
	rt-thread/components/utilities/resource
)

ADD_DEFINITIONS(
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-DSTM32F411xE
	-DUSE_HAL_DRIVER
	-D_POSIX_C_SOURCE=1
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	packages/aht10-latest/aht10.c
	build/applications/dht11_lib/dht11.c
	applications/bh1750_lib/bh1750.c
	build/applications/dht11_lib/dht11_read.c
	applications/air_quality/air_quality_mtor.c
	applications/noise_analysis/noise_mtor.c
	applications/at_connect/at_server_user.c
	applications/aht10_lib/aht10_read.c
	applications/data_upload/data_upload.c
	applications/bmp280_lib/bmp280.c
	build/applications/noise_analysis/fliter.c
	applications/at_connect/tcp_accept.c
	applications/gps_analysis/gps_recv.c
	applications/voice_command/voice_uart.c
	applications/bh1750_lib/bh1750_config.c
	applications/voice_command/voice_ctrl.c
	applications/main.c
	applications/at_connect/at_client_user.c
	applications/bmp280_lib/bmp280_read.c
	rt-thread/components/net/at/src/at_client.c
	rt-thread/components/net/at/at_socket/at_socket.c
	rt-thread/components/net/at/src/at_utils.c
	rt-thread/components/net/at/src/at_cli.c
	packages/at_device-latest/src/at_device.c
	packages/at_device-latest/samples/at_sample_esp8266.c
	packages/at_device-latest/class/esp8266/at_device_esp8266.c
	packages/at_device-latest/class/esp8266/at_socket_esp8266.c
	packages/cJSON-latest/cJSON_Utils.c
	packages/cJSON-latest/cJSON.c
	rt-thread/components/libc/compilers/common/cctype.c
	rt-thread/components/libc/compilers/common/cstdio.c
	rt-thread/components/libc/compilers/common/cstdlib.c
	rt-thread/components/libc/compilers/common/cstring.c
	rt-thread/components/libc/compilers/common/ctime.c
	rt-thread/components/libc/compilers/common/cwchar.c
	rt-thread/components/libc/compilers/newlib/syscalls.c
	rt-thread/libcpu/arm/common/atomic_arm.c
	rt-thread/libcpu/arm/common/div0.c
	rt-thread/libcpu/arm/common/showmem.c
	rt-thread/libcpu/arm/cortex-m4/context_gcc.S
	rt-thread/libcpu/arm/cortex-m4/cpuport.c
	rt-thread/components/drivers/hwtimer/hwtimer.c
	rt-thread/components/drivers/i2c/i2c-bit-ops.c
	rt-thread/components/drivers/i2c/i2c_core.c
	rt-thread/components/drivers/i2c/i2c_dev.c
	rt-thread/components/drivers/ipc/completion.c
	rt-thread/components/drivers/ipc/dataqueue.c
	rt-thread/components/drivers/ipc/pipe.c
	rt-thread/components/drivers/ipc/ringblk_buf.c
	rt-thread/components/drivers/ipc/ringbuffer.c
	rt-thread/components/drivers/ipc/waitqueue.c
	rt-thread/components/drivers/ipc/workqueue.c
	rt-thread/components/drivers/misc/adc.c
	rt-thread/components/drivers/misc/pin.c
	rt-thread/components/drivers/sensor/sensor.c
	rt-thread/components/drivers/sensor/sensor_cmd.c
	rt-thread/components/drivers/serial/serial.c
	board/CubeMX_Config/Src/stm32f4xx_hal_msp.c
	board/board.c
	libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f411xe.s
	libraries/HAL_Drivers/drv_adc.c
	libraries/HAL_Drivers/drv_common.c
	libraries/HAL_Drivers/drv_gpio.c
	libraries/HAL_Drivers/drv_soft_i2c.c
	libraries/HAL_Drivers/drv_usart.c
	rt-thread/components/dfs/dfs_v1/filesystems/devfs/devfs.c
	rt-thread/components/dfs/dfs_v1/src/dfs.c
	rt-thread/components/dfs/dfs_v1/src/dfs_file.c
	rt-thread/components/dfs/dfs_v1/src/dfs_fs.c
	rt-thread/components/dfs/dfs_v1/src/dfs_posix.c
	rt-thread/components/finsh/shell.c
	rt-thread/components/finsh/msh.c
	rt-thread/components/finsh/msh_parse.c
	rt-thread/components/finsh/cmd.c
	rt-thread/components/finsh/msh_file.c
	rt-thread/src/clock.c
	rt-thread/src/components.c
	rt-thread/src/device.c
	rt-thread/src/idle.c
	rt-thread/src/ipc.c
	rt-thread/src/irq.c
	rt-thread/src/kservice.c
	rt-thread/src/mem.c
	rt-thread/src/mempool.c
	rt-thread/src/object.c
	rt-thread/src/scheduler_up.c
	rt-thread/src/thread.c
	rt-thread/src/timer.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c
	libraries/STM32F4xx_HAL/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
	libraries/STM32F4xx_HAL/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	packages/onenet-latest/src/onenet_mqtt.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTSubscribeServer.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTConnectClient.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTSubscribeClient.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTUnsubscribeClient.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTSerializePublish.c
	packages/pahomqtt-latest/MQTTClient-RT/paho_mqtt_pipe.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTConnectServer.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTDeserializePublish.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTFormat.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTUnsubscribeServer.c
	packages/pahomqtt-latest/MQTTPacket/src/MQTTPacket.c
	rt-thread/components/libc/posix/io/poll/poll.c
	rt-thread/components/libc/posix/io/poll/select.c
	packages/rt_vsnprintf_full-latest/rt_vsnprintf.c
	rt-thread/components/net/netdev/src/netdev.c
	rt-thread/components/net/netdev/src/netdev_ipaddr.c
	rt-thread/components/net/sal/dfs_net/dfs_net.c
	rt-thread/components/net/sal/impl/af_inet_at.c
	rt-thread/components/net/sal/socket/net_netdb.c
	rt-thread/components/net/sal/socket/net_sockets.c
	rt-thread/components/net/sal/src/sal_socket.c
	rt-thread/components/utilities/resource/resource_id.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)
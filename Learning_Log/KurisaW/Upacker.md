```c
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     Yifang       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "user_info"
#include <rtdbg.h>

rt_device_t packer_serial;

// 定义串口接收缓冲区大小
#define BUFFER_SIZE 128

// 定义字段起始标志和结束标志
#define START_BYTE 0xFF
#define END_BYTE 0xFE

// 定义状态机的状态
enum States
{
  STATE_IDLE,    // 空闲状态
  STATE_START,   // 接收到起始标志
  STATE_RECEIVE  // 正在接收数据
};

// 定义串口接收缓冲区和指针
char buffer[BUFFER_SIZE];
int bufferIndex = 0;

// 定义状态机当前状态
enum States currentState = STATE_IDLE;

// 日志记录函数
void logError(const char* errorMessage)
{
    // 记录错误日志
    LOG_W("Error logging:%s",errorMessage);
}

// 发送错误通知函数
void sendErrorNotification(const char* errorMessage)
{
    // 发送错误通知
    LOG_E("Error notification function sent:%s",errorMessage);
}

// 回调函数类型
typedef void (*CallbackFunction)(char*, int);

// 声明全局变量用于存储注册的回调函数
CallbackFunction gCallback = NULL;

// 注册回调函数
void registerCallback(CallbackFunction callback)
{
    // 在接收到完整的帧后调用该回调函数
    gCallback = callback;
    LOG_I("You have successfully obtained the complete data frame!\n");
}

// 计算校验和
char calculateChecksum(char* data, int length)
{
      char checksum = 0;
      for (int i = 0; i < length; i++)
      {
          checksum ^= data[i];
      }

      return checksum;
}

// 接收到数据时的处理函数
void receiveData(char data)
{
    CallbackFunction callback = registerCallback;

    switch (currentState)
    {
      case STATE_IDLE:
        if (data == START_BYTE)
        {
              currentState = STATE_START;
              bufferIndex = 0;
        }
        break;
      case STATE_START:
        if (data != START_BYTE)
        {
              currentState = STATE_RECEIVE;
              buffer[bufferIndex++] = data;
        }
        break;
      case STATE_RECEIVE:
        if (data != END_BYTE)
        {
              buffer[bufferIndex++] = data;
              if (bufferIndex >= BUFFER_SIZE)
              {
                    currentState = STATE_IDLE;
                    logError("Buffer overflow");
              }
        }
        else
        {
          // 接收到结束标志，数据帧接收完整
          currentState = STATE_IDLE;
          if (bufferIndex > 2)
          {
              // 至少包含校验和字段（1字节）和数据字段（至少1字节）
                int dataLength = bufferIndex - 1; // 数据长度为帧长度减去校验和长度
                char receivedChecksum = buffer[bufferIndex - 1]; // 校验和位于帧的最后一个字节
                char calculatedChecksum = calculateChecksum(buffer, bufferIndex - 1);
                if (receivedChecksum == calculatedChecksum)
                {
                      // 校验和匹配，执行回调函数，并传递接收到的数据和长度
                    callback(buffer, dataLength);
                }
                else
                {
                  // 校验和不匹配，发生错误
                  logError("Checksum mismatch");
                  sendErrorNotification("Checksum mismatch");
                }
          }
          else
          {
            // 帧长度不足，发生错误
            logError("Invalid frame length");
            sendErrorNotification("Invalid frame length");
          }
        }
        break;
      default:
        break;
    }
}

// 接收到完整数据帧后的回调函数示例
void onDataReceived(char* data, int length)
{
  // 在这里处理接收到的完整数据帧
    LOG_I("[Get the complete data frame]:%s    [length]:%d", data, length);
}

void uart_test(void)
{
    /* 查找串口设备 */
    packer_serial = rt_device_find(SAMPLE_UART_NAME);
    if (!packer_serial)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART_NAME);
        return RT_ERROR;
    }
    
    // 注册回调函数
    registerCallback(onDataReceived);

    void *buffer = RT_NULL;
    // 循环接收串口数据
    while (1)
    {
        char receivedData = rt_device_read(packer_serial, 0, buffer, sizeof(buffer))/* 从串口接收数据 */;
        if(receivedData != RT_NULL)
        {
            receiveData(receivedData);
        }
    }
}
MSH_CMD_EXPORT(uart_test,uart_test);
```


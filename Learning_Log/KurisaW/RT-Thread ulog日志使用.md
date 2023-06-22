## 配置项说明

```md
[*] Enable ulog                   /* 使能 ulog */
      The static output log level./* 选择静态的日志输出级别。选择完成后，比设定级别低的日志（这里特指使用 LOG_X API 的日志）将不会被编译到 ROM 中 */
[ ]   Enable ISR log.             /* 使能中断 ISR 日志，即在 ISR 中也可以使用日志输出 API */
[*]   Enable assert check.        /* 使能断言检查。关闭后，断言的日志将不会被编译到 ROM 中 */
(128) The log's max width.        /* 日志的最大长度。由于 ulog 的日志 API 按行作为单位，所以这个长度也代表一行日志的最大长度 */
[ ]   Enable async output mode.   /* 使能异步日志输出模式。开启这个模式后，日志不会立刻输出到后端，而是先缓存起来，然后交给日志输出线程（例如：idle 线程）去输出 */
      log format  --->            /* 配置日志的格式，例如：时间信息，颜色信息，线程信息，是否支持浮点等等 */
[*]   Enable console backend.     /* 使能控制台作为后端。使能后日志可以输出到控制台串口上。建议保持开启。 */
[ ]   Enable file backend.        /* ulog 的文件后端 */
[ ]   Enable runtime log filter.  /* 使能运行时的日志过滤器，即动态过滤。使能后，日志将支持按标签、关键词等方式，在系统运行时进行动态过滤。 */
[ ]   Enable syslog format log and API.  /* 启用 syslog 格式日志和 API */
```

## 日志级别

| **级别**        | **名称** | **描述**                                                     |
| --------------- | -------- | ------------------------------------------------------------ |
| LOG_LVL_ASSERT  | 断言     | 发生无法处理、致命性的的错误，以至于系统无法继续运行的断言日志 |
| LOG_LVL_ERROR   | 错误     | 发生严重的、**不可修复**的错误时输出的日志属于错误级别日志   |
| LOG_LVL_WARNING | 警告     | 出现一些不太重要的、具有**可修复性**的错误时，会输出这些警告日志 |
| LOG_LVL_INFO    | 信息     | 给本模块上层使用人员查看的重要提示信息日志，例如：初始化成功，当前工作状态等。该级别日志一般在量产时依旧**保留** |
| LOG_LVL_DBG     | 调试     | 给本模块开发人员查看的调试日志，该级别日志一般在量产时**关闭** |

---

## 不需要开启Ulog也可使用LOG函数

在源文件首部定义如下。注意：`#include <rtdbg.h>`一定要在`DBG_LEVEL` 和`DBG_SECTION_NAME` 宏定义后面

```c
#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "user_info"
#include <rtdbg.h>
```

**debug输出等级**

DBG_LEVEL：打印信息等级，可以取如下值。只有比DBG_LEVEL低的打印信息才会输出。

```c
#define DBG_ERROR           0
#define DBG_WARNING         1
#define DBG_INFO            2
#define DBG_LOG             3
```

**常用的API**

| **API**  | **描述**     |
| -------- | ------------ |
| LOG_E(…) | 错误级别日志 |
| LOG_W(…) | 警告级别日志 |
| LOG_I(…) | 提示级别日志 |
| LOG_D(…) | 调试级别日志 |
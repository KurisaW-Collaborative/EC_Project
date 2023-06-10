首先请先阅读https://club.rt-thread.org/ask/article/dade55b009be592a.html

学习文章中启动多媒体板

在启动后阅读https://club.rt-thread.org/ask/article/2434.html

 ***此教程仅为简单使用lvgl，如果有更详细或者更好，以及在多媒体扩展板上使用新版本lvgl的教程欢迎留言，一起学习*** 

------



### 本教程使用的多媒体显示器并且为老版本lvgl

当使用如图方法时

![image-20230509185834332](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305091858382.png)

如图方法为使用新版本的lvgl，因为未知原因（怀疑为没有对多媒体板进行lvgl的适配移植，因水平和精力有限，没有选择移植而是选择了使用老版本lvgl，如果有更好的方法欢迎留言）

**配置方法请先阅读前面链接 ，接下来说明lvgl的使用方法 **

#### lvgl的正式使用

关于api可以阅读[🎨百问网LVGL中文教程手册文档 — 百问网LVGL中文教程手册文档 1.0 文档 (100ask.net)](http://lvgl.100ask.net/7.11/index.html)

对于使用api的开发类似css就不加赘述了。

下面结合一种更加方便的开发方式

**使用SquareLine Studio辅助开发（使用版本1.2.3）**

仅用于开发简单的UI，复杂UI并不适合这个教程

（本人也没有实际做过复杂的rtthread系统上的UI，认为lvgl配置与SquareLine Studio的lvgl配置并不统一，很多部分都是自行修改，如果过于负责的UI很可能因为rtthread中的lvgl配置信息与生成的代码并不匹配导致显示奇奇怪怪，实际效果本人并不确定，如果有人实现了欢迎留言告知是否真的会有一些显示问题）

安装去百度搜索即可

##### 进入SquareLine Studio![image-20230509193203716](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092208908.png)

随便选右边框包括一些路径选择和显示的一些设置，按硬件进行修改即可（**LVGL的版本选择8.2.0 **）

![image-20230509193650735](C:/Users/瓜子的皮/AppData/Roaming/Typora/typora-user-images/image-20230509193650735.png)创建后就可以使用左下角的组件进行图形化的编写了。

UI设置好后在上边栏中的File->Project settings进行导出路径及分辨率等的配置

![image-20230509194805680](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092208953.png)

##### 将生成的文件放入rtthread项目中![image-20230509195237929](C:/Users/瓜子的皮/AppData/Roaming/Typora/typora-user-images/image-20230509195237929.png)

##### 修改ui,h文件

![image-20230509200049880](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092208455.png)

将#include包含的lvgl.h路径换成你的lvgl.h路径即可

##### 修改ui.c文件![image-20230509195317143](C:/Users/瓜子的皮/AppData/Roaming/Typora/typora-user-images/image-20230509195317143.png)

注释掉这段代码 这是一些lvgl的配置，简单的UI这些设置影响不大，**如果你lvgl配置与你生成文件所需的lvgl配置一样则无需修改 **

ui_init函数添加littlevgl2rrt_init("lcd");并且将一些rtthread的lvgl库没有的函数删掉或使用类似的函数替换掉即可。

![image-20230509200205473](C:/Users/瓜子的皮/AppData/Roaming/Typora/typora-user-images/image-20230509200205473.png)

需要替换的函数如生成的文件lv_obj_create只有一个参数，而软件包中具有两个参数，这里就需要手动的修改替换（替换为何种或如何修改可以通过阅读前面的api文档或直接看软件包的代码）

------

欢迎内容的补充


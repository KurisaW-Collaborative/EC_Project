## 过程

主要场景在软件包移植这块，需要注意：

1.首先先随便添加一个软件包下载到本地后，然后在settings部分删除该软件包，只保留packages下的这四个文件

![image-20230627214641209](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306272146677.png)

2.将想要移植的软件包放在这个packages目录下，注意软件包中的.git文件需要删除，否则无法保留你在软件包中修改的配置

3.由于用户自己手动添加的软件包是不会包含头文件的，需要在studio手动设置下，如我需要构建头文件`packages\LittlevGL2RTT-v0.0.1\lvgl\lvgl.h`，它所包含的路径是`packages\LittlevGL2RTT-v0.0.1\lvgl`，我们在构建配置中添加路径

![image-20230627215351598](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306272153761.png)

![image-20230627215521000](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306272155132.png)
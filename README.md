# ESP32-S3 LVGL Board

## 项目描述

**基于ESP32-S3-WROOM-1-N16R8 设计的LVGL开发板，显示驱动ILI9488，采用并口驱动3.5寸LCD，电容触摸IC为FT6336U，可流畅运行LVGL图形库**



## 目录组成

### 1.Hardware

**存放PCB文件，包含立创EDA和Altiun Designer两个版本的文件**

### 2.Firmware

**存放ESP32-S3-WROOM1的LVGL库测试文件，用于测试板子是否能正常工作，也可以作为工程模板进行开发**

### **3.Project_demo**

**存放示例工程，使用Platformio进行编写**



## 成品展示



<img src=".\4.imgs\IMG_20240522_223426.jpg" alt="IMG_20240522_165220" style="zoom:20%;" />

<img src=".\4.imgs\IMG_20240522_223500.jpg" alt="IMG_20240522_165220" style="zoom:20%;" />

<img src=".\4.imgs\IMG_20240521_200419.jpg" alt="IMG_20240522_165220" style="zoom:20%;" />

<img src=".\4.imgs\IMG_20240522_165220.jpg" alt="IMG_20240522_165220" style="zoom:20%;" />



## 接口信息

### **已引出接口**

**40Pin LCD FPC座**

**6Pin 触摸 FPC座**

**USB串口**

**SD卡座**

**按键*5(其中两个同于复位和配置启动模式，3个可自定义功能)**

**RGB灯1个(可自定义状态显示)**

**16Pin FPC 扩展座(可用于连接其他外设，具体引脚定义见原理图)**





## 应用场景

**1.电子设计大赛人机交互系统(已应用)**

**2.智能门禁系统(见示例项目)**

**3.智能信息牌**

**4.LVGL及ESP32开发学习**



## 示例项目

### 基于STM32 ESP32 的NFC门禁系统

**视频链接：**

<video src=".\4.imgs\VID_20240522_185915.mp4" width = "720px"></video>

**#程序源码见Project_demo**



## 关于测试程序(使用必看)

**添加库路径时有些为了省事直接使用绝对路径，使用时注意根据报错信息一一修改即可**


#ifndef __FT6336U_DRIVER_H_
#define __FT6336U_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <Arduino.h>
#include <stdint.h>

//FT6336U触摸屏驱动程序
#define FT6336U_RST_IO  2   //复位低电平有效
#define FT6336U_INT_IO  40   //中断低电平有效

//芯片寄存器
#define Mode_Switch     0x00        //模式切换
#define TD_STATUS       0x02        //触摸点个数 ，最大支持两个


//第一个触摸点
#define P1_XH           0x03        //bit7-bit6为第1点触摸事件标志，bit3-bit0为第1点的X坐标高4位
#define P1_XL           0x04        //第1点的X坐标低8位
#define P1_YH           0x05        //bit7-bit6为第1点触摸事件标志，bit3-bit0为第1点的X坐标高4位
#define P1_YL           0x06        //第1点的Y坐标低8位

//第二个触摸点
#define P2_XH           0x09        //bit7-bit6为第1点触摸事件标志，bit3-bit0为第1点的X坐标高4位
#define P2_XL           0x0A        //第1点的X坐标低8位
#define P2_YH           0x0B        //bit7-bit6为第1点触摸事件标志，bit3-bit0为第1点的X坐标高4位
#define P2_YL           0x0C        //第1点的Y坐标低8位


#define ID_G_THGROUP    0x80        //触摸阈值 / 16
#define ID_G_THDIFF     0x85        //点滤波范围阈值
#define ID_G_CTRL       0x86        //monitor模式开关 写0 禁止  ， 写1 允许
#define ID_G_TIMEENTERMONITOR 0x87  //没触摸进入monitor延时
#define ID_G_PERIODACTIVE     0x88  //工作模式扫描周期
#define ID_G_PERIODMONITOR    0x89  //MONITOR模式扫描周期
#define ID_G_FREQ_HOPPING_EN  0x8B  //充电标识
#define ID_G_TEST_MODE_FILTER 0x96  //量测试模式下Alpha滤波使能

#define ID_G_CIPHER_HIGH      0xA3  //芯片代号高字节
#define ID_G_CIPHER_MIDE      0x9F  //芯片代号中字节
#define ID_G_CIPHER_LOW       0xA0  //芯片代号低字节

#define ID_G_LIB_VERSION_H    0xA1  //APP库文件版本高字节
#define ID_G_LIB_VERSION_L    0xA2  //APP库文件版本低字节

#define ID_G_MODE             0xA4  //报点INT模式

#define ID_G_PMODE            0xA5  //功耗模式

#define ID_G_FIRMID           0xA6  //固件版本
#define ID_G_FOCALTECH_ID     0xA8  //VENDOR ID

#define ID_G_VIRTUAL_KEY_THRES 0xA9 //量产测试模式下的虚拟按键阈值
#define ID_G_IS_CALLING        0xAD //用于HOST通知芯片是否在通话中

#define ID_G_FACTORY_MODE      0xAE //工厂模式种类

#define ID_G_FACE_DEC_MODE     0xB0 //近距离感应使能

#define ID_G_STATE             0xBC //工作模式

#define ID_G_SPEC_GESTURE_ENABLE 0xD0 //特殊手势模式使能
#define ID_G_SPEC_GESTURE_ID     0xD3 //手势ID
#define ID_G_SPEC_GESTURE_0      0xD1 //手势使能 ， 对应位写入1使能对应的手势
#define ID_G_SPEC_GESTURE_1      0xD2 //手势使能 ， 对应位写入1使能对应的手势
#define ID_G_SPEC_GESTURE_2      0xD5 //手势使能 ， 对应位写入1使能对应的手势
#define ID_G_SPEC_GESTURE_3      0xD6 //手势使能 ， 对应位写入1使能对应的手势
#define ID_G_SPEC_GESTURE_4      0xD7 //手势使能 ， 对应位写入1使能对应的手势
#define ID_G_SPEC_GESTURE_5      0xD8 //手势使能 ， 对应位写入1使能对应的手势

#define FT6336U_Slave_Addr      0x70 //IIC从机地址

#define FT_ENABLE          0x01
#define FT_DISABLE         0x00
//FT6336U芯片相关信息
typedef struct FT6336U_IC_INFO
{
    /* data */
    uint32_t    CPIPHER;
    uint16_t    LIB_VERSION;
    uint8_t     FIRMWARE_VERSION;
    uint8_t     VENDOR_ID;
}FT6336U_IC_INFO;


typedef struct FT6336U_TOUCH_POS
{
    /* data */
    uint8_t     touch_num;   //触摸点的数量
    //第一个触摸点的x,y值
    uint16_t    touch0_x;
    uint16_t    touch0_y;
    //第二个触摸点的x,y值
    uint16_t    touch1_x;
    uint16_t    touch1_y;

}FT6336U_TOUCH_POS;

//四种功耗模式
typedef enum POWER_MODE{
    P_ACTIVE = 0x00,
    p_MONITOR,
    P_STANDBY,
    P_HIBERNATE
}POWER_MODE;

typedef enum WORK_MODE{
    INFO_MODE = 0x00,           //InFO模式
    NORMAL_MODE,                //正常模式
    RESERVE,
    FACTORY_MODE,               //工厂模式
    AUTO_CALIBRATION_MODE       //自动校准模式
}WORK_MODE;


typedef enum SPEC_GESTURE_ID{
    slide_left      = 32,  //左滑
    slide_right     = 33,  //右滑
    slide_up        = 34,  //上滑
    slide_down      = 35,  //下滑
    double_click    = 36,  //双击

    //剩下特殊手势识别查看寄存器手册
}SPEC_GESTURE;

void ft6336u_init();   //初始化相关io和必要配置
void ft6336u_reset();  //复位芯片
void ft6336u_read_ic_info(FT6336U_IC_INFO *info);            //读取芯片信息
void ft6336u_face_dec_enable(uint8_t enable);                //写入近距离感应使能
void ft6336u_read_touch_pos(FT6336U_TOUCH_POS *touch_pos);   //读取触摸数据

void ft6336u_write_power_mode(POWER_MODE mode);     //写入功耗模式
uint8_t ft6336u_read_power_mode();                  //读取功耗模式


void ft6336u_write_work_mode(POWER_MODE mode);  //写入工作模式
void ft6336u_write_int_mode_enable(uint8_t enable);  //写入中断模式使能


void ft6336u_write_spec_gesture_enable(uint8_t enable); //写入特殊姿势识别模式使能
void ft6336u_read_spec_gesture_id(uint8_t *id);         //读取识别到的手势ID

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
#include "FT6336U_Driver.h"
#include "FT6336U_IIC.h"

//初始化相关io和必要配置
void ft6336u_init(){
    IIC_Init();
    gpio_config_t gpio_rst_configt = {
            .pin_bit_mask = (1ull << FT6336U_RST_IO),
            .mode = GPIO_MODE_OUTPUT,                   //设置为输出
            .pull_up_en = GPIO_PULLUP_ENABLE            //设置上拉
    };
    gpio_config(&gpio_rst_configt);

    gpio_config_t gpio_int_configt = {
            .pin_bit_mask = (1ull << FT6336U_INT_IO),
            .mode = GPIO_MODE_INPUT,                   //设置为输出
            .pull_up_en = GPIO_PULLUP_ENABLE,            //设置上拉
            .intr_type  = GPIO_INTR_NEGEDGE           //开启中断
    };
    gpio_config(&gpio_int_configt);
    gpio_set_level(FT6336U_RST_IO,1);
}

//复位芯片
void ft6336u_reset() {
    gpio_set_level(FT6336U_RST_IO,0);
    vTaskDelay(10);
    gpio_set_level(FT6336U_RST_IO,1);
}

//读取芯片信息
void ft6336u_read_ic_info(FT6336U_IC_INFO *info){
    uint8_t CIPHER_HIGH = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_CIPHER_HIGH);
    uint8_t CIPHER_MIDE = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_CIPHER_MIDE);
    uint8_t CIPHER_LOW = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_CIPHER_LOW);

    info->CPIPHER = (CIPHER_HIGH << 16) + (CIPHER_MIDE << 8) + CIPHER_LOW;

    uint8_t LIB_VERSION_H = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_LIB_VERSION_H);
    uint8_t LIB_VERSION_L = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_LIB_VERSION_L);

    info->LIB_VERSION = (LIB_VERSION_H << 8) + LIB_VERSION_L;

    uint8_t FIRMID = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_FIRMID);
    info->FIRMWARE_VERSION = FIRMID;

    uint8_t FOCALTECH_ID = IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_FOCALTECH_ID);
    info->VENDOR_ID = FOCALTECH_ID;
}


//写入近距离感应使能
void ft6336u_face_dec_enable(uint8_t enable){
    IIC_Write_One_Byte(FT6336U_Slave_Addr,ID_G_FACE_DEC_MODE,enable);
}
//读取触摸数据
void ft6336u_read_touch_pos(FT6336U_TOUCH_POS *touch_pos){

    //读取第一个点的数据
    uint8_t P1_XH_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P1_XH);
    uint8_t P1_XL_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P1_XL);
    uint8_t P1_YH_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P1_YH);
    uint8_t P1_YL_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P1_YL);
    //读取第二个点的数据
    uint8_t P2_XH_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P2_XH);
    uint8_t P2_XL_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P2_XL);
    uint8_t P2_YH_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P2_YH);
    uint8_t P2_YL_P = IIC_Read_One_Byte(FT6336U_Slave_Addr,P2_YL);
    //读取有效点的个数
    uint8_t tp_status = IIC_Read_One_Byte(FT6336U_Slave_Addr,TD_STATUS);

    touch_pos->touch_num = tp_status;
    touch_pos->touch0_x = ((P1_XH_P & 0x0F) << 8) + P1_XL_P;
    touch_pos->touch0_y = ((P1_YH_P & 0x0F) << 8) + P1_YL_P;
    touch_pos->touch1_x = ((P2_XH_P & 0x0F) << 8) + P2_XL_P;
    touch_pos->touch1_y = ((P2_YH_P & 0x0F) << 8) + P2_YL_P;
}

//写入功耗模式
void ft6336u_write_power_mode(POWER_MODE mode){
    IIC_Write_One_Byte(FT6336U_Slave_Addr,ID_G_PMODE,mode);
}
//读取功耗模式
uint8_t ft6336u_read_power_mode(){
    return IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_PMODE);
}

//写入中断模式使能
void ft6336u_write_int_mode_enable(uint8_t enable){
    if( enable == FT_ENABLE){
        gpio_config_t gpio_int_configt = {
                .pin_bit_mask = (1ull << FT6336U_INT_IO),
                .mode = GPIO_MODE_INPUT,                   //设置为输出
                .pull_up_en = GPIO_PULLUP_ENABLE,            //设置上拉
                .intr_type  = GPIO_INTR_NEGEDGE           //开启中断
        };
        gpio_config(&gpio_int_configt);
    }
    else{
        gpio_config_t gpio_int_configt = {
                .pin_bit_mask = (1ull << FT6336U_INT_IO),
                .mode = GPIO_MODE_INPUT,                   //设置为输出
                .pull_up_en = GPIO_PULLUP_ENABLE,            //设置上拉
                .intr_type  = GPIO_INTR_DISABLE            //关闭中断
        };
        gpio_config(&gpio_int_configt);
    }
    IIC_Write_One_Byte(FT6336U_Slave_Addr,ID_G_MODE,enable);
}

//写入工作模式
void ft6336u_write_work_mode(POWER_MODE mode){
    IIC_Write_One_Byte(FT6336U_Slave_Addr,ID_G_STATE,mode);
}


//写入特殊姿势识别模式使能
void ft6336u_write_spec_gesture_enable(uint8_t enable){
    IIC_Write_One_Byte(FT6336U_Slave_Addr,ID_G_SPEC_GESTURE_ENABLE,enable);
}
//读取识别到的手势ID
void ft6336u_read_spec_gesture_id(uint8_t *id){
    *id =  IIC_Read_One_Byte(FT6336U_Slave_Addr,ID_G_SPEC_GESTURE_ID);
}
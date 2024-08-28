#include "FT6336U_IIC.h"

//IIC初始化
void IIC_Init(void)
{
    gpio_config_t gpio_configt = {
            .pin_bit_mask = (1ull << SCL_io) | (1ull << SDA_io),
            .mode = GPIO_MODE_OUTPUT,                   //设置为输出
            .pull_up_en = GPIO_PULLUP_ENABLE            //设置上拉
    };
    gpio_config(&gpio_configt);
    SCL_HIGH;       //上拉
    SCL_HIGH;       //上拉
}
//数据端口配置为输出模式
void SDA_OUT(void)
{
    gpio_set_direction(SDA_io,GPIO_MODE_OUTPUT);
}
//数据端口配置为输入模式
void SDA_IN(void)
{
    gpio_set_direction(SDA_io,GPIO_MODE_INPUT);
}
//iic延时使用
static void IIC_delay(void)
{
    volatile int i = 100;
    while (i)
        i--;
}
//起始信号
void IIC_Start(void)
{
    SDA_OUT();
    SCL_HIGH;
    SDA_HIGH;
    IIC_delay();
    SDA_LOW;
    IIC_delay();
}
//停止信号
void IIC_Stop(void)
{
    SDA_OUT();
    SCL_LOW;
    IIC_delay();
    SDA_LOW;
    IIC_delay();
    SCL_HIGH;
    IIC_delay();
    SDA_HIGH;
    IIC_delay();
}
/* 等待从机应答信号          */
/* 返回值： 0：接收应答失败  */
/*          1：接收应答成功  */
unsigned char IIC_Slave_Ack(void)
{
    SDA_OUT();
    SCL_LOW;
    IIC_delay();
    SDA_HIGH;

    SDA_IN();
    IIC_delay();
    SCL_HIGH;

    IIC_delay();

    if(SDA_READ)
    {
        SCL_LOW;
        return 0;
    }
    SCL_LOW;
    IIC_delay();
    return 1;
}

//发送一个字节
void IIC_Send_Byte(unsigned char byte)
{
    unsigned char i = 8;
    SDA_OUT();
    while (i--)
    {
        SCL_LOW;                //拉低时钟开始数据传输
        IIC_delay();
        if (byte & 0x80)
            SDA_HIGH;
        else
            SDA_LOW;
        byte <<= 1;
        IIC_delay();
        SCL_HIGH;
        IIC_delay();
    }
    SCL_LOW;
    if(IIC_Slave_Ack()==0)
    {
        return ;
    }
}
/* 读取一个字节数据   */
/* 返回值：读取的数据 */
unsigned char IIC_Read_Byte(void)
{
    unsigned char i;
    unsigned char dat = 0;
    SDA_IN();
    for (i=0; i<8; i++)
    {
        dat <<= 1;
        SCL_HIGH;
        IIC_delay();
        dat |= SDA_READ;
        SCL_LOW;
        IIC_delay();
    }
    return dat;
}

/* 向寄存器写一个字节数据       */
/* SlaveAddress：从机地址       */
/* REG_Address：寄存器地址      */
/* REG_data：向寄存器写入的数据 */
void IIC_Write_One_Byte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
    IIC_Start();
    IIC_Send_Byte(SlaveAddress);
    IIC_Send_Byte(REG_Address);
    IIC_Send_Byte(REG_data);
    IIC_Stop();
}

//* 从寄存器读取一个字节数据 */
//* SlaveAddress：从机地址   */
//* REG_Address： 寄存器地址 */
//* 返回值：读取的数据       */
unsigned char IIC_Read_One_Byte(unsigned char SlaveAddress,unsigned char REG_Address)
{
    unsigned char REG_data;

    IIC_Start();
    IIC_Send_Byte(SlaveAddress);
    IIC_Send_Byte(REG_Address);
    IIC_Start();
    IIC_Send_Byte(SlaveAddress+1);
    REG_data = IIC_Read_Byte();
    IIC_Slave_Ack();
    IIC_Stop();
    return REG_data;
}
//连续读取两个字节数据
unsigned short int IIC_Read_Two_Bytes(unsigned char SlaveAddress,unsigned char REG_Address)
{
    unsigned char H, L;
    H = IIC_Read_One_Byte(SlaveAddress,REG_Address);
    L = IIC_Read_One_Byte(SlaveAddress,REG_Address+1);
    return ( ((unsigned short int)H) << 8 | L) ;
}

#ifndef __FT6336U_IIC_H_
#define __FT6336U_IIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/gpio.h"
//FT6336U IIC协议

#define  SCL_io   20
#define  SDA_io   19

#define SCL_HIGH          gpio_set_level(SCL_io,1)
#define SCL_LOW           gpio_set_level(SCL_io,0)

#define SDA_HIGH          gpio_set_level(SDA_io,1)
#define SDA_LOW           gpio_set_level(SDA_io,0)

#define SDA_READ          gpio_get_level(SDA_io)

//IIC协议
void IIC_Init(void);
void SDA_OUT(void);
void SDA_IN(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Slave_Ack(void);
void IIC_Send_Byte(unsigned char byte);
unsigned char IIC_Read_Byte(void);

//IIC 读写数据
void IIC_Write_One_Byte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char IIC_Read_One_Byte(unsigned char SlaveAddress,unsigned char REG_Address);
unsigned short int IIC_Read_Two_Bytes(unsigned char SlaveAddress,unsigned char REG_Address);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

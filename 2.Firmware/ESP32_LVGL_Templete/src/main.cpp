#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "demos/lv_demos.h"
#include "C:\Users\const\Documents\PlatformIO\Projects\ESP32_LVGL\lib\timer\timer.h"
#include "FT6336U_Driver.h"

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ 480 * 320 / 10 ];

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    FT6336U_TOUCH_POS touch;//储存触摸信息
    ft6336u_read_touch_pos(&touch); //读取触摸数据

    if( !touch.touch_num )	//识别到有触摸点
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = touch.touch0_y;//如果发现触摸反向，交换一下x,y坐标
        data->point.y = touch.touch0_x;
    }
}

void setup() {

  lv_init();
  tft.begin();  //初始化配置
  tft.setRotation(3);//设置显示方向

  pinMode(TFT_BL,OUTPUT); //打开背光
  digitalWrite(TFT_BL,1);

  lv_disp_draw_buf_init( &draw_buf, buf, NULL, 480 * 320 / 10 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = 480;
  disp_drv.ver_res = 320;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  ft6336u_init();
  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );
  
  lv_demo_benchmark();
  Timer0_Init();  //provide 1ms heart breaking
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay( 1 );
}

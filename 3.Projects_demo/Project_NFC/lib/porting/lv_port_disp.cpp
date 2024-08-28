#include "lv_port_disp.h"

#define MY_DISP_HOR_RES    320
#define MY_DISP_VER_RES    240

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();
static void disp_init(void);
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lv_port_disp_init(void)
{
    disp_init();

    static lv_disp_draw_buf_t draw_buf_dsc;
    static lv_color_t buf1[MY_DISP_HOR_RES * 10];    /*A buffer for 10 rows*/
    static lv_color_t buf2[MY_DISP_HOR_RES * 10];    /*A buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc, buf1, buf2, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/

    static lv_disp_drv_t disp_drv; /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf_dsc;
    lv_disp_drv_register(&disp_drv);
}

static void disp_init(void)
{
    tft.begin();  //初始化配置
    tft.setRotation(3);//设置显示方向
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}


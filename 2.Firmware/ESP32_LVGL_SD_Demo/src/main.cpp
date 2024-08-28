#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "demos/lv_demos.h"
#include "C:\Users\const\Documents\PlatformIO\Projects\Project\lib\timer\timer.h"
#include "FT6336U_Driver.h"
#include "gui_guider.h"
#include "events_init.h"
#include "communicate.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <FastLED.h>
#include <SD_MMC.h>

lv_ui guider_ui;
CRGB leds[1];

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[480 * 320 / 10];
uint8_t reply = 0;
uint8_t reply_flag = 0;
uint8_t admin_status = 0;
uint8_t inquire_flag = 0;


void lock_init();
void inquire();



/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	tft.startWrite();
	tft.setAddrWindow(area->x1, area->y1, w, h);
	tft.pushColors((uint16_t *)&color_p->full, w * h, true);
	tft.endWrite();

	lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	FT6336U_TOUCH_POS touch;		//储存触摸信息
	ft6336u_read_touch_pos(&touch); //读取触摸数据

	if (!touch.touch_num) //识别到有触摸点
	{
		data->state = LV_INDEV_STATE_REL;
	}
	else
	{
		data->state = LV_INDEV_STATE_PR;
		/*Set the coordinates*/
		data->point.x = 480 - touch.touch0_y; //如果发现触摸反向，交换一下x,y坐标
		data->point.y = touch.touch0_x;
	}
}

void initSDCard() {
	SD_MMC.setPins(12, 11, 41,45,47,42);
	if (!SD_MMC.begin("/sdcard", false, false, 20000, (uint8_t)5U))
	{
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD_MMC.cardType();
	uint64_t SD_size = SD_MMC.totalBytes();

	Serial.print("SD_MMC Card Size: ");
	Serial.print(SD_size / 1024 / 1024);
	Serial.println("MB");
 
    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }
 
    Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
	lv_fs_fatfs_init();
}

void task1(void *pvParameters) {
    int frame_cnt = 0;
	while (1) {
		char buf[30];
		sprintf(buf, "A:/video2img/frame_%06d.png",frame_cnt);
		//sprintf(buf, "A:/bin/frame_%06d.bin",frame_cnt);
		lv_img_set_src(guider_ui.screen_img_1, buf);
		frame_cnt++;
		lv_timer_handler(); /* let the GUI do its work */
		//vTaskDelay(1 / portTICK_PERIOD_MS);  // 延时1秒
    }
}

void task2(void *pvParameters) {
    while (1) {
		vTaskDelay(1 / portTICK_PERIOD_MS);  // 延时1秒
    }
}

void setup()
{
	Serial.begin(512000);

	FastLED.addLeds<WS2812, 38, GRB>(leds, 1);
	leds[0] = CRGB (25, 25, 25);
    FastLED.show();

	initSDCard();

	lv_init();

	tft.begin();		//初始化配置
	tft.setRotation(3); //设置显示方向

	pinMode(TFT_BL, OUTPUT); //打开背光
	digitalWrite(TFT_BL, 1);

	lv_disp_draw_buf_init(&draw_buf, buf, NULL, 480 * 320 / 10);

	/*Initialize the display*/
	static lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	/*Change the following line to your display resolution*/
	disp_drv.hor_res = 480;
	disp_drv.ver_res = 320;
	disp_drv.flush_cb = my_disp_flush;
	disp_drv.draw_buf = &draw_buf;
	lv_disp_drv_register(&disp_drv);

	ft6336u_init();
	/*Initialize the (dummy) input device driver*/
	static lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_touchpad_read;
	lv_indev_drv_register(&indev_drv);

	Serial.println("lv_init()");

	// lv_demo_benchmark();
	setup_ui(&guider_ui);
	events_init(&guider_ui);

	Timer0_Init(); // provide 1ms heart breaking

	//UI线程
    xTaskCreate(task1, "task1", 4096, NULL, 1, NULL);
    //串口线程
    //xTaskCreate(task2, "task2", 4096, NULL, 2, NULL);
}

void loop()
{
	
}






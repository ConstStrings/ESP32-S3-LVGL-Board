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

static void event_btn_open_cb(lv_event_t *e)
{
	uint8_t command = OPEN;
	Serial.write(&command, 1);
}

static void event_btn_add_cb(lv_event_t *e)
{
	uint8_t command = NEW_UID;
	Serial.write(&command, 1);
	reply_flag = 1;
	lv_label_set_text(guider_ui.screen_wait, "Waiting for Card...");
}

static void event_btn_erase_cb(lv_event_t *e)
{
	uint8_t command = ERASE_CHIP;
	Serial.write(&command, 1);
	reply_flag = 2;
	lv_label_set_text(guider_ui.screen_erasetxt, "Executive erase...");
}

static void event_btn_admin_cb(lv_event_t *e)
{
	uint8_t command = ADMIN;
	Serial.write(&command, 1);
	reply_flag = 3;
}

void add_enent()
{
	lv_obj_add_event_cb(guider_ui.screen_open, event_btn_open_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(guider_ui.screen_add, event_btn_add_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(guider_ui.screen_erase, event_btn_erase_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(guider_ui.screen_admin, event_btn_admin_cb, LV_EVENT_CLICKED, NULL);
}

void screen_refresh()
{
	if (reply_flag == 0)
	{
		if(reply == USER_S)
		{
			lv_obj_clear_flag( guider_ui.screen_success, LV_OBJ_FLAG_HIDDEN );
			leds[0] = CRGB (0, 25, 0);
    		FastLED.show();
		}
		else if(reply == USER_F)
		{
			lv_obj_clear_flag( guider_ui.screen_failure, LV_OBJ_FLAG_HIDDEN );
			leds[0] = CRGB (0, 0, 25);
    		FastLED.show();
		}
		delay(5000);
		lv_obj_add_flag( guider_ui.screen_failure, LV_OBJ_FLAG_HIDDEN );
 		lv_obj_add_flag( guider_ui.screen_success, LV_OBJ_FLAG_HIDDEN );
	}
	else if(reply_flag == 1)
	{
		if(reply == NEW_UID_DONE)
		{
			lv_label_set_text(guider_ui.screen_wait, "Add UID Done");
			
		}
		else if(reply == NEW_UID_FAIL)
		{
			lv_label_set_text(guider_ui.screen_wait, "Add UID Fail");
		}
		delay(3000);
		lv_label_set_text(guider_ui.screen_wait, "No Action");
	}
	else if(reply_flag == 2)
	{
		if(reply == ERASE_DONE)
		{
			lv_label_set_text(guider_ui.screen_erasetxt, "Erase Done");
		}
		delay(3000);
		lv_label_set_text(guider_ui.screen_erasetxt, "No Action");
	}
	else if(reply_flag == 3)
	{
		if(reply == ADMIN_OK)
		{
			admin_status = 1;
		}
		else if(reply == ADMIN_FAIL)
		{
			admin_status = 0;
		}
	}
}

void lock_init()
{
	lv_obj_add_flag( guider_ui.screen_failure, LV_OBJ_FLAG_HIDDEN );
 	lv_obj_add_flag( guider_ui.screen_success, LV_OBJ_FLAG_HIDDEN );
	lv_label_set_text(guider_ui.screen_wait, "No Action");
	lv_label_set_text(guider_ui.screen_erasetxt, "No Action");
}

int cnt = 0;

void task1(void *pvParameters) {
    while (1) {
        lv_timer_handler(); /* let the GUI do its work */
		vTaskDelay(1 / portTICK_PERIOD_MS);  // 延时1秒
    }
}

void task2(void *pvParameters) {
    while (1) {
		// cnt++;
		// if(cnt == 1000)
		// {
		// 	inquire();
		// 	cnt = 0;
		// }
		if(Serial.available())
		{
			Serial.read(&reply,1);
			screen_refresh();
			reply_flag = 0;
			leds[0] = CRGB (25, 0, 0);
    		FastLED.show();
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时1秒
    }
}

void inquire() {   
	uint8_t command = ASK_NUM;
	Serial.write(&command, 1);
	inquire_flag = 1;
	while(Serial.available() == 0);
		;
	uint8_t num;
	Serial.read(&num,1);
	inquire_flag = 0;
	lv_label_set_text(guider_ui.screen_num, std::to_string(num).c_str());	
}

void setup()
{
	FastLED.addLeds<WS2812, 38, GRB>(leds, 1);
	leds[0] = CRGB (25, 25, 25);
    FastLED.show();

	lv_init();
	Serial.begin(115200);
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

	// lv_demo_benchmark();
	setup_ui(&guider_ui);
	events_init(&guider_ui);

	add_enent();
	lock_init();

	Timer0_Init(); // provide 1ms heart breaking

	//UI线程
    xTaskCreate(task1, "task1", 4096, NULL, 1, NULL);
    //串口线程
    xTaskCreate(task2, "task2", 4096, NULL, 2, NULL);
}

void loop()
{
	
}

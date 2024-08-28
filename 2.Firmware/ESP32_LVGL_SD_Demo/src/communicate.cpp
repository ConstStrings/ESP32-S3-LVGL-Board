#include <lvgl.h>
#include "SD.h"
#include "communicate.h"
#include "lvgl.h"

void lv_fs_test(void)
{
	lv_fs_file_t f;
	lv_fs_res_t res;
	res = lv_fs_open(&f, "A:/test.txt", LV_FS_MODE_RD);
	if(res != LV_FS_RES_OK) 
	{
		Serial.println("Open fail");
	}
	else
	{
		Serial.println("Open OK");
		uint32_t read_num;
		uint8_t buf[8];
		res = lv_fs_read(&f, buf, 8, &read_num);
		Serial.printf("read:%s",buf);
		lv_fs_close(&f);
	}
}



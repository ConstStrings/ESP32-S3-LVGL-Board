/*
 * Copyright 2024 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "./guider_fonts/guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_windows;
	lv_obj_t *windows_statistics;
	lv_obj_t *screen_num;
	lv_obj_t *screen_number;
	lv_obj_t *screen_stati;
	lv_obj_t *windows_lock;
	lv_obj_t *screen_lockimg;
	lv_obj_t *screen_failure;
	lv_obj_t *screen_success;
	lv_obj_t *windows_settings;
	lv_obj_t *screen_loaderase;
	lv_obj_t *screen_open;
	lv_obj_t *screen_open_label;
	lv_obj_t *screen_erasetxt;
	lv_obj_t *screen_erase;
	lv_obj_t *screen_erase_label;
	lv_obj_t *screen_load;
	lv_obj_t *screen_wait;
	lv_obj_t *screen_add;
	lv_obj_t *screen_add_label;
	lv_obj_t *screen_admin;
	lv_obj_t *screen_admin_label;
	lv_obj_t *screen_settingtxt;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_2_480x320);
LV_IMG_DECLARE(_Successful_200x100);
LV_IMG_DECLARE(_failure_200x100);

#ifdef __cplusplus
}
#endif
#endif
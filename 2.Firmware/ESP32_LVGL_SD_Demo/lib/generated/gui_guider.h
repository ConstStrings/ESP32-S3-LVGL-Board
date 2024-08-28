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
	lv_obj_t *screen_tileview_1;
	lv_obj_t *tileview_1_name_1;
	lv_obj_t *screen_img_2;
	lv_obj_t *tileview_1_name_2;
	lv_obj_t *screen_img_1;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_2_480x320);
LV_IMG_DECLARE(_6a9e3e4fae4ebb9bbc83556ecabcda55a394de49_raw_480x320);

#ifdef __cplusplus
}
#endif
#endif
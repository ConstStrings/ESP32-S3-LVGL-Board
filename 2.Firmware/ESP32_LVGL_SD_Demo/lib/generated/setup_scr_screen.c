/*
 * Copyright 2024 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "../custom/custom.h"


void setup_scr_screen(lv_ui *ui){
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_img_1, 0, 0);
	lv_obj_set_size(ui->screen_img_1, 480, 320);
	lv_obj_set_scrollbar_mode(ui->screen_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_1_main_main_default
	static lv_style_t style_screen_img_1_main_main_default;
	if (style_screen_img_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_img_1_main_main_default);
	else
		lv_style_init(&style_screen_img_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_img_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_img_1, &style_screen_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);




	// //Write codes screen
	// ui->screen = lv_obj_create(NULL);
	// lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	// //Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	// static lv_style_t style_screen_main_main_default;
	// if (style_screen_main_main_default.prop_cnt > 1)
	// 	lv_style_reset(&style_screen_main_main_default);
	// else
	// 	lv_style_init(&style_screen_main_main_default);
	// lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	// lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	// //Write codes screen_tileview_1
	// ui->screen_tileview_1 = lv_tileview_create(ui->screen);
	// lv_obj_set_pos(ui->screen_tileview_1, 0, 0);
	// lv_obj_set_size(ui->screen_tileview_1, 480, 320);
	// lv_obj_set_scrollbar_mode(ui->screen_tileview_1, LV_SCROLLBAR_MODE_ON);

	// //Write style state: LV_STATE_DEFAULT for style_screen_tileview_1_main_main_default
	// static lv_style_t style_screen_tileview_1_main_main_default;
	// if (style_screen_tileview_1_main_main_default.prop_cnt > 1)
	// 	lv_style_reset(&style_screen_tileview_1_main_main_default);
	// else
	// 	lv_style_init(&style_screen_tileview_1_main_main_default);
	// lv_style_set_radius(&style_screen_tileview_1_main_main_default, 0);
	// lv_style_set_bg_color(&style_screen_tileview_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	// lv_style_set_bg_grad_color(&style_screen_tileview_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	// lv_style_set_bg_grad_dir(&style_screen_tileview_1_main_main_default, LV_GRAD_DIR_NONE);
	// lv_style_set_bg_opa(&style_screen_tileview_1_main_main_default, 255);
	// lv_obj_add_style(ui->screen_tileview_1, &style_screen_tileview_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	// //Write style state: LV_STATE_DEFAULT for style_screen_tileview_1_main_scrollbar_default
	// static lv_style_t style_screen_tileview_1_main_scrollbar_default;
	// if (style_screen_tileview_1_main_scrollbar_default.prop_cnt > 1)
	// 	lv_style_reset(&style_screen_tileview_1_main_scrollbar_default);
	// else
	// 	lv_style_init(&style_screen_tileview_1_main_scrollbar_default);
	// lv_style_set_radius(&style_screen_tileview_1_main_scrollbar_default, 0);
	// lv_style_set_bg_color(&style_screen_tileview_1_main_scrollbar_default, lv_color_make(0xea, 0xef, 0xf3));
	// lv_style_set_bg_opa(&style_screen_tileview_1_main_scrollbar_default, 255);
	// lv_obj_add_style(ui->screen_tileview_1, &style_screen_tileview_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	// //add new tile tileview_1_name_1
	// ui->tileview_1_name_1 = lv_tileview_add_tile(ui->screen_tileview_1, 0, 0, LV_DIR_RIGHT);

	// //Write codes screen_img_2
	// ui->screen_img_2 = lv_img_create(ui->tileview_1_name_1);
	// lv_obj_set_pos(ui->screen_img_2, 0, 0);
	// lv_obj_set_size(ui->screen_img_2, 480, 320);
	// lv_obj_set_scrollbar_mode(ui->screen_img_2, LV_SCROLLBAR_MODE_OFF);

	// //Write style state: LV_STATE_DEFAULT for style_screen_img_2_main_main_default
	// static lv_style_t style_screen_img_2_main_main_default;
	// if (style_screen_img_2_main_main_default.prop_cnt > 1)
	// 	lv_style_reset(&style_screen_img_2_main_main_default);
	// else
	// 	lv_style_init(&style_screen_img_2_main_main_default);
	// lv_style_set_img_recolor(&style_screen_img_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_img_recolor_opa(&style_screen_img_2_main_main_default, 0);
	// lv_style_set_img_opa(&style_screen_img_2_main_main_default, 255);
	// lv_obj_add_style(ui->screen_img_2, &style_screen_img_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
	// lv_img_set_src(ui->screen_img_2,&_2_480x320);
	// lv_img_set_pivot(ui->screen_img_2, 0,0);
	// lv_img_set_angle(ui->screen_img_2, 0);

	// //add new tile tileview_1_name_2
	// ui->tileview_1_name_2 = lv_tileview_add_tile(ui->screen_tileview_1, 1 , 0, LV_DIR_LEFT);

	// //Write codes screen_img_1
	// ui->screen_img_1 = lv_img_create(ui->tileview_1_name_2);
	// lv_obj_set_pos(ui->screen_img_1, 0, 0);
	// lv_obj_set_size(ui->screen_img_1, 480, 320);
	// lv_obj_set_scrollbar_mode(ui->screen_img_1, LV_SCROLLBAR_MODE_OFF);

	// //Write style state: LV_STATE_DEFAULT for style_screen_img_1_main_main_default
	// static lv_style_t style_screen_img_1_main_main_default;
	// if (style_screen_img_1_main_main_default.prop_cnt > 1)
	// 	lv_style_reset(&style_screen_img_1_main_main_default);
	// else
	// 	lv_style_init(&style_screen_img_1_main_main_default);
	// lv_style_set_img_recolor(&style_screen_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	// lv_style_set_img_recolor_opa(&style_screen_img_1_main_main_default, 0);
	// lv_style_set_img_opa(&style_screen_img_1_main_main_default, 255);
	// lv_obj_add_style(ui->screen_img_1, &style_screen_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	// lv_img_set_src(ui->screen_img_1,&_6a9e3e4fae4ebb9bbc83556ecabcda55a394de49_raw_480x320);
	// lv_img_set_pivot(ui->screen_img_1, 0,0);
	// lv_img_set_angle(ui->screen_img_1, 0);
}
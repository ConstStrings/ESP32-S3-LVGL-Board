/*
 * Copyright 2024 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "./gui_guider.h"
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

	//Write codes screen_windows
	ui->screen_windows = lv_tileview_create(ui->screen);
	lv_obj_set_pos(ui->screen_windows, 0, 0);
	lv_obj_set_size(ui->screen_windows, 480, 320);
	lv_obj_set_scrollbar_mode(ui->screen_windows, LV_SCROLLBAR_MODE_ON);

	//Write style state: LV_STATE_DEFAULT for style_screen_windows_main_main_default
	static lv_style_t style_screen_windows_main_main_default;
	if (style_screen_windows_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_windows_main_main_default);
	else
		lv_style_init(&style_screen_windows_main_main_default);
	lv_style_set_radius(&style_screen_windows_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_windows_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_windows_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_windows_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_windows_main_main_default, 255);
	lv_obj_add_style(ui->screen_windows, &style_screen_windows_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_windows_main_scrollbar_default
	static lv_style_t style_screen_windows_main_scrollbar_default;
	if (style_screen_windows_main_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_screen_windows_main_scrollbar_default);
	else
		lv_style_init(&style_screen_windows_main_scrollbar_default);
	lv_style_set_radius(&style_screen_windows_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_screen_windows_main_scrollbar_default, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_opa(&style_screen_windows_main_scrollbar_default, 255);
	lv_obj_add_style(ui->screen_windows, &style_screen_windows_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//add new tile windows_statistics
	ui->windows_statistics = lv_tileview_add_tile(ui->screen_windows, 0, 0, LV_DIR_RIGHT);

	//Write codes screen_num
	ui->screen_num = lv_label_create(ui->windows_statistics);
	lv_obj_set_pos(ui->screen_num, 154, 166);
	lv_obj_set_size(ui->screen_num, 172, 115);
	lv_obj_set_scrollbar_mode(ui->screen_num, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_num, "000");
	lv_label_set_long_mode(ui->screen_num, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_num_main_main_default
	static lv_style_t style_screen_num_main_main_default;
	if (style_screen_num_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_num_main_main_default);
	else
		lv_style_init(&style_screen_num_main_main_default);
	lv_style_set_radius(&style_screen_num_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_num_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_num_main_main_default, 0);
	lv_style_set_text_color(&style_screen_num_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_num_main_main_default, &lv_font_Acme_Regular_60);
	lv_style_set_text_letter_space(&style_screen_num_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_num_main_main_default, 0);
	lv_style_set_text_align(&style_screen_num_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_num_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_num_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_num_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_num_main_main_default, 0);
	lv_obj_add_style(ui->screen_num, &style_screen_num_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_number
	ui->screen_number = lv_label_create(ui->windows_statistics);
	lv_obj_set_pos(ui->screen_number, 111, 95);
	lv_obj_set_size(ui->screen_number, 248, 54);
	lv_obj_set_scrollbar_mode(ui->screen_number, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_number, "Number of people passed");
	lv_label_set_long_mode(ui->screen_number, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_number_main_main_default
	static lv_style_t style_screen_number_main_main_default;
	if (style_screen_number_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_number_main_main_default);
	else
		lv_style_init(&style_screen_number_main_main_default);
	lv_style_set_radius(&style_screen_number_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_number_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_number_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_number_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_number_main_main_default, 0);
	lv_style_set_text_color(&style_screen_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_number_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_number_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_number_main_main_default, 0);
	lv_style_set_text_align(&style_screen_number_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_number_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_number_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_number_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_number_main_main_default, 0);
	lv_obj_add_style(ui->screen_number, &style_screen_number_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_stati
	ui->screen_stati = lv_label_create(ui->windows_statistics);
	lv_obj_set_pos(ui->screen_stati, 0, 0);
	lv_obj_set_size(ui->screen_stati, 480, 30);
	lv_obj_set_scrollbar_mode(ui->screen_stati, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_stati, "Statistics");
	lv_label_set_long_mode(ui->screen_stati, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_stati_main_main_default
	static lv_style_t style_screen_stati_main_main_default;
	if (style_screen_stati_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_stati_main_main_default);
	else
		lv_style_init(&style_screen_stati_main_main_default);
	lv_style_set_radius(&style_screen_stati_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_stati_main_main_default, lv_color_make(0x2b, 0x2b, 0x2b));
	lv_style_set_bg_grad_color(&style_screen_stati_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_stati_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_stati_main_main_default, 255);
	lv_style_set_text_color(&style_screen_stati_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_stati_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_stati_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_stati_main_main_default, 0);
	lv_style_set_text_align(&style_screen_stati_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_stati_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_stati_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_stati_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_stati_main_main_default, 0);
	lv_obj_add_style(ui->screen_stati, &style_screen_stati_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//add new tile windows_lock
	ui->windows_lock = lv_tileview_add_tile(ui->screen_windows, 1 , 0, LV_DIR_LEFT | LV_DIR_RIGHT);

	//Write codes screen_lockimg
	ui->screen_lockimg = lv_img_create(ui->windows_lock);
	lv_obj_set_pos(ui->screen_lockimg, 0, 0);
	lv_obj_set_size(ui->screen_lockimg, 480, 320);
	lv_obj_set_scrollbar_mode(ui->screen_lockimg, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_lockimg_main_main_default
	static lv_style_t style_screen_lockimg_main_main_default;
	if (style_screen_lockimg_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_lockimg_main_main_default);
	else
		lv_style_init(&style_screen_lockimg_main_main_default);
	lv_style_set_img_recolor(&style_screen_lockimg_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_lockimg_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_lockimg_main_main_default, 255);
	lv_obj_add_style(ui->screen_lockimg, &style_screen_lockimg_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_lockimg, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_lockimg,&_2_480x320);
	lv_img_set_pivot(ui->screen_lockimg, 0,0);
	lv_img_set_angle(ui->screen_lockimg, 0);

	//Write codes screen_failure
	ui->screen_failure = lv_img_create(ui->windows_lock);
	lv_obj_set_pos(ui->screen_failure, 140, 110);
	lv_obj_set_size(ui->screen_failure, 200, 100);
	lv_obj_set_scrollbar_mode(ui->screen_failure, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_failure_main_main_default
	static lv_style_t style_screen_failure_main_main_default;
	if (style_screen_failure_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_failure_main_main_default);
	else
		lv_style_init(&style_screen_failure_main_main_default);
	lv_style_set_img_recolor(&style_screen_failure_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_failure_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_failure_main_main_default, 205);
	lv_obj_add_style(ui->screen_failure, &style_screen_failure_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_failure, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_failure,&_failure_200x100);
	lv_img_set_pivot(ui->screen_failure, 0,0);
	lv_img_set_angle(ui->screen_failure, 0);

	//Write codes screen_success
	ui->screen_success = lv_img_create(ui->windows_lock);
	lv_obj_set_pos(ui->screen_success, 140, 110);
	lv_obj_set_size(ui->screen_success, 200, 100);
	lv_obj_set_scrollbar_mode(ui->screen_success, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_success_main_main_default
	static lv_style_t style_screen_success_main_main_default;
	if (style_screen_success_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_success_main_main_default);
	else
		lv_style_init(&style_screen_success_main_main_default);
	lv_style_set_img_recolor(&style_screen_success_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_success_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_success_main_main_default, 205);
	lv_obj_add_style(ui->screen_success, &style_screen_success_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_success, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_success,&_Successful_200x100);
	lv_img_set_pivot(ui->screen_success, 0,0);
	lv_img_set_angle(ui->screen_success, 0);

	//add new tile windows_settings
	ui->windows_settings = lv_tileview_add_tile(ui->screen_windows, 2 , 0, LV_DIR_LEFT);

	//Write codes screen_loaderase
	ui->screen_loaderase = lv_spinner_create(ui->windows_settings, 1000, 60);
	lv_obj_set_pos(ui->screen_loaderase, 374, 149);
	lv_obj_set_size(ui->screen_loaderase, 67, 51);

	//Write style state: LV_STATE_DEFAULT for style_screen_loaderase_main_main_default
	static lv_style_t style_screen_loaderase_main_main_default;
	if (style_screen_loaderase_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_loaderase_main_main_default);
	else
		lv_style_init(&style_screen_loaderase_main_main_default);
	lv_style_set_bg_color(&style_screen_loaderase_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_loaderase_main_main_default, lv_color_make(0xee, 0xee, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_loaderase_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_loaderase_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_loaderase_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_loaderase_main_main_default, 5);
	lv_style_set_pad_top(&style_screen_loaderase_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_loaderase_main_main_default, 5);
	lv_style_set_arc_color(&style_screen_loaderase_main_main_default, lv_color_make(0xb2, 0xb2, 0xae));
	lv_style_set_arc_width(&style_screen_loaderase_main_main_default, 6);
	lv_obj_add_style(ui->screen_loaderase, &style_screen_loaderase_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_loaderase_main_indicator_default
	static lv_style_t style_screen_loaderase_main_indicator_default;
	if (style_screen_loaderase_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_loaderase_main_indicator_default);
	else
		lv_style_init(&style_screen_loaderase_main_indicator_default);
	lv_style_set_arc_color(&style_screen_loaderase_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_arc_width(&style_screen_loaderase_main_indicator_default, 12);
	lv_obj_add_style(ui->screen_loaderase, &style_screen_loaderase_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_open
	ui->screen_open = lv_btn_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_open, 108, 237);
	lv_obj_set_size(ui->screen_open, 276, 38);
	lv_obj_set_scrollbar_mode(ui->screen_open, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_open_main_main_default
	static lv_style_t style_screen_open_main_main_default;
	if (style_screen_open_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_open_main_main_default);
	else
		lv_style_init(&style_screen_open_main_main_default);
	lv_style_set_radius(&style_screen_open_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_open_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_open_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_open_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_open_main_main_default, 255);
	lv_style_set_border_color(&style_screen_open_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_open_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_open_main_main_default, 255);
	lv_style_set_text_color(&style_screen_open_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_open_main_main_default, &lv_font_Acme_Regular_30);
	lv_style_set_text_align(&style_screen_open_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_open, &style_screen_open_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_open_label = lv_label_create(ui->screen_open);
	lv_label_set_text(ui->screen_open_label, "OPEN");
	lv_obj_set_style_pad_all(ui->screen_open, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_open_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_erasetxt
	ui->screen_erasetxt = lv_label_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_erasetxt, 185, 164);
	lv_obj_set_size(ui->screen_erasetxt, 164, 28);
	lv_obj_set_scrollbar_mode(ui->screen_erasetxt, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_erasetxt, "Executive erase...");
	lv_label_set_long_mode(ui->screen_erasetxt, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_erasetxt_main_main_default
	static lv_style_t style_screen_erasetxt_main_main_default;
	if (style_screen_erasetxt_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_erasetxt_main_main_default);
	else
		lv_style_init(&style_screen_erasetxt_main_main_default);
	lv_style_set_radius(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_erasetxt_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_erasetxt_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_erasetxt_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_text_color(&style_screen_erasetxt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_erasetxt_main_main_default, &lv_font_Acme_Regular_16);
	lv_style_set_text_letter_space(&style_screen_erasetxt_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_text_align(&style_screen_erasetxt_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_erasetxt_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_erasetxt_main_main_default, 0);
	lv_obj_add_style(ui->screen_erasetxt, &style_screen_erasetxt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_erase
	ui->screen_erase = lv_btn_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_erase, 46, 153);
	lv_obj_set_size(ui->screen_erase, 100, 40);
	lv_obj_set_scrollbar_mode(ui->screen_erase, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_erase_main_main_default
	static lv_style_t style_screen_erase_main_main_default;
	if (style_screen_erase_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_erase_main_main_default);
	else
		lv_style_init(&style_screen_erase_main_main_default);
	lv_style_set_radius(&style_screen_erase_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_erase_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_erase_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_erase_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_erase_main_main_default, 255);
	lv_style_set_border_color(&style_screen_erase_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_erase_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_erase_main_main_default, 255);
	lv_style_set_text_color(&style_screen_erase_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_erase_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_align(&style_screen_erase_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_erase, &style_screen_erase_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_erase_label = lv_label_create(ui->screen_erase);
	lv_label_set_text(ui->screen_erase_label, "Erase All");
	lv_obj_set_style_pad_all(ui->screen_erase, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_erase_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_load
	ui->screen_load = lv_spinner_create(ui->windows_settings, 1000, 60);
	lv_obj_set_pos(ui->screen_load, 373, 73);
	lv_obj_set_size(ui->screen_load, 67, 50);

	//Write style state: LV_STATE_DEFAULT for style_screen_load_main_main_default
	static lv_style_t style_screen_load_main_main_default;
	if (style_screen_load_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_load_main_main_default);
	else
		lv_style_init(&style_screen_load_main_main_default);
	lv_style_set_bg_color(&style_screen_load_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_load_main_main_default, lv_color_make(0xee, 0xee, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_load_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_load_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_load_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_load_main_main_default, 5);
	lv_style_set_pad_top(&style_screen_load_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_load_main_main_default, 5);
	lv_style_set_arc_color(&style_screen_load_main_main_default, lv_color_make(0xb5, 0xb6, 0xba));
	lv_style_set_arc_width(&style_screen_load_main_main_default, 6);
	lv_obj_add_style(ui->screen_load, &style_screen_load_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_load_main_indicator_default
	static lv_style_t style_screen_load_main_indicator_default;
	if (style_screen_load_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_load_main_indicator_default);
	else
		lv_style_init(&style_screen_load_main_indicator_default);
	lv_style_set_arc_color(&style_screen_load_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_arc_width(&style_screen_load_main_indicator_default, 12);
	lv_obj_add_style(ui->screen_load, &style_screen_load_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_wait
	ui->screen_wait = lv_label_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_wait, 187, 87);
	lv_obj_set_size(ui->screen_wait, 160, 37);
	lv_obj_set_scrollbar_mode(ui->screen_wait, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_wait, "Waiting for Card...");
	lv_label_set_long_mode(ui->screen_wait, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_wait_main_main_default
	static lv_style_t style_screen_wait_main_main_default;
	if (style_screen_wait_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_wait_main_main_default);
	else
		lv_style_init(&style_screen_wait_main_main_default);
	lv_style_set_radius(&style_screen_wait_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_wait_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_wait_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_wait_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_wait_main_main_default, 0);
	lv_style_set_text_color(&style_screen_wait_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_wait_main_main_default, &lv_font_Acme_Regular_16);
	lv_style_set_text_letter_space(&style_screen_wait_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_wait_main_main_default, 0);
	lv_style_set_text_align(&style_screen_wait_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_wait_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_wait_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_wait_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_wait_main_main_default, 0);
	lv_obj_add_style(ui->screen_wait, &style_screen_wait_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_add
	ui->screen_add = lv_btn_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_add, 46, 77);
	lv_obj_set_size(ui->screen_add, 100, 40);
	lv_obj_set_scrollbar_mode(ui->screen_add, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_add_main_main_default
	static lv_style_t style_screen_add_main_main_default;
	if (style_screen_add_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_add_main_main_default);
	else
		lv_style_init(&style_screen_add_main_main_default);
	lv_style_set_radius(&style_screen_add_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_add_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_add_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_add_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_add_main_main_default, 255);
	lv_style_set_border_color(&style_screen_add_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_add_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_add_main_main_default, 255);
	lv_style_set_text_color(&style_screen_add_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_add_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_align(&style_screen_add_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_add, &style_screen_add_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_add_label = lv_label_create(ui->screen_add);
	lv_label_set_text(ui->screen_add_label, "ADD NEW");
	lv_obj_set_style_pad_all(ui->screen_add, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_add_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_admin
	ui->screen_admin = lv_btn_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_admin, 141, 292);
	lv_obj_set_size(ui->screen_admin, 212, 24);
	lv_obj_set_scrollbar_mode(ui->screen_admin, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_admin_main_main_default
	static lv_style_t style_screen_admin_main_main_default;
	if (style_screen_admin_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_admin_main_main_default);
	else
		lv_style_init(&style_screen_admin_main_main_default);
	lv_style_set_radius(&style_screen_admin_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_admin_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_admin_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_admin_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_admin_main_main_default, 255);
	lv_style_set_border_color(&style_screen_admin_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_admin_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_admin_main_main_default, 255);
	lv_style_set_text_color(&style_screen_admin_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_admin_main_main_default, &lv_font_Acme_Regular_12);
	lv_style_set_text_align(&style_screen_admin_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_admin, &style_screen_admin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_admin_label = lv_label_create(ui->screen_admin);
	lv_label_set_text(ui->screen_admin_label, "Administrator Permission Authentication");
	lv_obj_set_style_pad_all(ui->screen_admin, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_admin_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_settingtxt
	ui->screen_settingtxt = lv_label_create(ui->windows_settings);
	lv_obj_set_pos(ui->screen_settingtxt, 0, 0);
	lv_obj_set_size(ui->screen_settingtxt, 480, 30);
	lv_obj_set_scrollbar_mode(ui->screen_settingtxt, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_settingtxt, "Settings");
	lv_label_set_long_mode(ui->screen_settingtxt, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_settingtxt_main_main_default
	static lv_style_t style_screen_settingtxt_main_main_default;
	if (style_screen_settingtxt_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_settingtxt_main_main_default);
	else
		lv_style_init(&style_screen_settingtxt_main_main_default);
	lv_style_set_radius(&style_screen_settingtxt_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_settingtxt_main_main_default, lv_color_make(0x21, 0x21, 0x21));
	lv_style_set_bg_grad_color(&style_screen_settingtxt_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_settingtxt_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_settingtxt_main_main_default, 255);
	lv_style_set_text_color(&style_screen_settingtxt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_settingtxt_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_settingtxt_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_settingtxt_main_main_default, 0);
	lv_style_set_text_align(&style_screen_settingtxt_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_settingtxt_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_settingtxt_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_settingtxt_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_settingtxt_main_main_default, 0);
	lv_obj_add_style(ui->screen_settingtxt, &style_screen_settingtxt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}
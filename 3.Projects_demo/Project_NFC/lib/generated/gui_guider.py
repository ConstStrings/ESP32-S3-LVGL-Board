# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=480,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(480*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 480
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)


screen = lv.obj()
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_main_default.set_bg_opa(0)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_windows = lv.tileview(screen)
screen_windows.set_pos(int(0),int(0))
screen_windows.set_size(480,320)
screen_windows.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
windows_statistics = screen_windows.add_tile(0, 0, lv.DIR.RIGHT)
screen_num = lv.label(windows_statistics)
screen_num.set_pos(int(154),int(166))
screen_num.set_size(172,115)
screen_num.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_num.set_text("000")
screen_num.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_num_main_main_default
style_screen_num_main_main_default = lv.style_t()
style_screen_num_main_main_default.init()
style_screen_num_main_main_default.set_radius(0)
style_screen_num_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_num_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_num_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_num_main_main_default.set_bg_opa(0)
style_screen_num_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_num_main_main_default.set_text_font(lv.font_Acme_Regular_60)
except AttributeError:
    try:
        style_screen_num_main_main_default.set_text_font(lv.font_montserrat_60)
    except AttributeError:
        style_screen_num_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_num_main_main_default.set_text_letter_space(2)
style_screen_num_main_main_default.set_text_line_space(0)
style_screen_num_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_num_main_main_default.set_pad_left(0)
style_screen_num_main_main_default.set_pad_right(0)
style_screen_num_main_main_default.set_pad_top(0)
style_screen_num_main_main_default.set_pad_bottom(0)

# add style for screen_num
screen_num.add_style(style_screen_num_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_number = lv.label(windows_statistics)
screen_number.set_pos(int(111),int(95))
screen_number.set_size(248,54)
screen_number.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_number.set_text("Number of people passed")
screen_number.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_number_main_main_default
style_screen_number_main_main_default = lv.style_t()
style_screen_number_main_main_default.init()
style_screen_number_main_main_default.set_radius(0)
style_screen_number_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_number_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_number_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_number_main_main_default.set_bg_opa(0)
style_screen_number_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_number_main_main_default.set_text_font(lv.font_Acme_Regular_20)
except AttributeError:
    try:
        style_screen_number_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_number_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_number_main_main_default.set_text_letter_space(2)
style_screen_number_main_main_default.set_text_line_space(0)
style_screen_number_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_number_main_main_default.set_pad_left(0)
style_screen_number_main_main_default.set_pad_right(0)
style_screen_number_main_main_default.set_pad_top(0)
style_screen_number_main_main_default.set_pad_bottom(0)

# add style for screen_number
screen_number.add_style(style_screen_number_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_stati = lv.label(windows_statistics)
screen_stati.set_pos(int(0),int(0))
screen_stati.set_size(480,30)
screen_stati.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_stati.set_text("Statistics")
screen_stati.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_stati_main_main_default
style_screen_stati_main_main_default = lv.style_t()
style_screen_stati_main_main_default.init()
style_screen_stati_main_main_default.set_radius(0)
style_screen_stati_main_main_default.set_bg_color(lv.color_make(0x2b,0x2b,0x2b))
style_screen_stati_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_stati_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_stati_main_main_default.set_bg_opa(255)
style_screen_stati_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_stati_main_main_default.set_text_font(lv.font_Acme_Regular_20)
except AttributeError:
    try:
        style_screen_stati_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_stati_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_stati_main_main_default.set_text_letter_space(2)
style_screen_stati_main_main_default.set_text_line_space(0)
style_screen_stati_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_stati_main_main_default.set_pad_left(0)
style_screen_stati_main_main_default.set_pad_right(0)
style_screen_stati_main_main_default.set_pad_top(0)
style_screen_stati_main_main_default.set_pad_bottom(0)

# add style for screen_stati
screen_stati.add_style(style_screen_stati_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

windows_lock = screen_windows.add_tile(1 , 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_lockimg = lv.img(windows_lock)
screen_lockimg.set_pos(int(0),int(0))
screen_lockimg.set_size(480,320)
screen_lockimg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_lockimg.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-1360016672.png','rb') as f:
        screen_lockimg_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-1360016672.png')
    sys.exit()

screen_lockimg_img = lv.img_dsc_t({
  'data_size': len(screen_lockimg_img_data),
  'header': {'always_zero': 0, 'w': 480, 'h': 320, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_lockimg_img_data
})

screen_lockimg.set_src(screen_lockimg_img)
screen_lockimg.set_pivot(0,0)
screen_lockimg.set_angle(0)
# create style style_screen_lockimg_main_main_default
style_screen_lockimg_main_main_default = lv.style_t()
style_screen_lockimg_main_main_default.init()
style_screen_lockimg_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_lockimg_main_main_default.set_img_recolor_opa(0)
style_screen_lockimg_main_main_default.set_img_opa(255)

# add style for screen_lockimg
screen_lockimg.add_style(style_screen_lockimg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_failure = lv.img(windows_lock)
screen_failure.set_pos(int(140),int(110))
screen_failure.set_size(200,100)
screen_failure.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_failure.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-481487246.png','rb') as f:
        screen_failure_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-481487246.png')
    sys.exit()

screen_failure_img = lv.img_dsc_t({
  'data_size': len(screen_failure_img_data),
  'header': {'always_zero': 0, 'w': 200, 'h': 100, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_failure_img_data
})

screen_failure.set_src(screen_failure_img)
screen_failure.set_pivot(0,0)
screen_failure.set_angle(0)
# create style style_screen_failure_main_main_default
style_screen_failure_main_main_default = lv.style_t()
style_screen_failure_main_main_default.init()
style_screen_failure_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_failure_main_main_default.set_img_recolor_opa(0)
style_screen_failure_main_main_default.set_img_opa(205)

# add style for screen_failure
screen_failure.add_style(style_screen_failure_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_success = lv.img(windows_lock)
screen_success.set_pos(int(140),int(110))
screen_success.set_size(200,100)
screen_success.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_success.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-812770416.png','rb') as f:
        screen_success_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\RC522\\generated\\mPythonImages\\mp-812770416.png')
    sys.exit()

screen_success_img = lv.img_dsc_t({
  'data_size': len(screen_success_img_data),
  'header': {'always_zero': 0, 'w': 200, 'h': 100, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_success_img_data
})

screen_success.set_src(screen_success_img)
screen_success.set_pivot(0,0)
screen_success.set_angle(0)
# create style style_screen_success_main_main_default
style_screen_success_main_main_default = lv.style_t()
style_screen_success_main_main_default.init()
style_screen_success_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_success_main_main_default.set_img_recolor_opa(0)
style_screen_success_main_main_default.set_img_opa(205)

# add style for screen_success
screen_success.add_style(style_screen_success_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

windows_settings = screen_windows.add_tile(2 , 0, lv.DIR.LEFT)
screen_loaderase = lv.spinner(windows_settings, 1000, 60)
screen_loaderase.set_pos(int(374),int(149))
screen_loaderase.set_size(67,51)
screen_loaderase.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_loaderase_main_main_default
style_screen_loaderase_main_main_default = lv.style_t()
style_screen_loaderase_main_main_default.init()
style_screen_loaderase_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_screen_loaderase_main_main_default.set_bg_grad_color(lv.color_make(0xee,0xee,0xf6))
style_screen_loaderase_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_loaderase_main_main_default.set_bg_opa(255)
style_screen_loaderase_main_main_default.set_pad_left(5)
style_screen_loaderase_main_main_default.set_pad_right(5)
style_screen_loaderase_main_main_default.set_pad_top(5)
style_screen_loaderase_main_main_default.set_pad_bottom(5)
style_screen_loaderase_main_main_default.set_arc_color(lv.color_make(0xb2,0xb2,0xae))
style_screen_loaderase_main_main_default.set_arc_width(6)

# add style for screen_loaderase
screen_loaderase.add_style(style_screen_loaderase_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_loaderase_main_indicator_default
style_screen_loaderase_main_indicator_default = lv.style_t()
style_screen_loaderase_main_indicator_default.init()
style_screen_loaderase_main_indicator_default.set_arc_color(lv.color_make(0x21,0x95,0xf6))
style_screen_loaderase_main_indicator_default.set_arc_width(12)

# add style for screen_loaderase
screen_loaderase.add_style(style_screen_loaderase_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

screen_open = lv.btn(windows_settings)
screen_open.set_pos(int(108),int(237))
screen_open.set_size(276,38)
screen_open.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_open_label = lv.label(screen_open)
screen_open_label.set_text("OPEN")
screen_open.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_open_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_open_main_main_default
style_screen_open_main_main_default = lv.style_t()
style_screen_open_main_main_default.init()
style_screen_open_main_main_default.set_radius(5)
style_screen_open_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_open_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_open_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_open_main_main_default.set_bg_opa(255)
style_screen_open_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_open_main_main_default.set_border_width(0)
style_screen_open_main_main_default.set_border_opa(255)
style_screen_open_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_open_main_main_default.set_text_font(lv.font_Acme_Regular_30)
except AttributeError:
    try:
        style_screen_open_main_main_default.set_text_font(lv.font_montserrat_30)
    except AttributeError:
        style_screen_open_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_open_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_open
screen_open.add_style(style_screen_open_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_erasetxt = lv.label(windows_settings)
screen_erasetxt.set_pos(int(185),int(164))
screen_erasetxt.set_size(164,28)
screen_erasetxt.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_erasetxt.set_text("Executive erase...")
screen_erasetxt.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_erasetxt_main_main_default
style_screen_erasetxt_main_main_default = lv.style_t()
style_screen_erasetxt_main_main_default.init()
style_screen_erasetxt_main_main_default.set_radius(0)
style_screen_erasetxt_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_erasetxt_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_erasetxt_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_erasetxt_main_main_default.set_bg_opa(0)
style_screen_erasetxt_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_erasetxt_main_main_default.set_text_font(lv.font_Acme_Regular_16)
except AttributeError:
    try:
        style_screen_erasetxt_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_erasetxt_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_erasetxt_main_main_default.set_text_letter_space(2)
style_screen_erasetxt_main_main_default.set_text_line_space(0)
style_screen_erasetxt_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_erasetxt_main_main_default.set_pad_left(0)
style_screen_erasetxt_main_main_default.set_pad_right(0)
style_screen_erasetxt_main_main_default.set_pad_top(0)
style_screen_erasetxt_main_main_default.set_pad_bottom(0)

# add style for screen_erasetxt
screen_erasetxt.add_style(style_screen_erasetxt_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_erase = lv.btn(windows_settings)
screen_erase.set_pos(int(46),int(153))
screen_erase.set_size(100,40)
screen_erase.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_erase_label = lv.label(screen_erase)
screen_erase_label.set_text("Erase All")
screen_erase.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_erase_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_erase_main_main_default
style_screen_erase_main_main_default = lv.style_t()
style_screen_erase_main_main_default.init()
style_screen_erase_main_main_default.set_radius(5)
style_screen_erase_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_erase_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_erase_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_erase_main_main_default.set_bg_opa(255)
style_screen_erase_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_erase_main_main_default.set_border_width(0)
style_screen_erase_main_main_default.set_border_opa(255)
style_screen_erase_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_erase_main_main_default.set_text_font(lv.font_Acme_Regular_20)
except AttributeError:
    try:
        style_screen_erase_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_erase_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_erase_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_erase
screen_erase.add_style(style_screen_erase_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_load = lv.spinner(windows_settings, 1000, 60)
screen_load.set_pos(int(373),int(73))
screen_load.set_size(67,50)
screen_load.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_load_main_main_default
style_screen_load_main_main_default = lv.style_t()
style_screen_load_main_main_default.init()
style_screen_load_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_screen_load_main_main_default.set_bg_grad_color(lv.color_make(0xee,0xee,0xf6))
style_screen_load_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_load_main_main_default.set_bg_opa(255)
style_screen_load_main_main_default.set_pad_left(5)
style_screen_load_main_main_default.set_pad_right(5)
style_screen_load_main_main_default.set_pad_top(5)
style_screen_load_main_main_default.set_pad_bottom(5)
style_screen_load_main_main_default.set_arc_color(lv.color_make(0xb5,0xb6,0xba))
style_screen_load_main_main_default.set_arc_width(6)

# add style for screen_load
screen_load.add_style(style_screen_load_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_load_main_indicator_default
style_screen_load_main_indicator_default = lv.style_t()
style_screen_load_main_indicator_default.init()
style_screen_load_main_indicator_default.set_arc_color(lv.color_make(0x21,0x95,0xf6))
style_screen_load_main_indicator_default.set_arc_width(12)

# add style for screen_load
screen_load.add_style(style_screen_load_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

screen_wait = lv.label(windows_settings)
screen_wait.set_pos(int(187),int(87))
screen_wait.set_size(160,37)
screen_wait.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_wait.set_text("Waiting for Card...")
screen_wait.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_wait_main_main_default
style_screen_wait_main_main_default = lv.style_t()
style_screen_wait_main_main_default.init()
style_screen_wait_main_main_default.set_radius(0)
style_screen_wait_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wait_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wait_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_wait_main_main_default.set_bg_opa(0)
style_screen_wait_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_wait_main_main_default.set_text_font(lv.font_Acme_Regular_16)
except AttributeError:
    try:
        style_screen_wait_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_wait_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_wait_main_main_default.set_text_letter_space(2)
style_screen_wait_main_main_default.set_text_line_space(0)
style_screen_wait_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_wait_main_main_default.set_pad_left(0)
style_screen_wait_main_main_default.set_pad_right(0)
style_screen_wait_main_main_default.set_pad_top(0)
style_screen_wait_main_main_default.set_pad_bottom(0)

# add style for screen_wait
screen_wait.add_style(style_screen_wait_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_add = lv.btn(windows_settings)
screen_add.set_pos(int(46),int(77))
screen_add.set_size(100,40)
screen_add.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_add_label = lv.label(screen_add)
screen_add_label.set_text("ADD NEW")
screen_add.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_add_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_add_main_main_default
style_screen_add_main_main_default = lv.style_t()
style_screen_add_main_main_default.init()
style_screen_add_main_main_default.set_radius(5)
style_screen_add_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_add_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_add_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_add_main_main_default.set_bg_opa(255)
style_screen_add_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_add_main_main_default.set_border_width(0)
style_screen_add_main_main_default.set_border_opa(255)
style_screen_add_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_add_main_main_default.set_text_font(lv.font_Acme_Regular_20)
except AttributeError:
    try:
        style_screen_add_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_add_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_add_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_add
screen_add.add_style(style_screen_add_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_admin = lv.btn(windows_settings)
screen_admin.set_pos(int(141),int(292))
screen_admin.set_size(212,24)
screen_admin.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_admin_label = lv.label(screen_admin)
screen_admin_label.set_text("Administrator Permission Authentication")
screen_admin.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_admin_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_admin_main_main_default
style_screen_admin_main_main_default = lv.style_t()
style_screen_admin_main_main_default.init()
style_screen_admin_main_main_default.set_radius(5)
style_screen_admin_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_admin_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_admin_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_admin_main_main_default.set_bg_opa(255)
style_screen_admin_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_admin_main_main_default.set_border_width(0)
style_screen_admin_main_main_default.set_border_opa(255)
style_screen_admin_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_admin_main_main_default.set_text_font(lv.font_Acme_Regular_12)
except AttributeError:
    try:
        style_screen_admin_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_admin_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_admin_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_admin
screen_admin.add_style(style_screen_admin_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_settingtxt = lv.label(windows_settings)
screen_settingtxt.set_pos(int(0),int(0))
screen_settingtxt.set_size(480,30)
screen_settingtxt.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_settingtxt.set_text("Settings")
screen_settingtxt.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_settingtxt_main_main_default
style_screen_settingtxt_main_main_default = lv.style_t()
style_screen_settingtxt_main_main_default.init()
style_screen_settingtxt_main_main_default.set_radius(0)
style_screen_settingtxt_main_main_default.set_bg_color(lv.color_make(0x21,0x21,0x21))
style_screen_settingtxt_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_settingtxt_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_settingtxt_main_main_default.set_bg_opa(255)
style_screen_settingtxt_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_settingtxt_main_main_default.set_text_font(lv.font_Acme_Regular_20)
except AttributeError:
    try:
        style_screen_settingtxt_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_settingtxt_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_settingtxt_main_main_default.set_text_letter_space(2)
style_screen_settingtxt_main_main_default.set_text_line_space(0)
style_screen_settingtxt_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_settingtxt_main_main_default.set_pad_left(0)
style_screen_settingtxt_main_main_default.set_pad_right(0)
style_screen_settingtxt_main_main_default.set_pad_top(0)
style_screen_settingtxt_main_main_default.set_pad_bottom(0)

# add style for screen_settingtxt
screen_settingtxt.add_style(style_screen_settingtxt_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_windows_main_main_default
style_screen_windows_main_main_default = lv.style_t()
style_screen_windows_main_main_default.init()
style_screen_windows_main_main_default.set_radius(0)
style_screen_windows_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_screen_windows_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_screen_windows_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_windows_main_main_default.set_bg_opa(255)

# add style for screen_windows
screen_windows.add_style(style_screen_windows_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_windows_main_scrollbar_default
style_screen_windows_main_scrollbar_default = lv.style_t()
style_screen_windows_main_scrollbar_default.init()
style_screen_windows_main_scrollbar_default.set_radius(0)
style_screen_windows_main_scrollbar_default.set_bg_color(lv.color_make(0xea,0xef,0xf3))
style_screen_windows_main_scrollbar_default.set_bg_opa(255)

# add style for screen_windows
screen_windows.add_style(style_screen_windows_main_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)

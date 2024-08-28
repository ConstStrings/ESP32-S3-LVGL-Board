import cv2
import pyautogui
import numpy as np
import serial

serial_port = 'COM5'  # 替换为你的串口号，例如 'COM3' 或 '/dev/ttyUSB0'
baud_rate = 512000  # 根据你的需求设置波特率


def screenshot():
    img = pyautogui.screenshot()
    img.save('screenshot.png')
    return img


def convert_to_16bit_array(image):
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # 初始化RGB565图像数组
    height, width = image_rgb.shape[:2]
    image_rgb565 = np.zeros((height, width), dtype = np.uint16)

    # RGB888转RGB565
    for i in range(height):
        for j in range(width):
            r = image_rgb[i, j, 0] >> 3
            g = image_rgb[i, j, 1] >> 2
            b = image_rgb[i, j, 2] >> 3
            rgb565 = np.uint16((np.uint16(r) << 11) | (np.uint16(g) << 5) | b)
            image_rgb565[i, j] = rgb565

    # 将RGB565图像转为8位数组
    output_array = image_rgb565.flatten()

    # 分成高字节和低字节
    high_byte = (output_array >> 8).astype(np.uint8)
    low_byte = (output_array & 0xFF).astype(np.uint8)

    # 合并成8位数组
    output_8bit_array = np.zeros(output_array.size * 2, dtype = np.uint8)
    output_8bit_array[0::2] = high_byte
    output_8bit_array[1::2] = low_byte

    return output_8bit_array


def send_serial(data):
    try:
        with serial.Serial(serial_port, baud_rate, timeout = 100000) as ser:
            ser.write(data)
            print(f"Successfully sent {len(data)} bytes of data.")
    except serial.SerialException as e:
        print(f"Error: {e}")

while True:
    screenshot()
    # 设置图片路径和目标尺寸
    image_path = 'screenshot.png'
    width = 480
    height = 320

    img = cv2.imread(image_path)
    resized_img = cv2.resize(img, (width, height))
    # 转换为16位数组
    image_16bit_array = convert_to_16bit_array(resized_img)

    # np.savetxt('image_16bit_array.txt', image_16bit_array, fmt = '%d')

    send_serial(image_16bit_array)

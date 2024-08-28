/*

 Example sketch for TFT_eSPI library.

 No fonts are needed.
 
 Draws a 3d rotating cube on the TFT screen.
 
 Original code was found at http://forum.freetronics.com/viewtopic.php?f=37&t=5495
 
 */

#define BLACK 0x0000
#define WHITE 0xFFFF

#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

int16_t h;
int16_t w;

const int dataLength = 960; // 数据长度
byte receivedData[dataLength]; // 用于存储接收到的数据
int receivedBytes = 0; // 已接收的字节数


void processData(byte* data, int length) {
  static int row = 0;
  for (int i = 0; i < 480; i++)
  {
    uint16_t pix = (((uint16_t)data[i * 2] << 8) | (uint16_t)data[i * 2 + 1]);
    tft.drawPixel(i, row, pix);
  }
  row++;
  if(row == 320)
  {
    row = 0;
  }
}


/***********************************************************************************************************************************/
void setup() {
  Serial.begin(512000);
  tft.init();

  h = tft.height();
  w = tft.width();

  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  //tft.drawChar(0, 0, 'A', TFT_WHITE, TFT_BLACK, 2);
  //tft.drawBitmap(0, 0, color, 480, 320,TFT_BLACK);
}

/***********************************************************************************************************************************/
void loop() {
  while (Serial.available() > 0 && receivedBytes < dataLength) {
    receivedData[receivedBytes] = Serial.read(); // 读取一个字节并存储到数组中
    receivedBytes++;
  }

  // 当接收到960字节的数据时，进行处理
  if (receivedBytes == dataLength) {
    processData(receivedData, dataLength); // 处理数据的函数
    receivedBytes = 0; // 重置已接收字节数，以便下次接收
  }
}


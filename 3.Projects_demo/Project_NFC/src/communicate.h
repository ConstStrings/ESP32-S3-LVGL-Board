#pragma once
#include <Arduino.h>
#include <Wire.h>

//============ASK COMMAND=============
#define NEW_UID 0x01
#define OPEN 0x02
#define ERASE_CHIP 0x03
#define ADMIN 0x04
#define ASK_NUM 0x05

//===========REPLY COMMAND============
#define NEW_UID_DONE 0x01
#define NEW_UID_FAIL 0x02
#define OPEN_DONE 0x03
#define CLOSE_DONE 0x04
#define ERASE_DONE 0x05
#define LOAD_FINISH 0x06
#define ADMIN_OK 0x07
#define ADMIN_FAIL 0x08
#define USER_S 0x09
#define USER_F 0x0A

void communicate_init();
void communicate_ask(uint8_t command);
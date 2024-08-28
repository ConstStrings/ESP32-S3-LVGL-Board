#include "communicate.h"

uint8_t buffer[1] = {0};

void communicate_init()
{
    Serial2.begin(9600);

}

void communicate_ask(uint8_t command)
{
    buffer[0] = command;
    Serial2.write(buffer,1);
    buffer[0] = 0;
}


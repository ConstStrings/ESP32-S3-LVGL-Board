#ifndef __TIMER_H__
#define __TIMER_H__

//extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。
//加上extern "C"后，会指示编译器这部分代码按C语言（而不是C++）的方式进行编译。
#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>

void Timer0_Init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
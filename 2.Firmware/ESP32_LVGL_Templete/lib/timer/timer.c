#include "timer.h"
#include <lvgl.h>

hw_timer_t * timer = NULL;

void Timer0_IRQ() //1ms中断一次
{
    lv_tick_inc(1); //提供LVGL运行的心跳包
}

void Timer0_Init()
{
  timer = timerBegin(0, 80, true);  //1MHZ,向上计数
  timerAttachInterrupt(timer, &Timer0_IRQ, true);  //开定时器中断
  timerAlarmWrite(timer, 1000, true); //溢出值1000，自动重装载
  timerAlarmEnable(timer);//使能定时器报警功能
}
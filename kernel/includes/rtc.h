//https://wiki.osdev.org/CMOS#Accessing_CMOS_Registers
#pragma once
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>

#define RTC_COMMAND 0x70
#define RTC_DATA 0x71

#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04   //   Hours, highest bit tells us am/pm or military time
#define RTC_DAY  0x07    //day of month not weekday
#define RTC_MONTH  0x08  
#define RTC_YEAR  0x09 
#define RTC_FREQ 0x8A // set the high bit to disable interrupts 
#define RTC_ENABLE 0x8B // again set high bit to disable interrupts

#define EST -5
#define CST -6
#define PST -7
#define GMT 0

static int current_timezone = GMT;
/***
 * @param freq
*/
void set_rtc_freq(uint16_t freq); 

void start_rtc();
void rtc_display_clock();

void set_timezone(int timezone_offset);
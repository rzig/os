#include "../includes/rtc.h"

void start_rtc() {
  asm volatile("cli");
  outb(RTC_COMMAND, 0x8B);
  uint8_t curr = inb(RTC_DATA);
  outb(RTC_COMMAND, 0x8B);
  outb(RTC_DATA, curr | (0x40));
}

void set_rtc_freq(uint16_t freq) {
  asm volatile("cli");
  int freql2 = intLog2(freq);
  int rate = intLog2(32768) - freql2 + 1;
  printf("calculated rate is: %h\n", rate);
  printf("int log 2 of freq is: %h\n", freql2);
  rate &= 0x0F;
  outb(RTC_COMMAND, 0x8A);
  uint8_t curr = inb(RTC_DATA);
  outb(RTC_COMMAND, 0x8A);
  outb(RTC_DATA, (curr & 0xF0) | rate);
  asm volatile("sti");
}

void set_timezone(int timezone_offset) { current_timezone = timezone_offset; }

void rtc_display_clock() {
  outb(RTC_COMMAND, 0x0B);
  io_wait();
  uint8_t reg_flags = inb(RTC_DATA);
  io_wait();
  bool binary_mode = reg_flags & 0b100;
  uint8_t military_time = reg_flags & 0b10;
  outb(RTC_COMMAND, RTC_MINUTES);
  io_wait();
  uint8_t minutes = inb(RTC_DATA);
  io_wait();
  outb(RTC_COMMAND, RTC_HOURS);
  io_wait();
  uint8_t hours = inb(RTC_DATA);
  io_wait();
  outb(RTC_COMMAND, RTC_DAY);
  io_wait();
  uint8_t day = inb(RTC_DATA);
  io_wait();
  outb(RTC_COMMAND, RTC_MONTH);
  io_wait();
  uint8_t month = inb(RTC_DATA);
  io_wait();
  outb(RTC_COMMAND, RTC_YEAR);
  io_wait();
  uint8_t year = inb(RTC_DATA);
  io_wait();
  if (!binary_mode) {
    if (!military_time && (hours & 0x80)) {
      hours = ((hours >> 4) * 10) + (hours % 16); // convert back to decimal
      hours += current_timezone;
      if (minutes >= 10) {
        printf_top("%d:%hpm  %h/%h/%h", hours, minutes, month, day, year);
      } else {
        printf_top("%d:0%hpm  %h/%h/%h", hours, minutes, month, day, year);
      }
    } else {
      hours = ((hours >> 4) * 10) + (hours % 16); // convert back to decimal
      hours += current_timezone;
      if (minutes >= 10) {
        printf_top("%d:%h  %h/%h/%h", hours, minutes, month, day, year);
      } else {
        printf_top("%d:0%h  %h/%h/%h", hours, minutes, month, day, year);
      }
    }
  } else {
    if (!military_time && (hours & 0x80)) {
      hours &= 0x1F;
      hours += current_timezone;
      if (minutes >= 10) {
        printf_top("%d:%dpm  %d/%d/%d", hours, minutes, month, day, year);
      } else {
        printf_top("%d:0%dpm  %d/%d/%d", hours, minutes, month, day, year);
      }
    } else {
      hours += current_timezone;
      if (minutes >= 10) {
        printf_top("%d:%d  %d/%d/%d", hours, minutes, month, day, year);
      } else {
        printf_top("%d:0%d  %d/%d/%d", hours, minutes, month, day, year);
      }
    }
  }
}

#include "../includes/user_isr.h"
#include "../includes/syscalls.h"

void execute_user_int(exn_info int_data) {
  int int_number = int_data.int_number;
  if (int_number == 0x80) {
    handle_syscall(int_data);
  }
  else if (int_number != 32) {
    if (int_number != 39 && int_number != 47) {
      if (int_number == 33) { // keyboard
        uint8_t scan_code = inb(0x60);
        uint16_t out_char = atkbd_set1_keycode[scan_code];
        uint16_t res = keyboard_parsekey(out_char);
        // printf(" %d ", res);
        bool common = false;
        if (res < 128 && res != 0) {
          terminal_putchar(res);
          common = true;
        } else if (out_char == SPACE_PRESSED) {
          terminal_putchar(0);
          common = true;
        } else if (out_char == BACKSPACE_PRESSED) {
          terminal_remove_last();
          common = true;
        }
        //move the cursor
        if (common) {
          outb(0x3D4, 0x0F);
          int index = get_terminal_row() * VGA_WIDTH + get_terminal_column();
          outb(0x3D5, (uint8_t) (index & 0xFF));
          outb(0x3D4, 0x0E);
          outb(0x3D5, (uint8_t) ((index >> 8) & 0xFF));
        }
      } else if (int_number == 40) { // rtc
        outb(0x70, 0x0C);
        inb(0x71);
        rtc_display_clock();
      }
      PIC_sendEOI(int_number - 32);
    } else {
      // handle spurious irqs later
    }
  } else {
    PIC_sendEOI(int_number - 32);
  }
}

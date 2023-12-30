#include "../includes/keyboard.h"

static bool shift_on = false;
static bool control_on = false;
static bool caps_lock_on = false;
static bool num_lock_on = false;

static unsigned char alpha_top = 'a';
static unsigned char alpha_bottom = 'z';
static int alpha_offset = 'a' - 'A';

void keyboard_init() {
  outb(0x64, 0xAD); // disable PS2 dev0
  io_wait();
  outb(0x64, 0xA7); // disable PS2 dev1
  io_wait();
  inb(0x60);
  io_wait();        // flush buffer
  outb(0x64, 0x20); // tell the PS2 Controller that we want to read
  uint8_t config = inb(0x60);
  bool dual_ps2 = config & 0b10000;
  if (dual_ps2) {
    printf("we have a dually\n");
  }
  outb(0x64, 0x60);
  uint8_t new_config = config & 0b10111100;
  io_wait();
  outb(0x60, new_config);
  io_wait();

  outb(0x64, 0xAA); // check status
  io_wait();

  uint8_t temp = inb(0x60);
  io_wait();
  if (temp != 0x55) {
    return; // PS2 failed
  }
  outb(0x64, 0xAB); // test first ps2
  io_wait();
  uint8_t ftest_res = inb(0x60);
  io_wait();
  if (ftest_res) {
    printf("init ps2 failed\n");
    return;
  }
  if (dual_ps2) {
    outb(0x64, 0xA9); // test second ps2
    io_wait();
    uint8_t ftest_sec = inb(0x60);
    io_wait();
    if (ftest_sec) {
      printf("init ps2 failed\n");
    }
  }

  outb(0x64, 0xAE); // enable dev0
  io_wait();
  outb(0x64, 0xA8); // enable dev2
  io_wait();
  if (dual_ps2) {
    outb(0x64, 0x20); // tell the PS2 Controller that we want to read
    io_wait();
    uint8_t config = inb(0x60);
    io_wait();
    config = config | 0b00000011; // enable both
    outb(0x64, 0x60);
    io_wait();
    outb(0x60, config);
  } else {
    outb(0x64, 0x20); // tell the PS2 Controller that we want to read
    io_wait();
    uint8_t config = inb(0x60);
    io_wait();
    config = config | 0b00000001; // enable both
    outb(0x64, 0x60);
    io_wait();
    outb(0x60, config);
  }

  outb(0x60, 0xF0);
  outb(0x60, 0x01);
  uint8_t status = inb(0x60);

  printf("finished ps2 init\n");
}

uint16_t keyboard_parsekey(uint16_t key) {
  if (key == CAPS_LOCK_PRESSED) {
    caps_lock_on = ~caps_lock_on;
  } else if (key == NUMLOCK_PRESSED) {
    num_lock_on = ~num_lock_on;
  } else if (key == SHIFT_PRESSED) {
    shift_on = true;
  } else if (key == SHIFT_RELEASED) {
    shift_on = false;
  } else if (caps_lock_on || shift_on) {
    if (key >= alpha_top && key <= alpha_bottom) {
      key -= alpha_offset;
    } else if (key == '1') {
      key = '!';
    } else if (key == '2') {
      key = '@';
    } else if (key == '3') {
      key = '~';
    } else if (key == '4') {
      key = '$';
    } else if (key == '5') {
      key = '%';
    } else if (key == '6') {
      key = '^';
    } else if (key == '7') {
      key = '&';
    } else if (key == '8') {
      key = '*';
    } else if (key == '9') {
      key = '(';
    } else if (key == '0') {
      key = ')';
    } else if (key == '-') {
      key = '_';
    } else if (key == '+') {
      key = '=';
    } else if (key == '[') {
      key = '{';
    } else if (key == ']') {
      key = '}';
    } else if (key == '\\') {
      key = '|';
    } else if (key == ';') {
      key = ':';
    } else if (key == '\'') {
      key = '\"';
    } else if (key == ',') {
      key = '<';
    } else if (key == '.') {
      key = '>';
    } else if (key == '/') {
      key = '?';
    }
  } else if (num_lock_on) {
    if (key == ONEKP_PRESSED) {
      key = '1';
    } else if (key == TWOKP_PRESSED) {
      key = '2';
    } else if (key == THREEKP_PRESSED) {
      key = '3';
    } else if (key == FOURKP_PRESSED) {
      key = '4';
    } else if (key == FIVEKP_PRESSED) {
      key = '5';
    } else if (key == SIXKP_PRESSED) {
      key = '6';
    } else if (key == SEVENKP_PRESSED) {
      key = '7';
    } else if (key == EIGHTKP_PRESSED) {
      key = '8';
    } else if (key == NINEKP_PRESSED) {
      key = '9';
    } else if (key == ZEROKP_PRESSED) {
      key = '0';
    } else if (key == PERIODKP_PRESSED) {
      key = '.';
    } else if (key == PLUSKP_PRESSED) {
      key = '+';
    } else if (key == MINUSKP_PRESSED) {
      key = '-';
    }
  }

  return key;
}

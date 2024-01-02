#include "../includes/utilities.h"

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;
static char last_char;

void terminal_initialize(void) {
  terminal_row = 1; // reserve the top row for the date
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *)0xC00B8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_remove_last() {
  if (terminal_column == 0) {
    if (terminal_row > 1) {
      terminal_row--;
      terminal_column = VGA_WIDTH - 1;
    }
  } else {
    terminal_column--;
  }
  terminal_putentryat(0, terminal_color, terminal_column, terminal_row);
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_row++;
    terminal_column = 0;
    if (terminal_row > VGA_HEIGHT) {
      terminal_row = 0;
    }
  } else if (c == '\t') {
    for (int i = 0; i < TAB_LENGTH; i++) {
      terminal_column++;
      if (terminal_column > VGA_WIDTH)
        terminal_column = 0;
    }
  } else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT)
        terminal_row = 1; // reserve the top row for the date
    }
  }
  last_char = c;
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}

void itoa(char *buf, int base, int d) {
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;

  /* If %d is specified and D is minus, put ‘-’ in the head. */
  if (base == 'd' && d < 0) {
    *p++ = '-';
    buf++;
    ud = -d;
  } else if (base == 'x')
    divisor = 16;

  /* Divide UD by DIVISOR until UD == 0. */
  do {
    int remainder = ud % divisor;

    *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
  } while (ud /= divisor);

  /* Terminate BUF. */
  *p = 0;

  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2) {
    char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    p1++;
    p2--;
  }
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

void *memset(void *s, int c, size_t n) {
  uint8_t *casted_s = (uint8_t *)s;
  for (size_t i = 0; i < n; i++) {
    casted_s[i] = (uint8_t)c; // this operates at the byte level
  }
}
void *memcpy(void *dest, const void *src, size_t n) {
  uint8_t *casted_src = (uint8_t *)src;
  uint8_t *casted_dest = (uint8_t *)dest;
  for (size_t i = 0; i < n; i++) {
    casted_dest[i] = casted_src[i];
  }
}
int memcmp(const void *s1, const void *s2, size_t n) {
  unsigned char *casted_s1 = (unsigned char *)s1;
  unsigned char *casted_s2 = (unsigned char *)s2;
  for (size_t i = 0; i < n; i++) {
    if (casted_s1[i] != casted_s2[i]) {
      return casted_s1 - casted_s2;
    }
  }
  return 0;
}

void printf(char *format, ...) {
  char **arg_ptr = &format;
  arg_ptr++;
  char int_buffer[32];
  for (size_t i = 0; i < strlen(format); i++) {
    if (format[i] != '%') {
      terminal_putchar(format[i]);
    } else {
      i++;
      char curr = format[i];
      switch (curr) {
      case 'p':
        terminal_putchar('0');
        terminal_putchar('x');
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'x', *(((int *)arg_ptr)));
        for (size_t i = 0; i < PTR_WIDTH - strlen(int_buffer); i++) {
          terminal_putchar('0');
        }
        arg_ptr++;
        int ptr_idx = 0;
        while (int_buffer[ptr_idx] != 0) {
          terminal_putchar(int_buffer[ptr_idx]);
          ptr_idx++;
        }
        break;
      case 'h':
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'x', *(((int *)arg_ptr)));
        arg_ptr++;
        int hex_idx = 0;
        while (int_buffer[hex_idx] != 0) {
          terminal_putchar(int_buffer[hex_idx]);
          hex_idx++;
        }
        break;
      case 'd':
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'd', *(((int *)arg_ptr)));
        arg_ptr++;
        int int_idx = 0;
        while (int_buffer[int_idx] != 0) {
          terminal_putchar(int_buffer[int_idx]);
          int_idx++;
        }
        break;
      case 's':
        char *curr_str = *arg_ptr;
        while (*curr_str != 0) {
          terminal_putchar(*curr_str);
          curr_str++;
        }
        arg_ptr++;
        break;
      default:
        terminal_writestring("error in printf\n");
        break;
      }
    }
  }
}

void printf_top(char *format, ...) {
  char **arg_ptr = &format;
  arg_ptr++;
  char int_buffer[32];
  int column_old = terminal_column;
  int row_old = terminal_row;
  terminal_column = 0;
  terminal_row = 0;
  for (size_t i = 0; i < strlen(format); i++) {
    if (format[i] != '%') {
      terminal_putchar(format[i]);
    } else {
      i++;
      char curr = format[i];
      switch (curr) {
      case 'p':
        terminal_putchar('0');
        terminal_putchar('x');
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'x', *(((int *)arg_ptr)));
        for (size_t i = 0; i < PTR_WIDTH - strlen(int_buffer); i++) {
          terminal_putchar('0');
        }
        arg_ptr++;
        int ptr_idx = 0;
        while (int_buffer[ptr_idx] != 0) {
          terminal_putchar(int_buffer[ptr_idx]);
          ptr_idx++;
        }
        break;
      case 'h':
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'x', *(((int *)arg_ptr)));
        arg_ptr++;
        int hex_idx = 0;
        while (int_buffer[hex_idx] != 0) {
          terminal_putchar(int_buffer[hex_idx]);
          hex_idx++;
        }
        break;
      case 'd':
        memset(int_buffer, 0, 32);
        itoa(int_buffer, 'd', *(((int *)arg_ptr)));
        arg_ptr++;
        int int_idx = 0;
        while (int_buffer[int_idx] != 0) {
          terminal_putchar(int_buffer[int_idx]);
          int_idx++;
        }
        break;
      case 's':
        char *curr_str = *arg_ptr;
        while (*curr_str != 0) {
          terminal_putchar(*curr_str);
          curr_str++;
        }
        arg_ptr++;
        break;
      default:
        terminal_writestring("error in printf\n");
        break;
      }
    }
  }
  terminal_column = column_old;
  terminal_row = row_old;
}

int intLog2(int input) {
  int count = 0;
  while (input) {
    count++;
    input = input >> 1;
  }
  return count;
}

int strcmp(const char *s1, const char *s2) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

  while (*p1 && *p1 == *p2)
    ++p1, ++p2;

  return (*p1 > *p2) - (*p2 > *p1);
}

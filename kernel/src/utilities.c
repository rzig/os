#include "../includes/utilities.h"

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

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
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}

void _itoa(int num, char *buffer, unsigned int base, char is_signed) {
  // base cases :)
  if (base == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }
  if (base > 32) {
    buffer[0] = '\0';
    return;
  }

  char *p = buffer;
  unsigned int divisor = base;

  if (is_signed && num < 0) {
    *p++ = '-';
    buffer++;
    num = -num;
  }

  /* Divide num by divisor until num == 0. */
  do {
    int remainder = num % divisor;
    *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
  } while (num /= divisor);

  /* Terminate BUF. */
  *p = 0;

  /* Reverse BUF. */
  char *p1 = buffer, *p2 = p - 1;
  while (p1 < p2) {
    char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    p1++;
    p2--;
  }
}

void itoa(int num, char *buffer, int base) {
  _itoa(num, buffer, base, 1);
}

void uitoa(unsigned int num, char *buffer, int base) {
  _itoa(num, buffer, base, 0);
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

void *memset(void *s, int c, size_t n) {
  uint64_t *long_s = (uint64_t *)s;
  size_t blocks = n >> 3;
  // construct mask
  uint64_t c_mask = ((uint64_t)c << 56) | ((uint64_t)c << 48) | ((uint64_t)c << 40) 
                  | ((uint64_t)c << 32) | ((uint64_t)c << 24) | ((uint64_t)c << 16) 
                  | ((uint64_t)c << 8)  | (uint64_t)c;
  for (size_t i = 0; i < blocks; ++i) {
    long_s[i] = c_mask;
  }
  // n is multiple of 8
  size_t n_complete = blocks << 3;
  if (n_complete == n) return s;

  // set remainder byte-wise
  uint8_t *byte_s = (uint8_t *)s;
  for (size_t i = n_complete; i < n; ++i) {
    byte_s[i] = (uint8_t)c;
  }
  return s;
}

void *memcpy(void *dest, const void *src, size_t n) {
  uint64_t *long_src = (uint64_t *)src;
  uint64_t *long_dest = (uint64_t *)dest;
  size_t blocks = n >> 3;
  for (size_t i = 0; i < blocks; ++i) {
    long_dest[i] = long_src[i];
  }
  // n is multiple of 8
  size_t n_complete = blocks << 3;
  if (n_complete == n) return dest;

  // set remainder byte-wise
  uint8_t *byte_src = (uint8_t *)src;
  uint8_t *byte_dest = (uint8_t *)dest;
  for (size_t i = n_complete; i < n; ++i) {
    byte_dest[i] = byte_src[i];
  }
  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  uint64_t *long_s1 = (uint64_t *)s1;
  uint64_t *long_s2 = (uint64_t *)s2;
  size_t blocks = n >> 3;
  for (size_t i = 0; i < blocks; ++i) {
    if (long_s1[i] != long_s2[i]) {
      return long_s1 - long_s2;
    }
  }
  // n is multiple of 8
  size_t n_complete = blocks << 3;
  if (n_complete == n) return 0;

  // set remainder byte-wise
  uint8_t *byte_s1 = (uint8_t *)s1;
  uint8_t *byte_s2 = (uint8_t *)s2;
  for (size_t i = n_complete; i < n; ++i) {
    if (byte_s1[i] != byte_s2[i]) {
      return byte_s1 - byte_s2;
    }
  }
  return 0;
}

// void printf(char *format, ...) {
//   char **arg_ptr = &format;
//   arg_ptr++;
//   char value_buffer[32];
//   for (size_t i = 0; i < strlen(format); i++) {
//     if (format[i] != '%') {
//       terminal_putchar(format[i]);
//       continue;
//     }
//     // read next char and clear buffer
//     char curr = format[++i];
//     memset(value_buffer, 0, 32);
//     switch (curr) {
//       case 'p':
//         terminal_write("0x", 2);
//         itoa(*((int *)arg_ptr++), value_buffer, 16);
//         // write leading zeros
//         for (size_t i = 0; i < PTR_WIDTH - strlen(value_buffer); i++) {
//           terminal_putchar('0');
//         }
//         terminal_writestring(value_buffer);
//         break;
//       case 'h':
//         itoa(*((int *)arg_ptr++), value_buffer, 16);
//         terminal_writestring(value_buffer);
//         break;
//       case 'd':
//         itoa(*((int *)arg_ptr++), value_buffer, 10);
//         terminal_writestring(value_buffer);
//         break;
//       case 'u':
//         uitoa(*((unsigned int *)arg_ptr++), value_buffer, 10);
//         terminal_writestring(value_buffer);
//         break;
//       case 's':
//         char *str = *arg_ptr++;
//         terminal_writestring(str);
//         break;
//       default:
//         terminal_writestring("error in printf\n");
//         break;
      
//     }
//   }
// }

// strongly disapprove of this function's existence -_-
// void printf_top(char *format, ...) {
//   char **arg_ptr = &format;
//   arg_ptr++;
//   char value_buffer[32];
//   int column_old = terminal_column;
//   int row_old = terminal_row;
//   terminal_column = 0;
//   terminal_row = 0;
//   for (size_t i = 0; i < strlen(format); i++) {
//     if (format[i] != '%') {
//       terminal_putchar(format[i]);
//       continue;
//     }
//     // read next char and clear buffer
//     char curr = format[++i];
//     memset(value_buffer, 0, 32);
//     switch (curr) {
//       case 'p':
//         terminal_write("0x", 2);
//         itoa(*((int *)arg_ptr++), value_buffer, 16);
//         // write leading zeros
//         for (size_t i = 0; i < PTR_WIDTH - strlen(value_buffer); i++) {
//           terminal_putchar('0');
//         }
//         terminal_writestring(value_buffer);
//         break;
//       case 'h':
//         itoa(*((int *)arg_ptr++), value_buffer, 16);
//         terminal_writestring(value_buffer);
//         break;
//       case 'd':
//         itoa(*((int *)arg_ptr++), value_buffer, 10);
//         terminal_writestring(value_buffer);
//         break;
//       case 'u':
//         uitoa(*((unsigned int *)arg_ptr++), value_buffer, 10);
//         terminal_writestring(value_buffer);
//         break;
//       case 's':
//         char *str = *arg_ptr++;
//         terminal_writestring(str);
//         break;
//       default:
//         terminal_writestring("error in printf\n");
//         break;
//     }
//   }
//   terminal_column = column_old;
//   terminal_row = row_old;
// }
void printf(char *format, ...) {
  char **arg_ptr = &format;
  arg_ptr++;
  char int_buffer[32];
  for (size_t i = 0; i < strlen(format); i++) {
    if (format[i] != '%') {
      terminal_putchar(format[i]);
      continue;
    } 
    i++;
    char curr = format[i];
    memset(int_buffer, 0, 32);
    switch (curr) {
    case 'p':
      terminal_putchar('0');
      terminal_putchar('x');
      itoa(*(((int *)arg_ptr++)), int_buffer, 16);
      for (size_t i = 0; i < PTR_WIDTH - strlen(int_buffer); i++) {
        terminal_putchar('0');
      }
      int ptr_idx = 0;
      while (int_buffer[ptr_idx] != 0) {
        terminal_putchar(int_buffer[ptr_idx]);
        ptr_idx++;
      }
      break;
    case 'h':
      itoa(*((int *)arg_ptr++), int_buffer, 16);
      int hex_idx = 0;
      while (int_buffer[hex_idx] != 0) {
        terminal_putchar(int_buffer[hex_idx]);
        hex_idx++;
      }
      break;
    case 'd':
      itoa(*(((int *)arg_ptr++)), int_buffer, 10);
      int int_idx = 0;
      while (int_buffer[int_idx] != 0) {
        terminal_putchar(int_buffer[int_idx]);
        int_idx++;
      }
      break;
    case 'u':
      uitoa(*(((unsigned int *)arg_ptr++)), int_buffer, 16);
      int unsigned_idx = 0;
      while (int_buffer[unsigned_idx] != 0) {
        terminal_putchar(int_buffer[unsigned_idx]);
        unsigned_idx++;
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
        itoa(*(((int *)arg_ptr++)), int_buffer, 16);
        for (size_t i = 0; i < PTR_WIDTH - strlen(int_buffer); i++) {
          terminal_putchar('0');
        }
        int ptr_idx = 0;
        while (int_buffer[ptr_idx] != 0) {
          terminal_putchar(int_buffer[ptr_idx]);
          ptr_idx++;
        }
        break;
      case 'h':
        memset(int_buffer, 0, 32);
        itoa(*(((int *)arg_ptr++)), int_buffer, 16);
        int hex_idx = 0;
        while (int_buffer[hex_idx] != 0) {
          terminal_putchar(int_buffer[hex_idx]);
          hex_idx++;
        }
        break;
      case 'd':
        memset(int_buffer, 0, 32);
        itoa(*(((int *)arg_ptr++)), int_buffer, 10);
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
int log2(int num) {
  if (num < 0) return -1;
  int count = 0;
  while (num) {
    count++;
    num = num >> 1;
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

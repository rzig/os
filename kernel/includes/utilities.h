#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PTR_WIDTH 8
#define TAB_LENGTH 4

typedef struct {
  uint32_t ds; // from push ax but stack is 32 bit aligned
  uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
  uint32_t exn_code, int_number;
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags, esp;
  uint32_t ss;
} __attribute__((packed)) exn_info;

/* Hardware text mode color constants. */
enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

static inline void outb(uint16_t port, uint8_t val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}

// temporarily stall processor for slow devices
static inline void io_wait(void) { outb(0x80, 0); }

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_remove_last();

void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);

void itoa(char *buf, int base, int d);
size_t strlen(const char *str);
void __attribute__((cdecl)) fail_cpu();
void __attribute__((cdecl)) dead_hang();

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
// void *memmove(void dest[.n], const void src[.n], size_t n); I believe we need
// malloc before doing this
int memcmp(const void *s1, const void *s2, size_t n);

void printf(char *format, ...); // variable number of args after this
void printf_top(char *format, ...);

// a very basic implementation that only works for positive non zero numbers
int intLog2(int input);

int strcmp(const char* s1, const char* s2);

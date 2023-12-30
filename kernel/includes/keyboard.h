#pragma once
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>

void keyboard_init();

#define CONTROL_PRESSED 0xF000
#define CONTROL_PRESSED 0xF001
#define SHIFT_PRESSED 0xF002
#define ALT_PRESSED 0xF003
#define CAPS_LOCK_PRESSED 0xF004
#define SPACE_PRESSED 0xFF05 // pick unused value
#define F1_PRESSED 0xF006
#define F2_PRESSED 0xF007
#define F3_PRESSED 0xF008
#define F4_PRESSED 0xF009
#define F5_PRESSED 0xF00A
#define F6_PRESSED 0xF00B
#define F7_PRESSED 0xF00C
#define F8_PRESSED 0xF00D
#define F9_PRESSED 0xF00E
#define F10_PRESSED 0xF00F
#define NUMLOCK_PRESSED 0xF010
#define SCROLL_LOCK_PRESSED 0xF011
#define ONEKP_PRESSED 0xF012
#define TWOKP_PRESSED 0xF013
#define THREEKP_PRESSED 0xF014
#define FOURKP_PRESSED 0xF015
#define FIVEKP_PRESSED 0xF016
#define SIXKP_PRESSED 0xF017
#define SEVENKP_PRESSED 0xF018
#define EIGHTKP_PRESSED 0xF019
#define NINEKP_PRESSED 0xF01A
#define ZEROKP_PRESSED 0xF01B
#define PLUSKP_PRESSED 0xF01C
#define MINUSKP_PRESSED 0xF01D
#define PERIODKP_PRESSED 0xF01E
#define F11_PRESSED 0xF01F
#define F12_PRESSED 0xF020
#define BACKSPACE_PRESSED 0xF021
#define ESCAPE_PRESSED 0xF022
#define CONTROL_RELEASED 0xF023
#define SHIFT_RELEASED 0xF024
#define ALT_RELEASED 0xF025

#define ATKBD_KEYMAP_SIZE 512

static const uint16_t atkbd_set1_keycode[ATKBD_KEYMAP_SIZE] = {
    0, ESCAPE_PRESSED, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE_PRESSED, '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', CONTROL_PRESSED, 'a', 's', 
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', SHIFT_PRESSED, '\\', 'z', 'x', 'c', 'v', 
    'b', 'n', 'm', ',', '.', '/', SHIFT_PRESSED, '*', ALT_PRESSED, SPACE_PRESSED, CAPS_LOCK_PRESSED, F1_PRESSED, F2_PRESSED, F3_PRESSED, F4_PRESSED, F5_PRESSED, 
    F6_PRESSED, F7_PRESSED, F8_PRESSED, F9_PRESSED, F10_PRESSED, NUMLOCK_PRESSED, SCROLL_LOCK_PRESSED, SEVENKP_PRESSED, EIGHTKP_PRESSED, NINEKP_PRESSED, MINUSKP_PRESSED, FOURKP_PRESSED, FIVEKP_PRESSED, SIXKP_PRESSED, PLUSKP_PRESSED, ONEKP_PRESSED, 
    TWOKP_PRESSED, THREEKP_PRESSED, ZEROKP_PRESSED, PERIODKP_PRESSED, 0, 0, 0, F11_PRESSED, F12_PRESSED, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CONTROL_RELEASED, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SHIFT_RELEASED, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, SHIFT_RELEASED, 0, ALT_RELEASED, 0, 0, 0, 0, 0, 0, 0,
};

static const unsigned char atkbd_set2_keycode[ATKBD_KEYMAP_SIZE] = {
        0, 67, 65, 63, 61, 59, 60, 88,  0, 68, 66, 64, 62, 15, 41,117,
        0, 56, 42, 93, 29, 16,  2,  0,  0,  0, 44, 31, 30, 17,  3,  0,
        0, 46, 45, 32, 18,  5,  4, 95,  0, 57, 47, 33, 20, 19,  6,183,
        0, 49, 48, 35, 34, 21,  7,184,  0,  0, 50, 36, 22,  8,  9,185,
        0, 51, 37, 23, 24, 11, 10,  0,  0, 52, 53, 38, 39, 25, 12,  0,
        0, 89, 40,  0, 26, 13,  0,  0, 58, 54, 28, 27,  0, 43,  0, 85,
        0, 86, 91, 90, 92,  0, 14, 94,  0, 79,124, 75, 71,121,  0,  0,
        82, 83, 80, 76, 77, 72,  1, 69, 87, 78, 81, 74, 55, 73, 70, 99,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        217,100,255,  0, 97,165,  0,  0,156,  0,  0,  0,  0,  0,  0,125,
        173,114,  0,113,  0,  0,  0,126,128,  0,  0,140,  0,  0,  0,127,
        159,  0,115,  0,164,  0,  0,116,158,  0,172,166,  0,  0,  0,142,
        157,  0,  0,  0,  0,  0,  0,  0,155,  0, 98,  0,  0,163,  0,  0,
        226,  0,  0,  0,  0,  0,  0,  0,  0,255, 96,  0,  0,  0,143,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,107,  0,105,102,  0,  0,112,
        110,111,108,112,106,103,  0,119,  0,118,109,  0, 99,104,119,  0,
        0,  0,  0, 65, 99,
};

static const unsigned short atkbd_set3_keycode[ATKBD_KEYMAP_SIZE] = {

         0,  0,  0,  0,  0,  0,  0, 59,  1,138,128,129,130, 15, 41, 60,
        131, 29, 42, 86, 58, 16,  2, 61,133, 56, 44, 31, 30, 17,  3, 62,
        134, 46, 45, 32, 18,  5,  4, 63,135, 57, 47, 33, 20, 19,  6, 64,
        136, 49, 48, 35, 34, 21,  7, 65,137,100, 50, 36, 22,  8,  9, 66,
        125, 51, 37, 23, 24, 11, 10, 67,126, 52, 53, 38, 39, 25, 12, 68,
        113,114, 40, 43, 26, 13, 87, 99, 97, 54, 28, 27, 43, 43, 88, 70,
        108,105,119,103,111,107, 14,110,  0, 79,106, 75, 71,109,102,104,
         82, 83, 80, 76, 77, 72, 69, 98,  0, 96, 81,  0, 78, 73, 55,183,

        184,185,186,187, 74, 94, 92, 93,  0,  0,  0,125,126,127,112,  0,
          0,139,172,163,165,115,152,172,166,140,160,154,113,114,167,168,
        148,149,147,140
};

uint16_t keyboard_parsekey(uint16_t key);
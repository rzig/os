#pragma once

#include "keyboard.h"
#include "utilities.h"
#include <stdint.h>
#define ATKBD_KEYMAP_SIZE 512
/***
 * PIC is the programmable interrupt controller, first we need to setup master
 * and slave then we need to set which ports the PIC should report too
 */

// I got this from osdev not sure where in the manual this is

void ICW1(uint8_t flags);
void ICW2(uint8_t flags);
void ICW3(uint8_t flags);
void ICW4(uint8_t flags);

void OCW(uint8_t flags);

void setup_addr(uint8_t icw1_flags, uint8_t isr_offset, uint8_t master_slave_id,
                uint8_t icw4_flags);

void initialize_pic(); // call with predefined flags
uint16_t pic_get_irr();
uint16_t pic_get_isr();

void PIC_sendEOI(unsigned char irq);
void PIC_remap();

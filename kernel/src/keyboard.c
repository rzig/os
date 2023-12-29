#include "keyboard.h"



void keyboard_init() {
    outb(0x64, 0xAD);// disable PS2 dev0
    io_wait();
    outb(0x64, 0xA7);// disable PS2 dev1
    io_wait();
    inb(0x60);
    io_wait(); //flush buffer
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
    
    outb(0x64, 0xAA);//check status
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
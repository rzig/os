#include "pic.h"

#define PIC_EOI		0x20

uint16_t PIC_M_COMMAND = 0x20; 
uint16_t PIC_M_DATA = 0x21;
uint16_t PIC_S_COMMAND = 0xA0;
uint16_t PIC_S_DATA = 0xA1;

//ICW1 (we don't need to set A0 just tells us if we need to write to the command or data segment, A0 = 1 -> data, A0 = 0 -> Code)
uint8_t ICW4_REQ = 0b01; // we will use this
uint8_t ICW4_NOTREQ = 0b00;
uint8_t SINGLE = 0b10;
uint8_t CASCADE = 0b00; // we will use this
uint8_t ADI4 = 0b100;
uint8_t ADI8 = 0b00; // we will use this 
uint8_t LEVEL = 0b1000;
uint8_t EDGE = 0b00; // we will use this 
uint8_t ICW1_FLAG = 0b10000; // we will use this

//ICW3 FLAGS 

uint8_t M_OFFSET = 0b100; // this is an 8 bit number, where the bit selected = id (e.g. 0 = id 0, 10 = 1, 100 = 2, 1000 = 3, etc)
uint8_t S_ID = 0b10; // functions as a normal binary number to tell identity

//ICW4 FLAGS
uint8_t MCS = 0b00;
uint8_t E8086 = 0b01;
uint8_t AUTOEOI = 0b10;
uint8_t NORMALEOI = 0b00;
uint8_t NONBUFFERED_MODE = 0b00;
uint8_t BUFFERED_S = 0b1000;
uint8_t BUFFERED_M = 0b1100;
uint8_t SPECIAL_FULLY_NESTED = 0b10000;
uint8_t NORMAL_FULLY_NESTED = 0b00;

//I am going to presume for now that we will not define the OCW flags and will just setup PIC but if not the definitions are page 13 of intel manual for PIC



//at some point could use for setting/getting interrupt masks
void OCW(uint8_t flags) {

}

// we will just use predefined values but theoretically we could make functions for this
void initialize_pic() {
	asm volatile("cli");
    terminal_writestring("starting init of PIC\n");
    uint8_t orig_m_flags = inb(PIC_M_DATA);
    uint8_t orig_s_flags = inb(PIC_S_DATA);
	printf("original m flags: %d\n", orig_m_flags);
	printf("original s flags: %d\n", orig_s_flags);
	outb(PIC_M_COMMAND, (ICW1_FLAG | ICW4_REQ));
	io_wait();
    outb(PIC_S_COMMAND, (ICW1_FLAG | ICW4_REQ));
	io_wait();
	outb(PIC_M_DATA, (uint8_t) 0x20); //after ISR 31 the rest are free so just start here
 	io_wait();
	outb(PIC_S_DATA, (uint8_t) 0x28);
	io_wait();
	outb(PIC_M_DATA, M_OFFSET);
	io_wait();
	outb(PIC_S_DATA, S_ID); 
	io_wait();
	outb(PIC_M_DATA, E8086);
	io_wait();
	outb(PIC_S_DATA, E8086);
	io_wait();

	//ICWs have been sent, now turn off the interrupt masks
    outb(PIC_M_DATA, 0);
    io_wait();
    outb(PIC_S_DATA, 0);
    io_wait();// not needed probably
    terminal_writestring("finished setup PIC\n");
} 

 
void PIC_sendEOI(unsigned char irq)
{
	if(irq >= 8) {
		outb(PIC_S_COMMAND,PIC_EOI);
	}
	outb(PIC_M_COMMAND,PIC_EOI);
}
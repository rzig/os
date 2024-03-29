#include "../includes/idt.h"
// declare IDT constants in global memory(originally I did them in Kernel memory
// for GDT which I will move at some point) Entries 22-31 are intel reserved,
// look into if we should still generate exceptions for these!
IDTEntry idt_entries[256]; // create 256 entries
static int interrupt_counter = 0;
idtr_entry idtr_val = {
    sizeof(idt_entries) - 1,
    idt_entries // pointer to the start of the idt (32 bit address)
};

void start_idt() {
  // now time for the stub code hmm
  set_idtr(&idtr_val);
  setupISR();
}

// sets the idt entry up
void set_idt_entry(int entry_number, uint8_t flags, uint16_t segment_selector,
                   void *offset) {
  idt_entries[entry_number].flags = flags;
  idt_entries[entry_number].segment_selector = segment_selector;
  idt_entries[entry_number].offset_high = ((uint32_t)offset >> 16) & 0xFFFF;
  idt_entries[entry_number].offset_low = (uint32_t)offset & 0xFFFF;
}

void __attribute__((cdecl)) int_handler(exn_info register_values) {
  if (register_values.int_number >= 32) {
    execute_user_int(register_values);
  } else {
    printf("exn code: %u and int number: %d\n", register_values.exn_code, register_values.int_number);
    printf("ss: %x, eip: %x, ds: %x, edx: %x\n", register_values.ss, register_values.eip, register_values.ds, register_values.edx);
    exn_handler();
  }
}

void __attribute__((cdecl)) ISR_ERRROUTINE0();
void __attribute__((cdecl)) ISR_ERRROUTINE1();
void __attribute__((cdecl)) ISR_ERRROUTINE2();
void __attribute__((cdecl)) ISR_ERRROUTINE3();
void __attribute__((cdecl)) ISR_ERRROUTINE4();
void __attribute__((cdecl)) ISR_ERRROUTINE5();
void __attribute__((cdecl)) ISR_ERRROUTINE6();
void __attribute__((cdecl)) ISR_ERRROUTINE7();
void __attribute__((cdecl)) ISR_ERRROUTINE8();
void __attribute__((cdecl)) ISR_ERRROUTINE9();
void __attribute__((cdecl)) ISR_ERRROUTINE10();
void __attribute__((cdecl)) ISR_ERRROUTINE11();
void __attribute__((cdecl)) ISR_ERRROUTINE12();
void __attribute__((cdecl)) ISR_ERRROUTINE13();
void __attribute__((cdecl)) ISR_ERRROUTINE14();
void __attribute__((cdecl)) ISR_ERRROUTINE15();
void __attribute__((cdecl)) ISR_ERRROUTINE16();
void __attribute__((cdecl)) ISR_ERRROUTINE17();
void __attribute__((cdecl)) ISR_ERRROUTINE18();
void __attribute__((cdecl)) ISR_ERRROUTINE19();
void __attribute__((cdecl)) ISR_ERRROUTINE20();
void __attribute__((cdecl)) ISR_ERRROUTINE21();
void __attribute__((cdecl)) ISR_ERRROUTINE22();
void __attribute__((cdecl)) ISR_ERRROUTINE23();
void __attribute__((cdecl)) ISR_ERRROUTINE24();
void __attribute__((cdecl)) ISR_ERRROUTINE25();
void __attribute__((cdecl)) ISR_ERRROUTINE26();
void __attribute__((cdecl)) ISR_ERRROUTINE27();
void __attribute__((cdecl)) ISR_ERRROUTINE28();
void __attribute__((cdecl)) ISR_ERRROUTINE29();
void __attribute__((cdecl)) ISR_ERRROUTINE30();
void __attribute__((cdecl)) ISR_ERRROUTINE31();
void __attribute__((cdecl)) ISR_ERRROUTINE32();
void __attribute__((cdecl)) ISR_ERRROUTINE33();
void __attribute__((cdecl)) ISR_ERRROUTINE34();
void __attribute__((cdecl)) ISR_ERRROUTINE35();
void __attribute__((cdecl)) ISR_ERRROUTINE36();
void __attribute__((cdecl)) ISR_ERRROUTINE37();
void __attribute__((cdecl)) ISR_ERRROUTINE38();
void __attribute__((cdecl)) ISR_ERRROUTINE39();
void __attribute__((cdecl)) ISR_ERRROUTINE40();
void __attribute__((cdecl)) ISR_ERRROUTINE41();
void __attribute__((cdecl)) ISR_ERRROUTINE42();
void __attribute__((cdecl)) ISR_ERRROUTINE43();
void __attribute__((cdecl)) ISR_ERRROUTINE44();
void __attribute__((cdecl)) ISR_ERRROUTINE45();
void __attribute__((cdecl)) ISR_ERRROUTINE46();
void __attribute__((cdecl)) ISR_ERRROUTINE47();
void __attribute__((cdecl)) ISR_ERRROUTINE48();
void __attribute__((cdecl)) ISR_ERRROUTINE49();
void __attribute__((cdecl)) ISR_ERRROUTINE50();
void __attribute__((cdecl)) ISR_ERRROUTINE51();
void __attribute__((cdecl)) ISR_ERRROUTINE52();
void __attribute__((cdecl)) ISR_ERRROUTINE53();
void __attribute__((cdecl)) ISR_ERRROUTINE54();
void __attribute__((cdecl)) ISR_ERRROUTINE55();
void __attribute__((cdecl)) ISR_ERRROUTINE56();
void __attribute__((cdecl)) ISR_ERRROUTINE57();
void __attribute__((cdecl)) ISR_ERRROUTINE58();
void __attribute__((cdecl)) ISR_ERRROUTINE59();
void __attribute__((cdecl)) ISR_ERRROUTINE60();
void __attribute__((cdecl)) ISR_ERRROUTINE61();
void __attribute__((cdecl)) ISR_ERRROUTINE62();
void __attribute__((cdecl)) ISR_ERRROUTINE63();
void __attribute__((cdecl)) ISR_ERRROUTINE64();
void __attribute__((cdecl)) ISR_ERRROUTINE65();
void __attribute__((cdecl)) ISR_ERRROUTINE66();
void __attribute__((cdecl)) ISR_ERRROUTINE67();
void __attribute__((cdecl)) ISR_ERRROUTINE68();
void __attribute__((cdecl)) ISR_ERRROUTINE69();
void __attribute__((cdecl)) ISR_ERRROUTINE70();
void __attribute__((cdecl)) ISR_ERRROUTINE71();
void __attribute__((cdecl)) ISR_ERRROUTINE72();
void __attribute__((cdecl)) ISR_ERRROUTINE73();
void __attribute__((cdecl)) ISR_ERRROUTINE74();
void __attribute__((cdecl)) ISR_ERRROUTINE75();
void __attribute__((cdecl)) ISR_ERRROUTINE76();
void __attribute__((cdecl)) ISR_ERRROUTINE77();
void __attribute__((cdecl)) ISR_ERRROUTINE78();
void __attribute__((cdecl)) ISR_ERRROUTINE79();
void __attribute__((cdecl)) ISR_ERRROUTINE80();
void __attribute__((cdecl)) ISR_ERRROUTINE81();
void __attribute__((cdecl)) ISR_ERRROUTINE82();
void __attribute__((cdecl)) ISR_ERRROUTINE83();
void __attribute__((cdecl)) ISR_ERRROUTINE84();
void __attribute__((cdecl)) ISR_ERRROUTINE85();
void __attribute__((cdecl)) ISR_ERRROUTINE86();
void __attribute__((cdecl)) ISR_ERRROUTINE87();
void __attribute__((cdecl)) ISR_ERRROUTINE88();
void __attribute__((cdecl)) ISR_ERRROUTINE89();
void __attribute__((cdecl)) ISR_ERRROUTINE90();
void __attribute__((cdecl)) ISR_ERRROUTINE91();
void __attribute__((cdecl)) ISR_ERRROUTINE92();
void __attribute__((cdecl)) ISR_ERRROUTINE93();
void __attribute__((cdecl)) ISR_ERRROUTINE94();
void __attribute__((cdecl)) ISR_ERRROUTINE95();
void __attribute__((cdecl)) ISR_ERRROUTINE96();
void __attribute__((cdecl)) ISR_ERRROUTINE97();
void __attribute__((cdecl)) ISR_ERRROUTINE98();
void __attribute__((cdecl)) ISR_ERRROUTINE99();
void __attribute__((cdecl)) ISR_ERRROUTINE100();
void __attribute__((cdecl)) ISR_ERRROUTINE101();
void __attribute__((cdecl)) ISR_ERRROUTINE102();
void __attribute__((cdecl)) ISR_ERRROUTINE103();
void __attribute__((cdecl)) ISR_ERRROUTINE104();
void __attribute__((cdecl)) ISR_ERRROUTINE105();
void __attribute__((cdecl)) ISR_ERRROUTINE106();
void __attribute__((cdecl)) ISR_ERRROUTINE107();
void __attribute__((cdecl)) ISR_ERRROUTINE108();
void __attribute__((cdecl)) ISR_ERRROUTINE109();
void __attribute__((cdecl)) ISR_ERRROUTINE110();
void __attribute__((cdecl)) ISR_ERRROUTINE111();
void __attribute__((cdecl)) ISR_ERRROUTINE112();
void __attribute__((cdecl)) ISR_ERRROUTINE113();
void __attribute__((cdecl)) ISR_ERRROUTINE114();
void __attribute__((cdecl)) ISR_ERRROUTINE115();
void __attribute__((cdecl)) ISR_ERRROUTINE116();
void __attribute__((cdecl)) ISR_ERRROUTINE117();
void __attribute__((cdecl)) ISR_ERRROUTINE118();
void __attribute__((cdecl)) ISR_ERRROUTINE119();
void __attribute__((cdecl)) ISR_ERRROUTINE120();
void __attribute__((cdecl)) ISR_ERRROUTINE121();
void __attribute__((cdecl)) ISR_ERRROUTINE122();
void __attribute__((cdecl)) ISR_ERRROUTINE123();
void __attribute__((cdecl)) ISR_ERRROUTINE124();
void __attribute__((cdecl)) ISR_ERRROUTINE125();
void __attribute__((cdecl)) ISR_ERRROUTINE126();
void __attribute__((cdecl)) ISR_ERRROUTINE127();
void __attribute__((cdecl)) ISR_ERRROUTINE128();
void __attribute__((cdecl)) ISR_ERRROUTINE129();
void __attribute__((cdecl)) ISR_ERRROUTINE130();
void __attribute__((cdecl)) ISR_ERRROUTINE131();
void __attribute__((cdecl)) ISR_ERRROUTINE132();
void __attribute__((cdecl)) ISR_ERRROUTINE133();
void __attribute__((cdecl)) ISR_ERRROUTINE134();
void __attribute__((cdecl)) ISR_ERRROUTINE135();
void __attribute__((cdecl)) ISR_ERRROUTINE136();
void __attribute__((cdecl)) ISR_ERRROUTINE137();
void __attribute__((cdecl)) ISR_ERRROUTINE138();
void __attribute__((cdecl)) ISR_ERRROUTINE139();
void __attribute__((cdecl)) ISR_ERRROUTINE140();
void __attribute__((cdecl)) ISR_ERRROUTINE141();
void __attribute__((cdecl)) ISR_ERRROUTINE142();
void __attribute__((cdecl)) ISR_ERRROUTINE143();
void __attribute__((cdecl)) ISR_ERRROUTINE144();
void __attribute__((cdecl)) ISR_ERRROUTINE145();
void __attribute__((cdecl)) ISR_ERRROUTINE146();
void __attribute__((cdecl)) ISR_ERRROUTINE147();
void __attribute__((cdecl)) ISR_ERRROUTINE148();
void __attribute__((cdecl)) ISR_ERRROUTINE149();
void __attribute__((cdecl)) ISR_ERRROUTINE150();
void __attribute__((cdecl)) ISR_ERRROUTINE151();
void __attribute__((cdecl)) ISR_ERRROUTINE152();
void __attribute__((cdecl)) ISR_ERRROUTINE153();
void __attribute__((cdecl)) ISR_ERRROUTINE154();
void __attribute__((cdecl)) ISR_ERRROUTINE155();
void __attribute__((cdecl)) ISR_ERRROUTINE156();
void __attribute__((cdecl)) ISR_ERRROUTINE157();
void __attribute__((cdecl)) ISR_ERRROUTINE158();
void __attribute__((cdecl)) ISR_ERRROUTINE159();
void __attribute__((cdecl)) ISR_ERRROUTINE160();
void __attribute__((cdecl)) ISR_ERRROUTINE161();
void __attribute__((cdecl)) ISR_ERRROUTINE162();
void __attribute__((cdecl)) ISR_ERRROUTINE163();
void __attribute__((cdecl)) ISR_ERRROUTINE164();
void __attribute__((cdecl)) ISR_ERRROUTINE165();
void __attribute__((cdecl)) ISR_ERRROUTINE166();
void __attribute__((cdecl)) ISR_ERRROUTINE167();
void __attribute__((cdecl)) ISR_ERRROUTINE168();
void __attribute__((cdecl)) ISR_ERRROUTINE169();
void __attribute__((cdecl)) ISR_ERRROUTINE170();
void __attribute__((cdecl)) ISR_ERRROUTINE171();
void __attribute__((cdecl)) ISR_ERRROUTINE172();
void __attribute__((cdecl)) ISR_ERRROUTINE173();
void __attribute__((cdecl)) ISR_ERRROUTINE174();
void __attribute__((cdecl)) ISR_ERRROUTINE175();
void __attribute__((cdecl)) ISR_ERRROUTINE176();
void __attribute__((cdecl)) ISR_ERRROUTINE177();
void __attribute__((cdecl)) ISR_ERRROUTINE178();
void __attribute__((cdecl)) ISR_ERRROUTINE179();
void __attribute__((cdecl)) ISR_ERRROUTINE180();
void __attribute__((cdecl)) ISR_ERRROUTINE181();
void __attribute__((cdecl)) ISR_ERRROUTINE182();
void __attribute__((cdecl)) ISR_ERRROUTINE183();
void __attribute__((cdecl)) ISR_ERRROUTINE184();
void __attribute__((cdecl)) ISR_ERRROUTINE185();
void __attribute__((cdecl)) ISR_ERRROUTINE186();
void __attribute__((cdecl)) ISR_ERRROUTINE187();
void __attribute__((cdecl)) ISR_ERRROUTINE188();
void __attribute__((cdecl)) ISR_ERRROUTINE189();
void __attribute__((cdecl)) ISR_ERRROUTINE190();
void __attribute__((cdecl)) ISR_ERRROUTINE191();
void __attribute__((cdecl)) ISR_ERRROUTINE192();
void __attribute__((cdecl)) ISR_ERRROUTINE193();
void __attribute__((cdecl)) ISR_ERRROUTINE194();
void __attribute__((cdecl)) ISR_ERRROUTINE195();
void __attribute__((cdecl)) ISR_ERRROUTINE196();
void __attribute__((cdecl)) ISR_ERRROUTINE197();
void __attribute__((cdecl)) ISR_ERRROUTINE198();
void __attribute__((cdecl)) ISR_ERRROUTINE199();
void __attribute__((cdecl)) ISR_ERRROUTINE200();
void __attribute__((cdecl)) ISR_ERRROUTINE201();
void __attribute__((cdecl)) ISR_ERRROUTINE202();
void __attribute__((cdecl)) ISR_ERRROUTINE203();
void __attribute__((cdecl)) ISR_ERRROUTINE204();
void __attribute__((cdecl)) ISR_ERRROUTINE205();
void __attribute__((cdecl)) ISR_ERRROUTINE206();
void __attribute__((cdecl)) ISR_ERRROUTINE207();
void __attribute__((cdecl)) ISR_ERRROUTINE208();
void __attribute__((cdecl)) ISR_ERRROUTINE209();
void __attribute__((cdecl)) ISR_ERRROUTINE210();
void __attribute__((cdecl)) ISR_ERRROUTINE211();
void __attribute__((cdecl)) ISR_ERRROUTINE212();
void __attribute__((cdecl)) ISR_ERRROUTINE213();
void __attribute__((cdecl)) ISR_ERRROUTINE214();
void __attribute__((cdecl)) ISR_ERRROUTINE215();
void __attribute__((cdecl)) ISR_ERRROUTINE216();
void __attribute__((cdecl)) ISR_ERRROUTINE217();
void __attribute__((cdecl)) ISR_ERRROUTINE218();
void __attribute__((cdecl)) ISR_ERRROUTINE219();
void __attribute__((cdecl)) ISR_ERRROUTINE220();
void __attribute__((cdecl)) ISR_ERRROUTINE221();
void __attribute__((cdecl)) ISR_ERRROUTINE222();
void __attribute__((cdecl)) ISR_ERRROUTINE223();
void __attribute__((cdecl)) ISR_ERRROUTINE224();
void __attribute__((cdecl)) ISR_ERRROUTINE225();
void __attribute__((cdecl)) ISR_ERRROUTINE226();
void __attribute__((cdecl)) ISR_ERRROUTINE227();
void __attribute__((cdecl)) ISR_ERRROUTINE228();
void __attribute__((cdecl)) ISR_ERRROUTINE229();
void __attribute__((cdecl)) ISR_ERRROUTINE230();
void __attribute__((cdecl)) ISR_ERRROUTINE231();
void __attribute__((cdecl)) ISR_ERRROUTINE232();
void __attribute__((cdecl)) ISR_ERRROUTINE233();
void __attribute__((cdecl)) ISR_ERRROUTINE234();
void __attribute__((cdecl)) ISR_ERRROUTINE235();
void __attribute__((cdecl)) ISR_ERRROUTINE236();
void __attribute__((cdecl)) ISR_ERRROUTINE237();
void __attribute__((cdecl)) ISR_ERRROUTINE238();
void __attribute__((cdecl)) ISR_ERRROUTINE239();
void __attribute__((cdecl)) ISR_ERRROUTINE240();
void __attribute__((cdecl)) ISR_ERRROUTINE241();
void __attribute__((cdecl)) ISR_ERRROUTINE242();
void __attribute__((cdecl)) ISR_ERRROUTINE243();
void __attribute__((cdecl)) ISR_ERRROUTINE244();
void __attribute__((cdecl)) ISR_ERRROUTINE245();
void __attribute__((cdecl)) ISR_ERRROUTINE246();
void __attribute__((cdecl)) ISR_ERRROUTINE247();
void __attribute__((cdecl)) ISR_ERRROUTINE248();
void __attribute__((cdecl)) ISR_ERRROUTINE249();
void __attribute__((cdecl)) ISR_ERRROUTINE250();
void __attribute__((cdecl)) ISR_ERRROUTINE251();
void __attribute__((cdecl)) ISR_ERRROUTINE252();
void __attribute__((cdecl)) ISR_ERRROUTINE253();
void __attribute__((cdecl)) ISR_ERRROUTINE254();
void __attribute__((cdecl)) ISR_ERRROUTINE255();

void setupISR() {
  set_idt_entry(0, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE0);
  set_idt_entry(1, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE1);
  set_idt_entry(2, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE2);
  set_idt_entry(3, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE3);
  set_idt_entry(4, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE4);
  set_idt_entry(5, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE5);
  set_idt_entry(6, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE6);
  set_idt_entry(7, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE7);
  set_idt_entry(8, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE8);
  set_idt_entry(9, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE9);
  set_idt_entry(10, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE10);
  set_idt_entry(11, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE11);
  set_idt_entry(12, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE12);
  set_idt_entry(13, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE13);
  set_idt_entry(14, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE14);
  set_idt_entry(15, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE15);
  set_idt_entry(16, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE16);
  set_idt_entry(17, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE17);
  set_idt_entry(18, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE18);
  set_idt_entry(19, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE19);
  set_idt_entry(20, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE20);
  set_idt_entry(21, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE21);
  set_idt_entry(22, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE22);
  set_idt_entry(23, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE23);
  set_idt_entry(24, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE24);
  set_idt_entry(25, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE25);
  set_idt_entry(26, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE26);
  set_idt_entry(27, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE27);
  set_idt_entry(28, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE28);
  set_idt_entry(29, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE29);
  set_idt_entry(30, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE30);
  set_idt_entry(31, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE31);
  set_idt_entry(32, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE32);
  set_idt_entry(33, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE33);
  set_idt_entry(34, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE34);
  set_idt_entry(35, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE35);
  set_idt_entry(36, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE36);
  set_idt_entry(37, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE37);
  set_idt_entry(38, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE38);
  set_idt_entry(39, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE39);
  set_idt_entry(40, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE40);
  set_idt_entry(41, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE41);
  set_idt_entry(42, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE42);
  set_idt_entry(43, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE43);
  set_idt_entry(44, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE44);
  set_idt_entry(45, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE45);
  set_idt_entry(46, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE46);
  set_idt_entry(47, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE47);
  set_idt_entry(48, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE48);
  set_idt_entry(49, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE49);
  set_idt_entry(50, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE50);
  set_idt_entry(51, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE51);
  set_idt_entry(52, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE52);
  set_idt_entry(53, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE53);
  set_idt_entry(54, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE54);
  set_idt_entry(55, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE55);
  set_idt_entry(56, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE56);
  set_idt_entry(57, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE57);
  set_idt_entry(58, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE58);
  set_idt_entry(59, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE59);
  set_idt_entry(60, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE60);
  set_idt_entry(61, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE61);
  set_idt_entry(62, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE62);
  set_idt_entry(63, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE63);
  set_idt_entry(64, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE64);
  set_idt_entry(65, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE65);
  set_idt_entry(66, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE66);
  set_idt_entry(67, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE67);
  set_idt_entry(68, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE68);
  set_idt_entry(69, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE69);
  set_idt_entry(70, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE70);
  set_idt_entry(71, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE71);
  set_idt_entry(72, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE72);
  set_idt_entry(73, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE73);
  set_idt_entry(74, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE74);
  set_idt_entry(75, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE75);
  set_idt_entry(76, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE76);
  set_idt_entry(77, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE77);
  set_idt_entry(78, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE78);
  set_idt_entry(79, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE79);
  set_idt_entry(80, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE80);
  set_idt_entry(81, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE81);
  set_idt_entry(82, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE82);
  set_idt_entry(83, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE83);
  set_idt_entry(84, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE84);
  set_idt_entry(85, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE85);
  set_idt_entry(86, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE86);
  set_idt_entry(87, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE87);
  set_idt_entry(88, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE88);
  set_idt_entry(89, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE89);
  set_idt_entry(90, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE90);
  set_idt_entry(91, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE91);
  set_idt_entry(92, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE92);
  set_idt_entry(93, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE93);
  set_idt_entry(94, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE94);
  set_idt_entry(95, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE95);
  set_idt_entry(96, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE96);
  set_idt_entry(97, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE97);
  set_idt_entry(98, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE98);
  set_idt_entry(99, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE99);
  set_idt_entry(100, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE100);
  set_idt_entry(101, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE101);
  set_idt_entry(102, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE102);
  set_idt_entry(103, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE103);
  set_idt_entry(104, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE104);
  set_idt_entry(105, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE105);
  set_idt_entry(106, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE106);
  set_idt_entry(107, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE107);
  set_idt_entry(108, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE108);
  set_idt_entry(109, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE109);
  set_idt_entry(110, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE110);
  set_idt_entry(111, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE111);
  set_idt_entry(112, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE112);
  set_idt_entry(113, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE113);
  set_idt_entry(114, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE114);
  set_idt_entry(115, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE115);
  set_idt_entry(116, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE116);
  set_idt_entry(117, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE117);
  set_idt_entry(118, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE118);
  set_idt_entry(119, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE119);
  set_idt_entry(120, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE120);
  set_idt_entry(121, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE121);
  set_idt_entry(122, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE122);
  set_idt_entry(123, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE123);
  set_idt_entry(124, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE124);
  set_idt_entry(125, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE125);
  set_idt_entry(126, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE126);
  set_idt_entry(127, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE127);
  set_idt_entry(128, PRESENT | INTERRUPT_GATE32 | USER, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE128);
  set_idt_entry(129, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE129);
  set_idt_entry(130, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE130);
  set_idt_entry(131, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE131);
  set_idt_entry(132, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE132);
  set_idt_entry(133, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE133);
  set_idt_entry(134, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE134);
  set_idt_entry(135, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE135);
  set_idt_entry(136, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE136);
  set_idt_entry(137, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE137);
  set_idt_entry(138, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE138);
  set_idt_entry(139, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE139);
  set_idt_entry(140, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE140);
  set_idt_entry(141, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE141);
  set_idt_entry(142, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE142);
  set_idt_entry(143, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE143);
  set_idt_entry(144, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE144);
  set_idt_entry(145, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE145);
  set_idt_entry(146, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE146);
  set_idt_entry(147, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE147);
  set_idt_entry(148, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE148);
  set_idt_entry(149, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE149);
  set_idt_entry(150, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE150);
  set_idt_entry(151, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE151);
  set_idt_entry(152, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE152);
  set_idt_entry(153, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE153);
  set_idt_entry(154, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE154);
  set_idt_entry(155, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE155);
  set_idt_entry(156, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE156);
  set_idt_entry(157, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE157);
  set_idt_entry(158, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE158);
  set_idt_entry(159, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE159);
  set_idt_entry(160, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE160);
  set_idt_entry(161, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE161);
  set_idt_entry(162, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE162);
  set_idt_entry(163, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE163);
  set_idt_entry(164, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE164);
  set_idt_entry(165, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE165);
  set_idt_entry(166, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE166);
  set_idt_entry(167, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE167);
  set_idt_entry(168, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE168);
  set_idt_entry(169, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE169);
  set_idt_entry(170, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE170);
  set_idt_entry(171, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE171);
  set_idt_entry(172, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE172);
  set_idt_entry(173, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE173);
  set_idt_entry(174, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE174);
  set_idt_entry(175, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE175);
  set_idt_entry(176, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE176);
  set_idt_entry(177, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE177);
  set_idt_entry(178, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE178);
  set_idt_entry(179, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE179);
  set_idt_entry(180, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE180);
  set_idt_entry(181, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE181);
  set_idt_entry(182, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE182);
  set_idt_entry(183, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE183);
  set_idt_entry(184, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE184);
  set_idt_entry(185, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE185);
  set_idt_entry(186, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE186);
  set_idt_entry(187, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE187);
  set_idt_entry(188, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE188);
  set_idt_entry(189, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE189);
  set_idt_entry(190, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE190);
  set_idt_entry(191, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE191);
  set_idt_entry(192, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE192);
  set_idt_entry(193, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE193);
  set_idt_entry(194, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE194);
  set_idt_entry(195, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE195);
  set_idt_entry(196, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE196);
  set_idt_entry(197, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE197);
  set_idt_entry(198, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE198);
  set_idt_entry(199, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE199);
  set_idt_entry(200, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE200);
  set_idt_entry(201, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE201);
  set_idt_entry(202, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE202);
  set_idt_entry(203, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE203);
  set_idt_entry(204, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE204);
  set_idt_entry(205, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE205);
  set_idt_entry(206, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE206);
  set_idt_entry(207, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE207);
  set_idt_entry(208, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE208);
  set_idt_entry(209, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE209);
  set_idt_entry(210, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE210);
  set_idt_entry(211, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE211);
  set_idt_entry(212, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE212);
  set_idt_entry(213, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE213);
  set_idt_entry(214, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE214);
  set_idt_entry(215, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE215);
  set_idt_entry(216, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE216);
  set_idt_entry(217, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE217);
  set_idt_entry(218, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE218);
  set_idt_entry(219, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE219);
  set_idt_entry(220, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE220);
  set_idt_entry(221, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE221);
  set_idt_entry(222, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE222);
  set_idt_entry(223, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE223);
  set_idt_entry(224, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE224);
  set_idt_entry(225, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE225);
  set_idt_entry(226, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE226);
  set_idt_entry(227, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE227);
  set_idt_entry(228, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE228);
  set_idt_entry(229, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE229);
  set_idt_entry(230, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE230);
  set_idt_entry(231, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE231);
  set_idt_entry(232, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE232);
  set_idt_entry(233, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE233);
  set_idt_entry(234, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE234);
  set_idt_entry(235, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE235);
  set_idt_entry(236, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE236);
  set_idt_entry(237, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE237);
  set_idt_entry(238, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE238);
  set_idt_entry(239, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE239);
  set_idt_entry(240, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE240);
  set_idt_entry(241, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE241);
  set_idt_entry(242, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE242);
  set_idt_entry(243, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE243);
  set_idt_entry(244, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE244);
  set_idt_entry(245, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE245);
  set_idt_entry(246, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE246);
  set_idt_entry(247, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE247);
  set_idt_entry(248, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE248);
  set_idt_entry(249, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE249);
  set_idt_entry(250, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE250);
  set_idt_entry(251, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE251);
  set_idt_entry(252, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE252);
  set_idt_entry(253, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE253);
  set_idt_entry(254, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE254);
  set_idt_entry(255, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT,
                &ISR_ERRROUTINE255);
}

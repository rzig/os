#include <stdio.h>

int main(int argc, char** argv) {
    for (int i = 0; i < 256; i++) {
        printf("void __attribute__((cdecl)) ISR_ERRROUTINE%d();\n", i);
    }
    printf("\n");
    printf("void setupISR() {\n");
    for (int i = 0; i < 256; i++) {
        printf("    set_entry(%d, PRESENT | INTERRUPT_GATE32 | KERNEL, KERNEL_CODE_SEGMENT, &ISR_ERRROUTINE%d);\n",i, i);
    }
    printf("}\n");
    return 0;
}
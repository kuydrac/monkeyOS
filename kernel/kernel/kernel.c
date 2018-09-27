#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/isr.h>

void kernel_main(){
    isr_install();
    irq_install();
    terminal_initialize();
    printf("Hello World!\n");
    serial_configure(1);
    char *test = "hey!\n";
    serial_write(1,test,strlen(test));
    asm("int $2");
    asm("int $3");
    char *test2 = "hey2!\n";
    serial_write(1,test2,strlen(test2));
    char *test3 = "hey3!\n";
    serial_write(1,test3,strlen(test3));

    /*
    char test4[32];
    while(1){
        printf("Tick: ");
        int_to_ascii(get_tick(),test4);
        printf(test4);
        printf("\n");
    }
    */
    printf("Type. Kernel will process it\nType END to halt the CPU\n> ");
}

void user_input(char *input){
    if (strcmp(input, "END") == 0){
        printf("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    printf("You said: ");
    printf(input);
    printf("\n> ");
}

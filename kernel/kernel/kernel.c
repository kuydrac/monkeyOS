#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/isr.h>

void kernel_init(){
    isr_install();
    irq_install();
    terminal_initialize();
    serial_configure(1);
}

void test_terminal(){
    printf("Hello World!\n");
}

void test_serial(){
    char *test = "hey!\n";
    serial_write(1,test,strlen(test));
}

void test_isr(){
    asm("int $2");
    asm("int $3");
}

void test_irq_timer(){
    char test4[32];
    while(1){
        printf("Tick: ");
        int_to_ascii(get_tick(),test4);
        printf(test4);
        printf("\n");
    }
}

void test_irq(){
    // test_irq_timer does not return
    //test_irq_timer();
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

void kernel_main(){
    kernel_init();

    test_terminal();
    test_serial();
    test_isr();
    test_irq();

    printf("Type. Kernel will process it\nType END to halt the CPU\n> ");
}

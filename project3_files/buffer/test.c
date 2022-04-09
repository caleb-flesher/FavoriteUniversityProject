#include "buffer.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_init_buffer_421 442
#define __NR_insert_buffer_421 443
#define __NR_print_buffer_421 444
#define __NR_delete_buffer_421 445

long init_buff_syscall(void){
	return syscall(__NR_init_buffer_421);
}

long insert_buff_syscall(void){
        return syscall(__NR_insert_buffer_421);
}

long print_buff_syscall(void){
        return syscall(__NR_print_buffer_421);
}

long del_buff_syscall(void){
        return syscall(__NR_delete_buffer_421);
}

int main(int argc, char *argv[]){
	printf("Creating the buffer in kernel space.\n");
	printf("%d\n", init_buff_syscall());

	printf("Deleting the buffer from kernel space.\n");
	printf("%d\n", del_buff_syscall());

	return 0;
}

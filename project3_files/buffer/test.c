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
	long initb;
	initb = init_buff_syscall();
	if(initb < 0){
		perror("Initialization of buffer failed.");
	}
	else{
		printf("Buffer was initialized. Please check dmesg.\n");
	}

	//printf("Deleting the buffer from kernel space. Please check the dmesg...\n");
	//printf("%d\n", del_buff_syscall());

	return 0;
}

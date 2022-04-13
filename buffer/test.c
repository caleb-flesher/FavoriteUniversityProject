#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
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

long insert_buff_syscall(int i){
        return syscall(__NR_insert_buffer_421, i);
}

long print_buff_syscall(void){
        return syscall(__NR_print_buffer_421);
}

long del_buff_syscall(void){
        return syscall(__NR_delete_buffer_421);
}

int main(int argc, char *argv[]){
	long initb;
	long insrb;
	long prntb;
	long deltb;

        // Delete the buffer before it is initialized.
        printf("Testing deletion of buffer before being created.\n");
        deltb = del_buff_syscall();
        if(deltb < 0){
                perror("Deletion  of buffer failed");
        }
        else{
                printf("Buffer was deleted.\n");
        }

	// Insert into the buffer before it is initialized
        printf("Insert into the buffer before it is initialized.\n");
	insrb = insert_buff_syscall(0);
	if(insrb < 0){
		perror("Insert into buffer failed");
	}
	else{
		printf("Value was inserted into buffer.\n");
	}

	// Print the buffer before it is initialized
        printf("Print the buffer before it is initialized.\n");
	prntb = print_buff_syscall();
	if(prntb < 0){
		perror("Printing of buffer failed");
	}
	else{
		printf("Buffer was printed. Please check dmesg.\n");
	}

	// Initialize the buffer
        printf("Initialize the buffer.\n");
	initb = init_buff_syscall();
	if(initb < 0){
		perror("Initialization of buffer failed");
	}
	else{
		printf("Buffer was initialized.\n");
	}

        // Initialize the buffer after already being initialized
        printf("Attempt to reinitialize the buffer.\n");
        initb = init_buff_syscall();
        if(initb < 0){
                perror("Initialization of buffer failed");
        }
        else{
                printf("Buffer was initialized.\n");
        }

	// Print the buffer after being initialized
        printf("Print the buffer before it is initialized.\n");
	prntb = print_buff_syscall();
	if(prntb < 0){
		perror("Printing of buffer failed");
	}
	else{
		printf("Buffer was printed. Please check dmesg.\n");
	}

	// Insert into the buffer after it is initialized
	printf("Insert into the buffer adter it is initialized.\n");
	int count = 0;
	while(count < 20){
		insrb = insert_buff_syscall(count + 1);
		if(insrb < 0){
			perror("Insert into buffer failed");
		}
		else{
			printf("Value was inserted into buffer.\n");
		}

		count++;
	}

	// Print the buffer after being initialized
	printf("Print the buffer after it is initialized and filled.\n");
	prntb = print_buff_syscall();
	if(prntb < 0){
		perror("Printing of buffer failed");
	}
	else{
		printf("Buffer was printed. Please check dmesg.\n");
	}

        // Delete the buffer after it is initialized.
        printf("Testing deletion of buffer after being created.\n");
	deltb = del_buff_syscall();
	if(deltb < 0){
		perror("Deletion of buffer failed\n");
	}
	else{
		printf("Buffer was deleted.\n");
	}

        // Delete the buffer after it is deleted.
        printf("Testing deletion of buffer after being deleted.\n");
        deltb = del_buff_syscall();
        if(deltb < 0){
                perror("Deletion  of buffer failed");
        }
        else{
                printf("Buffer was deleted.\n");
        }

	// Insert into the buffer after it is deleted
	printf("Testing inserting into buffer after being deleted.\n");
	insrb = insert_buff_syscall(1);
	if(insrb < 0){
		perror("Insert into buffer failed");
	}
	else{
		printf("Value was inserted into buffer.\n");
	}

	// Print the buffer after being deleted
	printf("Testing printing of buffer after it is deleted.\n");
	prntb = print_buff_syscall();
	if(prntb < 0){
		perror("Printing of buffer failed");
	}
	else{
		printf("Buffer was printed. Please check dmesg.\n");
	}

        // Initialize the buffer after it is deletes
        printf("Reinitialize the buffer after being deleted.\n");
        initb = init_buff_syscall();
        if(initb < 0){
                perror("Initialization of buffer failed");
        }
        else{
                printf("Buffer was initialized.\n");
        }

        // Delete the buffer after it is reinitialized.
        printf("Delete the buffer after the buffer is reinitialized.\n");
        deltb = del_buff_syscall();
        if(deltb < 0){
                perror("Deletion  of buffer failed");
        }
        else{
                printf("Buffer was deleted.\n");
        }

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "buffer_sem.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_init_buffer_sem_421 446
#define __NR_enqueue_buffer_sem_421 447
#define __NR_dequeue_buffer_sem_421 448
#define __NR_delete_buffer_sem_421 449

static int ITERATE_MAX = 1000;
static int INPUT_VAL = 0;
static int RESTART_INPUT = 9;

long init_buff_syscall(void){
        return syscall(__NR_init_buffer_sem_421);
}

long enqueue_buff_syscall(char *data){
        return syscall(__NR_enqueue_buffer_sem_421, data);
}

long dequeue_buff_syscall(char *data){
        return syscall(__NR_dequeue_buffer_sem_421, data);
}

long del_buff_syscall(void){
        return syscall(__NR_delete_buffer_sem_421);
}


void* producer(void* arg) {
	// Seed for time randomization
	srand(time(NULL));
	int prd_cnt = 0;
	int chr_cnt = 0;
	char pass[DATA_LENGTH] = {};
	char *input = pass;

	while (prd_cnt < ITERATE_MAX){
		// Project document outlines sleep of 10 milliseconds
		usleep(rand() % 10);
		char c = INPUT_VAL + '0';
		while (chr_cnt < DATA_LENGTH){
			pass[chr_cnt] = c;
			chr_cnt++;
		}
		chr_cnt = 0;

		if(INPUT_VAL == RESTART_INPUT)
			INPUT_VAL = 0;
		else
			INPUT_VAL++;

		enqueue_buff_syscall(input);

		// Only print out every 9 iterations
                if(prd_cnt % RESTART_INPUT == 0)
			printf("Produced: %c\n", pass[0]);

		prd_cnt++;
	}
}

void* consumer(void* arg){
        // Seed for time randomization
        srand(time(0) + 1);
	int con_cnt = 0;
	char empty[DATA_LENGTH];
	char *emp_inp = empty;
        while (con_cnt < ITERATE_MAX){
                // Project document outlines sleep of 10 milliseconds
                usleep(rand() % 10);
                dequeue_buff_syscall(emp_inp);

                // Only print out every 9 iterations
                if(con_cnt % RESTART_INPUT == 0)
			printf("Consumed: %c\n", empty[0]);

		con_cnt++;
        }
}

int main(int argc, char *argv[]){
	pthread_t threadId1;
	pthread_t threadId2;
        long initb;
	long enqub;
	long dequb;
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

	// The "random" string is just a value to pass to the function
        // Enqueue to the buffer before it is initialized
	printf("Enqueue to the buffer before it is initialized.\n");
        enqub = enqueue_buff_syscall("random");
        if(enqub < 0){
                perror("Enqueue to buffer failed");
        }
        else{
                printf("Queued to buffer successfully. Please check dmesg.\n");
        }

	// Dequeue from the buffer before it is initialized
        printf("Dequeue to the buffer before it is initialized.\n");
	dequb = dequeue_buff_syscall("random");
        if(enqub < 0){
                perror("Dequeue from buffer failed");
        }
        else{
                printf("Dequeued from buffer successfully. Please check dmesg.\n");
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

	// Create the producer and consumer
	printf("Testing enqueue into buffer after being created. Check dmesg.\n");
        printf("%d\n", pthread_create(&threadId1, NULL, producer, "val"));

	printf("Testing dequeue from buffer after being created. Check dmesg.\n");
        printf("%d\n", pthread_create(&threadId2, NULL, consumer, "val"));

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);

        // Delete the buffer after it is initialized.
        printf("Testing deletion of buffer after being created.\n");
        deltb = del_buff_syscall();
        if(deltb < 0){
                perror("Deletion  of buffer failed");
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

        // Enqueue to the buffer before it is initialized
        printf("Enqueue to the buffer after being deleted.\n");
        enqub = enqueue_buff_syscall("random");
        if(enqub < 0){
                perror("Enqueue to buffer failed");
        }
        else{
                printf("Queued to buffer successfully. Please check dmesg.\n");
        }

        // Dequeue from the buffer before it is initialized
        printf("Dequeue to the buffer before it is initialized.\n");
        dequb = dequeue_buff_syscall("random");
        if(enqub < 0){
                perror("Dequeue from buffer failed");
        }
        else{
                printf("Dequeued from buffer successfully. Please check dmesg.\n");
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

#include <stdio.h>
#include <stdlib.h>
#include "buffer_mon.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>

static int ITERATE_MAX = 1000;
static int INPUT_VAL = 0;
static int RESTART_INPUT = 9;


void* producer(void* arg) {
	// Seed for time sleep randomization
	srand(time(NULL));
	int prd_cnt = 0;
	int chr_cnt = 0;
	char pass[DATA_LENGTH] = {};
	char *input = pass;

	while (prd_cnt < ITERATE_MAX){
		// Project document outlines 10 milliseconds
		usleep(rand() % 10);
		char c = INPUT_VAL + '0';
		while (chr_cnt < DATA_LENGTH){
			pass[chr_cnt] = c;
			chr_cnt++;
		}

		// Restart the input if it is 9
		if(INPUT_VAL == RESTART_INPUT)
			INPUT_VAL = 0;
		else
			INPUT_VAL++;

		enqueue_buffer_421(input);

		// Only print out every 9 iterations
		if(prd_cnt % RESTART_INPUT == 0){
			printf("Produced: %c\n", pass[0]);
		}
		prd_cnt++;
		chr_cnt = 0;
	}
}

void* consumer(void* arg){
	// Seed for time randomization
//	srand(time(0) + 1);
	int con_cnt = 0;
	char empty[DATA_LENGTH] = {};
	char *emp_inp = empty;

        while (con_cnt < ITERATE_MAX){
                // Project document outlines 10 milliseconds
                usleep(rand() % 10);
                dequeue_buffer_421(emp_inp);

                // Only print out every 9 iterations
                if(con_cnt % RESTART_INPUT == 0){
			printf("Consumed: %c\n", emp_inp[0]);
		}
		con_cnt++;
        }
}

int main(int argc, char *argv[]){
	pthread_t threadId1;
	pthread_t threadId2;

	// Test the delete buffer function does not work before the buffer is initialized
        printf("Testing deletion of buffer before being created. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	// Test that the program cannot enqueue/dequeue before the buffer is initialized
	// The "random" string is included below only to satidfy the parameters of the function
	printf("Testing enqueue into buffer before being created. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer before being created. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

	// Initialize the buffer
        printf("Testing initialization of buffer. This will return 0...\n");
        printf("%d\n", init_buffer_421());

	// Test that the buffer cannot be initialized again
        printf("Testing initialization of buffer after being initialized already. This will return -1...\n");
        printf("%d\n", init_buffer_421());

	// Test the enqueue and dequeue functions after the buffer is initialized
	// There are print_semaphores() calls in the producer/consumer to help track what is happening
	// Create the producer and consumer
	printf("Testing enqueue into buffer after being created. This will return 0...\n");
        printf("%d\n", pthread_create(&threadId1, NULL, producer, "val"));

	printf("Testing dequeue from buffer after being created. This will return 0...\n");
        printf("%d\n", pthread_create(&threadId2, NULL, consumer, "val"));

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);

	// Delete the buffer
        printf("Testing deletion of buffer after being created. This will return 0...\n");
        printf("%d\n", delete_buffer_421());

	// Check the buffer cannot be deleted again
        printf("Testing deletion of buffer after being deleted. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	// Check that enqueue and dequeue cannot be called after the buffer is deleted
        // The "random" string is included below only to satidfy the parameters of the function
	printf("Testing enqueue into buffer after being deleted. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer after being deleted. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

	// Check that we can reinitialize the buffer
        printf("Testing reinitialization of buffer. This will return 0...\n");
        printf("%d\n", init_buffer_421());

	// Delete the buffer
        printf("Testing deletion of buffer after being recreated. This will return 0...\n");
        printf("%d\n", delete_buffer_421());

	return 0;
}

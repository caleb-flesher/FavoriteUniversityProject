#include <stdio.h>
#include <stdlib.h>
#include "buffer_sem.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>

static int ITERATE_MAX = 1000;
static int INPUT_VAL = 0;
static int RESTART_INPUT = 9;

void* producer(void* arg) {
	int prd_cnt = 0;
	int chr_cnt = 0;
	char *input[DATA_LENGTH];

	while (prd_cnt < ITERATE_MAX){
		while (chr_cnt < DATA_LENGTH){
			*input[chr_cnt] = INPUT_VAL + '0';
			chr_cnt++;
		}

		if(INPUT_VAL == RESTART_INPUT)
			INPUT_VAL = 0;
		else
			INPUT_VAL++;

		srand(time(NULL));
		usleep(rand());
		enqueue_buffer_421(*input);
		print_semaphores();
		prd_cnt++;
		chr_cnt = 0;
	}
}

void* consumer(void* arg){
	int con_cnt = 0;
	char *emp_inp[DATA_LENGTH];
	*emp_inp[0] = INPUT_VAL + '0';
        while (con_cnt < ITERATE_MAX){
		srand(time(0) + 1);
                usleep(rand());
                dequeue_buffer_421(NULL);
                print_semaphores();
                con_cnt++;
        }
}

int main(int argc, char *argv[]){
	pthread_t threadId1;
	pthread_t threadId2;

        printf("Testing deletion of buffer before being created. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	printf("Testing enqueue into buffer before being created. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer before being created. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

        printf("Testing initialization of buffer. This will return 0...\n");
        printf("%d\n", init_buffer_421());

	printf("Calling print semaphores.\n");
	print_semaphores();

	// Create the producer and consumer
	printf("Testing enqueue into buffer after being created. This will return 0...\n");
        pthread_create(&threadId1, NULL, producer, NULL);

	printf("Testing dequeue from buffer after being created. This will return 0...\n");
        pthread_create(&threadId2, NULL, consumer, NULL);

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);

        printf("Testing deletion of buffer after being created. This will return 0...\n");
        printf("%d\n", delete_buffer_421());

        printf("Testing deletion of buffer after being deleted. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	printf("Testing enqueue into buffer after being deleted. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer after being deleted. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

	return 0;
}

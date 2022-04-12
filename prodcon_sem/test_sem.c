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
	srand(time(NULL));

	int prd_cnt = 0;
	int chr_cnt = 0;
	char pass[DATA_LENGTH] = {};
	char *input = pass;

	while (prd_cnt < ITERATE_MAX){
		usleep(rand() % 10);
		char c = INPUT_VAL + '0';
		while (chr_cnt < DATA_LENGTH){
			pass[chr_cnt] = c;
			chr_cnt++;
		}

		if(INPUT_VAL == RESTART_INPUT)
			INPUT_VAL = 0;
		else
			INPUT_VAL++;

		enqueue_buffer_421(input);
		printf("Produced: %c\n", pass[0]);
		print_semaphores();
		prd_cnt++;
		chr_cnt = 0;
	}
}

void* consumer(void* arg){
	int con_cnt = 0;
	char empty[DATA_LENGTH] = {'0'};
	char *emp_inp = empty;
        while (con_cnt < ITERATE_MAX){
                usleep(rand() % 30);
                dequeue_buffer_421(emp_inp);
//		printf("Consumed: %d\n", con_cnt);
                print_semaphores();
		con_cnt++;
        }
}

int main(int argc, char *argv[]){
	pthread_t threadId1;
	pthread_t threadId2;

        printf("Testing deletion of buffer before being created. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	// The "random" string is included below only to satidfy the parameters of the function
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
        printf("%d\n", pthread_create(&threadId1, NULL, producer, "val"));

	printf("Testing dequeue from buffer after being created. This will return 0...\n");
        printf("%d\n", pthread_create(&threadId2, NULL, consumer, "val"));

//        printf("Testing deletion of buffer during enqueue/dequeue. This will return -1...\n");
//        printf("%d\n", delete_buffer_421());

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

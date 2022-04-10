#include <stdlib.h>
#include <stdio.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

long init_buffer_421(void) {
	// Write your code to initialize buffer
       	// Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                // Allocate the space for the ring buffer and first node
                usrBuf = malloc(sizeof(bb_buffer_421_t));

                struct node_421 *frstNode = malloc(sizeof(bb_node_421_t));
                frstNode->data = 0;

                //Set the read and write to the first node (since it's empty)
                usrBuf->read = frstNode;
                usrBuf->length = 0;

                // Count how many nodes are in the buffer
                int count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
                        struct node_421 *nextNode = malloc(sizeof(node_421_t));
                        nextNode->data = 0;
                        frstNode->next = nextNode;
                        frstNode = nextNode;
                        usrBuf->write = nextNode;
                        count++;
                }

                // Set the ending node next to the read node
                usrBuf->write->next = usrBuf->read;
                usrBuf->read = usrBuf->write;

                // Free the nextNode
                //free(nextNode);
                // Set the buffer to initialized
                isInitialized = true;
	}
	// Initialize your semaphores here.
	
	return 0;
}


long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
}

long dequeue_buffer_421(char * data) {

	// Write your code to dequeue data from the buffer

	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}

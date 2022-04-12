#include <stdlib.h>
#include <stdio.h>
#include "buffer_sem.h"
#include <stdbool.h>
#include <pthread.h>
#include <string.h>

static bb_buffer_421_t *buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;
static bool isInitialized = false;

long init_buffer_421(void) {
	// Write your code to initialize buffer
       	// Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                // Allocate the space for the ring buffer and first node
                buffer = malloc(sizeof(bb_buffer_421_t));

                struct bb_node_421 *frstNode = malloc(sizeof(bb_node_421_t));
                memcpy(frstNode->data, "", DATA_LENGTH);

                //Set the read and write to the first node (since it's empty)
                buffer->read = frstNode;
                buffer->length = 0;

                // Count how many nodes are in the buffer
                int count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
                        struct bb_node_421 *nextNode = malloc(sizeof(bb_node_421_t));
	                memcpy(nextNode->data, "", DATA_LENGTH);
                        frstNode->next = nextNode;
                        frstNode = nextNode;
                        buffer->write = nextNode;
                        count++;
                }

                // Set the ending node next to the read node
                buffer->write->next = buffer->read;
                buffer->read = buffer->write;

                // Free the nextNode
                //free(nextNode);
                // Set the buffer to initialized
                isInitialized = true;
	}
	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1);
	sem_init(&empty_count, 0, SIZE_OF_BUFFER);
	sem_init(&fill_count, 0, 0);
	return 0;
}


long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
	// Check that buffer exists
	if(isInitialized == true){
		// Use the empty_count semaphore to BLOCK if the buffer is empty
		sem_wait(&empty_count);
		sem_wait(&mutex);

		printf("Enqueue: %c\n", data[0]);

		// Write the data to the buffer's write pointer
                memcpy(buffer->write->data, data, DATA_LENGTH);
		buffer->length++;
		buffer->write = buffer->write->next;

		sem_post(&mutex);
		sem_post(&fill_count);

		return 0;
	}

	return -1;
}


long dequeue_buffer_421(char * data) {
	// Write your code to dequeue data from the buffer
        // Check that buffer exists
	if(isInitialized == true){
		// Use the empty_count semaphore to BLOCK if the buffer is empty
		sem_wait(&fill_count);
		sem_wait(&mutex);

		printf("Dequeue: %c\n", buffer->write->data[0]);

		// Write the buffer's read point into the passed char parameter
                memcpy(data, buffer->write->data, DATA_LENGTH);
		buffer->length--;
		buffer->read = buffer->read->next;

		sem_post(&mutex);
		sem_post(&empty_count);

		return 0;
	}

	return -1;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// Check the values of each of the semaphores. If not 0 do not allow the call.

	// Destroy the semaphores
	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);

	// write your code to delete buffer and other unwanted components
        // Check that buffer exists
        if(isInitialized == true){
                // Free the buffer
                struct bb_node_421 *temp;
		int count = SIZE_OF_BUFFER;
                while(count > 0){
                        temp = buffer->read;
                        buffer->read = temp->next;
                        free(temp);
                        temp = NULL;
			count--;
                }

                // Free the buffer
                free(buffer);

                // Set buffer initialized back to false
                isInitialized = false;

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist
        return -1;
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

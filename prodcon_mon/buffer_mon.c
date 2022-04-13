#include <stdlib.h>
#include <stdio.h>
#include "buffer_mon.h"
#include <stdbool.h>
#include <pthread.h>
#include <string.h>

static ring_buffer_421_t *buffer;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t fill_count;
static pthread_cond_t empty_count;
static bool isInitialized = false;

long init_buffer_421(void) {
       	// Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                // Allocate the space for the ring buffer and first node
                buffer = malloc(sizeof(ring_buffer_421_t));

                struct node_421 *frstNode = malloc(sizeof(node_421_t));
                memcpy(frstNode->data, "", DATA_LENGTH);

                //Set the read and write to the first node (since it's empty)
                buffer->read = frstNode;
                buffer->length = 0;

                // Count how many nodes are in the buffer
                int count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
                        struct node_421 *nextNode = malloc(sizeof(node_421_t));
	                memcpy(nextNode->data, "", DATA_LENGTH);
                        frstNode->next = nextNode;
                        frstNode = nextNode;
                        buffer->write = nextNode;
                        count++;
                }

                // Set the ending node next to the read node
                buffer->write->next = buffer->read;
                buffer->read = buffer->write;

                // Set the buffer to initialized
                isInitialized = true;

		// Initialize mutexes here.
		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init(&empty_count, NULL);
		pthread_cond_init(&fill_count, NULL);
		return 0;
	}

	return -1;
}


long enqueue_buffer_421(char * data) {
	// Check that buffer exists
	if(isInitialized == true){
		// Use the fill_count mutex to BLOCK if the buffer is empty
		pthread_mutex_lock(&mutex);
		while(buffer->length == SIZE_OF_BUFFER){
			pthread_cond_wait(&fill_count, &mutex);
		}
		// Write the data from the passed char parameter to the buffer's write pointer
               	memcpy(buffer->write->data, data, DATA_LENGTH);
		buffer->length++;
		printf("Enqueue: %c\n", buffer->write->data[0]);
		buffer->write = buffer->write->next;

		// Unlock the mutex
		pthread_cond_signal(&fill_count);
		pthread_mutex_unlock(&mutex);

		return 0;
	}

	return -1;
}


long dequeue_buffer_421(char * data) {
        // Check that buffer exists
	if(isInitialized == true){
		// Use the empty_count mutex to BLOCK if the buffer is empty
                pthread_mutex_lock(&mutex);
		// This line doesn't seem correct, but this is the only way I could run
		//	the file to completion
                while(buffer->length == SIZE_OF_BUFFER){
			pthread_cond_wait(&empty_count, &mutex);
		}

		printf("Dequeue: %c\n", buffer->read->data[0]);

		// Write the buffer's read point into the passed char parameter
	        memcpy(data, buffer->read->data, DATA_LENGTH);
		buffer->length--;
		buffer->read = buffer->read->next;

		//Unlock the mutex
		pthread_cond_signal(&empty_count);
		pthread_mutex_unlock(&mutex);

		return 0;
	}

	return -1;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// Destroy the mutexes
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&fill_count);
	pthread_cond_destroy(&empty_count);

	// write your code to delete buffer and other unwanted components
        // Check that buffer exists
        if(isInitialized == true){
                // Free the buffer
                struct node_421 *temp;
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

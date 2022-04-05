// C file for the circular buffer in user space
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

struct ring_buffer_421 *usrBuf = NULL;

long init_buffer_421(void){
	// Allocate space for the buffer
	// Check the buffer was not already allocated
	if(usrBuf == NULL){
		// Allocate the space for the ring buffer and first node
		struct ring_buffer_421 *usrBuf = malloc(sizeof(ring_buffer_421_t));

		struct node_421 *usrNode = malloc(sizeof(node_421_t));
		//Set the read and write to the first node (since it's empty)
		usrBuf->read, usrBuf->write = usrNode;
		usrBuf->length = 0;

		// Count how many nodes are in the buffer
		int count = 1;
		struct node_421 *nextNode = malloc(sizeof(node_421_t));

		// Create the nodes of the ring buffer
		while(count < 20){
			nextNode->data = -1;
			usrNode->next = nextNode;
			usrNode = nextNode;
			count++;
		}

		// Set the ending node next to the read node
		nextNode->next = usrBuf->read;

		// Free the nextNode
		//free(nextNode);

		// Return 0 if buffer successfully created
		return 0;
	}

	// Return -1 if buffer is already created
	return -1;
}

long insert_buffer_421(int i){
	// Check that buffer exists
	if(usrBuf != NULL){
		// Return -1 if buffer is already full
		if(usrBuf->length == SIZE_OF_BUFFER)
			return -1;

		// Insert the data into the write node
		usrBuf->write->data = i;

		// Set write node of the buffer to the next empty node, and increase the length of
		//	usrBuf
		usrBuf->write = usrBuf->write->next;
		usrBuf->length += 1;

		// Return 0 if successful
		return 0;
	}

	// Return -1 if buffer does not exist, or any other scenario
	return -1;
}

long print_buffer_421(void){
	// Check that buffer exists
	if(usrBuf != NULL){
		// Print contents
		// Temporary node for the node being printed
		int count = 0;
		while(count < SIZE_OF_BUFFER){
			printf("%d", usrBuf->read->data);
			usrBuf->read = usrBuf->read->next;
			count++;
		}

		// Return 0 if successful
		return 0;
	}

	// Return -1 if buffer is not initialized
	return -1;
}

long delete_buffer_421(void){
	// Check that buffer exists
	if(usrBuf != NULL){
		// Free the buffer
		struct node_421 *temp;
		while(usrBuf->read != NULL){
			temp = usrBuf->read;
			usrBuf->read = temp->next;
			free(temp);
		}

		// Free the buffer
		free(usrBuf);

		// Return 0 if successful
		return 0;
	}

	// Return -1 if buffer does not exist
	return -1;
}

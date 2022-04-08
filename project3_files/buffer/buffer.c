// C file for the circular buffer in kernel space
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"
#include <stdbool.h>

struct ring_buffer_421 *usrBuf;
bool isInitialized = false;

long init_buffer_421(void){
        // Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                // Allocate the space for the ring buffer and first node
                usrBuf = malloc(sizeof(ring_buffer_421_t));

                struct node_421 *frstNode = malloc(sizeof(node_421_t));
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
                // Return 0 if buffer successfully created
                return 0;
        }

        // Return -1 if buffer is already created
        return -1;
}

long insert_buffer_421(int i){
        // Check that buffer exists
        if(isInitialized == true){
                // Return -1 if buffer is already full
                if(usrBuf->length == SIZE_OF_BUFFER)
                        return -1;
                // Insert the data into the write node
                usrBuf->write->data = i;
                //printf("%i\n", i);
                //printf("%i\n", usrBuf->write->data);

                // Set write node of the buffer to the next empty node, and increase the length of
                //      usrBuf
                usrBuf->write = usrBuf->write->next;
                usrBuf->length += 1;

                //print_buffer_421();

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist, or any other scenario
        return -1;
}

long print_buffer_421(void){
        // Check that buffer exists
        if(isInitialized == true){
                // Print contents
                // Temporary node for the node being printed
                int count = 0;
                while(count < SIZE_OF_BUFFER){
                        printf("%i\n", usrBuf->read->data);
                        usrBuf->read = usrBuf->read->next;
                        count++;
                }




long init_buffer_421(void){
	ring_buffer_421 *cirBuf = malloc(sizeOf(ring_buffer_421));
	cirBuf->length = SIZE_OF_BUFFER;

}

long insert_buffer_421(int i){

}

long print_buffer_421(){
	if (
}

long delete_buffer_421(){

}

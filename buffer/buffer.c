// C file for the circular buffer in kernel space
#include "buffer.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>

static ring_buffer_421 *usrBuf;
static int isInitialized = 0;
static int count;

SYSCALL_DEFINE0(init_buffer_421){
        // Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == 0){
		struct node_421 *frstNode;
                // Allocate the space for the ring buffer and first node
                usrBuf = kmalloc(sizeof(ring_buffer_421_t), GFP_KERNEL);
                frstNode = kmalloc(sizeof(node_421_t), GFP_KERNEL);
                frstNode->data = 0;

                //Set the read and write to the first node (since it's empty)
                usrBuf->read = frstNode;
                usrBuf->length = 0;

                // Count how many nodes are in the buffer
		count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
			struct node_421 *nextNode;
                        nextNode = kmalloc(sizeof(node_421_t), GFP_KERNEL);
                        nextNode->data = 0;
                        frstNode->next = nextNode;
                        frstNode = nextNode;
                        count++;
                }

                // Set the ending node next to the read node
                frstNode->next = usrBuf->read;
                usrBuf->write = usrBuf->read;

                // Set the buffer to initialized
                isInitialized = 1;
		// Return 0 if buffer successfully created
                return 0;
        }
        // Return -1 if buffer is already created
        return -1;
}

SYSCALL_DEFINE1(insert_buffer_421, int, i){
        // Check that buffer exists
        if(isInitialized == 1){
                // Return -1 if buffer is already full
                if(usrBuf->length == SIZE_OF_BUFFER)
                        return -1;
                // Insert the data into the write node
                usrBuf->write->data = i;

                // Set write node of the buffer to the next empty node, and increase the length of
                //      usrBuf
                usrBuf->write = usrBuf->write->next;
                usrBuf->length++;

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist, or any other scenario
        return -1;
}

SYSCALL_DEFINE0(print_buffer_421){
	// Check that buffer exists
        if(isInitialized == 1){
                // Print contents
                // Temporary node for the node being printed
                count = 0;
                while(count < SIZE_OF_BUFFER){
                        printk("%d\n", usrBuf->read->data);
                        usrBuf->read = usrBuf->read->next;
                        count++;
                }

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer is not initialized
        return -1;
}

SYSCALL_DEFINE0(delete_buffer_421){
	// Check that buffer exists
        if(isInitialized == 1){
                // Free the buffer
                while(usrBuf->length > 0){
			struct node_421 *temp;
                        temp = usrBuf->read;
                        usrBuf->read = temp->next;
                        kfree(temp);
                        temp = NULL;
                        usrBuf->length--;
                }

                // Free the buffer
                kfree(usrBuf);

                // Set buffer initialized back to false
                isInitialized = 0;

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist
        return -1;
}

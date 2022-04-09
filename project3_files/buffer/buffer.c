// C file for the circular buffer in kernel space
#include "buffer.h"
#include <stdbool.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

struct ring_buffer_421 *usrBuf;
bool isInitialized = false;

SYSCALL_DEFINE0(init_buffer_421){
        // Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                // Allocate the space for the ring buffer and first node
                usrBuf = kmalloc(sizeof(ring_buffer_421_t), GFP_KERNEL);

                struct node_421 *frstNode = kmalloc(sizeof(node_421_t), GFP_KERNEL);
                frstNode->data = 0;

                //Set the read and write to the first node (since it's empty)
                usrBuf->read = frstNode;
                usrBuf->length = 0;

                // Count how many nodes are in the buffer
                int count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
                        struct node_421 *nextNode = kmalloc(sizeof(node_421_t), GFP_KERNEL);
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

SYSCALL_DEFINE1(insert_buffer_421, i){
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

SYSCALL_DEFINE0(print_buffer_421){
        // Check that buffer exists
        if(isInitialized == true){
                // Print contents
                // Temporary node for the node being printed
                int count = 0;
                while(count < SIZE_OF_BUFFER){
                        printk("%i\n", usrBuf->read->data);
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
        if(isInitialized == true){
                // Free the buffer
                struct node_421 *temp;
                while(usrBuf->length > 0){
                        temp = usrBuf->read;
                        usrBuf->read = temp->next;
                        kfree(temp);
                        temp = NULL;
                        usrBuf->length--;
                }

                // Free the buffer
                free(usrBuf);

                // Set buffer initialized back to false
                isInitialized = false;

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist
        return -1;
}

// C file for the semaphore buffer in kernel space
#include "buffer_sem.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>

static bb_buffer_421_t *buffer;
static struct semaphore mutex;
static struct semaphore fill_count;
static struct semaphore empty_count;
static int isInitialized = 0;
static int count;

SYSCALL_DEFINE0(init_buffer_sem_421) {
	// Write your code to initialize buffer
       	// Allocate space for the buffer
        // Check the buffer was not already allocated
        if(isInitialized == false){
                struct bb_node_421 *frstNode;
		long ret;
                // Allocate the space for the ring buffer and first node
                buffer = kmalloc(sizeof(bb_buffer_421_t), GFP_KERNEL);
		frstNode = kmalloc(sizeof(bb_node_421_t), GFP_KERNEL);
                ret = copy_from_user(frstNode->data, "", DATA_LENGTH);

                //Set the read and write to the first node (since it's empty)
                buffer->read = frstNode;
                buffer->length = 0;

                // Count how many nodes are in the buffer
                count = 1;

                // Create the nodes of the ring buffer
                while(count < SIZE_OF_BUFFER){
			long ret2;
                        struct bb_node_421 *nextNode;
			nextNode = kmalloc(sizeof(bb_node_421_t), GFP_KERNEL);
	                ret2 = copy_from_user(nextNode->data, "", DATA_LENGTH);
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
                isInitialized = 1;
	}
	// Initialize your semaphores here.
	sema_init(&mutex, 1);
	sema_init(&empty_count, SIZE_OF_BUFFER);
	sema_init(&fill_count, 0);
	return 0;
}


SYSCALL_DEFINE1(enqueue_buffer_sem_421, char *, data){
	// Write your code to enqueue data into the buffer
	// Check that buffer exists
	if(isInitialized == 1){
		long ret;
		// Use the empty_count semaphore to BLOCK if the buffer is empty
		down(&empty_count);
		down(&mutex);

		// Write the data from the passed char parameter to the buffer's write pointer
                ret = copy_from_user(buffer->write->data, data, DATA_LENGTH);
		buffer->length++;

		printk("Enqueue: %c\n", buffer->write->data[0]);

		buffer->write = buffer->write->next;

		up(&mutex);
		up(&fill_count);

		return 0;
	}

	return -1;
}


SYSCALL_DEFINE1(dequeue_buffer_sem_421, char *, data){
	// Write your code to dequeue data from the buffer
        // Check that buffer exists
	if(isInitialized == 1){
		long ret;
		// Use the empty_count semaphore to BLOCK if the buffer is empty
		down(&fill_count);
		down(&mutex);

		printk("Dequeue: %c\n", buffer->write->data[0]);

		// Write the buffer's read pointer into the passed char parameter
                ret = copy_to_user(data, buffer->write->data, DATA_LENGTH);
		buffer->length--;

		buffer->read = buffer->read->next;

		up(&mutex);
		up(&empty_count);

		return 0;
	}

	return -1;
}


SYSCALL_DEFINE0(delete_buffer_sem_421){
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.

	// write your code to delete buffer and other unwanted components
        // Check that buffer exists
        if(isInitialized == 1){
                // Free the buffer
                struct bb_node_421 *temp;
		count = SIZE_OF_BUFFER;
                while(count > 0){
                        temp = buffer->read;
                        buffer->read = temp->next;
                        kfree(temp);
                        temp = NULL;
			count--;
                }

                // Free the buffer
                kfree(buffer);

                // Set buffer initialized back to false
                isInitialized = 0;

                // Return 0 if successful
                return 0;
        }

        // Return -1 if buffer does not exist
        return -1;
}

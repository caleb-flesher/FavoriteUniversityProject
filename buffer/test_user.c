#include <stdio.h>
#include <stdlib.h>
#include "buffer_user.c"

int main(int argc, char *argv[]){
        // Test the delete buffer function does not work before the buffer is initialized
	printf("Testing deletion of buffer before being created. This will return -1...\n");
	printf("%d\n", delete_buffer_421());

	// Test the print buffer functio does not work before the buffer is initialized
	printf("Testing printing of buffer before being created. This will return -1...\n");
	printf("%d\n", print_buffer_421());

	// Test the insert function does not work before being created
	printf("Testing inserting into buffer before being created. This will return -1...\n");
	printf("%d\n", insert_buffer_421(1));

	// Initialize the buffer
	printf("Testing initialization of buffer. This will return 0...\n");
	printf("%d\n", init_buffer_421());

	// Test that the buffer cannot be reinitialized
	printf("Testing initialization of buffer after already being initialized. This will return -1...\n");
	printf("%d\n", init_buffer_421());

	// Fill the buffer
	printf("Testing inserting into buffer after being created. This will return nothing...\n");
	int count = 0;
	while(count < 20){
		insert_buffer_421(count + 1);
		count = count + 1;
	}

	// Test that the buffer cannot be inserted into after being filled
	printf("Testing inserting into buffer after filled. This will return -1...\n");
	printf("%d\n", insert_buffer_421(1));

	// Print the buffer
	printf("Testing printing of buffer after being created. This will return the buffer and lastly 0...\n");
	printf("%d\n", print_buffer_421());

	// Delete the buffer
	printf("Testing deletion of buffer after being created. This will return 0...\n");
	printf("%d\n", delete_buffer_421());

	// Test insert, print, delete functions of the buffer after the buffer is deleted
	printf("Testing inserting, print, and deleting into buffer after deletion. ");
	printf("This will return -1 for all results...\n");
	printf("There is a while loop that runs 5 times, thus there are many -1 values.\n");
	count = 0;
	while(count < 5){
		printf("%d\n", insert_buffer_421(count));
		printf("%d\n", print_buffer_421());
		printf("%d\n", delete_buffer_421());
		count = count + 1;
	}

	// Test that the buffer reinitializes after being deleted
        printf("Testing reinitialization of buffer after being deleted. This will return 0...\n");
        printf("%d\n", init_buffer_421());

	// Delete the buffer
        printf("Testing deletion of buffer after being recreated. This will return 0...\n");
        printf("%d\n", delete_buffer_421());

	return 0;
}

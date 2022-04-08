#include <stdio.h>
#include <stdlib.h>
#include "buffer_user.c"

int main(int argc, char *argv[]){
	struct ring_buffer_421 *usrBuf;
	printf("Testing deletion of buffer before being created. This will return -1...\n");
	printf("%d\n", delete_buffer_421());

	printf("Testing printing of buffer before being created. This will return -1...\n");
	printf("%d\n", print_buffer_421());

	printf("Testing inserting into buffer before being created. This will return -1...\n");
	printf("%d\n", insert_buffer_421(1));

	printf("Testing initialization of buffer. This will return 0...\n");
	printf("%d\n", init_buffer_421());

	// Causing issues
	printf("Testing initialization of buffer after already being initialized. This will return -1...\n");
	printf("%d\n", init_buffer_421());

	printf("Testing inserting into buffer after being created. This will return nothing...\n");
	int count = 0;
	while(count < 20){
		insert_buffer_421(count + 1);
		count = count + 1;
	}

	printf("Testing inserting into buffer after filled. This will return -1...\n");
	printf("%d\n", insert_buffer_421(1));

	printf("Testing printing of buffer after being created. This will return the buffer and 0...\n");
	printf("%d\n", print_buffer_421());

	printf("Testing deletion of buffer after being created. This will return 0...\n");
	printf("%d\n", delete_buffer_421());

	printf("Testing inserting into buffer after deletion. This will return -1...\n");
	printf("%d\n", insert_buffer_421(1));

	return 0;
}

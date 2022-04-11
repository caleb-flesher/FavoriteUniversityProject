#include <stdio.h>
#include <stdlib.h>
#include "buffer_sem.h"
#include <pthread.h>

int main(int argc, char *argv[]){
        printf("Testing deletion of buffer before being created. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	printf("Testing enqueue into buffer before being created. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer before being created. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

        printf("Testing initialization of buffer. This will return 0...\n");
        printf("%d\n", init_buffer_421());

	printf("Calling print semaphores.\n");
	print_semaphores();

	pthread_t threadId;

	printf("Testing enqueue into buffer after being created. This will return 0...\n");
        printf("%d\n", pthread_create(&threadId, NULL, enqueue_buffer_421, "Agrl3SNGxxJUXFfMivciY8UST3S4q7Q35NVy5JVJ2WZdWbrf5PZ3aMoQtXWqtROIzRewxBEiDVaIdrHjIcvNjJaP7hrRQ0dfWj6qa2SwNI7MTCDdCUPkBmhUx6UZRC2G8GnVorcQwpYSEdQPg1qvcNEubddPYfs9aveZW94m6A4Bs36SLClXhGIKQ8buTHYFzRLG8sCJevbghqXkru2vBa04JHPGt3TCgIysPQJNcKUqMmbAtykCyh8a778p5RBoEQtZpN3ykFIUsbYh5TRRetvhIJqe3GlKX2XPjyzf1TWWiuZsgNzNcftDoj4anpZWNW9tF4xga8PBMiwGfUROL2T1DptNLwHtPnsQr1WKwAec5MtedYblc8sBf4ODj1yTInvdYoz7FyyUmQGBDV9Rs5xkcxgiEy2gf1nK1kBuoJYubgGxQcUTx1r5scOoMRhPoCNOfolKNFzRHm6AEFyBdtJr7e6KWhzg6b1ovFC3xfLPjVG9qVzNr1GDvQXhFlYIojBXuJxiE1IIwqzZwX7KBY4Dc3fUDjmAOhKawm6wiUuhdoghSfNAbTppNHl3PIuJCO4kq4bmiXn5PB8HIUINVnP8u1uxkHUEQroyd5h6Tf4dQ2bDDkWv0sPdYLlV54kPk2SRyptT9Ik7UssKsMfNZN7FuONaZJlmUMxJnTMrXcPxY4wbP2Bd4rxSKUUHirT7xobiFrtHLL2dVF7x8mc3l3TDCny1RW7Afq0k6EdXkrI3XhAiHs81flVLQFQhm1yS4krfHy0FbWtjNClxdolTPpPyVH4oxfb2fgzIT5HMMbH9lXMgN4oimkmQsdAT3ZDeiCGE4ZIOtkKqFDKa3J6yeMHCs4PVVw0gJZAiZlpsyGAegRNo8lU1OyrxwBHk81vENmFLs7J0QHMKFUYnXIIBgcTprzh7ibub3JmJG4w0FWq0Q872F1jKHb7I4nWizSMkBKTL29TWEigxaHY3dITIaOegK4o8bhmd4K57oCEukfmdcJllJwNMPKSRm9Ht9o7o"));

	printf("Calling print semaphores.\n");
	print_semaphores();

	printf("Testing dequeue from buffer after being created. This will return 0...\n");
        printf("%d\n", dequeue_buffer_421("Agrl3SNGxxJUXFfMivciY8UST3S4q7Q35NVy5JVJ2WZdWbrf5PZ3aMoQtXWqtROIzRewxBEiDVaIdrHjIcvNjJaP7hrRQ0dfWj6qa2SwNI7MTCDdCUPkBmhUx6UZRC2G8GnVorcQwpYSEdQPg1qvcNEubddPYfs9aveZW94m6A4Bs36SLClXhGIKQ8buTHYFzRLG8sCJevbghqXkru2vBa04JHPGt3TCgIysPQJNcKUqMmbAtykCyh8a778p5RBoEQtZpN3ykFIUsbYh5TRRetvhIJqe3GlKX2XPjyzf1TWWiuZsgNzNcftDoj4anpZWNW9tF4xga8PBMiwGfUROL2T1DptNLwHtPnsQr1WKwAec5MtedYblc8sBf4ODj1yTInvdYoz7FyyUmQGBDV9Rs5xkcxgiEy2gf1nK1kBuoJYubgGxQcUTx1r5scOoMRhPoCNOfolKNFzRHm6AEFyBdtJr7e6KWhzg6b1ovFC3xfLPjVG9qVzNr1GDvQXhFlYIojBXuJxiE1IIwqzZwX7KBY4Dc3fUDjmAOhKawm6wiUuhdoghSfNAbTppNHl3PIuJCO4kq4bmiXn5PB8HIUINVnP8u1uxkHUEQroyd5h6Tf4dQ2bDDkWv0sPdYLlV54kPk2SRyptT9Ik7UssKsMfNZN7FuONaZJlmUMxJnTMrXcPxY4wbP2Bd4rxSKUUHirT7xobiFrtHLL2dVF7x8mc3l3TDCny1RW7Afq0k6EdXkrI3XhAiHs81flVLQFQhm1yS4krfHy0FbWtjNClxdolTPpPyVH4oxfb2fgzIT5HMMbH9lXMgN4oimkmQsdAT3ZDeiCGE4ZIOtkKqFDKa3J6yeMHCs4PVVw0gJZAiZlpsyGAegRNo8lU1OyrxwBHk81vENmFLs7J0QHMKFUYnXIIBgcTprzh7ibub3JmJG4w0FWq0Q872F1jKHb7I4nWizSMkBKTL29TWEigxaHY3dITIaOegK4o8bhmd4K57oCEukfmdcJllJwNMPKSRm9Ht9o7o"));

	// Use usleep instead of sleep for fast execution

        printf("Testing deletion of buffer after being created. This will return 0...\n");
        printf("%d\n", delete_buffer_421());

        printf("Testing deletion of buffer after being deleted. This will return -1...\n");
        printf("%d\n", delete_buffer_421());

	printf("Testing enqueue into buffer after being deleted. This will return -1...\n");
        printf("%d\n", enqueue_buffer_421("random"));

	printf("Testing dequeue from buffer after being deleted. This will return -1...\n");
        printf("%d\n", dequeue_buffer_421("random"));

	return 0;
}

Name:           Caleb Flesher
Campus ID:      II92330
Class Section:  Section 03

-------INSTRUCTIONS TO RUN THE FILES-------

There are 7 files in this folder for the project, this folder being part 1. The files included are as follows:
- buffer_sem.h

Kernel Space
- buffer_sem.c
- test_sem.c
- MakeFile

User Space
- buffer_user_sem.c
- test_user_sem.c

General information
- On my VM, which is the Debian VM provided to us from the beginning of the semester, I have configured for the use of 6 cores.
- 8192 MB of memory was allocated for the VM.

User space:
- The files must be run in the "prodcon_sem" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/prodcon_sem".
- A Makefile for the user space implementation is not provided.
- In order to compile the test_user_sem.c file, compile the file using the following command: "gcc -pthread buffer_user_sem.c test_user_sem.c -o test_user_sem".
- In order to run the file, run the file using the following command: "./test_user_sem".
- Valgrind is operational with this file. To run the file with valgrind, use the following command: "valgrind ./test_user_sem".
- The code should free all the memory/no memory should be allocated after the test_user.c file is executed.

Kernel Space:
- The files must be run in the "prodcon_sem" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/prodcon_sem".
- The included Makefile is in the "prodcon_Sem" directory is used only to compile the kernel code.
- In order to compile the test_sem.c file, compile the file using the following command: "gcc -pthread test_sem.c -o test_sem".
- In order to run the file, run the file using the following command: "./test_sem".
- You will need to check dmesg after the kernel file is executed. To see dmesg, use the following command: "sudo dmesg". It may take some scrolling, but you
	will notice that the enqueue and dequeue functions will have points where one enqueues or dequeues more data than the other, due to the sleep time.
	This is expected and desired behaviour.
- You can also use the following command to see the tail of the dmesg (this will print the last 50 values that were queued/dequeued):
        "sudo dmesg | tail -50"

-------METHODS-------

I began by creating the user space code, in the buffer_user_sem.c file. I was able to copy the function from the buffer_user.c file from part 1,
then I initialized the semaphores for the enqueue and dequeue functions. I had trouble understanding how these were supposed to be implemented,
but after reading some documentation at length I found a method that created them as they are now. Then I started working on the enqueue and
dequeue functions, in an effort to just have them alter the semaphores so I could make sure they are being accessed. Both of the functions are operational,
however I have found there is an odd issue with the dequeue function. I do not know why, but the dequeue function will fall behind and dequeue the
buffer nodes after enqueue is finished. While this is good because it does not leave queued nodes in the buffer, the function prints zeros at the end of
execution in this scenario. I chose to move forward and bring the functions to kernel space. I revisited this issue again later, and found that the way the
consumer was being passed the variables was what caused the issue. I have not seen it occur again since that change. Regarding the consumer and producer 
functions, these took some time to implement mostly because I needed to research how they should be properly created. I could have used modulus to help
restart the char array input, but for my understanding and therefore implementation of these functions, I used a constant and check the values being passed
to the char array every iteration. A very similar method for the producer and consumer was used in the kernel space implementation.

-NOTE- The producer/consumer only prints what was produced/consumed every 9 times. This was done to allow the graders to see the tests at the beginning 
of the file.

In the kernel space implementation, I started by simply copying the user space files to use as a base, since the logic in the user files could be transferred over
to kernel space. I changed all the user space functions for allocating memory into kernel space functions (such as kfree, printk, etc) and took time to figure
out how to get the semaphore functions to work in kernel space. This took some time and comments from the Discord channel were very helpful in finding the
proper functions to call to get the expected results. One issue I found was that there were some caution messages created when compiling the kernel regarding
the copy_from_user, and copy_to_user functions. These functions return a value, which I was originally not saving which flagged an issue to the compiler.
That is the reason there are "ret" values in the enqueue and dequeue kernel functions, and they are not used elsewhere. I ran into an issue that was identical
to one I had in part 1 of the project, which was the pointer for the dequeue/consumer functions was being printed instead of the first value which is the
expected behaviour. It took me some time to realize I was passing the pointer address to the syscall, rather than the object being pointed to. To clarify,
I was passing "*char" to the syscall rather than just "char". After deleting the asterisk ("*") from the syscall definition, the program ran as expected.

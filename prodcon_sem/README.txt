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
- 8192 MD of memory was allocated for the VM.

User space:
- The files must be run in the "prodcon_sem" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/prodcon_sem".
- A Makefile for the user space implementation is not provided.
- In order to compile the test_user.c file, compile the file using the following command: "gcc -pthread buffer_user_sem.c test_user_sem.c -o test_user_sem".
- In order to run the file, run the file using the following command: "./test_user_sem".
- Valgrind is operational with this file. To run the file with valgrind, use the following command: "valgrind ./test_user_sem".
- The code should free all the memory/no memory should be allocated after the test_user.c file is executed.

Kernel Space:
- The files must be run in the "buffer" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/project3-files/buffer".
- The included Makefile is in the "buffer" directory is used only to compile the kernel code.
- In order to compile the test.c file, compile the file using the following command: "gcc test.c -o test".
- In order to run the file, run the file using the following command: "./test".
- You will need to check dmesg after the kernel file is executed. To see dmesg, use the following command: "sudo dmesg"
- You can also use the following command to see the tail of the dmesg (with the last kernel log message prior to running the kernel buffer file):
        "sudo dmesg | tail -41"

-------METHODS-------

I began by creating the user space code, in the buffer_user_sem.c file. I was able to copy the function from the buffer_user.c file from part 1,
then I initialized the semaphores for the enqueue and dequeue functions. I had trouble understanding how these were supposed to be implemented,
but after reading some documentation at length I found a method that created them as they are now. Then I started working on the enqueue and
dequeue functions, in an effort to just have them alter the semaphores so I could make sure they are being accessed. Both of the functions are operational,
however I have found there is an odd issue with the dequeue function. I do not know why, but the dequeue function will fall behind and dequeue the
buffer nodes after enqueue is finished. While this is good because it does not leave queued nodes in the buffer, the function prints zeros at the end of
execution in this scenario. I chose to move forward and bring the functions to kernel space. See the details below for the kernel space implementation.



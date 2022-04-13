Name:           Caleb Flesher
Campus ID:      II92330
Class Section:  Section 03

-------INSTRUCTIONS TO RUN THE FILES-------

There are 7 files in this folder for the project, this folder being part 1. The files included are as follows:
- buffer_mon.h
- README.txt

User Space
- buffer_mon.c
- test_mon.c

General information
- On my VM, which is the Debian VM provided to us from the beginning of the semester, I have configured for the use of 6 cores.
- 8192 MB of memory was allocated for the VM.

User space:
- The files must be run in the "prodcon_mon" directory. The directory path should read similarly to "/usr/src/project3-calebf2/prodcon_mon".
- A Makefile for this part of the project is not provided.
- In order to compile the test_mon.c file, compile the file using the following command: "-pthread buffer_mon.c test_mon.c -o test_mon".
- In order to run the file, run the file using the following command: "./test_mon".
- Valgrind is operational with this file. To run the file with valgrind, use the following command: "valgrind ./test_mon".
- The code should free all the memory/no memory should be allocated after the test_user.c file is executed.
- The kernel code was not required for this part of the project.

-------METHODS-------

I began part 3 of the project by copying and pasting the buffer_user_sem.c and test_user_sem.c files from part 2.1 of the project. These files had a lot
of the content needed to implement this part of the project, so I knew they would be useful as a base to get the code for this portion. The test file
(test_mon.c) is essentially the same test file as part 2.1 (test_user_sem.c), so few changes were made to the file (such as comments). For the buffer_mon.c
file, I struggled the most with understanding how the condition variables were supposed to be used. The order of them is where I had a lot of issues, 
because I did not know when the pthread_cond_wait() and pthread_cond_signal() functions were supposed to be called. I could not get the program to consistently
run to completion, however almost every time that I ran the program it did complete without memory leaks or errors. One line in particular in the dequeue
function is what I believe to be the major issue and the way I have submitted does not entirely make sense to me, and I have added a comment to it as such.
The examples I did see using the mutex for locking made sense and I tried to apply the same logic in this project. 

--NOTE-- When running this part of the project, it may require a few different executions. It nearly always does execute to completion when I run it. There may
be occasions where execution does not complete.

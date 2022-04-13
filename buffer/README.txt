Name:		Caleb Flesher
Campus ID:	II92330
Class Section:	Section 03

-------INSTRUCTIONS TO RUN THE FILES-------

There are 7 files in this folder for the project, this folder being part 1. The files included are as follows:
- buffer.h
- README.txt

Kernel Space
- buffer.c
- test.c
- MakeFile

User Space
- buffer_user.c
- test_user.c

General information
- On my VM, which is the Debian VM provided to us from the beginning of the semester, I have configured for the use of 6 cores.
- 8192 MB of memory was allocated for the VM.

User space:
- The files must be run in the "buffer" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/buffer".
- A Makefile for the user space implementation is not provided.
- In order to compile the test_user.c file, compile the file using the following command: "gcc test_user.c -o test_user".
- In order to run the file, run the file using the following command: "./test_user". 
- Valgrind is operational with this file. To run the file with valgrind, use the following command: "valgrind ./test_user".
- The code should free all the memory/no memory should be allocated after the test_user.c file is executed.

Kernel Space:
- The files must be run in the "buffer" directory. The directory path should read similarly to "/usr/src/cmsc421-project3/buffer".
- The included Makefile is in the "buffer" directory is used only to compile the kernel code.
- In order to compile the test.c file, compile the file using the following command: "gcc test.c -o test".
- In order to run the file, run the file using the following command: "./test". 
- You will need to check dmesg after the kernel file is executed. To see dmesg, use the following command: "sudo dmesg"
- You can also use the following command to see the tail of the dmesg (with the last kernel log message prior to running the kernel buffer file):
	"sudo dmesg | tail -41"

-------METHODS-------

I began by creating the user space code, in the buffer_user.c file. I struggled with creating the buffer at the start because I did not know a good
method of checking to see if the buffer was already initialized. After asking the class in the Discord server for some information to help me, the
solution I used was to create a static boolean to indicate if the buffer was initialized or not initialized. The print function prints the entirety
of the buffer regardless if data has been entered into it or not, which is how I understood the outline of the project. 

After spending time getting the user space implementation working, I moved to the kernel space. For the buffer.c file, I transferred much of the 
contents from the buffer_user.c file and changed the functions (such as free to kfree and printf to printk) so they would work properly in kernel 
space. After lengthy debugging, I found one of the major issues in the kernel space was printing the contents of the buffer. The kernel 
implementation would print a random garbage value repeatedly. After speaking with Rushabh, I discovered I never passed the parameter into the syscall 
for the insert function. Upon this discovery, I edited the test file, recompiled, and run the test with success.




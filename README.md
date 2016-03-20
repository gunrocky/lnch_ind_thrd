# lnch_ind_thrd
**Running independent threads**:
Write a program that

1. Launches *N* independent threads of execution and waits for the completion of execution of all threads (let *N* be specified as a command line parameter for launching the program).
2. Let each of the threads a fixed number of times in a loop, only indicate itself with a letter or number (different for each thread) in the common indication line, and perform the shortest passive delay each loop (to allow others to work as well).
3. Ensure that threads begin active execution loops not immediately at the moment of creation of each of them, but simultaneously after the creation of the last of *N* threads.
4. Before the program terminates, print an indication line showing the sequence of threads.

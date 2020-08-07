

Our shell by:

Jared Wilson 

Matthew J


Design of our shell:
Our shell is very simple as it has all the executable commands along with a few built-in ones we created. We spent a lot of time
testing and working on this code. Throughout the file, there are countless fprintf statements that we used to test and make sure
commands were running the way they were. We designed our commands using a switch statement that tests for the specific builtins
that we created. With this, it calls upon the specific functions corresponding with the keyword used. Using the "help" command
will show all the built-ins that we created and how to use them. Also in this README, we will describe how to use these as well.
We used fork and execvp to create a parent and child process that can be seen while running our Shell. Once the child process is
initialized, it can execute another program in that process. The second part of this design was that we implemented a way to
spawn a new namespace using the clone command. With this command, we can share a namespace between parent and child processes.
There are a few different containers that can be used while using this command.


List of Commands and how they are used:



CD:
Using the "cd" command, you can surf through your current directory that you are in. This comes in parallel with the ls (system
command) that lists what's in your current directory. Using CD, you can go forward to the next spot in your path.

Help:
Using the "help" command, it produces a list of all the built-in commands that we have implemented. This is helpful to new users
as they can see what they can do while running our shell.

Dog:
Using the "dog" command, this produces a wall of text that represents a dog. We used this for testing and kept it in our code
just for fun.

Clone:
The "clone" command allows for virtualization and the sharing of spaces between a parent and child process. Using this command
will create a child process and allows for different namespaces to be used. These namespaces are called containers and the ones
we have implemented include CLONE_NEWIPC (New namespace for IPC), CLONE_NEWUTS (Setup new hostname and domain), CLONE_NEWUSR
(user and group changes), CLONE_NEWNET(new network namespace), and CLONE_NEWNS (new mount namespace).

Exit:
The "exit" command turns off our shell. This completely stops the current process you are in. If you are in a cloned, child
process then it will take you back to the first parent. If you are in the parent, it will close the program entirely. 


Pros and Cons of our Shell:

Pros: Easy to use, compiles, runs forever unless exited, does the simple tasks as assigned to us, creates parent and child using
fork and execvp

Cons: Kind of messy code with functions all over the place, had to free memory before testing a lot, this was a lot of new 
information for us so it took awhile to figure out.

Intructions on using our Shell:
1. Put the file into a specific place on your computer
2. Open up the terminal and cd into that folder
3. Run "gcc myshell.c -o foo"
4. Run "sudo ./a.out"
5. This should show the command line for the shell, you can now enter any of the above commands shown.
6. Type help to see the list of builtin commands
7. The system commands can also be used such as mkdir, echo, and ls.
8. To exit, type exit into the shell

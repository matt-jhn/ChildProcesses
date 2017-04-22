//Matthew Johnson
//ITCS 3146-001

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    //Will hold result of forking a child process to error check and sync up child and parent
    pid_t child_pid;
    int userChoice;

    do
    {
        do
        {
            printf("\nMenu Process ID: %ld", (long)getpid());
            printf("\nChoose the menu option you wish to execute:");
            printf("\n(1) Display current date and time");
            printf("\n(2) Display the calendar of the current month");
            printf("\n(3) List the files in the current directory");
            printf("\n(4) Exit from the program\n\nEnter your choice: ");
            scanf("%d", &userChoice);
        }
        //loops if the user inputs an invalid menu choice
        while (userChoice != 1 && userChoice != 2 && userChoice !=3 && userChoice != 4);
        if (userChoice == 1)
        {
            //creates child process for calling date
            child_pid = fork();
            //error checking if the fork failed, which terminates the program
            if (child_pid == -1)
            {
                printf("\nFailed to fork, terminating process.");
                return 1;
            }
            //This block will only be executed by the child process
            if (child_pid == 0)
            {
                //lists the ID of the child and the parent
                printf("\nChild Process ID: %ld; Parent ID: %ld\n", (long)getpid(), (long)getppid());
                system("date");
                //ends the child process
                exit(0);
            }
            else
            {
                //has the parent process wait to loop back to the menu until the child is finished
                wait(NULL);
            }
        }
        //Each if statement is identical to the previous one save for the system call it uses
        else if (userChoice == 2)
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                printf("\nFailed to fork, terminating process.");
                return 1;
            }
            if (child_pid == 0)
            {
                printf("\nChild Process ID: %ld; Parent ID: %ld", (long)getpid(), (long)getppid());
                system("cal");
                exit(0);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (userChoice == 3)
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                printf("\nFailed to fork, terminating process.");
                return 1;
            }
            if (child_pid == 0)
            {
                printf("\nChild Process ID: %ld; Parent ID: %ld", (long)getpid(), (long)getppid());
                system("ls -l");
                exit(0);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            printf("\n\nProgram terminated by user choice.\n");
            return 1;
        }
    }
    while(1);
}
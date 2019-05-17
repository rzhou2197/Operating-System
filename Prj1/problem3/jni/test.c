#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t parent_pid;
    pid_t child_pid;

    parent_pid = getpid();
    child_pid = fork();

    if(child_pid==0)
    {
      execl("./ptree","ptree",(char*)0 );
    }
    else{
      printf("516021910576Parent, %d\n", parent_pid);
      printf("516021910576Child, %d\n", child_pid);
    }

    return 0;
}

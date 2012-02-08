#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int abc = 1;

void ctrl_c(int signo)
{
	int pid = 0, gid = 0;
	pid = getpid();
	gid = getppid();
	
	printf ("PID: %d GID: %d signal: %d\n", pid, gid, signo);
}
void ctrl_z(int signo)
{	
	abc = 0;
}


int main()
{
	signal(SIGINT, ctrl_c);
	signal(SIGTSTP, ctrl_z);
	while(abc);
}


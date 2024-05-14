#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
void ret_creation(ret1,ret2,ret3,ret4,ret5,ret6);
void sigchld_handler(int sig) {
	int s;
	wait(&s);
	printf("child exit status: %d\n", WEXITSTATUS(s));
}

int main() {
	int ret1,ret2,ret3,ret4,ret5,ret6, i;
	ret_creation()
	signal(SIGCHLD, sigchld_handler);
	if(ret == 0) {
		// child process
		for(i=1; i<=5; i++) {
			printf("child: %d\n", i);
			sleep(1);
		}
		_exit(2);
	}
	else {
		// parent process
		for(i=1; i<=10; i++) {
			printf("parent: %d\n", i);
			sleep(1);
		}
	}
	return 0;
}
void ret_creation(ret1,ret2,ret3,ret4,ret5,ret6){
	ret1 =fork();
	ret2=fork();
	ret3 =fork();
	ret4 =fork();
	ret5 =fork();
	ret6 =fork();
}

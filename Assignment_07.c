/*From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these
processes should run concurrently for 5 seconds and cleaned up properly upon termination.*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){

	int childA,childB,childC,childD
	int i,s1,s2,s3,s4;
	childA=fork();
	printf("Child A is created\n");
	if(childA==0){
			childB=fork();
			printf("Child B is created\n");
			if(childB==0){
				childC=fork();
				printf("ChildC is created\n");
				if(childC==0){
					ChildD=fork();
					printf("ChildD is created \n");
					if(childD==0){
						sleep(1);
						_exit(0);
					}
					sleep(1);
					waitpid(childD,&s4,0);
					_exit(0);
				}
					sleep(1);
					waitpid(childC,&s3,0);
					_exit(0);
			}
					sleep(1);
					waitpid(childB,&s2,0);
					_exit(0);
	}
					sleep(1);
					waitpid(childa,&s1,0);
					_exit(0);
	
	return 0;

}


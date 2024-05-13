
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){

	int ret,i,s;
	
	for(i=1;i<=5;i++){
		ret = fork();
		if(ret ==0){
			for(int j =1;j<=5;j++){
				printf("%d %d\n",j,getpid());
				sleep(1);
			}
		_exit(2);	
		}
	}
	for(i=1;i<=5;i++){
		wait(&s);

	}	
	return 0;

}

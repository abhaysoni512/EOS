#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(){
	int ret,s,n1,n2,res;
	int arr1[2],arr2[2];
	ret = pipe(arr1);
	if(ret<0){
		perror("pipe failed");
		_exit(1);

	}
	ret = pipe(arr2);
	if(ret<0){
		perror("pipe failed");
		_exit(1);

	}
	ret = fork();
	if(ret<0){
		perror("fork failed");
		_exit(1);

	}
	if(ret==0){
		close(arr1[0]);
		close(arr2[1]);
		printf("Enter 1st no :");
		scanf("%d",&n1);
		printf("Enter 2nd no :");
		scanf("%d",&n2);
		write(arr1[1],&n1,sizeof(n1));
		write(arr1[1],&n2,sizeof(n2));

		read(arr2[0],&res,sizeof(res));
		printf("result: %d\n",res);
		close(arr1[1]);
		close(arr2[0]);
	}
	else{
		close(arr1[1]);
		close(arr2[0]);
		read(arr1[0],&n1,sizeof(n1));
		read(arr1[0],&n2,sizeof(n2));
		res = n1+n2;
		write(arr2[1],&res,sizeof(res));
		close(arr2[1]);
		close(arr1[0]);
		
		waitpid(-1,&s,0);
		
	}
	printf("bye\n");
	return 0;




}

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// p1 -- writer
int main() {
	int fd1,fd2;
	int n1,n2,res;
	fd1 = open("/tmp/fifo1", O_WRONLY);
	if(fd1 < 0) {
		perror("open() failed");
		_exit(1);
	}
	
	fd2 = open("/tmp/fifo2", O_RDONLY);
	if(fd2 < 0) {
		perror("open() failed");
		_exit(1);
	}
	printf("enter n1: ");
	scanf("%d",&n1);
	printf("enter n2: ");
	scanf("%d",&n2);

	write(fd1, &n1,sizeof(n1));
	printf("%d wriiten sucessfully\n",n1);
	write(fd1, &n2,sizeof(n2));
	printf("%d wriiten sucessfully\n",n2);
	
	//
	printf("waiting for data3....\n");
	read(fd2,&res,sizeof(res));
	printf("%d is result\n",res);
	close(fd1);
	close(fd2);
	return 0;
}


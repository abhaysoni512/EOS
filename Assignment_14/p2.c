#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// p2 -- reader
int main() {
	
	int fd1,fd2,cnt;
	int n1,n2,res;
	fd1 = open("/tmp/fifo1", O_RDONLY);
	if(fd1 < 0) {
		perror("open() failed");
		_exit(1);
	}
	
	fd2 = open("/tmp/fifo2", O_WRONLY);
	if(fd2 < 0) {
		perror("open() failed");
		_exit(1);
	}
	printf("waiting for data1...\n");
	cnt = read(fd1, &n1, sizeof(n1));
	printf("read from fifo1: %d bytes -- %d\n", cnt, n1);
	printf("waiting for data2...\n");
	cnt = read(fd1, &n2, sizeof(n2));
	printf("read from fifo2: %d bytes -- %d\n", cnt, n2);
	res = n1+n2;
	write(fd2,&res,sizeof(res));
	printf("%d is send in fifo sucessfully\n",res);
	close(fd1);
	close(fd2);
	return 0;
}



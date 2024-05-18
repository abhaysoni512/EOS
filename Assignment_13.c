#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int arr[2];
void sigint_handler(int s){
    printf("SIGINT Caught %d\n",s);
    close(arr[1]);
    close(arr[0]);
    _exit(0);
}
int main(){

    char ch = 'A';
    int ret;
    int count =1;
    ret = pipe(arr);
    struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);
    if(ret < 0) {
		perror("sigaction() failed");
		_exit(1);
	}
    while(1){
        write(arr[1],&ch,1);
        count++;
        printf("bytes written %d\n",count);
    }
   return 0;
}

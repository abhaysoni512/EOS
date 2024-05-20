#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/desd_socket"

int serv_fd;
void SIG_INT(int sig){
	
	close(serv_fd);
	shutdown(serv_fd, SHUT_RDWR);
	_exit(0);

}
int main(){
	int num1,num2,result;
	int	ret,cli_fd;
	struct sockaddr_un serv_addr, cli_addr; // Corrected struct name
	socklen_t socklen;
	
	struct sigaction sa;
	memset(&sa,0,sizeof(struct sigaction));
	sa.sa_handler =SIG_INT;
	ret = sigaction(SIGINT,&sa,NULL);
	if(ret<0){
		perror("sigaction() failed");
	}
	
	serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(serv_fd < 0){ // Corrected variable name
		perror("socket failed");
		_exit(1);
	}

	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path,SOCK_PATH);
	ret = bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret < 0){
		perror("bind() failed");
		_exit(2);
	}

	listen(serv_fd, 5);


	while(1) {
		socklen = sizeof(cli_addr);
		cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &socklen);
		if(cli_fd < 0){
			perror("accept() failed");
			_exit(2);
		}

		read(cli_fd, &num1, sizeof(int));
		read(cli_fd, &num2, sizeof(int));
		result = num1 + num2;
		write(cli_fd, &result, sizeof(int));
		close(cli_fd);
	}
	return 0;
}












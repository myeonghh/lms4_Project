#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
	
#define BUF_SIZE 1000
	
void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);
	
char msg[BUF_SIZE];
	
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	 }
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	  
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");
	
	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);
	close(sock);  
	return 0;
}
	
void * send_msg(void * arg)   // send thread main
{
	int sock=*((int*)arg);
	char msg[BUF_SIZE];
	while(1) 
	{
		fgets(msg, BUF_SIZE, stdin);
		if (!strcmp(msg,"/q\n")||!strcmp(msg,"/Q\n")) 
		{
			close(sock);
			exit(0);
		}
		else if (strcmp(msg, "/clear\n") == 0)
		{
			system("clear");
		}
		else if (strcmp(msg, "/l\n") == 0)
		{
			system("clear");
			// printf("\t\t\t   < 내 쪽지함 >\n\n");
			// printf("[번호]       [보낸시간]           [보낸사람]         [쪽지내용]\n");
			// printf("----------------------------------------------------------------------------------\n");
		}	
		write(sock, msg, strlen(msg));
	}
	return NULL;
}
	
void * recv_msg(void * arg)   // read thread main
{
	int sock=*((int*)arg);
	char msg[BUF_SIZE];
	int str_len;
	while(1)
	{
		memset(msg, 0, sizeof(msg));
		str_len = read(sock, msg, BUF_SIZE-1);
		if(str_len==-1) 
			return (void*)-1;
		msg[str_len]=0;
		// if (strcmp(msg, "&^clear^&\n") == 0)
		// {
		// 	system("clear"); // 서버에게 위의 문장 수신하면 클라이언트 화면 초기화
		// }
		// else
		// {
		// 	fputs(msg, stdout);
		// }
		fputs(msg, stdout);
		
	}

	return NULL;
}
	
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
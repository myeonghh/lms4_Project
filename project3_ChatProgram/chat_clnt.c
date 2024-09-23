#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <time.h>
	
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
			write(sock, msg, strlen(msg));
		}
		else if (strcmp(msg, "/clear\n") == 0)
		{
			system("clear");
		}
		else if (strcmp(msg, "/help\n") == 0)
		{
			printf("\n―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n\n");
			printf(" 로그아웃: /q,  화면초기화: /clear,  채팅수신차단: /b,  채팅수신허용: /p\n\n");
			printf(" 쪽지함 모드: /letter,  현재방 유저목록보기: /users,  유저검색: /s 닉네임\n\n");
			printf(" 귓속말 전송: /w 닉네임 귓속말내용,  생성된 방 목록보기: /rooms\n\n");
			printf(" 방입장: /enter 방번호 비밀번호(비밀방일시),  초대하기: /invite 닉네임\n\n");
			printf(" 방만들기: /create 방최대인원 비밀번호(공개방일시 '0'입력) 방제목\n");
			printf("\n―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n\n");
		}
		else
		{
			write(sock, msg, strlen(msg));
		}
	}
	return NULL;
}
	
void * recv_msg(void * arg)   // read thread main
{
	int sock=*((int*)arg);
	char msg[BUF_SIZE];
	char *l_msg;
	int str_len;
	while(1)
	{
		memset(msg, 0, sizeof(msg));
		str_len = read(sock, msg, BUF_SIZE-1);
		if(str_len==-1) 
			return (void*)-1;
		msg[str_len]=0;

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
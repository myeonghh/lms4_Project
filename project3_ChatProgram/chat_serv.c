#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 200
#define MAX_CLNT 256
#define MAX_ID_LEN 30
#define MAX_PW_LEN 30
#define MAX_NK_lEN 30
#define MAX_REG_USER 50

typedef struct letter
{
	 char sender_id[MAX_ID_LEN];
	 char sender_nck[MAX_NK_lEN];
	 char text[500];

}LETTER;

typedef struct user
{
	int user_num;
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
	char nick_name[MAX_NK_lEN];
	char phone_num[12];
	char e_mail[40];
	char f_question[100];
	char f_answer[100];
	int socket_num;
	int state; // 1: 로그인, 2: 로그아웃, 3: 회원탈퇴, 
	LETTER letter_box[10];

}USER;

USER reg_user_list[MAX_REG_USER] = {0,};




void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(char * msg);

int reg_user_cnt = 0;
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	pthread_mutex_init(&mutx, NULL);
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	while(1)
	{
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
		
		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutx);
	
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}
	
void * handle_clnt(void * arg)
{
	// int user_num;
	// char id[MAX_ID_LEN];
	// char pw[MAX_PW_LEN];
	// char nck_name[MAX_NK_lEN];
	// int phone_num;
	// char e_mail[30];
	// char f_question[100];
	// char f_answer[20];
	int clnt_sock=*((int*)arg);
	int str_len=0, i, choice_num, dup_chk, login_chk, back_chk;
	char msg[BUF_SIZE];
	char choice_str[BUF_SIZE];
	char id_str[BUF_SIZE];
	char pw_str[BUF_SIZE];
	char pw_re_str[BUF_SIZE];
	char nick_str[BUF_SIZE];
	char phone_num_str[BUF_SIZE];
	char e_mail_str[BUF_SIZE];
	char f_question_str[BUF_SIZE];
	char f_answer_str[BUF_SIZE];

	char start_str[] = "짭레그램에 오신걸 환영합니다\n";

	write(clnt_sock, start_str, strlen(start_str));

	while(1)
	{
		write(clnt_sock, "1.로그인 / 2.회원가입 / 3.ID 찾기 / 4.비밀번호 찾기\n", strlen("1.로그인 / 2.회원가입 / 3.ID 찾기 / 4.비밀번호 찾기\n"));
		str_len = read(clnt_sock, choice_str, sizeof(choice_str));
		printf("입력한 숫자 %s", choice_str);
		choice_str[str_len-1] = '\0';
		choice_num = atoi(choice_str);

		if (choice_num == 1) // 로그인
		{
			printf("1번 입력\n");

			while (1)
			{
				back_chk = 0;

				write(clnt_sock, "[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
				str_len = read(clnt_sock, id_str, sizeof(id_str));
				printf("입력한 아이디 %s", id_str);
				id_str[str_len-1] = '\0';
								
				if (strcmp(id_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}

				write(clnt_sock, "[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
				str_len = read(clnt_sock, pw_str, sizeof(pw_str));
				printf("입력한 비밀번호 %s", pw_str);
				pw_str[str_len-1] = '\0';

				if (strcmp(pw_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}

				login_chk = 0;
				for (i = 0; i < reg_user_cnt; i++)
				{
					if (strcmp(id_str, reg_user_list[i].id) == 0 && strcmp(pw_str, reg_user_list[i].pw) == 0)
					{
						login_chk = 1;
						break;
					}
				}

				if (login_chk == 1)
				{
					write(clnt_sock, "로그인 성공\n", strlen("로그인 성공\n"));
					break;
				}
				else
				{
					write(clnt_sock, "아이디 또는 비밀번호가 맞지 않습니다.\n", strlen("아이디 또는 비밀번호가 맞지 않습니다.\n"));
					continue;
				}
				
			}
			if (login_chk == 1)
				break;
			if (back_chk == 1)
				continue;
		}
		else if (choice_num == 2) // 회원가입
		{
			printf("2번 입력\n");
			
			//============================================ 아이디 ============================================================
			write(clnt_sock, "[ 회원가입 할 아이디를 입력하세요 (영어, 숫자 사용 // 4~15 글자) ]\n", strlen("[ 회원가입 할 아이디를 입력하세요 (영어, 숫자 사용 // 4~15 글자) ]\n"));
			while ((str_len = read(clnt_sock, id_str, sizeof(id_str))) != 0) // 아이디 입력
			{
				printf("입력한 아이디 %s", id_str);

				id_str[str_len - 1] = '\0';

				if (!(strlen(id_str) >= 4 && strlen(id_str) <= 15)) // 아이디 숫자 수 체크
				{
					write(clnt_sock, "4~15 사이의 글자수를 입력하세요.\n", strlen("4~15 사이의 글자수를 입력하세요.\n"));
					continue;
				}
				
				dup_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < MAX_REG_USER; i++) // 아이디 중복 체크
				{
					if (strcmp(reg_user_list[i].id, id_str) == 0)
					{
						dup_chk = 1;
						break;
					}		
				}
				pthread_mutex_unlock(&mutx);
				if (dup_chk == 1)
				{
					write(clnt_sock, "이미 가입 된 아이디 입니다. 다시 입력하세요.\n", strlen("이미 가입 된 아이디 입니다. 다시 입력하세요.\n"));
					continue;
				}

				break;
			}
			printf("검수 완료 아이디 %s\n", id_str);

			//============================================ 비밀 번호 ====================================================================
			write(clnt_sock, "[ 비밀번호를 입력하세요 (4~15 글자) ]\n", strlen("[ 비밀번호를 입력하세요 (4~15 글자) ]\n"));
			while ((str_len = read(clnt_sock, pw_str, sizeof(pw_str))) != 0) // 비밀번호 입력
			{
				printf("입력한 비밀번호 %s", pw_str);

				pw_str[str_len - 1] = '\0';

				if (!(strlen(pw_str) >= 4 && strlen(pw_str) <= 15)) // 비밀번호 숫자 수 체크
				{
					write(clnt_sock, "4~15 사이의 글자수를 입력하세요.\n", strlen("4~15 사이의 글자수를 입력하세요.\n"));
					continue;
				}
				
				write(clnt_sock, "[ 비밀번호를 다시 한 번 입력하세요 ]\n", strlen("[ 비밀번호를 다시 한 번 입력하세요 ]\n"));
				str_len = read(clnt_sock, pw_re_str, sizeof(pw_str));
				pw_re_str[str_len - 1] = '\0';

				if (strcmp(pw_str, pw_re_str) != 0)
				{
					write(clnt_sock, "[ 비밀번호를 입력하세요 (4~15 글자) ]\n", strlen("[ 비밀번호를 입력하세요 (4~15 글자) ]\n"));
					continue;
				}

				break;
			}
			printf("검수 완료 비밀번호 %s\n", pw_str);

			//============================================ 닉네임 ================================================
			write(clnt_sock, "[ 닉네임을 입력하세요 (4~15 글자) ]\n", strlen("[ 닉네임을 입력하세요 (4~15 글자) ]\n"));
			while ((str_len = read(clnt_sock, nick_str, sizeof(nick_str))) != 0) // 닉네임 입력
			{
				printf("입력한 닉네임 %s", nick_str);

				nick_str[str_len - 1] = '\0';

				if (!(strlen(nick_str) >= 4 && strlen(nick_str) <= 15)) // 닉네임 숫자 수 체크
				{
					write(clnt_sock, "4~15 사이의 글자수를 입력하세요.\n", strlen("4~15 사이의 글자수를 입력하세요.\n"));
					continue;
				}
				
				dup_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < MAX_REG_USER; i++) // 닉네임 중복 체크
				{
					if (strcmp(reg_user_list[i].nick_name, nick_str) == 0)
					{
						dup_chk = 1;
						break;
					}
				}
				pthread_mutex_unlock(&mutx);
				if (dup_chk == 1)
				{
					write(clnt_sock, "이미 가입 된 닉네임 입니다. 다시 입력하세요.\n", strlen("이미 가입 된 닉네임 입니다. 다시 입력하세요.\n"));
					continue;
				}

				break;
			}
			printf("검수 완료 닉네임 %s\n", nick_str);

			//============================================ 휴대폰 번호 ================================================
			write(clnt_sock, "[ 휴대폰 번호를 입력하세요 ('-' 제외 숫자만)) ]\n", strlen("[ 휴대폰 번호를 입력하세요 ('-' 제외 숫자만)) ]\n"));
			while ((str_len = read(clnt_sock, phone_num_str, sizeof(phone_num_str))) != 0) // 휴대폰 번호 입력
			{
				printf("입력한 휴대폰 번호 %s", phone_num_str);

				phone_num_str[str_len - 1] = '\0';

				if (strlen(phone_num_str) != 11) // 휴대폰 번호 숫자 수 체크
				{
					write(clnt_sock, "휴대폰 번호 숫자 11개를 다시 입력하세요.\n", strlen("휴대폰 번호 숫자 11개를 다시 입력하세요.\n"));
					continue;
				}
				
				dup_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < MAX_REG_USER; i++) // 휴대폰 번호 중복 체크
				{
					if (strcmp(reg_user_list[i].phone_num, phone_num_str) == 0)
					{
						dup_chk = 1;
						break;
					}
				}
				pthread_mutex_unlock(&mutx);
				if (dup_chk == 1)
				{
					write(clnt_sock, "이미 가입 된 휴대폰 번호 입니다. 다시 입력하세요.\n", strlen("이미 가입 된 휴대폰 번호 입니다. 다시 입력하세요.\n"));
					continue;
				}
				break;
			}
			printf("검수 완료 휴대폰 번호 %s\n", phone_num_str);

			//============================================ 이메일 ================================================
			write(clnt_sock, "[ 이메일 주소를 입력하세요(30자 이하) ]\n", strlen("[ 이메일 주소를 입력하세요(30자 이하) ]\n"));
			while ((str_len = read(clnt_sock, e_mail_str, sizeof(e_mail_str))) != 0) // 이메일 주소 입력
			{
				printf("입력한 이메일 주소 %s", e_mail_str);

				e_mail_str[str_len - 1] = '\0';

				if (!(strlen(e_mail_str) >= 1 && strlen(e_mail_str) <= 30)) // 이메일 주소 숫자 수 체크
				{
					write(clnt_sock, "이메일 주소를 다시 입력하세요.\n", strlen("이메일 주소를 다시 입력하세요.\n"));
					continue;
				}
				
				dup_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < MAX_REG_USER; i++) // 이메일 주소 중복 체크
				{
					if (strcmp(reg_user_list[i].e_mail, e_mail_str) == 0)
					{
						dup_chk = 1;
						break;
					}
				}
				pthread_mutex_unlock(&mutx);
				if (dup_chk == 1)
				{
					write(clnt_sock, "이미 가입 된 이메일 주소 입니다. 다시 입력하세요.\n", strlen("이미 가입 된 이메일 주소 입니다. 다시 입력하세요.\n"));
					continue;
				}
				break;
			}
			printf("검수 완료 이메일 주소 %s\n", e_mail_str);

			//============================================ 비밀번호 찾기 질문 ================================================
			write(clnt_sock, "[ 비밀번호 찾기에 사용되는 질문을 입력하세요(30자 이하) ]\n", strlen("[ 비밀번호 찾기에 사용되는 질문을 입력하세요(30자 이하) ]\n"));
			while ((str_len = read(clnt_sock, f_question_str, sizeof(f_question_str))) != 0) // 질문 입력
			{
				printf("입력한 질문 %s", f_question_str);

				f_question_str[str_len - 1] = '\0';

				if (!(strlen(f_question_str) >= 1 && strlen(f_question_str) <= 90)) // 질문 숫자 수 체크
				{
					write(clnt_sock, "질문을 다시 입력하세요.\n", strlen("질문을 다시 입력하세요.\n"));
					continue;
				}
				
				break;
			}
			printf("검수 완료 질문 %s\n", f_question_str);


			//============================================ 비밀번호 찾기 정답 ================================================
			write(clnt_sock, "[ 비밀번호 찾기에 사용되는 정답을 입력하세요(20자 이하) ]\n", strlen("[ 비밀번호 찾기에 사용되는 정답을 입력하세요(20자 이하) ]\n"));
			while ((str_len = read(clnt_sock, f_answer_str, sizeof(f_answer_str))) != 0) // 정답 입력
			{
				printf("입력한 정답 %s", f_answer_str);

				f_answer_str[str_len - 1] = '\0';

				if (!(strlen(f_answer_str) >= 1 && strlen(f_answer_str) <= 60)) // 정답 숫자 수 체크
				{
					write(clnt_sock, "정답을 다시 입력하세요.\n", strlen("정답을 다시 입력하세요.\n"));
					continue;
				}
				
				break;
			}
			printf("검수 완료 질문 %s\n", f_answer_str);


			pthread_mutex_lock(&mutx);
			reg_user_list[reg_user_cnt].user_num = reg_user_cnt + 1;
			reg_user_list[reg_user_cnt].socket_num = clnt_sock;
			reg_user_list[reg_user_cnt].state = 2; // 유저 상태 로그아웃으로 바꿈 
			strcpy(reg_user_list[reg_user_cnt].id, id_str);
			strcpy(reg_user_list[reg_user_cnt].pw, pw_str);
			strcpy(reg_user_list[reg_user_cnt].nick_name, nick_str);
			strcpy(reg_user_list[reg_user_cnt].phone_num, phone_num_str);
			strcpy(reg_user_list[reg_user_cnt].e_mail, e_mail_str);
			strcpy(reg_user_list[reg_user_cnt].f_question, f_question_str);
			strcpy(reg_user_list[reg_user_cnt].f_answer, f_answer_str);
			reg_user_cnt++;
			pthread_mutex_unlock(&mutx);

			write(clnt_sock, "회원 가입이 완료 되었습니다! 로그인 하세요.\n\n", strlen("회원 가입이 완료 되었습니다! 로그인 하세요.\n\n"));
			continue;
		}
		else if (choice_num == 3) // 아이디 찾기
		{
			printf("3번 입력\n");
		}
		else if (choice_num == 4) // 비밀번호 찾기
		{
			printf("4번 입력\n");
		}
		else
		{
			write(clnt_sock, "번호를 다시 입력하세요!\n", strlen("번호를 다시 입력하세요!\n"));
		}

	}
	
	for (i = 0; i < reg_user_cnt; i++)
	{
		printf("%s, %s, %s, %s, %s, %s\n", reg_user_list[i].id, reg_user_list[i].pw, reg_user_list[i].nick_name, reg_user_list[i].phone_num, reg_user_list[i].e_mail, reg_user_list[i].f_question);
	}
	
	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
	{
		printf("%s", msg);
		send_msg(msg, str_len);
	}
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)   // remove disconnected client
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}
void send_msg(char * msg, int len)   // send to all
{
	int i;
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);
	pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
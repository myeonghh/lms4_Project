#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>

#define BUF_SIZE 1000
#define MAX_CLNT 256
#define MAX_ID_LEN 30
#define MAX_PW_LEN 30
#define MAX_NK_lEN 30
#define MAX_REG_USER 100
#define MAX_LOGIN_USER 100
#define MAX_ROOM 10
#define yellow "\033[38;2;255;255;0m"
#define blue "\033[38;2;79;117;255m"
#define green "\033[38;2;110;194;7m"
#define color_end "\033[0m"

typedef struct letter
{
	int letter_num;
	char time[500];
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
	int state; // 1: 회원가입, 2: 회원탈퇴, 3: 수신거부
	int room_num; // 현재 유저의 채팅방 번호 => 로비 채팅방 1번
	int letter_cnt;
    int letter_snum;
	LETTER letter_box[10];

}USER;

typedef struct room
{
	int room_num;
	int max_user;
	int user_cnt;
	char pw[20];
	char title[30];
	char private_chk[10];

}ROOM;


USER reg_user_list[MAX_REG_USER] = 
{{1, "qwer", "1111", "cookie", "01055555555", "ppp@naver.com", "안녕", "하세요", 0, 0, 0, 0, 0},
 {2, "toss", "1234", "google", "01044444444", "aoui@naver.com", "반갑", "습니다", 0, 0, 0, 0, 0}};

USER login_user_list[MAX_LOGIN_USER] = {0,};

ROOM room_list[MAX_ROOM] = {{1, MAX_LOGIN_USER, 0, "0", "로비", "공개방"}};


void * handle_clnt(void * arg);
void send_whisper(char * msg, USER *p_user);
void send_msg(char * msg, USER *p_user);
int withdraw(int clnt_sock);
void search_user(char * msg, int clnt_sock);
void show_user(USER *p_user);
void operate_letter(USER *p_user, int clnt_sock);
void show_letter_list(USER *p_user, int clnt_sock);
void create_room(char *msg, USER *p_user, int clnt_sock);
void show_room(int clnt_sock);
void error_handling(char * msg);

int r_num = 2;
int room_cnt = 1;
int reg_user_cnt = 2;
int login_user_cnt = 0;
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;
time_t t;
struct tm tm;

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

	USER p_user = {0,}; 
	int clnt_sock=*((int*)arg);
	int str_len = 0; 
	int i, j, choice_num, dup_chk, login_chk, back_chk, pnum_chk;
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
		write(clnt_sock, "1.로그인 // 2.회원가입 // 3.ID 찾기 // 4.비밀번호 찾기 // 5.회원탈퇴\n", strlen("1.로그인 // 2.회원가입 // 3.ID 찾기 // 4.비밀번호 찾기 // 5.회원탈퇴\n"));
		memset(choice_str, 0, sizeof(choice_str));
		str_len = read(clnt_sock, choice_str, sizeof(choice_str));
			
		if (str_len == 0)
		{
			pthread_mutex_lock(&mutx);
			for(i = 0; i < clnt_cnt; i++)   // remove disconnected client
			{
				if(clnt_sock == clnt_socks[i])
				{
					while(i++ <clnt_cnt - 1)
						clnt_socks[i] = clnt_socks[i+1];
					break;
				}
			}
			clnt_cnt--;
			pthread_mutex_unlock(&mutx);
			close(clnt_sock);
			return NULL;
		}

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
				memset(id_str, 0, sizeof(id_str));
				str_len = read(clnt_sock, id_str, sizeof(id_str));
				printf("입력한 아이디 %s", id_str);
				id_str[str_len-1] = '\0';
								
				if (strcmp(id_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}

				write(clnt_sock, "[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
				memset(pw_str, 0, sizeof(pw_str));
				str_len = read(clnt_sock, pw_str, sizeof(pw_str));
				printf("입력한 비밀번호 %s", pw_str);
				pw_str[str_len-1] = '\0';

				if (strcmp(pw_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}

				login_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < reg_user_cnt; i++)
				{
					for (j = 0; j < login_user_cnt; j++) // 중복 로그인 방지
					{
						if (strcmp(id_str, reg_user_list[i].id) == 0 && strcmp(pw_str, reg_user_list[i].pw) == 0 && strcmp(id_str, login_user_list[j].id) == 0)
						login_chk = 2;
						break;
					}
					if (login_chk == 2)
						break;

					if (strcmp(id_str, reg_user_list[i].id) == 0 && reg_user_list[i].state == 2) // 탈퇴 회원 로그인 방지
					{
						login_chk = 3;
						break;
					}

					if (strcmp(id_str, reg_user_list[i].id) == 0 && strcmp(pw_str, reg_user_list[i].pw) == 0) // 로그인 성공
					{
						p_user = reg_user_list[i];
						p_user.state = 1;
						p_user.socket_num = clnt_sock; // 로그인 성공시 자신의 소켓 번호 저장
						p_user.room_num = 1; // 현재 들어있는 방을 1로 바꿈(로비 채팅방)
						login_user_list[login_user_cnt] = p_user; // 로그인 유저 리스트에 로그인 성공 유저 구조체 담기
						login_user_cnt++; // 로그인 유저 리스트의 인덱스 값을 1 증가
						room_list[0].user_cnt += 1;
						login_chk = 1;
						break;
					}
				}
				pthread_mutex_unlock(&mutx);
				if (login_chk == 1)
				{
					break;
				}
				else if (login_chk == 2)
				{
					write(clnt_sock, "이미 접속중인 아이디 입니다.\n", strlen("이미 접속중인 아이디 입니다.\n"));
					continue;
				}
				else if (login_chk == 3)
				{
					write(clnt_sock, "해당 아이디는 회원 탈퇴된 계정입니다.\n", strlen("해당 아이디는 회원 탈퇴된 계정입니다.\n"));
					continue;
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
			while (1) // 아이디 입력
			{
				memset(id_str, 0, sizeof(id_str));
				str_len = read(clnt_sock, id_str, sizeof(id_str));
				printf("입력한 아이디 %s", id_str);

				id_str[str_len - 1] = '\0';

				if (!(strlen(id_str) >= 4 && strlen(id_str) <= 15)) // 아이디 숫자 수 체크
				{
					write(clnt_sock, "4~15 사이의 글자수를 입력하세요.\n", strlen("4~15 사이의 글자수를 입력하세요.\n"));
					continue;
				}
				
				dup_chk = 0;
				pthread_mutex_lock(&mutx);
				for (i = 0; i < reg_user_cnt; i++) // 아이디 중복 체크
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
			while (1) // 비밀번호 입력
			{
				memset(pw_str, 0, sizeof(pw_str));
				str_len = read(clnt_sock, pw_str, sizeof(pw_str));
				printf("입력한 비밀번호 %s", pw_str);

				pw_str[str_len - 1] = '\0';

				if (!(strlen(pw_str) >= 4 && strlen(pw_str) <= 15)) // 비밀번호 숫자 수 체크
				{
					write(clnt_sock, "4~15 사이의 글자수를 입력하세요.\n", strlen("4~15 사이의 글자수를 입력하세요.\n"));
					continue;
				}
				
				write(clnt_sock, "[ 비밀번호를 다시 한 번 입력하세요 ]\n", strlen("[ 비밀번호를 다시 한 번 입력하세요 ]\n"));
				memset(pw_re_str, 0, sizeof(pw_re_str));
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
			write(clnt_sock, "[ 닉네임을 입력하세요 (15 글자 이하) ]\n", strlen("[ 닉네임을 입력하세요 (15 글자 이하) ]\n"));
			while (1) // 닉네임 입력
			{
				memset(nick_str, 0, sizeof(nick_str));
				str_len = read(clnt_sock, nick_str, sizeof(nick_str));
				printf("입력한 닉네임 %s", nick_str);

				nick_str[str_len - 1] = '\0';

				if (!(strlen(nick_str) >= 1 && strlen(nick_str) <= 15)) // 닉네임 숫자 수 체크
				{
					write(clnt_sock, "15 글자 이하로 입력하세요.\n", strlen("15 글자 이하로 입력하세요.\n"));
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
			while (1) // 휴대폰 번호 입력
			{
				memset(phone_num_str, 0, sizeof(phone_num_str));
				str_len = read(clnt_sock, phone_num_str, sizeof(phone_num_str));
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
			while (1) // 이메일 주소 입력
			{
				memset(e_mail_str, 0, sizeof(e_mail_str));
				str_len = read(clnt_sock, e_mail_str, sizeof(e_mail_str));
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
			while (1) // 질문 입력
			{
				memset(f_question_str, 0, sizeof(f_question_str));
				str_len = read(clnt_sock, f_question_str, sizeof(f_question_str));
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
			while (1) // 정답 입력
			{
				memset(f_answer_str, 0, sizeof(f_answer_str));
				str_len = read(clnt_sock, f_answer_str, sizeof(f_answer_str));
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
			reg_user_list[reg_user_cnt].state = 1; // 유저 상태 회원가입으로 바꿈 
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
			while (1)
			{
				int index_num;
				back_chk = 0;
				write(clnt_sock, "[ 휴대폰 번호를 입력하세요. (메뉴로 돌아가려면 'b') ]\n", strlen("[ 휴대폰 번호를 입력하세요. (메뉴로 돌아가려면 'b') ]\n"));
				memset(phone_num_str, 0, sizeof(phone_num_str));
				str_len = read(clnt_sock, phone_num_str, sizeof(phone_num_str));
				printf("입력한 전화번호 %s", phone_num_str);
				phone_num_str[str_len-1] = '\0';

				if (strcmp(phone_num_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}
								
				pnum_chk = 0;
				for (i = 0; i < reg_user_cnt; i++)
				{
					if (strcmp(phone_num_str, reg_user_list[i].phone_num) == 0)
					{	
						index_num = i;
						pnum_chk = 1;
						break;
					}
					
				}

				if (pnum_chk == 1)
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "회원님의 ID는 '%s' 입니다. \n", reg_user_list[index_num].id);
					write(clnt_sock, msg, strlen(msg));
					break;
				}
				else
				{
					write(clnt_sock, "해당 휴대폰 번호로 등록된 ID가 없습니다.\n", strlen("해당 휴대폰 번호로 등록된 ID가 없습니다.\n"));
					continue;
				}
			}
			if (back_chk == 1)
				continue;
			if (pnum_chk == 1)
				continue;
		}
		else if (choice_num == 4) // 비밀번호 찾기
		{
			int id_chk, pw_chk;
			printf("4번 입력\n");
			while (1)
			{
				int index_num;
				back_chk = 0;
				write(clnt_sock, "[ 비밀번호를 찾을 ID를 입력하세요. (메뉴로 돌아가려면 'b') ]\n", strlen("[ 비밀번호를 찾을 ID를 입력하세요. (메뉴로 돌아가려면 'b') ]\n"));
				memset(id_str, 0, sizeof(id_str));
				str_len = read(clnt_sock, id_str, sizeof(id_str));
				printf("입력한 ID %s", id_str);
				id_str[str_len-1] = '\0';

				if (strcmp(id_str, "b") == 0)
				{
					back_chk = 1;
					break;
				}

				id_chk = 0;
				pw_chk = 0;
				for (i = 0; i < reg_user_cnt; i++)
				{
					if (strcmp(id_str, reg_user_list[i].id) == 0)
					{	
						index_num = i;
						id_chk = 1;
						break;
					}
				}
				if (id_chk == 1)
				{
					memset(msg, 0, sizeof(msg));
					sprintf(msg, "질문 : %s\n", reg_user_list[index_num].f_question);
					write(clnt_sock, msg, strlen(msg));
					write(clnt_sock, "질문에 대한 정답을 입력하세요.\n", strlen("질문에 대한 정답을 입력하세요.\n"));
					memset(f_answer_str, 0, sizeof(f_answer_str));
					str_len = read(clnt_sock, f_answer_str, sizeof(f_answer_str));
					f_answer_str[str_len-1] = '\0';

					if (strcmp(f_answer_str, reg_user_list[index_num].f_answer) == 0)
					{
						memset(msg, 0, sizeof(msg));
						sprintf(msg, "회원님의 비밀번호는 '%s' 입니다.\n", reg_user_list[index_num].pw);
						write(clnt_sock, msg, strlen(msg));
						pw_chk = 1;
						break;
					}
					else
					{
						write(clnt_sock, "정답이 일치하지 않습니다.\n", strlen("정답이 일치하지 않습니다.\n"));
						continue;
					}
					break;
				}
				else
				{
					write(clnt_sock, "등록된 ID가 없습니다.\n", strlen("등록된 ID가 없습니다.\n"));
					continue;
				}
			}
			if (back_chk == 1)
				continue;
			if (pw_chk == 1)
				continue;

		}
		else if (choice_num == 5) // 회원 탈퇴
		{
			withdraw(clnt_sock);
			continue;
		}
		else
		{
			write(clnt_sock, "다시 선택하세요!\n", strlen("다시 선택하세요!\n"));
		}

	}
	
	write(clnt_sock, "로그인 성공\n", strlen("로그인 성공\n"));
	write(clnt_sock, "\033[38;2;110;194;7m\n'로비' 채팅방에 입장 하였습니다.\033[0m\n\n", strlen("\033[38;2;110;194;7m\n'로비' 채팅방에 입장 하였습니다.\033[0m\n\n"));
	
	while (1)
	{
		memset(msg, 0, sizeof(msg));
		str_len = read(clnt_sock, msg, sizeof(msg));

		if (str_len == 0) // 해당 클라이언트가 종료 했을때
		{
			pthread_mutex_lock(&mutx);
			for(i = 0; i < login_user_cnt; i++)   // 로그인 유저 리스트에서 해당 유저 삭제하고 하나씩 땡김
			{
				if(clnt_sock == login_user_list[i].socket_num)
				{
					while(i < login_user_cnt)
					{
						login_user_list[i] = login_user_list[i+1];
						i++;
					}
					break;
				}
			}
			login_user_cnt--;
			pthread_mutex_unlock(&mutx);
			close(clnt_sock);
			return NULL;
		}

		if (strncmp(msg, "/w", 2) == 0) // 귓속말
		{
			send_whisper(msg, &p_user);
		}
		else if (strcmp(msg, "/b\n") == 0) // 채팅 수신 차단
		{

		}
		else if (strcmp(msg, "/p\n") == 0) // 채팅 수신 가능
		{

		}
		else if (strncmp(msg, "/s", 2) == 0) // 회원 찾기
		{
			search_user(msg, clnt_sock);
		}
		else if (strcmp(msg, "/u\n") == 0) // 현재 방에 있는 유저 목록 보기
		{
			show_user(&p_user);
		}
		else if (strcmp(msg, "/l\n") == 0) // 쪽지창으로 넘어가기
		{
			operate_letter(&p_user, clnt_sock);
		}
		else if (strcmp(msg, "/r\n") == 0) // 방 목록 보기
		{
			show_room(clnt_sock);
		}
		else if (strncmp(msg, "/create", 7) == 0) // 방 만들기
		{
			create_room(msg, &p_user, clnt_sock);
		}
		else if (strncmp(msg, "/join", 5) == 0) // 방 들어가기
		{

		}
		else if (strncmp(msg, "/invite", 7) == 0) // 초대하기
		{

		}
		else // 일반 채팅 메시지 보내기
		{
			send_msg(msg, &p_user);
		}
		
	}
}

void show_room(int clnt_sock)
{
	int i;
	char *f_msg;
	f_msg = (char *)malloc(sizeof(char) * 2000);

	write(clnt_sock, "---------------------------------------------------------------------\n", strlen("---------------------------------------------------------------------\n"));
	write(clnt_sock, " 방 번호 //  방 인원   // 공개 여부 // 방 제목\t\t\n", strlen(" 방 번호 //  방 인원   // 공개 여부 // 방 제목\t\t\n"));
	write(clnt_sock, "---------------------------------------------------------------------\n", strlen("\n---------------------------------------------------------------------\n"));
	pthread_mutex_lock(&mutx);
	for (i = 0; i < room_cnt; i++)
	{
		sprintf(f_msg, "%3d // %3d명/%3d명 // %s // %-30s\n", room_list[i].room_num, room_list[i].user_cnt, room_list[i].max_user, room_list[i].private_chk, room_list[i].title);
		write(clnt_sock, f_msg, strlen(f_msg));
	}
	pthread_mutex_unlock(&mutx);
	write(clnt_sock, "\n---------------------------------------------------------------------\n\n", strlen("\n---------------------------------------------------------------------\n\n"));
	free(f_msg);
}

void create_room(char *msg, USER *p_user, int clnt_sock)
{
	char *title_str, *pw_str, *max_str;
	char private_str[10];
	char enter_str[300];
	int room_pw, max_cnt, i;
	ROOM room;

	strtok(msg, " ");
	max_str = strtok(NULL, " ");
	pw_str = strtok(NULL, " ");
	title_str = strtok(NULL, "\n");

	max_cnt = atoi(max_str);

	if (max_cnt == 0 || !(max_cnt >= 1 && max_cnt <= 10))
	{
		write(clnt_sock, "방 최대 인원은 10명 까지만 가능합니다\n", strlen("방 최대 인원은 10명 까지만 가능합니다\n"));
		return;
	}
	if (strlen(pw_str) >= 20)
	{
		write(clnt_sock, "방 비밀번호가 길이를 초과했습니다.\n", strlen("방 비밀번호가 길이를 초과했습니다.\n"));
		return;
	}
	if (strlen(title_str) >= 30)
	{
		write(clnt_sock, "방 제목이 길이를 초과했습니다.\n", strlen("방 제목이 길이를 초과했습니다.\n"));
		return;
	}
	
	room.max_user = max_cnt; // 방 최대 인원 저장
	room.user_cnt = 1; // 방 유저수 저장
	strcpy(room.pw, pw_str); // 방 비밀번호 저장
	strcpy(room.title, title_str); // 방 제목 저장
	if (strcmp(pw_str, "0") == 0) // 방 공개여부 저장
	{
		strcpy(room.private_chk, "공개방");
	}
	else
	{
		strcpy(room.private_chk, "비밀방");
	}

	pthread_mutex_lock(&mutx);
	room.room_num = r_num; // 방 숫자 저장
	room_list[room_cnt] = room; // 방 구조체 배열에 생성한 방 추가
	p_user->room_num = room.room_num; // 현재 유저 방 번호 생성한 방 번호로 변경
	for (i = 0; i < login_user_cnt; i++)
	{
		if (strcmp(p_user->id, login_user_list[i].id) == 0)
		{
			login_user_list[i].room_num = room.room_num; // 로그인 유저 배열에서 해당 유저 방 번호 변경
			break;
		}
	}
	room_cnt++;
	r_num++;
	pthread_mutex_unlock(&mutx);

	memset(enter_str, 0, sizeof(enter_str));
	sprintf(enter_str, "\n%s'%s' 채팅방에 입장 하였습니다.%s\n\n", green, room.title, color_end);
	write(clnt_sock, enter_str, strlen(enter_str));
}


void show_user(USER *p_user) // 유저 목록 보기 함수
{
	int i;
	char *f_msg;
	f_msg = (char *)malloc(sizeof(char) * BUF_SIZE);

	write(p_user->socket_num, "\033[38;2;110;194;7m[ID]              [NICK_NAME]         [E_MAIL]\033[0m\n", strlen("\033[38;2;110;194;7m[ID]              [NICK_NAME]         [E_MAIL]\033[0m\n"));
	write(p_user->socket_num, "\033[38;2;110;194;7m―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\033[0m\n", strlen("\033[38;2;110;194;7m―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\033[0m\n"));
	pthread_mutex_lock(&mutx);
	for (i = 0; i < login_user_cnt; i++)
	{
		if (p_user->room_num == login_user_list[i].room_num)
		{
			memset(f_msg, 0, sizeof(f_msg));
			sprintf(f_msg, "%s%-15s // %-15s // %-20s%s\n", green, login_user_list[i].id, login_user_list[i].nick_name, login_user_list[i].e_mail, color_end);
			write(p_user->socket_num, f_msg, strlen(f_msg));
		}
	}
	pthread_mutex_unlock(&mutx);
	free(f_msg);
}

void show_letter_list(USER *p_user, int clnt_sock) // 쪽지함 출력함수
{
	int i, j;
	char preview[16];
	char f_msg[5000];

	write(clnt_sock, "\t\t\t   < 내 쪽지함 >\n\n", strlen("\t\t\t   < 내 쪽지함 >\n\n"));
	write(clnt_sock, "[번호]       [보낸시간]           [보낸사람]         [쪽지내용]\n", strlen("[번호]       [보낸시간]           [보낸사람]         [쪽지내용]\n"));
	write(clnt_sock, "----------------------------------------------------------------------------------\n", strlen("----------------------------------------------------------------------------------\n"));
	pthread_mutex_lock(&mutx);
	for (i = 0; i < reg_user_cnt; i++)
	{
		if (strcmp(p_user->id, reg_user_list[i].id) == 0)
		{
			for (j = 0; j < reg_user_list[i].letter_cnt; j++)
			{
				strncpy(preview, reg_user_list[i].letter_box[j].text, 15);
				preview[15] = '\0';
				memset(f_msg, 0, sizeof(f_msg));
				if (strlen(reg_user_list[i].letter_box[j].text) <= 15)
				{
					sprintf(f_msg, "%-4d // %-21s // %-15s // %s\n", reg_user_list[i].letter_box[j].letter_num, reg_user_list[i].letter_box[j].time, reg_user_list[i].letter_box[j].sender_nck, preview);
				}
				else
				{
					sprintf(f_msg, "%-4d // %-21s // %-15s // %s...\n", reg_user_list[i].letter_box[j].letter_num, reg_user_list[i].letter_box[j].time, reg_user_list[i].letter_box[j].sender_nck, preview);
				}
				write(clnt_sock, f_msg, strlen(f_msg));
			}
			break;
		}
	}
	pthread_mutex_unlock(&mutx);
	write(clnt_sock, "----------------------------------------------------------------------------------\n", strlen("----------------------------------------------------------------------------------\n"));
	write(clnt_sock, "\033[38;2;110;194;7m[ 쪽지 읽기: /read 쪽지번호,  쪽지 보내기: /send 닉네임 쪽지내용,  쪽지 지우기: /delete 쪽지번호 ]\033[0m\n", strlen("\033[38;2;110;194;7m[ 쪽지 읽기: /read 쪽지번호,  쪽지 보내기: /send 닉네임 쪽지내용,  쪽지 지우기: /delete 쪽지번호 ]\033[0m\n"));
	write(clnt_sock, "(채팅방으로 돌아가려면 'b'를 입력하세요)\n", strlen("(채팅방으로 돌아가려면 'b'를 입력하세요)\n"));
}

void operate_letter(USER *p_user, int clnt_sock) // 쪽지 함수
{
	int str_len, i, j, k, check, index_num, l_cnt, l_num, chk;
	char msg[BUF_SIZE];
	char preview[16];
	char *nick;
	char *l_text;
	char time_str[500];
	char f_msg[5000];
	
	pthread_mutex_lock(&mutx);
	for (i = 0; i < login_user_cnt; i++)
	{
		if (login_user_list[i].socket_num == p_user->socket_num)
		{
			login_user_list[i].state = 3; // 수신거부 상태
			break;
		}
	}
	pthread_mutex_unlock(&mutx);

	show_letter_list(p_user, clnt_sock); // 쪽지함 출력 함수 호출
	
	while (1)
	{
		memset(msg, 0, sizeof(msg));
		str_len = read(clnt_sock, msg, sizeof(msg));
		

		if (strcmp(msg, "b\n") == 0) // 채팅방으로 돌아가기
		{
			pthread_mutex_lock(&mutx);
			for (i = 0; i < login_user_cnt; i++)
			{
				if (login_user_list[i].socket_num == p_user->socket_num)
				{
					login_user_list[i].state = 1; // 채팅 수신 활성화
					break;
				}
			}
			pthread_mutex_unlock(&mutx);
			write(clnt_sock, "&^clear^&\n", strlen("&^clear^&\n"));
			return;
		}
		else if (strncmp(msg, "/read", 5) == 0) // 쪽지 읽기
		{
			strtok(msg, " ");
			nick = strtok(NULL, "\n");
			l_num = atoi(nick);

			check = 0;
			chk = 0;
			pthread_mutex_lock(&mutx);
			for (i = 0; i < reg_user_cnt; i++)
			{
				if (strcmp(p_user->id, reg_user_list[i].id) == 0)
				{
					for (j = 0; j < reg_user_list[i].letter_cnt; j++)
					{
						if (l_num == reg_user_list[i].letter_box[j].letter_num)
						{
							check = 1;
							break;
						}	
					}
					chk = 1;
				}
				if (chk == 1)
					break;
			}
			if (check == 1)
			{
				memset(f_msg, 0, sizeof(f_msg));
				sprintf(f_msg, "\n번호: %-4d // 보낸시간: %-21s   // 보낸사람: %-15s\n", reg_user_list[i].letter_box[j].letter_num, reg_user_list[i].letter_box[j].time, reg_user_list[i].letter_box[j].sender_nck);
				write(clnt_sock, f_msg, strlen(f_msg));
				write(clnt_sock, "――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n", strlen("――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n"));
				memset(f_msg, 0, sizeof(f_msg));
				sprintf(f_msg, "%s\n", reg_user_list[i].letter_box[j].text);
				write(clnt_sock, f_msg, strlen(f_msg));
				write(clnt_sock, "――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n", strlen("――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n"));
			}
			else 
			{
				write(clnt_sock, "해당 쪽지번호가 존재하지 않습니다.\n", strlen("해당 쪽지번호가 존재하지 않습니다.\n"));
			}
			pthread_mutex_unlock(&mutx);
		}
		else if (strncmp(msg, "/send", 5) == 0) // 쪽지 발송
		{
			strtok(msg, " ");
			nick = strtok(NULL, " ");
			l_text =strtok(NULL, "\n");

			check = 0;
			for (i = 0; i < reg_user_cnt; i++)
			{
				if (strcmp(nick, reg_user_list[i].nick_name) == 0 && reg_user_list[i].state != 2)
				{
					check = 1;
					index_num = i;
					break;
				}
			}
			if (check == 1)
			{
				t = time(NULL);
				tm = *localtime(&t);
				
				memset(time_str, 0, sizeof(time_str));
				sprintf(time_str, "[%04d/%02d/%02d] %02d:%02d:%02d", tm.tm_year + 1900 , 
						tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, 
						tm.tm_min, tm.tm_sec);
            				
				pthread_mutex_lock(&mutx);
				l_cnt = reg_user_list[index_num].letter_cnt;
				if (l_cnt < 10)
				{
					reg_user_list[index_num].letter_cnt += 1; // 쪽지 갯수 증가
				}
				if (l_cnt == 10)
				{
					while (i < l_cnt)
					{
						reg_user_list[index_num].letter_box[i] = reg_user_list[index_num].letter_box[i+1];
						i++; 
					}
				}
                reg_user_list[index_num].letter_snum += 1;
				l_cnt = reg_user_list[index_num].letter_cnt;
				reg_user_list[index_num].letter_box[l_cnt-1].letter_num = reg_user_list[index_num].letter_snum; // 쪽지 번호 저장
				strcpy(reg_user_list[index_num].letter_box[l_cnt-1].time, time_str); // 쪽지 발송 시간 저장
				strcpy(reg_user_list[index_num].letter_box[l_cnt-1].sender_nck, p_user->nick_name); // 쪽지 발신자 저장
				strcpy(reg_user_list[index_num].letter_box[l_cnt-1].text, l_text); // 쪽지 내용 저장
				pthread_mutex_unlock(&mutx);

				memset(f_msg, 0, sizeof(f_msg));
				sprintf(f_msg, "'%s' 님에게 쪽지를 발송 하였습니다.\n", reg_user_list[index_num].nick_name);
				write(clnt_sock, f_msg, strlen(f_msg));
			}
			else
			{
				write(clnt_sock, "존재하지 않은 닉네임 입니다.\n", strlen("존재하지 않은 닉네임 입니다.\n"));
			}
		}
		else if (strncmp(msg, "/delete", 7) == 0) // 쪽지 삭제
		{
			strtok(msg, " ");
			nick = strtok(NULL, "\n");
			l_num = atoi(nick);
			check = 0;
			chk = 0;
			pthread_mutex_lock(&mutx);
			for (i = 0; i < reg_user_cnt; i++)
			{
				if (strcmp(p_user->id, reg_user_list[i].id) == 0)
				{
					for (j = 0; j < reg_user_list[i].letter_cnt; j++)
					{
						if (l_num == reg_user_list[i].letter_box[j].letter_num)
						{
                            for (k = j; k < reg_user_list[i].letter_cnt; k++)
							{
								reg_user_list[i].letter_box[k] = reg_user_list[i].letter_box[k+1]; // 해당 쪽지 삭제 후 쪽지 한칸씩 땡김
							}
							reg_user_list[i].letter_cnt -= 1;
							check = 1;
							write(clnt_sock, "해당 쪽지를 삭제하였습니다.\n", strlen("해당 쪽지를 삭제하였습니다.\n"));
							break;
						}
						if (check == 1)
							break;
					}
					chk = 1;
				}
				if (chk == 1)
					break;
			}
			pthread_mutex_unlock(&mutx);
			if (check == 0)
			{
				write(clnt_sock, "해당 쪽지번호가 존재하지 않습니다.\n", strlen("해당 쪽지번호가 존재하지 않습니다.\n"));
			}
		}
		else
		{
			write(clnt_sock, "명령어를 제대로 입력하세요\n", strlen("명령어를 제대로 입력하세요\n"));
		}
	}
}

int withdraw(int clnt_sock) // 회원 탈퇴 함수
{
	int str_len = 0;
	int login_chk, i, j, index_num;
	char id_str[50], pw_str[50], msg[50];

	while (1)
	{
		write(clnt_sock, "[ 회원탈퇴 할 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 회원탈퇴 할 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
		memset(id_str, 0, sizeof(id_str));
		str_len = read(clnt_sock, id_str, sizeof(id_str));
		id_str[str_len-1] = '\0';

		if (strcmp(id_str, "b") == 0)
		{
			return 0;
		}

		write(clnt_sock, "[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
		memset(pw_str, 0, sizeof(pw_str));
		str_len = read(clnt_sock, pw_str, sizeof(pw_str));
		pw_str[str_len-1] = '\0';

		if (strcmp(pw_str, "b") == 0)
		{
			return 0;
		}

		write(clnt_sock, "[ 아래의 문장을 정확히 따라 입력하세요 ]\n회원탈퇴를 희망합니다\n", strlen("[ 아래의 문장을 정확히 따라 입력하세요 ]\n회원탈퇴를 희망합니다\n"));
		memset(msg, 0, sizeof(msg));
		str_len = read(clnt_sock, msg, sizeof(msg));
		msg[str_len-1] = '\0';

		login_chk = 0;
		pthread_mutex_lock(&mutx);
		for (i = 0; i < reg_user_cnt; i++)
		{
			for (j = 0; j < login_user_cnt; j++) // 로그인 유저 탈퇴 방지
			{
				if (strcmp(id_str, reg_user_list[i].id) == 0 && strcmp(pw_str, reg_user_list[i].pw) == 0 && strcmp(id_str, login_user_list[j].id) == 0)
				{
					login_chk = 2;
					break;
				}
			}
			if (login_chk == 2)
				break;
				
			if (strcmp(id_str, reg_user_list[i].id) == 0 && strcmp(pw_str, reg_user_list[i].pw) == 0 && strcmp(msg, "회원탈퇴를 희망합니다") == 0) // 회원 탈퇴
			{
				reg_user_list[i].state = 2; // 회원상태 회원탈퇴(2)로 변경
				login_chk = 1;
				break;
			}		
		}
		pthread_mutex_unlock(&mutx);
		if (login_chk == 1)
		{
			write(clnt_sock, "회원탈퇴 처리 되었습니다.\n", strlen("회원탈퇴 처리 되었습니다.\n"));
			return 0;
		}
		else if (login_chk == 2)
		{
			write(clnt_sock, "현재 로그인중인 유저는 탈퇴가 불가능합니다.\n", strlen("현재 로그인중인 유저는 탈퇴가 불가능합니다.\n"));
			continue;
		}
		else
		{
			write(clnt_sock, "아이디, 비밀번호 또는 확인문장이 맞지 않습니다.\n", strlen("아이디, 비밀번호 또는 확인문장이 맞지 않습니다.\n"));
			continue;
		}
	}
}

void search_user(char * msg, int clnt_sock) // 회원 검색 함수
{
	char f_msg[BUF_SIZE];
	char *nick;
	int i, j, state_chk;

	strtok(msg, " ");
	nick = strtok(NULL, "\n");

	state_chk = 0;

	pthread_mutex_lock(&mutx);
	for (i = 0; i < login_user_cnt; i++)
	{
		if (strcmp(nick, login_user_list[i].nick_name) == 0)
		{
			state_chk = 1;
			break;
		}
	}
	pthread_mutex_unlock(&mutx);
	if (state_chk == 1)
	{
		memset(f_msg, 0, sizeof(f_msg));
		sprintf(f_msg, "%s'%s'님은 현재 접속중 입니다.%s\n\n", blue, nick, color_end);
		write(clnt_sock, f_msg, strlen(f_msg));
		return;
	}

	pthread_mutex_lock(&mutx);
	for (i = 0; i < reg_user_cnt; i++)
	{
		if (strcmp(nick, reg_user_list[i].nick_name) == 0 && reg_user_list[i].state == 2)
		{
			state_chk = 2;
			break;
		}

		if (strcmp(nick, reg_user_list[i].nick_name) == 0)
		{
			state_chk = 3;
			break;
		}
	}
	pthread_mutex_unlock(&mutx);
	if (state_chk == 2)
	{
		memset(f_msg, 0, sizeof(f_msg));
		sprintf(f_msg, "%s해당 닉네임은 탈퇴된 계정입니다.%s\n\n", blue, color_end);
		write(clnt_sock, f_msg, strlen(f_msg));
		return;
	}
	else if (state_chk == 3)
	{
		memset(f_msg, 0, sizeof(f_msg));
		sprintf(f_msg, "%s'%s'님은 현재 오프라인 상태입니다.%s\n\n", blue, nick, color_end);
		write(clnt_sock, f_msg, strlen(f_msg));
		return;
	}
	else
	{
		memset(f_msg, 0, sizeof(f_msg));
		sprintf(f_msg, "%s해당 닉네임은 존재하지 않는 계정입니다.%s\n\n", blue, color_end);
		write(clnt_sock, f_msg, strlen(f_msg));
		return;
	}
}

void send_whisper(char * msg, USER *p_user) // 귓속말 함수
{
	char f_msg[BUF_SIZE];
	char *nick;
	char *w_msg;
	int i, index_num, w_chk;

	strtok(msg, " ");
	nick = strtok(NULL, " ");
	w_msg = strtok(NULL, "\n");

	w_chk = 0;

	pthread_mutex_lock(&mutx);
	for (i = 0; i < login_user_cnt; i++)
	{
		if (strcmp(nick, login_user_list[i].nick_name) == 0 && login_user_list[i].state == 1)
		{
			w_chk = 1;
			index_num = i;
			break;
		}
	}
	pthread_mutex_unlock(&mutx);

	if (w_chk == 1)
	{
		memset(f_msg, 0, sizeof(f_msg));
		sprintf(f_msg, "%s귓속말 [%s] %s%s\n", yellow, p_user->nick_name, w_msg, color_end);

		pthread_mutex_lock(&mutx);
		write(login_user_list[index_num].socket_num, f_msg, strlen(f_msg));
		pthread_mutex_unlock(&mutx);
	}
	else
	{
		write(p_user->socket_num, "접속중인 해당 ID를 찾을 수 없습니다.\n", strlen("접속중인 해당 ID를 찾을 수 없습니다.\n"));
	}
}

void send_msg(char * msg, USER *p_user)   // send to all
{
	int i;
	char f_msg[BUF_SIZE];
	memset(f_msg, 0, sizeof(f_msg));
	sprintf(f_msg, "[%s] %s", p_user->nick_name, msg);
	
	pthread_mutex_lock(&mutx);
	for(i = 0; i < login_user_cnt; i++)
	{
		if (p_user->room_num == login_user_list[i].room_num && p_user->socket_num != login_user_list[i].socket_num && login_user_list[i].state == 1)
		{
			write(login_user_list[i].socket_num, f_msg, strlen(f_msg));
		}
	}
	pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
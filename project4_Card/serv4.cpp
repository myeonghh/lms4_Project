#include <iostream>
#include <thread>
#include <list>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <sstream>
#include <string>
#include <limits>
#include <vector>

#define BUF_SIZE 300
#define MAX_CLNT 256

std::list<int> clnt_socks;  // 소켓 목록을 관리할 리스트
std::mutex mutx;  // 클라이언트 소켓 목록을 보호하기 위한 mutex

void handle_clnt(int clnt_sock);
void send_msg(const char * msg, int len);
void error_handling(const char * msg);

enum {Sinhan = 1, KB, NH, Samsung, Woori, Hana};


class User
{
private:
    int user_num;
    std::string id;
    std::string name;
    int age;
    bool sex;
public:
    User(int u_num, std::string id, std::string name, int age, bool sex) : user_num(u_num), id(id), name(name), age(age), sex(sex)
    {}
    int get_user_num() const {return user_num;}
    std::string get_id() const {return id;}
    std::string get_name() const {return name;}
    int get_age() const {return age;}
    int get_sex() const {return sex;}
};


class Card
{
private:
    int card_id; // 카드 일련번호
    std::string card_name; // 카드 이름
    int anufee; // 카드 연회비
    bool credit_chk; // 신용, 체크카드 여부
    int brand;
    std::string brand_name;
public:
    Card()
    {}
};



class SinhanCard : Card
{
private:

};

class KBCard : Card
{
private:

};

class NHCard : Card
{
private:

};

class SamsungCard : Card
{
private:

};

class WooriCard : Card
{
private:

};

class HanaCard : Card
{
private:

};

class Base_card 
{
private:
    char *cardlist[6] = {"신한은행", "국민은행", "NH농협카드", "삼성카드", "우리은행", "하나은행"};
    //삼성, 하나카드, 농협, 국민, 우리, 신한

public:
    char brand[BUF_SIZE];  // brand이므로 문자열인 string선언
    int cradit; //bool값이므로 int형 선언.
    int annual_fee;  //연회비 이므로 int형 선언.
    char benefit_01[BUF_SIZE]; //혜택이므로 문자열인 string선언

};



class select_card_benefit : public Base_card
{
private:
    int choice; //초이스

    // vvv benefit vvv
    int select_bus = 0;

    int select_traffic = 0;
    int select_food = 0;
    int select_oil = 0;
    int select_hospital = 0;
    int select_trip = 0;

    char *benefit_result[4] = { NULL, }; //여러 개의 혜택 목록을 저장
    
public:
    void if_to_benefits(char *benefit_list, char *choice_02)
    {
        if(!strcmp(choice_02, "2"))
        {
            if(select_bus == 1)
            {
                strcat(benefit_list, "대중 교통");
            }
            if(select_traffic == 1)
            {
                strcat(benefit_list, "교통");
            }
            if(select_oil == 1)
            {
                strcat(benefit_list, "주유");
            }
            if(select_hospital == 1)
            {
                strcat(benefit_list, "병원 ");
            }
            if(select_trip == 1)
            {   
                strcat(benefit_list, "여행 ");
            }
            if(select_food == 1)
            {
                strcat(benefit_list, "푸드 ");
            }
        }

        else if(!strcmp(choice_02, "3"))
        {
            int i = 0;
            char *ptr = strtok(benefit_list, " ");
            while (ptr != NULL)
            {
                benefit_result[i] = ptr;             // 문자열을 자른 뒤 메모리 주소를 문자열 포인터 배열에 저장
                i++;
                ptr = strtok(NULL, " ");
            }
        }
        
    }



    void start(void*arg)
    {
        int clnt_sock = *((int*)arg);
        char msg[BUF_SIZE];
        char select_benefit[8];
        char choice[BUF_SIZE];
        char choice_02[BUF_SIZE];
        char onechoice[BUF_SIZE];    //입력받은 답안 입출력문1
        char anotherchoice[BUF_SIZE];//입력받은 답안 입출력문2
        char yesorno[BUF_SIZE];      //선택자 목록
        char error_msg[BUF_SIZE];    //에러 메시지 출력자
        char benefitlist[BUF_SIZE];
        
        // char number[];
        while(1)
        {
            char firstmsg[BUF_SIZE] = "카드 추천 프로그램에 접속 하신 것을 환영합니다!\n\n|  1  | 카드 추천 받기  |  2  | 카드 검색하기";
            write(clnt_sock, firstmsg, sizeof(firstmsg));
            read(clnt_sock, choice, sizeof(choice));//메시지 읽기
            
            
            if(!strcmp(choice, "1"))
            {
                strcpy(msg, "나는 운전을 자주 하시는 편이다.\n\n|  1  | Yes  |  2  | No");
                write(clnt_sock, msg, sizeof(msg));
                read(clnt_sock, onechoice, sizeof(onechoice));


                if(!strcmp(onechoice, "1"))
                {
                    select_oil==1;  //주유 혜택
                }
                else
                {
                    strcpy(msg, "나는 대중교통을 자주 이용하시는 편이다.\n\n|  1  | Yes  |  2  | No");
                    write(clnt_sock, msg, sizeof(msg));
                    read(clnt_sock, anotherchoice, sizeof(anotherchoice));

                    if(!strcmp(anotherchoice, "1"))
                    {
                        select_bus==1;  //대중교통 혜택 +1
                    }
                }
                
                strcpy(msg, "나는 자주 다치거나 지병이 있다.\n\n|  1  | Yes  |  2  | No");
                write(clnt_sock, msg, sizeof(msg));
                read(clnt_sock, onechoice, sizeof(onechoice));

                if(!strcmp(onechoice, "1"))
                {
                    select_hospital==1;    //병원 혜택 +1
                }

                strcpy(msg, "나는 맛집을 찾아다니거나 먹는 것에 진심인 편이다.\n\n|  1  | Yes  |  2  | No");
                write(clnt_sock, msg, sizeof(msg));
                read(clnt_sock, onechoice, sizeof(onechoice));
                

                if(!strcmp(onechoice, "1"))
                {
                    select_food==1; 
                }

                strcpy(msg, "나는 여행을 좋아한다.\n\n|  1  | Yes  |  2  | No");
                write(clnt_sock, msg, sizeof(msg));
                read(clnt_sock, onechoice, sizeof(onechoice));

                if(!strcmp(onechoice, "1"))
                {
                    select_trip==1;
                }
                
                std::cout << "\n설문조사 설문 결과 전송 확인 (1은 Yes, 2는 No로 설정)"<<std::endl;
                if_to_benefits(benefitlist, choice_02);
                std::cout << benefitlist << std::endl;
                std::cout << "\n개인운전 및 일반 교통 혜택에 관한 선호 여부 : " << select_oil << "\n대중 교통 혜택에 관한 선호 여부 : " << select_bus << "\n의료 혜택에 관한 선호 여부 : " << select_hospital<< "\n식료품에 관한 혜택선호 여부 : " << select_food<< "\n여행에 대한 혜택선호 여부 : " << select_trip << std::endl;   //서버측에서 올바르게 값이 하달되었는지 확인 - 완료
                //해당 Bool 값을 기반으로 데이터를 불러올 수 있음
                break;
            }
            else if(!strcmp(choice, "2"))
            {
                strcpy(msg, "|  1  | 카드사별 |2| 혜택별 |3| 세부사항");
                write(clnt_sock, msg, sizeof(msg));
                read(clnt_sock, choice_02, sizeof(choice_02));
                if(!strcmp(choice_02, "1"))
                {
                    while(1)
                    {
                        strcpy(msg, "카드사별 선택 구문 입니다.\n선택하실 카드사를 입력 해 주세요\n|  1  | 신한 카드   |  2  | 국민 카드   |  3  | 농협 카드   |  4  | 삼성 카드   |  5  | 우리 은행   |  6  | 하나 은행");
                        write(clnt_sock, msg, sizeof(msg));
                        read(clnt_sock, onechoice, sizeof(onechoice));
                        if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5") || strstr(onechoice, "6"))
                        {
                            strcpy(brand, onechoice);
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }

                }
                else if(!strcmp(choice_02, "2"))
                {
                    while(1)
                    {
                        strcpy(msg, "혜택 별 선택 구문 입니다.\n선택하실 혜택 목록을 입력 해 주세요\n\n|  혜택 목록  |\n|  1  |  교통   |  2  |  주유   |  3  |  푸드   |  4  |  병원   |  5  |  여행   |");
                        write(clnt_sock, msg, sizeof(msg));
                        read(clnt_sock, onechoice, sizeof(onechoice));
                        if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5"))
                        {
                            if(strstr(onechoice, "1"))
                            {
                                select_traffic = 1;
                            }
                            if(strstr(onechoice, "2"))
                            {
                                select_oil = 1;
                            }
                            if(strstr(onechoice, "3"))
                            {
                                select_food = 1;
                            }
                            if(strstr(onechoice, "4"))
                            {
                                select_hospital = 1;
                            }
                            if(strstr(onechoice, "5"))
                            {
                                select_trip = 1;
                            }
                            break;
                        }
                        else
                        {
                            continue;
                        }

                        
                    }
                }
                else if(!strcmp(choice_02, "3"))
                {
                    strcpy(msg, "만드시려는 카드 종류를 선택해 주세요.\n\n|  1  | 체크카드  |  2  | 신용카드");
                    write(clnt_sock, msg, sizeof(msg));
                    read(clnt_sock, onechoice, sizeof(onechoice));

                    if(!strcmp(onechoice, "1"))
                    {
                        cradit = 0;
                    }
                    else if(!strcmp(onechoice, "2"))
                    {
                        cradit = 1;
                    }
                    while(1)
                    {
                        strcpy(msg, "원하시는 카드사를 입력하세요.\n\n|  카드사 목록  |\n|  1  | 신한 카드   |  2  | 국민 카드   |  3  | 농협 카드   |  4  | 삼성 카드   |  5  | 우리 은행   |  6  | 하나 은행  ");
                        write(clnt_sock, msg, sizeof(msg));
                        read(clnt_sock, onechoice, sizeof(onechoice));

                        if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5") || strstr(onechoice, "6"))
                        {
                            strcpy(brand, onechoice);
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }


                    while(1)
                    {
                        strcpy(msg, "희망하는 연회비를 입력하세요.('원'을 빼고 입력해주세요.)\n\n( 10,000원 ~ 30,000원 사이의 액수를 입력하셔야 합니다...)");
                        write(clnt_sock, msg, sizeof(msg));
                        read(clnt_sock, onechoice, sizeof(onechoice));

                        if(atoi(onechoice) >= 10000 && atoi(onechoice) <= 30000)
                        {
                            annual_fee = atoi(onechoice);
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }

                
                    while(1)
                    {
                        strcpy(msg, "원하시는 혜택을 입력하세요.\n( 4가지 까지 선택이 가능합니다. )\n|  혜택 목록  |\n|  1  |  교통   |  2  |  주유   |  3  |  푸드   |  4  |  병원   |  5  |  여행   |");
                        write(clnt_sock, msg, sizeof(msg));
                        read(clnt_sock, onechoice, sizeof(onechoice));
                        if(strlen(onechoice) <= 8)
                        {
                            std::cout << onechoice <<std::endl;
                            if(strstr(onechoice, "1"))
                            {
                                select_traffic = 1;
                            }
                            if(strstr(onechoice, "2"))
                            {
                                select_oil = 1;
                            }
                            if(strstr(onechoice, "3"))
                            {
                                select_food = 1;
                            }
                            if(strstr(onechoice, "4"))
                            {
                                select_hospital = 1;
                            }
                            if(strstr(onechoice, "5"))
                            {
                                select_trip = 1;
                            }
                            // std::istringstream stream(onechoice);

                            // for(int i=0; i<4; i++)
                            // {
                            //     stream >> number[i];
                            //     std::cout<<number[i]<<std::endl;
                            // }

                            //ben = strtok(onechoice, " ");
                            //if(strtok(NULL, " ") == 0)
                            //{
                            //    benefit_02 = strtok(NULL, "\0");
                            //}
                            //else
                            //{
                            //    benefit_02 = strtok(NULL, "\0");
                            //    if(strtok(NULL, " ") == 0)
                            //    {
                            //        benefit_03 = strtok(NULL, "\0");
                            //    }else{
                            //        benefit_03 = strtok(NULL, " ");
                            //        if(strtok(NULL, " ") == 0)
                            //        {
                            //            benefit_04 = strtok(NULL, "\0");
                            //        }
                            //        else
                            //        {
                            //            benefit_04 = strtok(NULL, " ");
                            //        }
                            //    }
                            //}


                            break;
                        }
                        else
                        {
                            std::cout<<strlen(onechoice)<<std::endl;
                            std::cout<<"fdsafafdsf"<<std::endl;
                            memset(onechoice, 0, sizeof(onechoice));
                            continue;
                        }
                    }
                }
                
                if_to_benefits(benefitlist, choice_02);
                std::cout << "\n카드 종류 (Bool형으로) : " <<cradit<< "\n입력받은 카드사 : " << brand << "\n희망 연 회비 : " << annual_fee<<"(원)"<< "\n가장 중시하는 혜택 : ";//서버로부터 올바르게 전달되었는지 확인
                if(!strcmp(choice_02, "3"))
                {
                    for(int i = 0; i < 4; i++)
                    {
                        std::cout << benefit_result[i] << ", "<<std::endl;
                    }
                }
                else if(!strcmp(choice_02, "2"))
                {
                    std::cout << benefitlist << std::endl;
                }
                
                //std::cout << benefit_02<< benefit_03<< benefit_04 <<std::endl;
                break;
            }
            else 
            {
                std::cout << "옳지 않은 명령어" <<std::endl;
                continue;
            }

        }
    }
};


int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (true) {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        if (clnt_sock == -1) {
            std::cerr << "accept() error" << std::endl;
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(mutx);
            clnt_socks.push_back(clnt_sock);
        }

        std::thread(handle_clnt, clnt_sock).detach();
        std::cout << "Connected client IP: " << inet_ntoa(clnt_adr.sin_addr) << std::endl;
    }

    close(serv_sock);
    return 0;
}

void handle_clnt(int clnt_sock)
{
    char msg[BUF_SIZE];
    int str_len;
    select_card_benefit first;
    first.start((void*)&clnt_sock);
    while (true) 
    {
        

        str_len = read(clnt_sock, msg, sizeof(msg));
        if (str_len == 0)
        {
            std::lock_guard<std::mutex> lock(mutx);
            clnt_socks.remove(clnt_sock);  // 리스트에서 해당 소켓 제거
            close(clnt_sock);
        }

        send_msg(msg, str_len);
    }
}

void send_msg(const char* msg, int len)
{
    std::lock_guard<std::mutex> lock(mutx);

    for (int sock : clnt_socks) {
        write(sock, msg, len);
    }
}

void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
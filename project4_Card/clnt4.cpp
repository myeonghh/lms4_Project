#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <thread>
#include <mutex>

//#include "benner.h"
#define BUF_SIZE 1000
void first(void* arg);
void* send_msg(void* arg);
void* recv_msg(void* arg);
void error_handling(const std::string& msg);

//class Base_card;
//class select_card_benefit;





std::mutex mtx;

int main(int argc, char* argv[])
{
    //select_card_benefit starts;
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <port>\n";
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr;

    // Create socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("connect() error");
    }
    //starts.start((void*)&sock);//설문조사 & 카드선택
    


    // Create threads for sending and receiving messages--
    std::thread snd_thread(send_msg, (void*)&sock);
    std::thread rcv_thread(recv_msg, (void*)&sock);

    snd_thread.join();
    rcv_thread.join();

    close(sock);
    return 0;
}
void first(void* arg)
{

    int sock = *((int*)arg);
    char msg[BUF_SIZE];
    char firstmsg[BUF_SIZE];
    char secendmsg[BUF_SIZE];
    char *choice;
    char *choice_02;
    char *onechoice;//설문 선택자
    char anotherchoice[BUF_SIZE];//두번째 설문 선택자
    char yesorno[BUF_SIZE];      //선택자 
    int maxchoice = strlen(onechoice);

    read(sock, firstmsg, sizeof(firstmsg));//첫 메시지값 읽기
    std::cout<< firstmsg << std::endl;
    std::cin >> choice;
    write(sock, choice, sizeof(choice));//입력받은 선택자 정보 서버로 전송
    if(!strcmp(choice, "1"))
    {
        read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
        std::cout<< msg << std::endl;
        std::cin >> onechoice;          //설문지 출력문 조사
        write(sock, onechoice, sizeof(onechoice));//답안 보내기

        if(!strcmp(onechoice, "2"))
        {
            read(sock, msg, sizeof(msg));//두번째 설문 메시지값 읽기
            std::cout<< msg << std::endl;
            std::cin >> anotherchoice;          //설문지 출력문 조사
            write(sock, anotherchoice, sizeof(anotherchoice));//답안 보내기
        }

        read(sock, msg, sizeof(msg));//세번째 설문 메시지값 읽기
        std::cout<< msg << std::endl;

        std::cin >> onechoice;          //설문지 출력문 조사
        write(sock, onechoice, sizeof(onechoice));//답안 보내기
        
        read(sock, msg, sizeof(msg));//네번째 설문 메시지값 읽기
        std::cout<< msg << std::endl;

        std::cin >> onechoice;          //설문지 출력문 조사
        write(sock, onechoice, sizeof(onechoice));//답안 보내기

        read(sock, msg, sizeof(msg));//다섯번째 설문 메시지값 읽기
        std::cout<< msg << std::endl;

        std::cin >> onechoice;          //설문지 출력문 조사
        write(sock, onechoice, sizeof(onechoice));//답안 보내기

    }
    else if(!strcmp(choice, "2"))
    {   
        read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
        std::cout<< msg << std::endl;
        std::cin >> choice_02;
        write(sock, choice_02, sizeof(choice_02));

        if(!strcmp(choice_02, "1"))
        {
            while(1)
            {
                read(sock, msg, sizeof(msg));
                std::cout << msg << std::endl;
                std::cin >> onechoice;
                if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5") || strstr(onechoice, "6"))
                {
                    write(sock, onechoice, sizeof(onechoice));
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
                read(sock, msg, sizeof(msg));
                std::cout << msg << std::endl;
                std::cin >> onechoice;
                if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5"))
                {
                    write(sock, onechoice, sizeof(onechoice));
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
            read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
            std::cout<< msg << std::endl;

            std::cin >> onechoice;          //설문지 출력문 조사
            write(sock, onechoice, sizeof(onechoice));//답안 보내기

            read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
            std::cout<< msg << std::endl;

            while(1)
            {
                std::cin >> onechoice;          //설문지 출력문 조사
                write(sock, onechoice, sizeof(onechoice));//답안 보내기
                if(strstr(onechoice, "1") || strstr(onechoice, "2") || strstr(onechoice, "3") || strstr(onechoice, "4") || strstr(onechoice, "5") || strstr(onechoice, "6"))
                {
                    break;
                }
                else
                {
                    continue;
                }
            }

            read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
            std::cout<< msg << std::endl;

            while(1)
            {
                std::cin >> onechoice;          //설문지 출력문 조사
                write(sock, onechoice, sizeof(onechoice));//답안 보내기
                if(atoi(onechoice) >= 10000 && atoi(onechoice) <= 30000)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }

            read(sock, msg, sizeof(msg));//첫번째 설문 메시지값 읽기
            std::cout<< msg << std::endl;

            while(1)
            {
                std::cin.getline(onechoice, sizeof(onechoice));          //설문지 출력문 조사1 2



                std::cout << maxchoice <<std::endl;
                if(strstr(onechoice, "1"))
                {
                    write(sock, onechoice, sizeof(onechoice));//답안 보내기
                    break;
                }
                else
                {
                    std::cout << "오류 : 선택은 4개 까지만 가능합니다 ( 숫자로 입력 해 주세요 )"<<std::endl;
                    continue;
                }
                if(strlen(onechoice) < 8)
                {
                    std::cout << "문자열 8초과"<<std::endl;
                }

            }
            std::cout << " 검색이 종료되었습니다 " << std::endl;
        }
    }

}
void* send_msg(void* arg)
{
    int sock = *((int*)arg);
    std::string msg;

    while (true)
    {
        std::getline(std::cin, msg);

        if (msg == "/q" || msg == "/Q")
        {
            close(sock);
            exit(0);
        }

        // Send message to the server
        if (write(sock, msg.c_str(), msg.size()) == -1)
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cerr << "write() error\n";
        }
    }
    return nullptr;
}

void* recv_msg(void* arg)
{
    int sock = *((int*)arg);
    char msg[BUF_SIZE];

    while (true)
    {
        memset(msg, 0, BUF_SIZE);
        int str_len = read(sock, msg, BUF_SIZE - 1);
        if (str_len == -1)
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cerr << "read() error\n";
            return (void*)-1;
        }

        // Output the message received from the server
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << msg << std::endl;
    }

    return nullptr;
}

void error_handling(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

void first_msg(void*arg)
{

}

//class Base_card
//{
//private:
//    char *cardlist[6] = {"신한은행", "국민은행", "NH농협카드", "삼성카드", "우리은행", "하나은행"};
//    //삼성, 하나카드, 농협, 국민, 우리, 신한
//
//public:
//    std::string brand;  // brand이므로 문자열인 string선언
//    int cradit; //bool값이므로 int형 선언.
//    int annual_fee;  //연회비 이므로 int형 선언.
//    std::string boon; //혜택이므로 문자열인 string선언
//};
//
//
//class select_card_benefit : public Base_card
//{
//private:
//    int choice; //초이스
//
//    // vvv benefit vvv
//
//    int oil=0;    //주유
//    int bus=0;    //대중교통
//    int food=0;  //음식
//    int hospital=0;//병원
//    int trip=0;   //여행
//
//public:
//
//    void start(void *arg)
//    {
//        int sock = *((int*)arg);
//        std::string msg;
//        while(1)
//        {
//            std::cout<<"카드 추천 프로그램에 접속 하신 것을 환영합니다!"<<std::endl;
//            std::cout<<"1. 카드 추천 받기 2. 카드 검색하기"<<std::endl;
//            std::cin >> choice;
//            std::cout << "\n";
//            if(choice == 1)
//            {
//                std::cout << "나는 운전을 자주 하시는 편이다." << std::endl;
//                std::cout << "1.yes 2.no" << std::endl;
//                std::cin >> choice;
//                std::cout << "\n";
//                if(choice == 1)
//                {
//                    oil=oil+1;  //주유 혜택
//
//                }
//                else
//                {
//                    std::cout << "나는 대중교통을 자주 이용하시는 편이다." << std::endl;
//                    std::cout << "1.yes 2.no" << std::endl;
//                    std::cin >> choice;
//                    std::cout << "\n";
//                    if(choice == 1)
//                    {
//                        bus=bus+1;  //대중교통 혜택 +1
//                        
//                    }
//                }
//                std::cout << "나는 자주 다치거나 지병이 있다." << std::endl;
//                std::cout << "1.yes 2.no" << std::endl;
//                std::cin >> choice;
//                std::cout << "\n";
//                if(choice == 1)
//                {
//                    hospital=hospital+1;    //병원 혜택 +1
//                }
//                std::cout << "나는 맛집을 찾아다니거나 먹는 것에 진심인 편이다."<< std::endl;
//                std::cout << "1.yes 2.no" << std::endl;
//                std::cin >> choice;
//                std::cout << "\n";
//                if(choice ==1)
//                {
//                    food=food+1; 
//                }
//                std::cout << "나는 여행을 좋아한다."<< std::endl;
//                std::cout << "1.yes 2.no" << std::endl;
//                std::cin >> choice;
//                std::cout << "\n";
//                if(choice ==1)
//                {
//                    trip=trip+1;
//                }
//
//                write(sock, msg.c_str(), msg.size());
//
//                
//                std::cout << oil << bus << hospital << food << trip << std::endl;
//                break;
//            }
//            else if(choice == 2)
//            {
//                std::cout << "\n";
//                std::cout << "만드시려는 카드 종류를 선택해 주세요."<<std::endl;
//                std::cout << "0. 체크카드 1. 신용카드" << std::endl;
//                std::cin >> cradit;
//                std::cout << "\n";        
//                std::cout << "원하시는 카드사를 입력하세요. "<< std::endl;
//                std::cout << "카드사\n<국민카드, 농협카드, 신한카드, 우리카드, 삼성카드, 하나카드>" << std::endl;
//                std::cin >> brand;
//                std::cout << "\n";
//                std::cout << "희망하는 연회비를 입력하세요.('원'을 빼고 입력해주세요.)\n<10000원 ~ 30000원>" << std::endl;
//                std::cin >> annual_fee;
//                std::cout << "\n";
//                std::cout<<"원하시는 혜택을 입력하세요."<<std::endl;
//                std::cout<<"혜택\n <교통 / 주유/ 푸드 / 병원 / 여행>" << std::endl;
//                std::cin >> boon;
//                std::cout << cradit << brand << annual_fee << boon << std::endl;
//                break;
//            }
//            else 
//            {
//                std::cout << "옳지 않은 명령어" <<std::endl;
//                continue;
//            }
//
//        }
//    }
//};
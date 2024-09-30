#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>

#define BUF_SIZE 100
#define MAX_CLNT 256

// 전역 변수 대신 클래스나 스코프 한정 변수로 리팩토링하는 것도 가능하지만, 기존 구조를 유지합니다.
std::vector<int> clnt_socks;
std::mutex mutx;  // C++ 표준 mutex

void handle_clnt(int clnt_sock);
void send_msg(const char* msg, int len);
void error_handling(const char* msg);

int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return -1;
    }

    // 서버 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    // 주소 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    // 소켓 바인딩
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

        // 새 클라이언트 소켓을 저장
        {
            std::lock_guard<std::mutex> lock(mutx);
            clnt_socks.push_back(clnt_sock);
        }

        // 새 클라이언트 연결에 대해 스레드 생성
        std::thread(handle_clnt, clnt_sock).detach();
        std::cout << "Connected client IP: " << inet_ntoa(clnt_adr.sin_addr) << std::endl;
    }

    close(serv_sock);
    return 0;
}

void handle_clnt(int clnt_sock)
{
    char msg[BUF_SIZE];
    int str_len = 0;

    // 클라이언트로부터 메시지 수신 및 브로드캐스트
    while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)
        send_msg(msg, str_len);


    close(clnt_sock);
}

void send_msg(const char* msg, int len)
{
    std::lock_guard<std::mutex> lock(mutx);

    // 모든 클라이언트에게 메시지 전송
    for (int sock : clnt_socks)
        write(sock, msg, len);
}

void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
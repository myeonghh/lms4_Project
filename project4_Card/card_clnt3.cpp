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

#define BUF_SIZE 1024

void* send_msg(void* arg);
void* recv_msg(void* arg);
void error_handling(const std::string& msg);

std::mutex mtx;

int main(int argc, char* argv[])
{
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
        error_handling("connect() error");

    // Create threads for sending and receiving messages
    std::thread snd_thread(send_msg, (void*)&sock);
    std::thread rcv_thread(recv_msg, (void*)&sock);

    snd_thread.join();
    rcv_thread.join();

    close(sock);
    return 0;
}

void* send_msg(void* arg)
{
    int sock = *((int*)arg);
    std::string msg;

    while (true)
    {
        std::getline(std::cin, msg);

        // if (msg == "/q" || msg == "/Q")
        // {
        //     close(sock);
        //     exit(0);
        // }

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
        int str_len = read(sock, msg, sizeof(msg) - 1);

        if (str_len > 0) 
        { 
            msg[str_len] = '\0'; 
            std::string message = msg;

            if (message == "&close&") // 프로그램 종료 선택했을때
            {
                close(sock);
                exit(0);
            }

            size_t pos = 0;  
            while ((pos = message.find("&clear&")) != std::string::npos) 
            { 
                std::cout << message.substr(0, pos);
                system("clear");
                message = message.substr(pos + 7);
            }

            if (!message.empty()) {
                std::cout << message;  // 처리 후 남은 메시지를 출력
            }
        }
    }
    return nullptr;
}

void error_handling(const std::string& msg)
{
    std::cerr << msg;
    exit(1);
}
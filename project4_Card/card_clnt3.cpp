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

#define BUF_SIZE 1000

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

        if (msg == "/q" || msg == "/Q")
        {
            close(sock);
            exit(0);
        }

        // Send message to the server
        if (write(sock, msg.c_str(), msg.size()) == -1)
        {
            //std::lock_guard<std::mutex> lock(mtx);
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
        int str_len = read(sock, msg, BUF_SIZE);
        if (str_len == -1)
        {
            //std::lock_guard<std::mutex> lock(mtx);
            std::cerr << "read() error\n";
            return (void*)-1;
        }

        // Output the message received from the server
        std::cout << msg;
    }

    return nullptr;
}

void error_handling(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
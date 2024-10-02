#include <iostream>
#include <thread>
#include <list>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <mariadb/conncpp.hpp>


#define BUF_SIZE 100
#define MAX_CLNT 256

std::list<int> clnt_socks;  // 소켓 목록을 관리할 리스트
std::mutex mutx;  // 클라이언트 소켓 목록을 보호하기 위한 mutex

void handle_clnt(int clnt_sock);
void send_msg(const char * msg, int len);
void error_handling(const char * msg);
void database(int clnt_sock, char *msg);   //db연동 프로그램
void showTasks(std::unique_ptr<sql::Connection> &conn);  // tasks 테이블에 있는 모든 레코드를 출력



class BaseCard 
{
public:
    int cardNum;
    std::string cardName;
    int anuFee;
    int checkOrCredit;
    std::string cardBrand;
    int cardBrandInt;

    // 생성자
    BaseCard(int cn, std::string cname, int af, int cc, std::string cbrand, int cbrandInt)
        : cardNum(cn), cardName(cname), anuFee(af), checkOrCredit(cc), cardBrand(cbrand), cardBrandInt(cbrandInt) {}
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

    while (true) 
    {
        str_len = read(clnt_sock, msg, sizeof(msg));
        database(clnt_sock, msg);
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

    for (int sock : clnt_socks) 
    {
        write(sock, msg, len);
    }
}

void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

// tasks 테이블에 있는 모든 레코드를 출력
void showTasks(std::unique_ptr<sql::Connection> &conn) 
{
    std::vector<BaseCard> baseCards;
    try 
    {
        // 새로운 Statement 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리 실행
        sql::ResultSet *res = stmnt->executeQuery("select * from BASECARD");
        // 결과를 반복하면서 출력
        while (res->next()) 
        {
            int cardNum = res->getInt(1);
            std::string cardName = std::string(res->getString(2));  
            int anuFee = res->getInt(3);
            int checkOrCredit = res->getInt(4);
            std::string cardBrand = std::string(res->getString(5)); 
            int cardBrandInt = res->getInt(6);
            // BaseCard 객체 생성 후 벡터에 추가
            baseCards.emplace_back(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt);
        }
        for (const auto& card : baseCards) 
        {
            std::cout << "CARDNUM = " << card.cardNum << "\n";
            std::cout << "CARDNAME = " << card.cardName << "\n";
            std::cout << "ANUFEE = " << card.anuFee << "\n";
            std::cout << "CHECK/CREDIT = " << card.checkOrCredit << "\n";
            std::cout << "CARDBRAND = " << card.cardBrand << "\n";
            std::cout << "CARDBRANDINT = " << card.cardBrandInt << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }
    catch(sql::SQLException& e)
    {
        std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
    }
}

// Main Process
void database(int clnt_sock, char *msg)
{
    // MariaDB와의 연결 및 로직 구현
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    sql::SQLString url("jdbc:mariadb://10.10.20.111:3306/todo");
    sql::Properties properties({{"user", "asd"}, {"password", "1234"}});

    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

    // 메시지를 처리하여 어떤 작업을 할지 결정 (예시로 showTasks 호출)
if (strcmp(msg, "/s") == 0)  // 문자열이 '/s'와 같은지 비교
{
    showTasks(conn);  // '/s'를 입력하면 showTasks 호출
}
}
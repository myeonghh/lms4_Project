#include <iostream>
#include <thread>
#include <list>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <vector>
#include <string>
#include <mariadb/conncpp.hpp>
#include <format>


#define BUF_SIZE 1000
#define MAX_CLNT 256

std::list<int> clnt_socks;  // 소켓 목록을 관리할 리스트
std::mutex mutx;  // 클라이언트 소켓 목록을 보호하기 위한 mutex

void handle_clnt(int clnt_sock);
void send_msg(const char * msg, int len);
void error_handling(const char * msg);
void showTasks(std::unique_ptr<sql::Connection> &conn);
void database(int clnt_sock, char *msg);

enum {SINHAN = 1, KB, NH, SAMSUNG, WOORI, HANA};

enum {LOGIN = 1, SIGNUP, WITHDRAW};


class User
{
private:
    int user_num;
    std::string id;
    std::string pw;
    std::string name;
    int age;
    bool sex;
public:
    User() : user_num(0), id(NULL), pw(NULL), name(NULL), age(0), sex(NULL) 
    {}
    int get_user_num() const {return user_num;}
    std::string get_id() const {return id;}
    std::string get_pw() const {return pw;}
    std::string get_name() const {return name;}
    int get_age() const {return age;}
    int get_sex() const {return sex;}
};

class UserHandler
{
private:
    std::vector<User*> user_v;
    int clnt_sock;
    
public:
    UserHandler(int clnt_sock) : clnt_sock(clnt_sock)
    {}

    int login(void)
    {
        char id_str[BUF_SIZE];
        char pw_str[BUF_SIZE];
        int str_len, back_chk;

        while (true)
        {
            back_chk = 0;

            write(clnt_sock, "[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
            memset(id_str, 0, sizeof(id_str));
            str_len = read(clnt_sock, id_str, sizeof(id_str));
            std::cout<<"입력한 아이디 "<<id_str<<std::endl;
            
            id_str[str_len-1] = '\0';		
            if (strcmp(id_str, "b") == 0)
            {
                back_chk = 1;
                return 0;
            }
            write(clnt_sock, "[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
            memset(pw_str, 0, sizeof(pw_str));
            str_len = read(clnt_sock, pw_str, sizeof(pw_str));
            printf("입력한 비밀번호 %s", pw_str);
            pw_str[str_len-1] = '\0';
            if (strcmp(pw_str, "b") == 0)
            {
                back_chk = 1;
                return 0;
            }
            for (User* v : user_v)
            {
                if (strcmp(v->get_id().c_str(), id_str) == 0 && strcmp(v->get_pw().c_str(), pw_str) == 0) // 로그인 성공
                {

                }
            }
            
                // p_user = reg_user_list[i];
                // p_user.state = 1;
                // p_user.socket_num = clnt_sock; // 로그인 성공시 자신의 소켓 번호 저장
                // p_user.room_num = 1; // 현재 들어있는 방을 1로 바꿈(로비 채팅방)
                // login_user_list[login_user_cnt] = p_user; // 로그인 유저 리스트에 로그인 성공 유저 구조체 담기
                // login_user_cnt++; // 로그인 유저 리스트의 인덱스 값을 1 증가
                // room_list[0].user_cnt += 1;
                // login_chk = 1;
                // break;
        
        
            // if (login_chk == 1)
            // {
            //     break;
            // }
            // else if (login_chk == 2)
            // {
            //     write(clnt_sock, "\033[38;2;231;41;41m이미 접속중인 아이디 입니다.\033[0m\n", strlen("\033[38;2;231;41;41m이미 접속중인 아이디 입니다.\033[0m\n"));
            //     continue;
            // }
            // else if (login_chk == 3)
            // {
            //     write(clnt_sock, "\033[38;2;231;41;41m해당 아이디는 회원 탈퇴된 계정입니다.\033[0m\n", strlen("\033[38;2;231;41;41m해당 아이디는 회원 탈퇴된 계정입니다.\033[0m\n"));
            //     continue;
            // }
            // else
            // {
            //     write(clnt_sock, "\033[38;2;231;41;41m아이디 또는 비밀번호가 맞지 않습니다.\033[0m\n", strlen("\033[38;2;231;41;41m아이디 또는 비밀번호가 맞지 않습니다.\033[0m\n"));
            //     continue;
            // }
        }

    }

    void sign_up(void)
    {

    }

    void withdraw(void)
    {

    }
    
    ~UserHandler()
    {

    };

};


class Card
{
protected:
    int card_num; // 카드 일련번호
    std::string card_name; // 카드 이름
    int anufee; // 카드 연회비
    bool check_or_credit; // 신용, 체크카드 여부
    std::string brand_name;
    int brand_int;
    int traffic;
    int oil;
    int food;
    int hospital;
    int trip;
    int clnt_sock;

public:
    Card(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock) 
    : card_num(c_id), card_name(c_name), anufee(anufee), check_or_credit(credit_chk), brand_name(b_name), brand_int(b_int), traffic(traffic), oil(oil), food(food), hospital(hospital), trip(trip), clnt_sock(clnt_sock)
    {}
    int get_cnum() const {return card_num;}
    std::string get_cname() const {return card_name;}
    int get_anufee() const {return anufee;}
    bool get_cchk() const {return check_or_credit;}
    std::string get_bname() const {return brand_name;}
    int get_bint() const {return brand_int;}
    int get_traffic() const {return traffic;}
    int get_oil() const {return oil;}
    int get_food() const {return food;}
    int get_hospital() const {return hospital;}
    int get_trip() const {return trip;}
    
    virtual void show_card () const = 0;

};

class SinhanCard : public Card
{
private:
public:
    SinhanCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {
        std::string res;
        res = "카드번호 : " + std::to_string(card_num);





        write(clnt_sock, res.c_str(), strlen(res.c_str()));
        std::cout << "CARDNUM = " << card.get_cnum() << "\n";
        std::cout << "CARDNAME = " << card.get_cname() << "\n";
        std::cout << "ANUFEE = " << card.get_anufee() << "\n";
        std::cout << "CHECK/CREDIT = " << card.get_cchk() << "\n";
        std::cout << "CARDBRAND = " << card.get_bname() << "\n";
        std::cout << "CARDBRANDINT = " << card.get_bint() << "\n";
        std::cout << "TRAFFIC = " << card.get_traffic() << "\n";
        std::cout << "OIL = " << card.get_oil() << "\n";
        std::cout << "FOOD = " << card.get_food() << "\n";
        std::cout << "HOSPITAL = " << card.get_hospital() << "\n";
        std::cout << "TRIP = " << card.get_trip() << "\n";
        std::cout << "---------------------------" << std::endl;
    }

};

class KBCard : public Card
{
private:
public:
    KBCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {

    }

};

class NHCard : public Card
{
private:
public:
    NHCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {

    }
};

class SamsungCard : public Card
{
private:
public:
    SamsungCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {

    }

};

class WooriCard : public Card
{
private:
public:
    WooriCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {

    }

};

class HanaCard : public Card
{
private:
public:
    HanaCard(int c_id, std::string c_name, int anufee, bool credit_chk, std::string b_name, int b_int, int traffic, int oil, int food, int hospital, int trip, int clnt_sock)
        : Card(c_id, c_name, anufee, credit_chk, b_name, b_int, traffic, oil, food, hospital, trip, clnt_sock)
    {}

    virtual void show_card() const
    {

    }

};

class CardHandler
{
private:
    std::vector<Card> baseCards;
public:
    CardHandler(/* args */);
    ~CardHandler();
};

CardHandler::CardHandler(/* args */)
{
}

CardHandler::~CardHandler()
{
}




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
    int str_len, choice, check;
    UserHandler u_handelr(clnt_sock);

    write(clnt_sock, "카추추에 오신걸 환영합니다\n\n", strlen("카추추에 오신걸 환영합니다\n\n"));
    while (true)
    {
        str_len = read(clnt_sock, msg, sizeof(msg));
        database(clnt_sock, msg);

        write(clnt_sock, "1. 로그인  2. 회원가입  3. 회원탈퇴\n", strlen("1. 로그인  2. 회원가입  3. 회원탈퇴\n"));
        memset(msg, 0, sizeof(msg));
        str_len = read(clnt_sock, msg, sizeof(msg));
		msg[str_len-1] = '\0';
		choice = atoi(msg);

        check = 0;
        if (choice == LOGIN)
        {
            check = u_handelr.login();
        }
        else if (choice == SIGNUP)
        {
            u_handelr.sign_up();
            continue;
        }
        else if (choice == WITHDRAW)
        {
            u_handelr.withdraw();
            continue;
        }
        else
        {
            write(clnt_sock, "다시 입력하세요.\n", strlen("다시 입력하세요.\n"));
            continue;
        }
    }
    
    while (true) // 해당 클라이언트가 접속종료했을때
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

void showTasks(std::unique_ptr<sql::Connection> &conn) 
{
    std::vector<Card> baseCards;
    try 
    {
        // 새로운 Statement 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리 실행
        // "select * from BASECARD A JOIN BENEFITS B ON A.CARDNUM = B.BENEFITNUM"
        sql::ResultSet *res = stmnt->executeQuery("select * from BASECARD A JOIN BENEFITS B ON A.CARDNUM = B.BENEFITNUM");
        // 결과를 반복하면서 출력
        while (res->next()) 
        {
            int cardNum = res->getInt(1);
            std::string cardName = std::string(res->getString(2));  
            int anuFee = res->getInt(3);
            int checkOrCredit = res->getInt(4);
            std::string cardBrand = std::string(res->getString(5)); 
            int cardBrandInt = res->getInt(6);
            int traffic = res->getInt(8);
            int oil = res->getInt(9);
            int food = res->getInt(10);
            int hospital = res->getInt(11);
            int trip = res->getInt(12);
            // BaseCard 객체 생성 후 벡터에 추가
            baseCards.emplace_back(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip);
        }
        for (const auto& card : baseCards) 
        {

            // int card_num; // 카드 일련번호
            // std::string card_name; // 카드 이름
            // int anufee; // 카드 연회비
            // bool check_or_credit; // 신용, 체크카드 여부
            // std::string brand_name;
            // int brand_int;
            std::cout << "CARDNUM = " << card.get_cnum() << "\n";
            std::cout << "CARDNAME = " << card.get_cname() << "\n";
            std::cout << "ANUFEE = " << card.get_anufee() << "\n";
            std::cout << "CHECK/CREDIT = " << card.get_cchk() << "\n";
            std::cout << "CARDBRAND = " << card.get_bname() << "\n";
            std::cout << "CARDBRANDINT = " << card.get_bint() << "\n";
            std::cout << "TRAFFIC = " << card.get_traffic() << "\n";
            std::cout << "OIL = " << card.get_oil() << "\n";
            std::cout << "FOOD = " << card.get_food() << "\n";
            std::cout << "HOSPITAL = " << card.get_hospital() << "\n";
            std::cout << "TRIP = " << card.get_trip() << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }
    catch(sql::SQLException& e)
    {
        std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
    }
}



void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
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
#include <sstream>

#define BUF_SIZE 1024
#define MAX_CLNT 256


std::list<int> clnt_socks;  // 소켓 목록을 관리할 리스트
std::mutex mutx;  // 클라이언트 소켓 목록을 보호하기 위한 mutex

void handle_clnt(int clnt_sock);
void send_msg(const char * msg, int len);
void error_handling(const char * msg);
void showTasks(std::unique_ptr<sql::Connection> &conn);
void database(int clnt_sock, char *msg);
void cardselect(std::unique_ptr<sql::Connection> &conn, std::string msg);
void Benefitselect(std::unique_ptr<sql::Connection> &conn, std::string msg);
void Brandselect(std::unique_ptr<sql::Connection> &conn, std::string msg);

enum {SINHAN = 1, KB, NH, SAMSUNG, WOORI, HANA};

namespace LoginMenu
{
    enum {LOGIN = 1, SIGNUP, WITHDRAW};
}


class User
{
private:
    int user_num;
    std::string id;
    std::string pw;
    std::string name;
    int age;
public:
    User() : user_num(0), id(""), pw(""), name(""), age(0)
    {}
    User(int user_num, std::string id, std::string pw, std::string name, int age) : user_num(user_num), id(id), pw(pw), name(name), age(age)
    {}
    int get_user_num() const {return user_num;}
    std::string get_id() const {return id;}
    std::string get_pw() const {return pw;}
    std::string get_name() const {return name;}
    int get_age() const {return age;}
};

std::vector<User*> user_v; // 유저 목록 벡터
int user_cnt = 0;

class UserHandler
{
private:
    int clnt_sock;
    User p_user;
    
public:
    UserHandler(int clnt_sock) : clnt_sock(clnt_sock)
    {}

    int login(void)
    {
        char id_str[BUF_SIZE];
        char pw_str[BUF_SIZE];
        int str_len, back_chk, login_chk, i;

        while (true)
        {
            back_chk = 0;

            write(clnt_sock, "[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 아이디를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
            memset(id_str, 0, sizeof(id_str));
            str_len = read(clnt_sock, id_str, sizeof(id_str));
            std::cout<<"입력한 아이디 "<<id_str<<std::endl;
            
            if (strcmp(id_str, "b") == 0)
            {
                back_chk = 1;
                return 0;
            }
            write(clnt_sock, "[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n", strlen("[ 비밀번호를 입력하세요 (메뉴로 돌아 가려면 'b' 입력) ]\n"));
            memset(pw_str, 0, sizeof(pw_str));
            str_len = read(clnt_sock, pw_str, sizeof(pw_str));
            std::cout<<"입력한 비밀번호 "<<pw_str<<std::endl;

            if (strcmp(pw_str, "b") == 0)
            {
                back_chk = 1;
                return 0;
            }

            for (i = 0; i < user_v.size(); i++)
            {
                std::cout<<user_v[i]->get_id()<<std::endl;
                std::cout<<user_v[i]->get_pw()<<std::endl;
                
                if (strcmp(user_v[i]->get_id().c_str(), id_str) == 0 && strcmp(user_v[i]->get_pw().c_str(), pw_str) == 0) // 로그인 성공
                {
                    write(clnt_sock, "\n로그인에 성공하였습니다.\n\n", strlen("\n로그인에 성공하였습니다.\n\n"));
                    User puser(user_v[i]->get_user_num(), user_v[i]->get_id(), user_v[i]->get_pw(), user_v[i]->get_name(), user_v[i]->get_age());
                    p_user = puser;
                    return 1;
                }
            }

            write(clnt_sock, "아이디 혹은 비밀번호가 맞지 않습니다.\n", strlen("아이디 혹은 비밀번호가 맞지 않습니다.\n"));
        }

    }

    void sign_up(void)
    {
        char id_str[BUF_SIZE];
        char pw_str[BUF_SIZE];
        char name_str[BUF_SIZE];
        char age_str[BUF_SIZE];
        int str_len;
        bool dup_chk;
        
        while (true)
        {
            write(clnt_sock, "[ 회원가입 할 아이디를 입력하세요 ]\n", strlen("[ 회원가입 할 아이디를 입력하세요 ]\n"));
            memset(id_str, 0, sizeof(id_str));
            str_len = read(clnt_sock, id_str, sizeof(id_str));
            std::cout<<"입력한 아이디 "<<id_str<<std::endl;

            dup_chk = false;
            {
                std::lock_guard<std::mutex> lock(mutx);
                for (User *user : user_v) // 아이디 중복 체크
                {
                    if (strcmp(user->get_id().c_str(), id_str) == 0)
                    {
                        dup_chk = true;
                        break;
                    }		
                }
            }
            if (dup_chk == true)
            {
                write(clnt_sock, "이미 가입 된 아이디 입니다. 다시 입력하세요.\n", strlen("이미 가입 된 아이디 입니다. 다시 입력하세요.\n"));
                continue;
            }

            write(clnt_sock, "[ 비밀번호를 입력하세요 ]\n", strlen("[ 비밀번호를 입력하세요 ]\n"));
            memset(pw_str, 0, sizeof(pw_str));
            str_len = read(clnt_sock, pw_str, sizeof(pw_str));
            std::cout<<"입력한 비밀번호 "<<pw_str<<std::endl;

            write(clnt_sock, "[ 이름을 입력하세요 ]\n", strlen("[ 이름을 입력하세요 ]\n"));
            memset(name_str, 0, sizeof(name_str));
            str_len = read(clnt_sock, name_str, sizeof(name_str));
            std::cout<<"입력한 이름 "<<name_str<<std::endl;

            write(clnt_sock, "[ 나이를 입력하세요 ]\n", strlen("[ 나이를 입력하세요 ]\n"));
            memset(age_str, 0, sizeof(age_str));
            str_len = read(clnt_sock, age_str, sizeof(age_str));
            std::cout<<"입력한 나이 "<<age_str<<std::endl;

            if (std::atoi(age_str) == 0)
            {
                write(clnt_sock, "다시 입력하세요\n", strlen("다시 입력하세요\n"));
                continue;
            }

            {
                std::lock_guard<std::mutex> lock(mutx); 
                User* new_user = new User(user_cnt+1, id_str, pw_str, name_str, std::atoi(age_str));
                user_cnt++;
                user_v.push_back(new_user); // 회원가입한 유저 포인터를 유저 벡터에 담음
            }
            break;
        }

    }

    void withdraw(void)
    {
        char id_str[BUF_SIZE];
        char pw_str[BUF_SIZE];
        int str_len, i;
        bool dup_chk;

        write(clnt_sock, "[ 탈퇴 할 아이디를 입력하세요 ]\n", strlen("[ 탈퇴 할 아이디를 입력하세요 ]\n"));
        memset(id_str, 0, sizeof(id_str));
        str_len = read(clnt_sock, id_str, sizeof(id_str));
        std::cout<<"입력한 아이디 "<<id_str<<std::endl;

        write(clnt_sock, "[ 비밀번호를 입력하세요 ]\n", strlen("[ 비밀번호를 입력하세요 ]\n"));
        memset(pw_str, 0, sizeof(pw_str));
        str_len = read(clnt_sock, pw_str, sizeof(pw_str));
        std::cout<<"입력한 비밀번호 "<<pw_str<<std::endl;

        for (i = 0; i < user_v.size(); i++)
        {
            if (strcmp(user_v[i]->get_id().c_str(), id_str) == 0 && strcmp(user_v[i]->get_pw().c_str(), pw_str) == 0) // 회원 탈퇴 성공
            {
                write(clnt_sock, "회원탈퇴 처리 되었습니다.\n", strlen("회원탈퇴 처리 되었습니다.\n"));
                {
                    std::lock_guard<std::mutex> lock(mutx);
                    user_v.erase(user_v.begin() + i);
                }
                return;
            }
        }

        write(clnt_sock, "아이디 혹은 비밀번호가 맞지 않습니다.\n", strlen("아이디 혹은 비밀번호가 맞지 않습니다.\n"));
        
    }

    User get_puser(void) const {return p_user;}
    
    ~UserHandler()
    { };

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
    
    virtual void show_card () const {};

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
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
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
        std::string res;
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
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
        std::string res;
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
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
        std::string res;
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
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
        std::string res;
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
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
        std::string res;
        res = "====================================================\n" 
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "신용카드" : "체크카드")  + " // " + brand_name + "\n"
            + "이름: " + card_name + " // " + "연회비: " + std::to_string(anufee) + "\n"
            + "할인혜택: " + ((traffic != 0)? "교통 " + std::to_string(traffic) + "%, " : "") 
            + ((oil != 0)? "주유 " + std::to_string(oil) + "%, " : "") 
            + ((food != 0)? "푸드 " + std::to_string(food) + "%, " : "") 
            + ((hospital != 0)? "병원 " + std::to_string(hospital) + "%, " : "") 
            + ((trip != 0)? "여행 " + std::to_string(trip) + "% " : "") + "\n"
            + "====================================================\n";

        write(clnt_sock, res.c_str(), res.length());
    }

};

class CardHandler
{
private:
    std::vector<Card*> cards_v;
    int clnt_sock;
    std::unique_ptr<sql::Connection> &conn;
    
public:
    CardHandler(int clnt_sock, std::unique_ptr<sql::Connection> &conn)  : clnt_sock(clnt_sock), conn(conn)
    {};

    void put_in_card()
    {
        // 새로운 Statement 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리 실행
        sql::ResultSet *res = stmnt->executeQuery("select * from BASECARD A JOIN BENEFITS B ON A.CARDNUM = B.BENEFITNUM");
        // 결과를 반복하면서 값 입력
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

            // 카드사별 Card 객체 생성 후 벡터에 추가
            // enum {SINHAN = 1, KB, NH, SAMSUNG, WOORI, HANA};
            switch (cardBrandInt)
            {
            case SINHAN:
                cards_v.emplace_back(new SinhanCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case KB:
                cards_v.emplace_back(new KBCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case NH:
                cards_v.emplace_back(new NHCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case SAMSUNG:
                cards_v.emplace_back(new SamsungCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case WOORI:
                cards_v.emplace_back(new WooriCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case HANA:
                cards_v.emplace_back(new HanaCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            default:
                break;
            }
        }
    }

    void show_all_card()
    {
        for (Card* card : cards_v)
        {
            card->show_card();
        }
    }

    void detailed_card_search()
    {
        char msg[BUF_SIZE];
        int choice_arr[7];
        int choice;
        std::string brand_str;
        std::string credit_chk_str;
        std::string anufee_str;
        std::string benefit1_str;
        std::string benefit2_str;
        std::string benefit3_str;
        std::string benefit4_str;
        std::string f_str;

        f_str = "=============================================================================\n"
                "[1] 카드회사: 선택안함 // [2] 신용/체크카드: 선택안함 // [3] 연회비: 선택안함 \n"
                "[4] 혜택 1: 선택안함 // [5] 혜택 2: 선택안함 // [6] 혜택 3: 선택안함 // [7] 혜택 4: 선택안함\n"
                "=============================================================================\n"
                "[8] 검색하기\n";
        
        while (true)
        {
            write(clnt_sock, "세부 조건을 선택해서 검색하세요\n", strlen("세부 조건을 선택해서 검색하세요\n"));
            write(clnt_sock, f_str.c_str(), f_str.length());
            
            memset(msg, 0, sizeof(msg));
            read(clnt_sock, msg, sizeof(msg));
            choice = atoi(msg);
            
            switch (choice)
            {
            case 1:
                write(clnt_sock, "1.신한 // 2.국민 // 3.농협 // 4.삼성 // 5.우리 // 6.하나\n", strlen("1.신한 // 2.국민 // 3.농협 // 4.삼성 // 5.우리 // 6.하나\n"));
                memset(msg, 0, sizeof(msg));
                read(clnt_sock, msg, sizeof(msg));
                if (strcmp(msg, "1") == 0 || strcmp(msg, "신한") == 0)
                {

                }

                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                
                break;
            case 8:
                
                break;
            default:
                break;
            }
            


            

        }
    }

    ~CardHandler() 
    {
        for (Card* card : cards_v)
        {
            delete card;
        }
    };
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
    int str_len, choice, check;
    UserHandler u_handelr(clnt_sock);
    User p_user;

    write(clnt_sock, "카추추에 오신걸 환영합니다\n", strlen("카추추에 오신걸 환영합니다\n"));
    while (true)
    {
        write(clnt_sock, "\n1. 로그인  2. 회원가입  3. 회원탈퇴\n", strlen("\n1. 로그인  2. 회원가입  3. 회원탈퇴\n"));
        memset(msg, 0, sizeof(msg));
        str_len = read(clnt_sock, msg, sizeof(msg));
        choice = atoi(msg);
        std::cout<<choice<<std::endl;
        
        if (choice == LoginMenu::LOGIN)
        {
            check = u_handelr.login();
            if (check == 0)
            {
                continue;
            }
            else
            {
                p_user = u_handelr.get_puser();
                break;
            }
                
        }
        else if (choice == LoginMenu::SIGNUP)
        {
            u_handelr.sign_up();
            continue;
        }
        else if (choice == LoginMenu::WITHDRAW)
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
    // ============================== DB 연결 =====================================
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    sql::SQLString url("jdbc:mariadb://10.10.20.111:3306/todo");
    sql::Properties properties({{"user", "asd"}, {"password", "1234"}});
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    // ============================================================================
    CardHandler card_handler(clnt_sock, conn);
    card_handler.put_in_card();

    while (true) // 카드 추천 기능
    {
        write(clnt_sock, "\n1. 카드전체 목록보기  2. 카드검색  3. 카드추천  4. 카드생성  5. 프로그램 종료\n\n", strlen("\n1. 카드전체 목록보기  2. 카드검색  3. 카드추천  4. 카드생성  5. 프로그램 종료\n\n"));
        memset(msg, 0, sizeof(msg));
        str_len = read(clnt_sock, msg, sizeof(msg));
        
        if (str_len == 0)
        {
            std::lock_guard<std::mutex> lock(mutx);
            clnt_socks.remove(clnt_sock);  // 리스트에서 해당 소켓 제거
            close(clnt_sock);
        }

        choice = atoi(msg);
        if (choice == 1) // 카드 전체보기
        {
            card_handler.show_all_card();
            continue;
        }
        else if (choice == 2) // 카드 검색
        {
            while (true)
            {
                write(clnt_sock, "1. 카드사별 검색  2. 카드혜택별 검색  3. 세부 검색  4. 뒤로가기\n\n", strlen("1. 카드사별 검색  2. 카드혜택별 검색  3. 세부 검색  4. 뒤로가기\n\n"));
                memset(msg, 0, sizeof(msg));
                read(clnt_sock, msg, sizeof(msg));
                choice = atoi(msg);
                if (choice == 1) // 카드사별 검색
                {

                }
                else if (choice == 2) // 카드혜택별 검색
                {

                }
                else if (choice == 3) // 세부 검색
                {
                    
                } 
                else if (choice == 4)
                {
                    break;
                }
                else
                {
                    write(clnt_sock, "다시 입력하세요.\n", strlen("다시 입력하세요.\n"));
                    continue;
                }
            }
            
        }
        else if (choice == 3) // 카드 추천
        {

        }
        else if (choice == 4) // 카드 생성
        {

        }
        else if (choice == 5) // 프로그램 종료
        {
            std::lock_guard<std::mutex> lock(mutx);
            write(clnt_sock, "&close&", strlen("&close&"));
            clnt_socks.remove(clnt_sock);  // 리스트에서 해당 소켓 제거
            close(clnt_sock);
        }
        else
        {
            write(clnt_sock, "잘못 입력하셨습니다.\n", strlen("잘못 입력하셨습니다.\n"));
            continue;
        }


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
	std::string msg1 = msg;
	std::istringstream iss(msg1);
	std::vector<std::string> tokens;

	std::string token;
	while (iss >> token) 
    { 
        // 공백을 기준으로 단어를 읽어옴
		tokens.push_back(token); // 벡터에 추가
    }
    if (tokens[0] == "/s")  // 문자열이 '/s'와 같은지 비교
    {
        showTasks(conn);  // '/s'를 입력하면 showTasks 호출
    }
    else if (tokens[0] == "/m")
    {
        Brandselect(conn, tokens[1]);
    }
    else if (tokens[0] == "/b")
    {
        strtok(msg, " ");
        char *msg0 = strtok(NULL, "\0");
        std::string msg2 = msg0;
        Benefitselect(conn, msg2);
    }
    
}

void Benefitselect(std::unique_ptr<sql::Connection> &conn, std::string msg)
{
	std::vector<Card> BrandCards;
    std::string beneifit;
    std::string asd = "";
    try 
    {
        std::istringstream iss(msg);
        std::vector<std::string> tokenss;

        std::string token;
        for (int i = 0; i < 4 && iss >> token; i++) 
        { 
            // 공백을 기준으로 단어를 읽어옴
            tokenss.push_back(token); // 벡터에 추가
            asd += " c." +tokenss[i]+ " DESC,";

        }

        // std::vector<std::string> parts = split(msg, ' ');

        asd.pop_back();
        std::cout << asd << std::endl;
        std::string query = "SELECT b.CARDNAME, b.ANUFEE, b.`CHECK/CREDIT`, b.CARDBRAND, "
        "b.CARDBRANDINT, c.`교통`, c.`주유`,c.`푸드`,c.병원 ,c.여행 "
        "FROM BASECARD AS b JOIN BENEFITS AS c ON b.CARDNUM = c.BENEFITNUM "
        "ORDER BY"+asd+ " LIMIT 10;";
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(query));
      
        sql::ResultSet *res = stmnt->executeQuery();
		
	
        // 결과를 반복하면서 출력
        while (res->next()) 
        {
            std::cout << std::string(res->getString(1)) << std::endl;
            std::cout << res->getInt(2) << std::endl;
            std::cout << res->getInt(3) << std::endl;
            std::cout << std::string(res->getString(4)) << std::endl;
            std::cout << res->getInt(6) << std::endl;
            std::cout << res->getInt(7) << std::endl;
            std::cout << res->getInt(8)<< std::endl;
            std::cout << res->getInt(9)<< std::endl;
            std::cout << res->getInt(10)<< std::endl;
        }
		
    }
    catch(sql::SQLException& e)
    {
        std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
    }
	
}
void Brandselect(std::unique_ptr<sql::Connection> &conn, std::string msg)
{
	std::vector<Card> BrandCards;
    try 
    {
        std::string query = "SELECT CARDNAME, ANUFEE, `CHECK/CREDIT`, CARDBRAND, CARDBRANDINT, 교통, 주유, 푸드, 병원, 여행 "
                    "FROM " + msg + " AS a "
                    "JOIN todo.BASECARD AS b ON a.BRANDNUM = b.CARDNUM "
                    "JOIN BENEFITS AS c ON b.CARDNUM = c.BENEFITNUM;";
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(query));
      
        sql::ResultSet *res = stmnt->executeQuery();
		
	
        // 결과를 반복하면서 출력
        while (res->next()) 
        {
            std::cout << std::string(res->getString(1)) << std::endl;
            std::cout << res->getInt(2) << std::endl;
            std::cout << res->getInt(3) << std::endl;
            std::cout << std::string(res->getString(4)) << std::endl;
            std::cout << res->getInt(6) << std::endl;
            std::cout << res->getInt(7) << std::endl;
            std::cout << res->getInt(8)<< std::endl;
            std::cout << res->getInt(9)<< std::endl;
            std::cout << res->getInt(10)<< std::endl;
        }
		
    }
    catch(sql::SQLException& e)
    {
        std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
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
            baseCards.emplace_back(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, 0);
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


// 문자열을 구분자로 분리하는 함수
std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


// 여기는 메인에서
// while (std::getline(ss, line))
// {
//     if (!line.empty())
//     {
//         std::vector<std::string> parts = split(line, ' ');
//     }
// }
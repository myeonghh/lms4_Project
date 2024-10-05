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
#include <unordered_set>
#include <iomanip>
#include <random>
#include <ctime>

#define BUF_SIZE 1024
#define MAX_CLNT 256
const std::string YELLOW  = "\033[38;2;255;255;0m";
const std::string BLUE  = "\033[38;2;79;117;255m";
const std::string GREEN = "\033[38;2;110;194;7m";
const std::string RED = "\033[38;2;231;41;41m";
const std::string SKIN = "\033[38;2;255;215;196m";
const std::string LIGHTBLUE = "\033[38;2;0;169;255m";
const std::string ORANGE = "\033[38;2;255;166;47m";
const std::string LIGTHBROWN ="\033[38;2;222;172;128m";
const std::string GRAYBLUE = "\033[38;2;155;184;205m";
const std::string END = "\033[0m";


std::list<int> clnt_socks;  // 소켓 목록을 관리할 리스트
std::mutex mutx;  // 클라이언트 소켓 목록을 보호하기 위한 mutex

void handle_clnt(int clnt_sock);
void error_handling(const char * msg);

enum {SINHAN = 1, KB, NH, SAMSUNG, WOORI, HANA};

namespace LoginMenu
{
    enum {LOGIN = 1, SIGNUP, WITHDRAW};
}

enum {TRAFFIC = 1, OIL, FOOD, HOSPITAL, TRIP};

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
                    write(clnt_sock, "&clear&", strlen("&clear&"));
                    write(clnt_sock, "\n\033[38;2;255;255;0m로그인에 성공하였습니다.\033[0m\n\n", strlen("\n\033[38;2;255;255;0m로그인에 성공하였습니다.\033[0m\n\n"));
                    User puser(user_v[i]->get_user_num(), user_v[i]->get_id(), user_v[i]->get_pw(), user_v[i]->get_name(), user_v[i]->get_age());
                    p_user = puser;
                    return 1;
                }
            }

            write(clnt_sock, "\033[38;2;231;41;41m아이디 혹은 비밀번호가 맞지 않습니다.\033[0m\n", strlen("\033[38;2;231;41;41m아이디 혹은 비밀번호가 맞지 않습니다.\033[0m\n"));
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
                write(clnt_sock, "\033[38;2;231;41;41m이미 가입 된 아이디 입니다. 다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m이미 가입 된 아이디 입니다. 다시 입력하세요.\033[0m\n"));
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
                write(clnt_sock, "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m다시 입력하세요.\033[0m\n"));
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
                write(clnt_sock, "\033[38;2;0;169;255m회원탈퇴 처리 되었습니다.\033[0m\n", strlen("\033[38;2;0;169;255m회원탈퇴 처리 되었습니다.\033[0m\n"));
                {
                    std::lock_guard<std::mutex> lock(mutx);
                    user_v.erase(user_v.begin() + i);
                }
                return;
            }
        }

        write(clnt_sock, "\033[38;2;231;41;41m아이디 혹은 비밀번호가 맞지 않습니다.\033[0m\n", strlen("\033[38;2;231;41;41m아이디 혹은 비밀번호가 맞지 않습니다.\033[0m\n"));
        
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
              "카드번호: " + std::to_string(card_num) + " // " + ((check_or_credit)? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + brand_name + "\n"
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
    std::vector<Card*> copy_v;
    int clnt_sock;
    std::unique_ptr<sql::Connection> &conn;
    
public:
    CardHandler(int clnt_sock, std::unique_ptr<sql::Connection> &conn)  : clnt_sock(clnt_sock), conn(conn)
    {};

    std::string paint_string(std::string str)
    {
        std::string res_str;
        if (str == "신한카드")
        {
            res_str = LIGHTBLUE+"신한카드"+END;
        }
        else if (str == "국민카드")
        {
            res_str = LIGTHBROWN+"국민카드"+END;
        }
        else if (str == "농협카드")
        {
            res_str = YELLOW+"농협카드"+END;
        }
        else if (str == "삼성카드")
        {
            res_str = BLUE+"삼성카드"+END;
        }
        else if (str == "우리카드")
        {
            res_str = SKIN+"우리카드"+END;
        }
        else if (str == "하나카드")
        {
            res_str = GREEN+"하나카드"+END;
        }
        return res_str;
    }

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
            std::string cardBrand = paint_string(std::string(res->getString(5))); 
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

    void put_in_card2()
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
            std::string cardBrand = paint_string(std::string(res->getString(5))); 
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
                copy_v.emplace_back(new SinhanCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case KB:
                copy_v.emplace_back(new KBCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case NH:
                copy_v.emplace_back(new NHCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case SAMSUNG:
                copy_v.emplace_back(new SamsungCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case WOORI:
                copy_v.emplace_back(new WooriCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
                break;
            case HANA:
                copy_v.emplace_back(new HanaCard(cardNum, cardName, anuFee, checkOrCredit, cardBrand, cardBrandInt, traffic, oil, food, hospital, trip, clnt_sock));
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
        int choice_arr[7] = {0,};
        int choice, i;
        bool check;
        std::string brand_str = RED+"선택안함"+END;
        std::string credit_chk_str = RED+"선택안함"+END;
        std::string anufee_str = RED+"선택안함"+END;
        std::string benefit1_str = RED+"선택안함"+END;
        std::string benefit2_str = RED+"선택안함"+END;
        std::string benefit3_str = RED+"선택안함"+END;
        std::string benefit4_str = RED+"선택안함"+END;
        std::string f_str;
        std::string sub_str;

        while (true)
        {
            
            f_str = "\n============================================================================================\n"
                    "[1] 카드회사: " + brand_str + " // [2] 신용/체크카드: " + credit_chk_str + " // [3] 연회비: " + anufee_str + " 이하\n"
                    "[4] 혜택 1: " + benefit1_str + " // [5] 혜택 2: " + benefit2_str + " // [6] 혜택 3: " + benefit3_str + " // [7] 혜택 4: " + benefit4_str + "\n"
                    "============================================================================================\n"
                    "\t\t\t   [8] 검색하기  [9] 뒤로가기\n";

            write(clnt_sock, "&clear&", strlen("&clear&"));
            write(clnt_sock, "\t\t<하나 이상의 세부조건을 선택해서 검색하세요>\n", strlen("\t\t<하나 이상의 세부조건을 선택해서 검색하세요>\n"));
            write(clnt_sock, f_str.c_str(), f_str.length());
            write(clnt_sock, sub_str.c_str(), sub_str.length());
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
                    brand_str = LIGHTBLUE+"신한카드"+END;
                    sub_str = "";
                    choice_arr[0] = 1;
                }
                else if (strcmp(msg, "2") == 0 || strcmp(msg, "국민") == 0)
                {
                    brand_str = LIGTHBROWN+"국민카드"+END;
                    sub_str = "";
                    choice_arr[0] = 2;
                }
                else if (strcmp(msg, "3") == 0 || strcmp(msg, "농협") == 0)
                {
                    brand_str = YELLOW+"농협카드"+END;
                    sub_str = "";
                    choice_arr[0] = 3;
                }
                else if (strcmp(msg, "4") == 0 || strcmp(msg, "삼성") == 0)
                {   
                    brand_str = BLUE+"삼성카드"+END;
                    sub_str = "";
                    choice_arr[0] = 4;
                }
                else if (strcmp(msg, "5") == 0 || strcmp(msg, "우리") == 0)
                {
                    brand_str = SKIN+"우리카드"+END;
                    sub_str = "";
                    choice_arr[0] = 5;
                }
                else if (strcmp(msg, "6") == 0 || strcmp(msg, "하나") == 0)
                {
                    brand_str = GREEN+"하나카드"+END;
                    sub_str = "";
                    choice_arr[0] = 6;
                }
                else
                {
                   sub_str = "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n";
                }
                break;
            case 2:
                write(clnt_sock, "1. 체크카드 // 2. 신용카드\n", strlen("1. 체크카드 // 2. 신용카드\n"));
                memset(msg, 0, sizeof(msg));
                read(clnt_sock, msg, sizeof(msg));
                if (strcmp(msg, "1") == 0 || strcmp(msg, "체크카드") == 0)
                {
                    credit_chk_str = ORANGE+"체크카드"+END;
                    sub_str = "";
                    choice_arr[1] = 1;
                }
                else if (strcmp(msg, "2") == 0 || strcmp(msg, "신용카드") == 0)
                {
                    credit_chk_str = GRAYBLUE+"신용카드"+END;
                    sub_str = "";
                    choice_arr[1] = 2;
                }
                else
                {
                    sub_str = "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n";
                }
                break;
            case 3:
                write(clnt_sock, "연회비를 입력하세요 (입력한 연회비 이하 검색)\n", strlen("연회비를 입력하세요 (입력한 연회비 이하 검색)\n"));
                memset(msg, 0, sizeof(msg));
                read(clnt_sock, msg, sizeof(msg));
                if (atoi(msg))
                {
                    anufee_str = LIGHTBLUE+msg+END;
                    sub_str = "";
                    choice_arr[2] = atoi(msg);
                }
                else
                {
                    sub_str = "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n";
                }
                break;
            case 4:
                input_benefit(msg, benefit1_str, choice_arr, 3, sub_str);
                break;
            case 5:
                if (!(choice_arr[3]))
                {
                    sub_str = "\033[38;2;231;41;41m혜택을 순서대로 선택하세요.\033[0m\n";
                    continue;
                }
                input_benefit(msg, benefit2_str, choice_arr, 4, sub_str);
                break;
            case 6:
                if (!(choice_arr[4]))
                {
                    sub_str = "\033[38;2;231;41;41m혜택을 순서대로 선택하세요.\033[0m\n";
                    continue;
                }
                input_benefit(msg, benefit3_str, choice_arr, 5, sub_str);
                break;
            case 7:
                if (!(choice_arr[5]))
                {
                    sub_str = "\033[38;2;231;41;41m혜택을 순서대로 선택하세요.\033[0m\n";
                    continue;
                }
                input_benefit(msg, benefit4_str, choice_arr, 6, sub_str);
                break;
            case 8:
                check = false;
                for (i = 0; i < sizeof(choice_arr) / sizeof(int); i++)
                {
                    if (choice_arr[i])
                    {
                        check = true;
                        break;
                    }
                }
                if (check == true)
                {
                    detail_search(choice_arr);
                    return;
                }
                else
                {
                    sub_str = "\033[38;2;231;41;41m적어도 하나의 조건은 선택해야 합니다.\033[0m\n";
                    continue;
                }
                break;
            case 9:
                write(clnt_sock, "&clear&", strlen("&clear&"));
                return;
                break;
            default:
                sub_str = "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n";
                break;
            }
        }
    }

    void input_benefit(char *msg, std::string& benefit_str, int choice_arr[], int index, std::string& sub_str)
    {
        write(clnt_sock, "1. 교통 // 2. 주유 // 3. 푸드 // 4. 병원 // 5. 여행\n", strlen("1. 교통 // 2. 주유 // 3. 푸드 // 4. 병원 // 5. 여행\n"));
        memset(msg, 0, sizeof(msg));
        read(clnt_sock, msg, sizeof(msg));
        if (strcmp(msg, "1") == 0 || strcmp(msg, "교통") == 0)
        {
            benefit_str = LIGHTBLUE+"교통"+END;
            sub_str = "";
            choice_arr[index] = 1;
        }
        else if (strcmp(msg, "2") == 0 || strcmp(msg, "주유") == 0)
        {
            benefit_str = LIGHTBLUE+"주유"+END;
            sub_str = "";
            choice_arr[index] = 2;
        }
        else if (strcmp(msg, "3") == 0 || strcmp(msg, "푸드") == 0)
        {
            benefit_str = LIGHTBLUE+"푸드"+END;
            sub_str = "";
            choice_arr[index] = 3;
        }
        else if (strcmp(msg, "4") == 0 || strcmp(msg, "병원") == 0)
        {   
            benefit_str = LIGHTBLUE+"병원"+END;
            sub_str = "";
            choice_arr[index] = 4;
        }
        else if (strcmp(msg, "5") == 0 || strcmp(msg, "여행") == 0)
        {
            benefit_str = LIGHTBLUE+"여행"+END;
            sub_str = "";
            choice_arr[index] = 5;
        }
        else
        {
            write(clnt_sock, "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m다시 입력하세요.\033[0m\n"));
        }
    }

    void detail_search(int choice_arr[])
    {
        int e1 = choice_arr[0];
        int e2 = choice_arr[1];
        int e3 = choice_arr[2];
        int e4 = choice_arr[3];
        int e5 = choice_arr[4];
        int e6 = choice_arr[5];
        int e7 = choice_arr[6];
        int i;

        put_in_card2();

        if (e1 > 0) // 카드사 필터링
        {
            for (i = 0; i < copy_v.size(); i++)
            {
                if (e1 != copy_v[i]->get_bint())
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
            }
        }

        if (e2 > 0) // 신용카드, 체크카드 필터링
        {
            for (i = 0; i < copy_v.size(); i++)
            {
                if (e2-1 != copy_v[i]->get_cchk())
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
            }
        }

        if (e3 > 0) // 연회비 필터링
        {
            for (i = 0; i < copy_v.size(); i++)
            {
                if (e3 < copy_v[i]->get_anufee())
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
            }
        }

        if (e4 > 0) // 혜택1 필터링
        {
            benefit_filtering(e4, copy_v);
        }

        if (e5 > 0) // 혜택2 필터링
        {
            benefit_filtering(e5, copy_v);
        }

        if (e6 > 0) // 혜택3 필터링
        {
            benefit_filtering(e6, copy_v);
        }

        if (e7 > 0) // 혜택4 필터링
        {
            benefit_filtering(e7, copy_v);
        }

        // 필터링 끝난 카드정보 클라이언트에게 전송
        for (Card* card : copy_v) 
        {
            card->show_card(); 
        }
        // 남아 있는 카드 포인터 delete로 동적 해제
        for (Card* card : copy_v)
        {
            delete card;
        }
        copy_v.clear(); // 남아있는 벡터 요소 clear
    }

    void benefit_filtering(int benefit, std::vector<Card*>& copy_v)
    {
        int i;

        for (i = 0; i < copy_v.size(); i++)
        {
            switch (benefit)
            {
            case TRAFFIC:
                if (!(copy_v[i]->get_traffic()))
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
                break;
            case OIL:
                if (!(copy_v[i]->get_oil()))
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
                break;
            case FOOD:
                if (!(copy_v[i]->get_food()))
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
                break;
            case HOSPITAL:
                if (!(copy_v[i]->get_hospital()))
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
                break;
            case TRIP:
                if (!(copy_v[i]->get_trip()))
                {
                    delete copy_v[i];
                    copy_v.erase(copy_v.begin() + i);
                    i--;
                }
                break;
            default:
                break;
            }
        }
    }

    void suggest_card()//카드 추천 설문
    {
        int select_bus = 0;
        int select_traffic = 0;
        int select_food = 0;
        int select_oil = 0;
        int select_hospital = 0;
        int select_trip = 0;
        char msg[BUF_SIZE];
        char select_benefit[8];
        char choice_02[BUF_SIZE];
        char benefitlist[BUF_SIZE];
        
        while(1)
        {
            strcpy(msg, "나는 운전을 자주 하는 편이다.\n\n|  1  | Yes  |  2  | No\n");
            write(clnt_sock, msg, sizeof(msg));
            read(clnt_sock, msg, sizeof(msg));
            int onechoice = atoi(msg);
            if(onechoice == 1)
            {
                select_oil = 1;  //주유 혜택
                break;
            }
            else if(onechoice == 2)
            {
                while(1)
                {
                    strcpy(msg, "나는 대중교통을 자주 이용하는 편이다.\n\n|  1  | Yes  |  2  | No\n");
                    write(clnt_sock, msg, sizeof(msg));
                    read(clnt_sock, msg, sizeof(msg));
                    int anotherchoice = atoi(msg);
                    if(anotherchoice == 1)
                    {
                        select_traffic = 1;  //대중교통 혜택 +1
                        break;
                    }
                    else if(anotherchoice == 2)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                    
                }
                break;
            }
            else
            {
                continue;
            }
        }
        while(1)
        {
            strcpy(msg, "나는 자주 다치거나 지병이 있다.\n\n|  1  | Yes  |  2  | No\n");
            write(clnt_sock, msg, sizeof(msg));
            read(clnt_sock, msg, sizeof(msg));
            int onechoice = atoi(msg);
            if(onechoice == 1)
            {
                select_hospital = 1;    //병원 혜택 +1
                break;
            }
            else if(onechoice == 2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        while(1)
        {
            strcpy(msg, "나는 맛집을 찾아다니거나 먹는 것에 진심인 편이다.\n\n|  1  | Yes  |  2  | No\n");
            write(clnt_sock, msg, sizeof(msg));
            read(clnt_sock, msg, sizeof(msg));
            int onechoice = atoi(msg);
            if(onechoice == 1)
            {
                select_food = 1; 
                break;
            }
            else if(onechoice == 2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        while(1)
        {
            strcpy(msg, "나는 여행을 좋아한다.\n\n|  1  | Yes  |  2  | No\n");
            write(clnt_sock, msg, sizeof(msg));
            read(clnt_sock, msg, sizeof(msg));
            int onechoice = atoi(msg);
            if(onechoice == 1)
            {
                select_trip = 1;
                break;
            }else if(onechoice == 2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
            
            std::cout << "\n설문조사 설문 결과 전송 확인 (1은 Yes, 2는 No로 설정)"<<std::endl;
            //if_to_benefits(benefitlist, choice_02);
            std::cout << benefitlist << std::endl;
            std::cout << "\n개인운전 및 일반 교통 혜택에 관한 선호 여부 : " << select_oil << "\n대중 교통 혜택에 관한 선호 여부 : " << select_traffic << "\n의료 혜택에 관한 선호 여부 : " << select_hospital<< "\n식료품에 관한 혜택선호 여부 : " << select_food<< "\n여행에 대한 혜택선호 여부 : " << select_trip << std::endl;   //서버측에서 올바르게 값이 하달되었는지 확인 - 완료
            //해당 Bool 값을 기반으로 데이터를 불러올 수 있음

        show_select_benefit(select_bus, select_traffic, select_food, select_oil, select_hospital, select_trip);
    }

    void show_select_benefit(int select_bus, int select_traffic, int select_food, int select_oil, int select_hospital, int select_trip)
    {
        for (Card* card : cards_v)
        {
            if(select_traffic ==1)
            {
                if(card->get_traffic()>=17)
                {
                    card->show_card();
                }
            }
            if(select_oil == 1)
            {
                if(card->get_oil()>=17)
                {
                    card->show_card();
                }
            }
            if(select_hospital ==1)
            {
                if(card->get_hospital()>=17)
                {
                    card->show_card();
                }
            }
            if(select_food == 1)
            {
                if(card->get_food()>=17)
                {
                    card->show_card();
                }
            }
            if(select_trip == 1)
            {
                if(card->get_trip()>=17)
                {
                    card->show_card();
                }
            }
        }          
    }

    void Benefitselect(int clnt_sock, std::unique_ptr<sql::Connection> &conn, std::string msg)
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
            std::string query = "SELECT b.CARDNUM, b.CARDNAME, b.ANUFEE, b.`CHECK/CREDIT`, b.CARDBRAND, "
            "b.CARDBRANDINT, c.`교통`, c.`주유`,c.`푸드`,c.병원 ,c.여행 "
            "FROM BASECARD AS b JOIN BENEFITS AS c ON b.CARDNUM = c.BENEFITNUM "
            "ORDER BY"+asd+ " LIMIT 10;";
            std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(query));
        
            sql::ResultSet *res = stmnt->executeQuery();
            
        
            // 결과를 반복하면서 출력
            while (res->next()) 
            {
                std::string str;
                str = "====================================================\n" 
                "카드번호: " + std::to_string(res->getInt(1)) + " // " + ((res->getString(2))? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + paint_string(std::string(res->getString(5))) + "\n"
                + "이름: " + res->getString(2) + " // " + "연회비: " + std::to_string(res->getInt(3)) + "\n"
                + "할인혜택: " + ((res->getInt(7) != 0)? "교통 " + std::to_string(res->getInt(7)) + "%, " : "") 
                + ((res->getInt(8) != 0)? "주유 " + std::to_string(res->getInt(8)) + "%, " : "") 
                + ((res->getInt(9) != 0)? "푸드 " + std::to_string(res->getInt(9)) + "%, " : "") 
                + ((res->getInt(10) != 0)? "병원 " + std::to_string(res->getInt(10)) + "%, " : "") 
                + ((res->getInt(11) != 0)? "여행 " + std::to_string(res->getInt(11)) + "% " : "") + "\n"
                + "====================================================\n";
                write(clnt_sock, str.c_str(), str.length());
            }
            
        }
        catch(sql::SQLException& e)
        {
            std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
        }
        
    }

    void Brandselect(int clnt_sock, std::unique_ptr<sql::Connection> &conn, std::string msg)
    {
        std::vector<Card> BrandCards;
        try 
        {
            std::string query = "SELECT CARDNUM, CARDNAME, ANUFEE, `CHECK/CREDIT`, CARDBRAND, CARDBRANDINT, 교통, 주유, 푸드, 병원, 여행 "
                        "FROM " + msg + " AS a "
                        "JOIN todo.BASECARD AS b ON a.BRANDNUM = b.CARDNUM "
                        "JOIN BENEFITS AS c ON b.CARDNUM = c.BENEFITNUM;";
            std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(query));
        
            sql::ResultSet *res = stmnt->executeQuery();
            
        
            // 결과를 반복하면서 출력
            while (res->next()) 
            {
                std::string str;
                str = "====================================================\n" 
                "카드번호: " + std::to_string(res->getInt(1)) + " // " + ((res->getString(2))? "\033[38;2;155;184;205m신용카드\033[0m" : "\033[38;2;255;166;47m체크카드\033[0m")  + " // " + paint_string(std::string(res->getString(5))) + "\n"
                + "이름: " + res->getString(2) + " // " + "연회비: " + std::to_string(res->getInt(3)) + "\n"
                + "할인혜택: " + ((res->getInt(7) != 0)? "교통 " + std::to_string(res->getInt(7)) + "%, " : "") 
                + ((res->getInt(8) != 0)? "주유 " + std::to_string(res->getInt(8)) + "%, " : "") 
                + ((res->getInt(9) != 0)? "푸드 " + std::to_string(res->getInt(9)) + "%, " : "") 
                + ((res->getInt(10) != 0)? "병원 " + std::to_string(res->getInt(10)) + "%, " : "") 
                + ((res->getInt(11) != 0)? "여행 " + std::to_string(res->getInt(11)) + "% " : "") + "\n"
                + "====================================================\n";
                write(clnt_sock, str.c_str(), str.length());
            }
            
        }
        catch(sql::SQLException& e)
        {
            std::cerr << "작업 조회 중 오류: " << e.what() << std::endl;
        }
        
    }

    bool contains_only_specific_strings(const std::string& str) 
    {
        // 확인할 문자열 목록을 집합으로 저장
        std::unordered_set<std::string> keywords = {"교통", "주유", "푸드", "병원", "여행"};

        // 입력 문자열을 공백으로 분리
        std::istringstream iss(str);
        std::string word;

        while (iss >> word) { // 공백을 기준으로 단어를 읽음
            // 단어가 키워드 집합에 없으면 false 반환
            if (keywords.find(word) == keywords.end()) {  
                return false;
            }    // word가 keywords안에 있는지 확인후 없으면 keywords.end()를 반환
        }
        return true; // 모든 단어가 키워드에 포함된 경우
    }

    std::string generate_card_number() 
    {
        std::string card_number;
        std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
        std::uniform_int_distribution<int> distribution(0, 9);   // 0~9 범위지정

        for (int i = 0; i < 16; ++i) {
            card_number += std::to_string(distribution(generator));  // 실제 랜덤값 반환
            // 4자리마다 공백 추가
            if ((i + 1) % 4 == 0 && i != 15) {
                card_number += ' ';
            }
        }

        return card_number;
    }

    void create_card(User p_user) 
    {
        std::string card;
        char msg[BUF_SIZE];
        int choice_cardnum;

        write(clnt_sock, "생성할 카드번호를 입력하세요.\n", strlen("생성할 카드번호를 입력하세요.\n"));
        memset(msg, 0, sizeof(msg));
        read(clnt_sock, msg, sizeof(msg));

        choice_cardnum = atoi(msg);

        if (choice_cardnum > 0 && choice_cardnum <= 100)
        {
            card = 
            " ==============================================\n"
            "｜\t\t\t\t  <"+cards_v[choice_cardnum-1]->get_bname()+">  ｜\n"
            "｜                                            ｜\n"
            "｜  "+cards_v[choice_cardnum-1]->get_cname()+"\t  "+p_user.get_name()+"\n"
            "｜                                            ｜\n"
            "｜\t      "+generate_card_number()+"\t      ｜\n"
            "｜                                            ｜\n"
            " ==============================================\n";

            write(clnt_sock, card.c_str(), card.length());
        }
        else
        {
            write(clnt_sock, "\033[38;2;231;41;41m카드번호를 제대로 다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m카드번호를 제대로 다시 입력하세요.\033[0m\n"));
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

    std::string title = 
"    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢰⢠⢢⠪⡢⡢⡀      \n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠂⡁⠄⠂⡈⢐⠠⠀⠀⠀⠠⡸⡸⠰⠱⠑⠕⢁⢃⢕⠁⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠐⡀⠂⠄⡁⠄⠂⠐⡈⠀⠄⠨⢐⢆⢖⢄⠥⡌⡆⡇⠇⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡀⠂⢌⢠⢊⠂⡁⠁⠄⡁⠌⢀⠂⠑⠅⢇⢇⢣⠱⠁⠅⠂⠀⠀⠀\n"
"⠀⠀⠠⡠⢄⠄⠀⠀⠀⣀⡠⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⡁⡐⣘⣀⠢⡢⡱⢠⢐⢒⠔⡈⡨⣂⠣⢰⢀⠂⡈⠄⠀⠀⠀⠀\n"
"⠀⠀⢀⠇⢔⢅⠀⡔⢝⢐⢅⠢⡩⢣⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠀⢂⠰⠀⠥⢘⠀⢅⠜⠄⠆⠣⠂⠥⢘⠠⠘⡐⠠⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⣀⢤⢠⢔⢕⠁⠂⢀⠠⠈⢐⢕⠤⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⣜⢜⡲⡢⡈⠠⠐⢐⢜⢴⢱⡢⡀⢂⠐⠀⢄⣀⢠⠀⠀⠀\n"
"⠀⢀⢜⢌⠢⠑⠐⠐⠁⠐⠀⠀⠄⠀⢂⢕⢕⡜⡭⡢⡆⣆⢔⡔⡤⡠⡪⠣⠳⠀⠀⠇⠏⠧⡝⠜⠎⠀⠀⠇⠏⡖⡄⠀⠰⡂⣘⠄⠀⠀\n"
"⠀⠸⡌⡢⠡⠐⠀⠂⠈⡀⠈⡀⠄⠁⠸⣜⠀⠀⠀⠀⠀⢱⡁⠀⢣⡫⡪⡀⠀⠀⠀⠀⡀⣜⢥⢀⠀⠀⠀⠀⣀⢜⠎⠀⠈⠀⠀⠁⠀⠀\n"
"⠀⠈⢎⡢⢡⠀⠂⠈⢀⠠⠀⡀⠄⠐⢨⡪⠪⠚⠘⠀⠀⢸⠀⠀⠀⠈⡇⠁⢀⢔⣕⡀⠈⡸⢜⠀⢀⢜⣔⡀⠀⣓⢕⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠑⡕⢅⠅⠈⠀⡀⠠⠀⠠⠀⠸⡸⣠⢠⢄⠀⠀⢜⠅⠀⢸⡱⡝⠁⠊⠈⠀⠉⠘⢸⡱⠁⠊⠈⠀⠑⠁⢇⢇⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⡇⢕⠠⠈⢀⠀⠄⠐⠀⠐⠀⡈⢌⢪⠣⣇⢦⠳⢕⠦⡣⠃⢏⢖⠀⢐⠆⠀⢢⡣⢳⢢⠀⢐⠆⠀⡢⡣⠃⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠹⡰⡡⡑⢄⠢⡊⣜⢐⠅⡢⢊⢔⢜⠁⣀⡀⣄⠀⠀⠀⠀⠈⠎⡖⡜⢕⢖⠵⠁⠈⠮⡲⡸⢱⢢⠳⠁⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠈⠊⠪⠒⠕⠉⠈⠊⠪⠆⠇⠃⠁⠀⡸⣀⡪⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                \n";

    write(clnt_sock, title.c_str(), title.length());
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
            write(clnt_sock, "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m다시 입력하세요.\033[0m\n"));
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
        std::string msg1;

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
                    while (true)
                    {
                        // char msg[BUF_SIZE];
                        write(clnt_sock,"카드 브랜드를 선택하세요 (신한, 국민, 농협, 삼성, 우리, 하나)(4 뒤로가기)\n", strlen("카드 브랜드를 선택하세요 (신한, 국민, 농협, 삼성, 우리, 하나)(4 뒤로가기)\n"));
                        read(clnt_sock, msg, sizeof(msg));
                        msg1 = msg;
            
                        if (msg1 == "삼성" || msg1 == "신한" ||msg1 == "국민" ||msg1 == "하나" ||msg1 == "우리" ||msg1 == "농협")
                        {
                            card_handler.Brandselect(clnt_sock, conn, msg1);    
                            msg1.clear();
                            memset(msg, 0, sizeof(msg));
                            break;
                        }
                        else if (msg1 == "4")
                        {
                            memset(msg, 0, sizeof(msg));
                            break;
                        }
                        else
                        {
                            memset(msg, 0, sizeof(msg));
                            continue;
                        }
                    }
                }
                else if (choice == 2) // 카드혜택별 검색
                {
                    while (true)
                    {
                        // char msg[BUF_SIZE];
                        write(clnt_sock,"원하는 혜택들을 수선순위 순서로 입력하세요 (교통, 주유, 푸드, 병원, 여행)(최대 4개까지 입력가능)(4 뒤로가기)\n", strlen("원하는 혜택들을 수선순위 순서로 입력하세요 (교통, 주유, 푸드, 병원, 여행)(최대 4개까지 입력가능)(4 뒤로가기)\n"));
                        read(clnt_sock, msg, sizeof(msg));
                        msg1 = msg;
            
                        if (card_handler.contains_only_specific_strings(msg1))
                        {
                            card_handler.Benefitselect(clnt_sock, conn, msg1);    
                            msg1.clear();
                            memset(msg, 0, sizeof(msg));
                            break;
                        }
                        else if (msg1 == "4")
                        {
                            memset(msg, 0, sizeof(msg));
                            break;
                        }
                        else
                        {
                            memset(msg, 0, sizeof(msg));
                            continue;
                        }
                    }
                }
                else if (choice == 3) // 세부 검색
                {
                    card_handler.detailed_card_search();
                } 
                else if (choice == 4)
                {
                    //write(clnt_sock, "&clear&", strlen("&clear&"));
                    break;
                }
                else
                {
                    write(clnt_sock, "\033[38;2;231;41;41m다시 입력하세요.\033[0m\n", strlen("\033[38;2;231;41;41m다시 입력하세요.\033[0m\n"));
                    continue;
                }
            }
        }
        else if (choice == 3) // 카드 추천
        {
            card_handler.suggest_card();
        }
        else if (choice == 4) // 카드 생성
        {
            card_handler.create_card(p_user);
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
            write(clnt_sock, "\033[38;2;231;41;41m잘못 입력하셨습니다.\033[0m\n", strlen("\033[38;2;231;41;41m잘못 입력하셨습니다.\033[0m\n"));
            continue;
        }
    }
}

void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}



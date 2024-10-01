#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#define MAX 100
std::stringstream ss;
class Base_card
{
private:
    //enum card_compeny
    //{
    //    Sin_han,
    //    Guk_min,
    //    Nong_heaup,
    //    Gui_up,
    //    신한은행
    //};
    char* cardlist[6] = {"삼성카드", "하나카드", "농협카드", "국민은행", "우리은행", "신한 카드"};
    //삼성, 하나카드, 농협, 국민, 우리, 신한

public:
    Base_card(char list_01, char list_02, char list_03)
    {
        (int)list_01;

    }
};

class Benefit
{
private:
    char* benefit_list[5] = {"교통", "주유", "도로", "여행", "병원"};

public:
    void start_screen()
    {
        char select[MAX];
        char list_01[MAX], list_02[MAX], list_03[MAX];
        int a, b, c;
        while(1)
        {
            std::cout << "카드 추천 프로그램 입니다!" << std::endl;
            std::cout <<"\n 원하시는 목록을 선택 해 주세요!\n"<<std::endl;
            std::cout << "|  1  | 혜택 기반 카드 추천   |  2  | 카드 추천을 위한 테스트 "<< std::endl;
            std::cin.getline(select, MAX);
            if(!strcmp(select, "1"))
            {
                std::cout<<"1번을 선택하셨습니다\n고객님이 가장 필요로 하시는 혜택 목록 3가지를 선택 해 주세요"<<std::endl;
                std::cout<<"|  1  |  교통    |  2  |  주유    |  3  |  도로    |  4  |  여행    |  5  |  병원    "<<std::endl;
                std::cin.getline(list_01, MAX);
                std::cin.getline(list_02, MAX);
                std::cin.getline(list_03, MAX);
                ss << list_01;
                ss >> a;
                ss << list_02;
                ss >> b;
                ss << list_03;
                ss >> c;
                list_01[MAX] = *benefit_list[1];
                list_02[MAX] = *benefit_list[2];
                list_03[MAX] = *benefit_list[3];
                std::cout << list_01 << list_02 << list_03 <<std::endl;
                break;
            }
            else if(!strcmp(select, "2"))
            {
                std::cout<<"2번을 선택하셨습니다"<<std::endl;
                break;
            }
            else
            {
                std::cout<<"옳지 않은 입력입니다!\n"<<std::endl;
                continue;
            }
        }
    }
};



int main(void)
{
    Benefit starts;
    starts.start_screen();


}

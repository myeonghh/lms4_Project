#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define z_len 8
#define y_len 50
#define x_len 50
// ctrl + shift + l ==> 변수 일괄 변경(드래그 해놓고)

int getch();
void player_move(int map[][50][50], int xlen, int ylen, int zlen, int *x, int *y, int *p_loc);
int map_move(int map[][50][50], int xlen, int ylen, int zlen, int *x, int *y, int *p_loc);


struct Monster
{
    int maxhp;
    int hp;
    int dmg;
    
};


int main(void)
{
    // 0: 빈공간, 1: 갈수 없는 곳, 2: 플레이어, 3: 몬스터, 4: 입구, 5: 출구, 
    // const int z_len = 8;
    // const int y_len = 10;
    // const int x_len = 10;

    // int map[z_len][y_len][x_len];
    int z, y, x, loc_x, loc_y, present_loc;
    //========================== 맵 생성 ===============================
    // for (z = 0; z < z_len; z++)
    // {
    //     for (y = 0; y < y_len; y++)
    //     {
    //         for (x = 0; x < x_len; x++)
    //         {
    //             map[z][y][x] = 0;
    //         }
    //     }
    //     map[z][0][0] = 4;
    //     map[z][y_len - 1][x_len - 1] = 5;
    // }
    //==================================================================
    
    int map[z_len][y_len][x_len] = {
                                {{2, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 5}},
                                {{4, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}
                                                                };


    loc_x = 0;
    loc_y = 0;
    present_loc = 0;
    // 0: 마을 // 1 ~ 7: 던전1 ~ 던전7s

    map[0][0][0] = 2;
    while (1)
    {
        for (y = 0; y < y_len; y++)
        {
            for (x = 0; x < x_len; x++)
            {
                switch (map[present_loc][y][x])
                {
                case 0:
                    printf(" ▫ ");
                    break;
                case 1:
                    printf(" 🪨");
                    break;
                case 2:
                    printf("🤺 ");
                    break;
                case 3:
                    printf(" 💀");
                    break;
                case 4:
                    printf(" ⛩ ");
                    break;
                case 5:
                    printf(" ➡ ");
                    break;                
                case 6:
                    printf(" 🟦");
                    break;
                case 7:
                    printf(" 🪜");
                    break;
                case 8:
                    printf(" 🚢");
                    break;
                case 9:
                    printf(" 🏰");
                    break;
                case 10:
                    printf(" 🏠");
                    break;
                case 11:
                    printf(" 💰");
                    break;
                case 12:
                    printf(" 🔥");
                    break;
                case 13:
                    printf(" 🌳");
                    break;
                case 14:
                    printf(" ⛲");
                    break;
                case 15:
                    printf(" 🔨");
                    break;
                case 16:
                    printf(" 🛡️ ");
                    break;
                case 17:
                    printf(" 🔮");
                    break;
                case 18:
                    printf(" 🎰");
                    break;
                case 19:
                    printf(" 🌊");
                    break;
                case 20:
                    printf(" 🕊️ ");
                    break;
                case 21:
                    printf(" 🟨");
                    break;
                case 22:
                    printf(" 🧱");
                    break;
                case 23:
                    printf(" 🌲");
                    break;
                case 24:
                    printf(" 🟥");
                    break;
                case 25:
                    printf(" 🌵");
                    break;
                case 26:
                    printf(" 🌴");
                    break;
                case 27:
                    printf(" 🌋");          
                    break;
                case 28:
                    printf(" 🌼");
                    break;
                case 29:
                    printf(" 🌸");
                    break;
                case 30:
                    printf(" 🍄");
                    break;
                case 31:
                    printf(" 🔯");          
                    break;
                case 32:
                    printf(" 🏔️ ");
                    break;
                case 33:
                    printf(" ❄️ ");
                    break;
                case 34:
                    printf(" ⬜");
                    break;
                case 35:
                    printf(" 🐅");          
                    break;
                case 36:
                    printf(" ⛄");
                    break;
                case 37:
                    printf(" 🪻 ");  
                    break;
                case 38:
                    printf(" ╔");
                    break;
                case 39:
                    printf(" ═");
                    break;
                case 40:
                    printf(" ╗");
                    break;
                case -1:
                    printf(" 👿");
                    break;
                case -2:
                    printf(" 🐻");
                    break;
                case -3:
                    printf(" 🐐");
                    break;
                case -4:
                    printf(" 🧑");          
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
       
        if (present_loc == 0)
            printf("현재 장소 : 마을\n");
        else
            printf("현재 장소 : 던전 %d 층\n", present_loc);
        //printf("00 ====> %d\n", map[present_loc+1][0][0]);

        player_move(map, x_len, y_len, z_len, &loc_x, &loc_y, &present_loc);

        map_move(map, x_len, y_len, z_len, &loc_x, &loc_y, &present_loc);
        
        system("clear");
    }

    return 0;
}

void player_move(int map[][50][50], int xlen, int ylen, int zlen, int *x, int *y, int *p_loc)
{
    int temp;

    char move = 0;

    printf("\n");
    printf("   w     \n");
    printf("   ↟    \n");
    printf("a↞  ↠d 플레이어(x,y) %d,%d\n", *x, *y);
    printf("   ↡    \n");
    printf("   s     >> %c", move);
    move = getch();

    if (move == 65 || move == 97) // ↞a
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*x > 0 && (map[*p_loc][*y][(*x)-1] != 1 || map[*p_loc][*y][(*x)-1] != 6 || map[*p_loc][*y][(*x)-1] != 10 || map[*p_loc][*y][(*x)-1] != 12 || map[*p_loc][*y][(*x)-1] != 13 || map[*p_loc][*y][(*x)-1] != 19 || map[*p_loc][*y][(*x)-1] != 22 || map[*p_loc][*y][(*x)-1] != 23 || map[*p_loc][*y][(*x)-1] != 24 || map[*p_loc][*y][(*x)-1] != 25 || map[*p_loc][*y][(*x)-1] != 26 || map[*p_loc][*y][(*x)-1] != 28 || map[*p_loc][*y][(*x)-1] != 29 || map[*p_loc][*y][(*x)-1] != 30 || map[*p_loc][*y][(*x)-1] != 32 || map[*p_loc][*y][(*x)-1] != 34 || map[*p_loc][*y][(*x)-1] != 37))
        {
            
            temp = map[*p_loc][*y][*x];
            *x -= 1;
            map[*p_loc][*y][*x] = 2;

            if(map[*p_loc][ylen-1][xlen-1] != 2)
                map[*p_loc][*y][(*x) + 1] = temp;
            else
                map[*p_loc][*y][(*x) + 1] = 5;
            
        }
        // break;
    }
    else if (move == 68 || move == 100) // d↠
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*x < xlen - 1 && (map[*p_loc][*y][(*x)+1] != 1 || map[*p_loc][*y][(*x)+1] != 6 || map[*p_loc][*y][(*x)+1] != 10 || map[*p_loc][*y][(*x)+1] != 12 || map[*p_loc][*y][(*x)+1] != 13 || map[*p_loc][*y][(*x)+1] != 19 || map[*p_loc][*y][(*x)+1] != 22 || map[*p_loc][*y][(*x)+1] != 23 || map[*p_loc][*y][(*x)+1] != 24 || map[*p_loc][*y][(*x)+1] != 25 || map[*p_loc][*y][(*x)+1] != 26 || map[*p_loc][*y][(*x)+1] != 28 || map[*p_loc][*y][(*x)+1] != 29 || map[*p_loc][*y][(*x)+1] != 30 || map[*p_loc][*y][(*x)+1] != 32 || map[*p_loc][*y][(*x)+1] != 34 || map[*p_loc][*y][(*x)+1] != 37))
        {
            //temp = map[*p_loc][*y][*x];
            *x += 1;
            map[*p_loc][*y][*x] = 2;
            map[*p_loc][*y][(*x) - 1] = 0;

            
        }
        // break;
    }
    else if (move == 87 || move == 119) // w위로
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*y > 0 && (map[*p_loc][(*y)-1][*x] != 1 || map[*p_loc][(*y)-1][*x] != 6 || map[*p_loc][(*y)-1][*x] != 10 || map[*p_loc][(*y)-1][*x] != 12 || map[*p_loc][(*y)-1][*x] != 13 || map[*p_loc][(*y)-1][*x] != 19 || map[*p_loc][(*y)-1][*x] != 22 || map[*p_loc][(*y)-1][*x] != 23 || map[*p_loc][(*y)-1][*x] != 24 || map[*p_loc][(*y)-1][*x] != 25 || map[*p_loc][(*y)-1][*x] != 26 || map[*p_loc][(*y)-1][*x] != 28 || map[*p_loc][(*y)-1][*x] != 29 || map[*p_loc][(*y)-1][*x] != 30 || map[*p_loc][(*y)-1][*x] != 32 || map[*p_loc][(*y)-1][*x] != 34 || map[*p_loc][(*y)-1][*x] != 37))
        {
            //temp = map[*p_loc][*y][*x];
            *y -= 1;
            map[*p_loc][*y][*x] = 2;
            map[*p_loc][(*y) + 1][*x] = 0;

            
        }
        // break;
    }
    else if (move == 83 || move == 115) // s아래로
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*y < ylen - 1 && (map[*p_loc][(*y)+1][*x] != 1 || map[*p_loc][(*y)+1][*x] != 6 || map[*p_loc][(*y)+1][*x] != 10 || map[*p_loc][(*y)+1][*x] != 12 || map[*p_loc][(*y)+1][*x] != 13 || map[*p_loc][(*y)+1][*x] != 19 || map[*p_loc][(*y)+1][*x] != 22 || map[*p_loc][(*y)+1][*x] != 23 || map[*p_loc][(*y)+1][*x] != 24 || map[*p_loc][(*y)+1][*x] != 25 || map[*p_loc][(*y)+1][*x] != 26 || map[*p_loc][(*y)+1][*x] != 28 || map[*p_loc][(*y)+1][*x] != 29 || map[*p_loc][(*y)+1][*x] != 30 || map[*p_loc][(*y)+1][*x] != 32 || map[*p_loc][(*y)+1][*x] != 34 || map[*p_loc][(*y)+1][*x] != 37))
        {
            temp = map[*p_loc][*y][*x];
            *y += 1;
            map[*p_loc][*y][*x] = 2;
            map[*p_loc][(*y) - 1][*x] = 0;

            
        }
        // break;
    }

    if (map[*p_loc][0][0] != 2)
        map[*p_loc][0][0] = 4;
    if (map[*p_loc][ylen - 1][xlen - 1] != 2)
        map[*p_loc][ylen - 1][xlen - 1] = 5;

    // system("clear");
}

int map_move(int map[][50][50], int xlen, int ylen, int zlen, int *x, int *y, int *p_loc)
{
    int cnum, scan;

    if(*p_loc < 7)
    {
        if (map[*p_loc][ylen-1][xlen-1] == 2 )
        {
            map[*p_loc][ylen-1][xlen-1] = 5;
            *p_loc += 1;
            map[*p_loc][0][0] = 2;
            
            *x = 0;
            *y = 0;
            return 0;
        }
    }
    if(*p_loc > 0)
    {
        if (map[*p_loc][0][0] == 2)
        {
            map[*(p_loc)][0][0] = 4;
            *p_loc -= 1;
            map[*p_loc][ylen-1][xlen-1] = 2;
            
            *x = xlen-1;
            *y = ylen-1;
            return 0;
        }
    }   
}


int getch()
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);        // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                     // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                    // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
}
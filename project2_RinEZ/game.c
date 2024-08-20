#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

// ctrl + shift + l ==> 변수 일괄 변경(드래그 해놓고)

int getch();
int p_move(int map[][20][20], int xlen, int ylen, int zlen, int* x, int* y);

int main(void)
{
    // 0: 빈공간, 1: 갈수 없는 곳, 2: 플레이어, 3: 몬스터, 4: 입구, 5: 출구
    const int z_len = 8;
    const int y_len = 20;
    const int x_len = 20;

    int map[z_len][y_len][x_len];
    int z, y, x;
//========================== 맵 생성 ===============================
    for (z = 0; z < z_len; z++)
    {
        for (y = 0; y < y_len; y++)
        {
            for (x = 0; x < x_len; x++)
            {
                map[z][y][x] = 0;
            }
        }

        map[z][0][0] = 2;

        map[z][y_len - 1][x_len - 1] = 5;
    }
//==================================================================



    int loc_x = 0;
    int loc_y = 0;
    
    while (1)
    {    
        for (y = 0; y < y_len; y++)
        {
            for (x = 0; x < x_len; x++)
            {
                printf(" %d ", map[0][y][x]);
            }
            printf("\n");
        }
        
        p_move(map, x_len, y_len, z_len, &loc_x, &loc_y);
        system("clear");
    }


    return 0;
}

int p_move(int map[][20][20], int xlen, int ylen, int zlen, int* x, int* y)
{
    char level[5][5] = {"🤺", "🏇", "♖ ", "♕ ", "♔ "};
    int temp;
    
    
    char move = 0;
    char arrow_list[8][5] = {"↖", "🔼", "↗", "◀", "▶", "↙", "🔽", "↘"};
    char arrow = 0;
 
    printf("\n");
    printf("   w     \n");
    printf("   ↟    \n");
    printf("a↞  ↠d 플레이어(x,y) %d,%d\n", *x, *y);
    printf("   ↡    이동방향: %s\n", arrow_list[arrow]);
    printf("   s     >> %c", move);
    move = getch();


    if (move == 65 || move == 97) // ↞a
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*x > 0)
        {
            temp = map[0][*y][*x];
            
            *x -= 1;
            map[0][*y][*x] = 2;
            map[0][*y][(*x)+1] = 0;

            arrow = 3;
        }
        // break;
    }
    else if (move == 68 || move == 100) // d↠
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*x < xlen-1)
        {
            temp = map[0][*y][*x];
            *x += 1;
            map[0][*y][*x] = 2;
            map[0][*y][(*x)-1] = 0;

            arrow = 4;
        }
        // break;
    }
    else if (move == 87 || move == 119) // w위로
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if(*y > 0)
        {
            temp = map[0][*y][*x];
            *y -= 1;
            map[0][*y][*x] = 2;
            map[0][(*y)+1][*x] = 0;

            arrow = 1;
        }
        // break;
    }
    else if (move == 83 || move == 115) // s아래로
    {
        // 움직이는 방향의 좌표가 이동 가능하면,
        if (*y < ylen-1)
        {
            temp = map[0][*y][*x];
            *y += 1;
            map[0][*y][*x] = 2;
            map[0][(*y)-1][*x] = 0;

            arrow = 6;
        }
        // break;
    }

    if (map[0][0][0] != 2)
        map[0][0][0] = 4;
    if (map[0][ylen-1][xlen-1] != 2)
        map[0][ylen-1][xlen-1] = 5;
    
    //system("clear");
    
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
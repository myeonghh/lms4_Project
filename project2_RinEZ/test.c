#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int getch();

int p_move(int map[][70][70], int len)
{
    char level[5][5] = {"🤺", "🏇", "♖ ", "♕ ", "♔ "};

    int x = 4;
    int y = 4;

    char move = 0;
    char arrow_list[8][5] = {"↖", "🔼", "↗", "◀", "▶", "↙", "🔽", "↘"};
    char arrow = 0;

    for (;;)
    {
        printf("\n");
        printf("   w     \n");
        printf("   ↟    \n");
        printf("a↞  ↠d 플레이어(x,y) %d,%d\n", (x / 4), (y / 4));
        printf("   ↡    이동방향: %s\n", arrow_list[arrow]);
        printf("   s     >> %c", move);
        move = getch();

        if (move == 65 || move == 97) // ↞a
        {
            // 움직이는 방향의 좌표가 이동 가능하면,

            x = x - 4;
            arrow = 3;

            // break;
        }
        else if (move == 68 || move == 100) // d↠
        {
            // 움직이는 방향의 좌표가 이동 가능하면,
            x = x + 4;
            arrow = 4;

            // break;
        }
        else if (move == 87 || move == 119) // w위로
        {
            // 움직이는 방향의 좌표가 이동 가능하면,
            y = y - 4;
            arrow = 1;

            // break;
        }
        else if (move == 83 || move == 115) // s아래로
        {
            // 움직이는 방향의 좌표가 이동 가능하면,
            y = y + 4;
            arrow = 6;

            // break;
        }

        system("clear");
    }
}
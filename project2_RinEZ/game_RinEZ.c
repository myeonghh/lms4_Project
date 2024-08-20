#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int getch();

void main()
{

    char level[5][5] = {"🤺", "🏇", "♖ ", "♕ ", "♔ "};

    int x = 4;
    int y = 16;

    char move = 0;
    char arrow_list[8][5] = {"↖", "🔼", "↗", "◀", "▶", "↙", "🔽", "↘"};
    char arrow = 0;

    for (;;)
    {
        printf("\n");
        printf("q  w  e  \n");
        printf(" ↖ ↟ ↗   \n");
        printf("a↞  ↠d 플레이어(x,y) %d,%d\n", (x / 4), y);
        printf(" ↙ ↡ ↘  이동방향: %s\n", arrow_list[arrow]);
        printf("z  x  c >> %c", move);
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
        system("clear");
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
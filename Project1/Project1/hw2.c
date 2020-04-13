#define _CRT_SECURE_NO_WARNINGS
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#include <stdio.h>
#include <windows.h>
#include <memory.h>

typedef struct {
    int highScore;
    int x;
    int y;
}Game;
void omok_start(void);
void omok_board(void);
int omok_choose(void);
int omok_winner(void);
void omok_user(int, int*, int*);
Game omok_computer(int, int, int);
void omok_play(int, int, int);
Game omok_min(int, int, int, int, int, int, int);
Game omok_max(int, int, int, int, int, int, int);
int omok_rule(int, int, int);

int board[20][20] = { 0, };
int alpha = -10000000;
int beta = +10000000;
int tempx = 0;
int tempy = 0;
int temp2x = 0;
int temp2y = 0;
int main(void) {
    int player, winner = 0;
    int color = BLACK;

    Game p1;
    p1.highScore = 0;
    p1.x = 0;
    p1.y = 0;
    Game p2;
    p2.highScore = 0;
    p2.x = 0;
    p2.y = 0;
    omok_start();
    player = omok_choose();
    system("color f0");
    while (1) {
        omok_board();
        winner = omok_winner();
        if (winner != EMPTY) {
            if (player == winner) {
                printf("you win!!");
                break;
            }
            else {
                printf("you lose!!");
                break;
            }
        }

        //사용자에게 돌의 위치 받아내기
        if (color == player) {
            omok_user(color, &p1.x, &p1.y);
            omok_play(color, p1.x, p1.y);
        }
        else {
            p2 = omok_computer(color, p1.x, p1.y);
            omok_play(color, p2.x, p2.y);
        }

        if (color == BLACK) color = WHITE;
        else color = BLACK;


    }
}
void omok_start(void) {
    int i;
    char input = 'n';
    for (i = 0; i < 80; i++) printf("*");
    puts("\n");
    for (i = 0; i < 30; i++) printf(" ");
    printf("Playing Gomoku \n\n");
    printf(" -> Implement an alpha-beta search with iterative deepening search \n\n");
    printf(" -> There is a preset time limit for each move in 10 seconds \n\n");
    printf(" -> You can choose 'Black' or 'White' \n");
    printf("\n                                               컴퓨터학과");
    printf("\n                                       2016320143  김동현\n");
    for (i = 0; i < 80; i++) printf("*");
    while (input != 'y') {
        printf("\n -> If you play the game, please input [Y / N] \n");
        scanf("%c", &input);
        if (input == 'y') break;
        else printf("\n -> Wrong Answer.\n");
    }
}
int omok_choose(void) {
    int first_choose = 0;
    system("cls");
    while (1) {
        printf("선공(Black), 후공(White)을 골라주십시오.\n");
        printf("(흑 : %d, 백 : %d) \n", BLACK, WHITE);
        scanf("%d", &first_choose);
        if (first_choose == BLACK || first_choose == WHITE)
            break;
        printf("1(Blakc) 혹은 2(White)로 입력해주십시오.\n");
        Sleep(500);
    }

    system("cls");
    return first_choose;
}

void omok_board(void) {
    int i, row, col;
    printf("\n\n    ");
    for (i = 1; i < 20; i++) printf(" %2d  ", i);
    for (row = 0; row < 20; row++) {
        puts("");
        for (i = 0; i < 100; i++) {
            if ((i - 3) % 5) printf("-");
            else printf("+");
        }
        if (row == 19) continue;

        printf("\n%2d |", row + 1);
        for (col = 0; col < 19; col++) {
            switch (board[row + 1][col + 1]) {
            case EMPTY: printf("    "); break;
            case WHITE: printf(" ○ "); break;
            case BLACK: printf(" ● "); break;
            }
            printf("|");
        }
    }
    puts("\n");

}

int omok_winner()
{
    int cnt = 0;
    int di = 0;
    int dj = 0;
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            if (board[i][j] == WHITE) {
                for (int dir = 1; dir <= 8; dir++) {
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == WHITE) {
                            cnt += 1;
                            di = di - 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (dj + 1 <= 20 && dir == 2 && board[di][dj + 1] == WHITE) {
                            cnt += 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dir == 3 && board[di + 1][dj] == WHITE) {
                            cnt += 1;
                            di = di + 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == WHITE) {
                            cnt += 1;
                            dj = dj - 1;

                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }

                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == WHITE) {
                            cnt += 1;
                            di = di - 1;
                            dj = dj - 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dj + 1 <= 20 && dir == 6 && board[di - 1][dj + 1] == WHITE) {
                            cnt += 1;
                            di = di - 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == WHITE) {
                            cnt += 1;
                            di = di + 1;
                            dj = dj - 1;

                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dj + 1 <= 20 && dir == 8 && board[di + 1][dj + 1] == WHITE) {
                            cnt += 1;
                            di = di + 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return WHITE;
                        else break;
                    }
                }
            }
            else if (board[i][j] == BLACK) {
                for (int dir = 1; dir <= 8; dir++) {
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == BLACK) {
                            cnt += 1;
                            di = di - 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (dj + 1 <= 20 && dir == 2 && board[di][dj + 1] == BLACK) {
                            cnt += 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dir == 3 && board[di + 1][dj] == BLACK) {
                            cnt += 1;
                            di = di + 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == BLACK) {
                            cnt += 1;
                            dj = dj - 1;

                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }

                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == BLACK) {
                            cnt += 1;
                            di = di - 1;
                            dj = dj - 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di - 1 >= 1 && dj + 1 <= 20 && dir == 6 && board[di - 1][dj + 1] == BLACK) {
                            cnt += 1;
                            di = di - 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == BLACK) {
                            cnt += 1;
                            di = di + 1;
                            dj = dj - 1;

                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                    cnt = 1;
                    di = i;
                    dj = j;
                    while (1) {
                        if (di + 1 <= 20 && dj + 1 <= 20 && dir == 8 && board[di + 1][dj + 1] == BLACK) {
                            cnt += 1;
                            di = di + 1;
                            dj = dj + 1;
                        }
                        else if (cnt == 5) return BLACK;
                        else break;
                    }
                }
            }
        }
    }
    return EMPTY;
}
void omok_play(int color, int x, int y)
{
    board[x][y] = color;
}
void omok_user(int color, int* x, int* y)
{
    int rule = 0;
    int a;
    int b;
    while (1) {
        printf("+---------------------------------------------------------------------+\n");
        printf("|                      여러분의 차례입니다.                           |\n");
        printf("| 돌을 놓고 싶은 위치의 좌표를 입력해주십시오. (입력형식 : row col )  |\n");
        printf("+---------------------------------------------------------------------+\n");
        scanf("%d %d", x, y);
        if (*x >= 20 || *x < 1 || *y >= 20 || *y < 1) {
            printf("+--------------------------------------------+\n");
            printf("|좌표의 값은 1~15 사이의 자연수이여야 합니다.|\n");
            printf("|  좌표의 값을 다시 입력해주시길 바랍니다.   |\n");
            printf("+--------------------------------------------+\n");
            continue;
        }

        if (board[*x][*y]) {
            printf("+--------------------------------------------+\n");
            printf("|     이미 그곳에는 돌이 놓여있습니다.       |\n");
            printf("|   좌표의 값을 다시 입력해주시길 바랍니다.  |\n");
            printf("+--------------------------------------------+\n");
            continue;
        }
        a = *x;
        b = *y;
        rule = omok_rule(a, b, color);
        if (rule >= 2) {
            printf("+--------------------------------------------+\n");
            printf("|     그곳에는 3 X 3 Rule이 적용됩니다.      |\n");
            printf("|   좌표의 값을 다시 입력해주시길 바랍니다.  |\n");
            printf("+--------------------------------------------+\n");
            continue;
        }
        break;
    }
}
Game omok_computer(int color, int x, int y)
{
    Game p;
    p.highScore = 0;
    p.x = 0;
    p.y = 0;
    if (x == 0 && y == 0) {
        p.highScore = 0;
        p.x = 9;
        p.y = 9;
    }
    else {
        for (int i = 1; i < 3; i++) {
            p = omok_max(0, i, alpha, beta, x, y, color);
            if (p.highScore >= 14) {
                return p;
            }
        }
    }
    return p;
}
Game omok_max(int count, int depth, int alpha, int beta, int x, int y, int color) {
    //printf("@@ %d %d %d @@\n", count, depth,color);
    Game c;
    int computer;
    int user;
    c.highScore = -10000000;
    computer = color;
    user = 3 - color;
    int max_exp = 0;
    int temp;
    int temp_high;
    int score_x = 0;
    int score_y = 0;
    int score_color = 0;
    int rule = 0;
    if (count == 2) {
        temp2x = x;
        temp2y = y;
    }
    if (count == depth) {
        c.x = temp2x;
        c.y = temp2y;
        score_x = 0;
        score_y = 0;

        rule = omok_rule(x, y, color);
        if (rule >= 2) {
            c.highScore = -20;
            return c;
        }
        if (computer == BLACK) {
            score_color = -1;
        }
        else {
            score_color = 1;
        }
        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK && board[a][b + 4] == BLACK) {
                    score_x = 20;
                    c.highScore = (-score_x) * (score_color);
                    return c;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a][b + 1] == EMPTY && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == EMPTY && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 3] != WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 3] == WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    b = b + 2;
                }
                // ●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 2] != WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 2] == WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                    b = b + 1;
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 1] != WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 1] == WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE && board[a][b + 4] == WHITE) {
                    score_y = 20;
                    c.highScore = (score_y) * (score_color);
                    return c;
                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a][b + 1] == EMPTY && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == EMPTY && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    b = b + 3;
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 3] != BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 3] == BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    b = b + 2;
                }
                // ○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 2] != BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 2] == BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                    b = b + 1;
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 1] != BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 1] == BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }
            }
        }

        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK && board[a + 4][b] == BLACK) {
                    score_x = 20;
                    c.highScore = (-score_x) * (score_color);
                    return c;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a + 1][b] == EMPTY && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == EMPTY && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 3][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 3][b] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 3][b] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    a = a + 2;
                }
                // ●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 2][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 2][b] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 2][b] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                    a = a + 1;
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 1][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 1][b] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 1][b] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE && board[a + 4][b] == WHITE) {
                    score_y = 20;
                    c.highScore = (score_y) * (score_color);
                    return c;

                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a + 1][b] == EMPTY && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == EMPTY && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    a = a + 3;
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 3][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 3][b] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 3][b] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    a = a + 2;
                }
                // ○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 2][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 2][b] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 2][b] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                    a = a + 1;
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 1][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 1][b] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 1][b] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }
            }
        }

        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK && board[a + 4][b + 4] == BLACK) {
                    score_x = 20;
                    c.highScore = (-score_x) * (score_color);
                    return c;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == EMPTY && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == EMPTY && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 3][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 3][b + 3] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 3][b + 3] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 2][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 2][b + 2] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 2][b + 2] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 1][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 1][b + 1] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 1][b + 1] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }
                // ○○○○○
                if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE && board[a + 4][b + 4] == WHITE) {
                    score_y = 20; c.highScore = (score_y) * (score_color);
                    return c;

                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18; c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17; c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == EMPTY && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == EMPTY && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 3][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 3][b + 3] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 3][b + 3] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            c.highScore = (score_y) * (score_color);
                            return c;

                        }
                    }
                }
                // ○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 2][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 2][b + 2] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 2][b + 2] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 1][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 1][b + 1] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 1][b + 1] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }

            }
        }

        for (int a = 4; a < 20; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK && board[a - 4][b + 4] == BLACK) {
                    score_x = 20;
                    c.highScore = (-score_x) * (score_color);
                    return c;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == EMPTY && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }

                // ●●  ●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == EMPTY && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 3][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 3][b + 3] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 3][b + 3] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            c.highScore = (-score_x) * (score_color);
                            return c;
                        }
                    }
                }
                // ●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 2][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 2][b + 2] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 2][b + 2] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 1][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 1][b + 1] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 1][b + 1] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE && board[a - 4][b + 4] == WHITE) {
                    score_y = 20;
                    c.highScore = (score_y) * (score_color);
                    return c;
                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == EMPTY && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == EMPTY && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 3][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 3][b + 3] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 3][b + 3] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            c.highScore = (score_y) * (score_color);
                            return c;
                        }
                    }
                }
                // ○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 2][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 2][b + 2] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 2][b + 2] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 1][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 1][b + 1] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 1][b + 1] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }
            }
        }
        c.highScore = (score_y - score_x) * (score_color);

        return c;
    }
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if ((board[i][j] == WHITE) || (board[i][j] == BLACK)) {

                if (i - 1 >= 1 && j - 1 >= 1 && board[i - 1][j - 1] == EMPTY) {
                    temp = board[i - 1][j - 1];
                    board[i - 1][j - 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i - 1, j - 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i - 1][j - 1] = temp;
                    if (c.highScore >= beta)
                    {
                        return c;
                    }
                }

                if (i - 1 >= 1 && board[i - 1][j] == EMPTY) {
                    temp = board[i - 1][j];
                    board[i - 1][j] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i - 1, j, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i - 1][j] = temp;

                    if (c.highScore >= beta) {

                        return c;
                    }
                }

                if (i - 1 >= 1 && j + 1 < 20 && board[i - 1][j + 1] == EMPTY) {
                    temp = board[i - 1][j + 1];
                    board[i - 1][j + 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i - 1, j + 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i - 1][j + 1] = temp;
                    if (c.highScore >= beta) return c;
                }
                if (j - 1 >= 1 && board[i][j - 1] == EMPTY) {
                    temp = board[i][j - 1];
                    board[i][j - 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i, j - 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i][j - 1] = temp;
                    if (c.highScore >= beta) return c;
                }

                if (j + 1 < 20 && board[i][j + 1] == EMPTY) {
                    temp = board[i][j + 1];
                    board[i][j + 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i, j + 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i][j + 1] = temp;
                    if (c.highScore >= beta) return c;
                }

                if (i + 1 < 20 && j - 1 >= 1 && board[i + 1][j - 1] == EMPTY) {
                    temp = board[i + 1][j - 1];
                    board[i + 1][j - 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i + 1, j - 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i + 1][j - 1] = temp;
                    if (c.highScore >= beta) return c;
                }

                if (i + 1 < 20 && board[i + 1][j] == EMPTY) {
                    temp = board[i + 1][j];
                    board[i + 1][j] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i + 1, j, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i + 1][j] = temp;
                    if (c.highScore >= beta) return c;
                }

                if (i + 1 < 20 && j + 1 < 20 && board[i + 1][j + 1] == EMPTY) {
                    temp = board[i + 1][j + 1];
                    board[i + 1][j + 1] = computer;
                    temp_high = c.highScore;
                    c = omok_min(count + 1, depth, alpha, beta, i + 1, j + 1, user);
                    c.highScore = max(temp_high, c.highScore);
                    board[i + 1][j + 1] = temp;
                    if (c.highScore >= beta) return c;
                }
                alpha = max(alpha, c.highScore);
            }
        }
    }
    return c;
}

Game omok_min(int count, int depth, int alpha, int beta, int x, int y, int color) {
    Game p;
    int computer;
    int user;
    p.highScore = +10000000;
    p.x = 0;
    p.y = 0;
    user = color;
    computer = 3 - color;
    int temp;
    int temp_high;
    int score_x = 0;
    int score_y = 0;
    int score_color = 0;
    int rule = 0;
    if (count == 1) {
        p.x = x;
        p.y = y;
        tempx = x;
        tempy = y;
    }

    if (count == depth) {

        p.x = tempx;
        p.y = tempy;
        score_x = 0;
        score_y = 0;
        rule = omok_rule(x, y, color);
        if (rule >= 2) {
            p.highScore = -20;
            return p;
        }
        if (computer == BLACK) {
            score_color = -1;
        }
        else {
            score_color = 1;
        }
        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK && board[a][b + 4] == BLACK) {
                    score_x = 20;
                    p.highScore = (-score_x) * (score_color);
                    return p;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a][b + 1] == EMPTY && board[a][b + 2] == BLACK && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == EMPTY && board[a][b + 3] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 4] != WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 4] == WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK && board[a][b + 2] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 3] != WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 3] == WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            p.highScore = (-score_x) * (score_color);

                            return p;
                        }
                    }
                    b = b + 2;
                }
                // ●●
                else if (board[a][b] == BLACK && board[a][b + 1] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 2] != WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 2] == WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                    b = b + 1;
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a][b - 1] == WHITE && board[a][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a][b - 1] == WHITE && board[a][b + 1] != WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a][b - 1] != WHITE && board[a][b + 1] == WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE && board[a][b + 4] == WHITE) {
                    score_y = 20;
                    p.highScore = (score_y) * (score_color);
                    return p;
                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a][b + 1] == EMPTY && board[a][b + 2] == WHITE && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == EMPTY && board[a][b + 3] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 4] != BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 4] == BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    b = b + 3;
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE && board[a][b + 2] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 3] != BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 3] == BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    b = b + 2;
                }
                // ○○
                else if (board[a][b] == WHITE && board[a][b + 1] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 2] != BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 2] == BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                    b = b + 1;
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a][b - 1] == BLACK && board[a][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a][b - 1] == BLACK && board[a][b + 1] != BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a][b - 1] != BLACK && board[a][b + 1] == BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }
            }
        }
        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK && board[a + 4][b] == BLACK) {
                    score_x = 20;
                    p.highScore = (-score_x) * (score_color);
                    return p;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a + 1][b] == EMPTY && board[a + 2][b] == BLACK && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == EMPTY && board[a + 3][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 4][b] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 4][b] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK && board[a + 2][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 3][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 3][b] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 3][b] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            p.highScore = (-score_x) * (score_color);

                            return p;
                        }
                    }
                    a = a + 2;
                }
                // ●●
                else if (board[a][b] == BLACK && board[a + 1][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 2][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 2][b] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 2][b] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                    a = a + 1;
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a - 1][b] == WHITE && board[a + 1][b] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b] != WHITE && board[a + 1][b] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a - 1][b] == WHITE && board[a + 1][b] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE && board[a + 4][b] == WHITE) {
                    score_y = 20;
                    p.highScore = (score_y) * (score_color);
                    return p;

                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a + 1][b] == EMPTY && board[a + 2][b] == WHITE && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == EMPTY && board[a + 3][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 4][b] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 4][b] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    a = a + 3;
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE && board[a + 2][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 3][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 3][b] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 3][b] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    a = a + 2;
                }
                // ○○
                else if (board[a][b] == WHITE && board[a + 1][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 2][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 2][b] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 2][b] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                    a = a + 1;
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a - 1][b] == BLACK && board[a + 1][b] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b] != BLACK && board[a + 1][b] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a - 1][b] == BLACK && board[a + 1][b] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }
            }
        }
        for (int a = 1; a < 16; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK && board[a + 4][b + 4] == BLACK) {
                    score_x = 20;
                    p.highScore = (-score_x) * (score_color);
                    return p;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == EMPTY && board[a + 2][b + 2] == BLACK && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }
                // ●●  ●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == EMPTY && board[a + 3][b + 3] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 4][b + 4] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 4][b + 4] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK && board[a + 2][b + 2] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 3][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 3][b + 3] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 3][b + 3] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            p.highScore = (-score_x) * (score_color);

                            return p;
                        }
                    }
                }
                // ●●
                else if (board[a][b] == BLACK && board[a + 1][b + 1] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 2][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 2][b + 2] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 2][b + 2] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a - 1][b - 1] == WHITE && board[a + 1][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != WHITE && board[a + 1][b + 1] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a - 1][b - 1] == WHITE && board[a + 1][b + 1] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }
                // ○○○○○
                if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE && board[a + 4][b + 4] == WHITE) {
                    score_y = 20;
                    p.highScore = (score_y) * (score_color);
                    return p;

                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == EMPTY && board[a + 2][b + 2] == WHITE && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == EMPTY && board[a + 3][b + 3] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 4][b + 4] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 4][b + 4] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE && board[a + 2][b + 2] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 3][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 3][b + 3] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 3][b + 3] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○
                else if (board[a][b] == WHITE && board[a + 1][b + 1] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 2][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 2][b + 2] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 2][b + 2] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a - 1][b - 1] == BLACK && board[a + 1][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a - 1][b - 1] != BLACK && board[a + 1][b + 1] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a - 1][b - 1] == BLACK && board[a + 1][b + 1] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }

            }
        }
        for (int a = 4; a < 20; a++) {
            for (int b = 1; b < 16; b++) {
                if (board[a][b] == EMPTY) continue;
                // ●●●●●
                if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK && board[a - 4][b + 4] == BLACK) {
                    score_x = 20;
                    p.highScore = (-score_x) * (score_color);
                    return p;
                }
                // ●●●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 18) {
                            score_x = 18;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 17) {
                            score_x = 17;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_x < 19) {
                            score_x = 19;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }
                // ●  ●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == EMPTY && board[a - 2][b + 2] == BLACK && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 11) {
                            score_x = 11;
                        }
                    }

                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 10) {
                            score_x = 10;
                        }
                    }
                    else {
                        if (score_x < 15) {
                            score_x = 15;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }

                // ●●  ●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == EMPTY && board[a - 3][b + 3] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 4][b + 4] == WHITE) {
                        if (score_x < 9) {
                            score_x = 9;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 4][b + 4] != WHITE) {
                        if (score_x < 8) {
                            score_x = 8;
                        }
                    }
                    else {
                        if (score_x < 14) {
                            score_x = 14;
                            p.highScore = (-score_x) * (score_color);
                            return p;
                        }
                    }
                }
                // ●●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK && board[a - 2][b + 2] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 3][b + 3] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 3][b + 3] == WHITE) {
                        if (score_x < 13) {
                            score_x = 13;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 3][b + 3] != WHITE) {
                        if (score_x < 12) {
                            score_x = 12;
                        }
                    }
                    else {
                        if (score_x < 16) {
                            score_x = 16;
                            p.highScore = (-score_x) * (score_color);

                            return p;
                        }
                    }
                }
                // ●●
                else if (board[a][b] == BLACK && board[a - 1][b + 1] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 2][b + 2] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 2][b + 2] == WHITE) {
                        if (score_x < 6) {
                            score_x = 6;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 2][b + 2] != WHITE) {
                        if (score_x < 5) {
                            score_x = 5;
                        }
                    }
                    else {
                        if (score_x < 7) {
                            score_x = 7;
                        }
                    }
                }
                // ●
                else if (board[a][b] == BLACK) {
                    if (board[a + 1][b - 1] == WHITE && board[a - 1][b + 1] == WHITE) {
                        if (score_x < 1) {
                            score_x = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != WHITE && board[a - 1][b + 1] == WHITE) {
                        if (score_x < 3) {
                            score_x = 3;
                        }
                    }
                    else if (board[a + 1][b - 1] == WHITE && board[a - 1][b + 1] != WHITE) {
                        if (score_x < 2) {
                            score_x = 2;
                        }
                    }
                    else {
                        if (score_x < 4) {
                            score_x = 4;
                        }
                    }
                }

                // ○○○○○
                if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE && board[a - 4][b + 4] == WHITE) {
                    score_y = 20;
                    p.highScore = (score_y) * (score_color);
                    return p;

                }
                // ○○○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 18) {
                            score_y = 18;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 17) {
                            score_y = 17;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                    else {
                        if (score_y < 19) {
                            score_y = 19;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○  ○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == EMPTY && board[a - 2][b + 2] == WHITE && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 11) {
                            score_y = 11;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 10) {
                            score_y = 10;
                        }
                    }
                    else {
                        if (score_y < 15) {
                            score_y = 15;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○  ○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == EMPTY && board[a - 3][b + 3] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 4][b + 4] == BLACK) {
                        if (score_y < 9) {
                            score_y = 9;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 4][b + 4] != BLACK) {
                        if (score_y < 8) {
                            score_y = 8;
                        }
                    }
                    else {
                        if (score_y < 14) {
                            score_y = 14;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE && board[a - 2][b + 2] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 3][b + 3] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 3][b + 3] == BLACK) {
                        if (score_y < 13) {
                            score_y = 13;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 3][b + 3] != BLACK) {
                        if (score_y < 12) {
                            score_y = 12;
                        }
                    }
                    else {
                        if (score_y < 16) {
                            score_y = 16;
                            p.highScore = (score_y) * (score_color);
                            return p;
                        }
                    }
                }
                // ○○
                else if (board[a][b] == WHITE && board[a - 1][b + 1] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 2][b + 2] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 2][b + 2] == BLACK) {
                        if (score_y < 6) {
                            score_y = 6;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 2][b + 2] != BLACK) {
                        if (score_y < 5) {
                            score_y = 5;
                        }
                    }
                    else {
                        if (score_y < 7) {
                            score_y = 7;
                        }
                    }
                }
                // ○
                else if (board[a][b] == WHITE) {
                    if (board[a + 1][b - 1] == BLACK && board[a - 1][b + 1] == BLACK) {
                        if (score_y < 1) {
                            score_y = 1;
                        }
                    }
                    else if (board[a + 1][b - 1] != BLACK && board[a - 1][b + 1] == BLACK) {
                        if (score_y < 3) {
                            score_y = 3;
                        }
                    }
                    else if (board[a + 1][b - 1] == BLACK && board[a - 1][b + 1] != BLACK) {
                        if (score_y < 2) {
                            score_y = 2;
                        }
                    }
                    else {
                        if (score_y < 4) {
                            score_y = 4;
                        }
                    }
                }

            }

        }

        p.highScore = (score_y - score_x) * score_color;

        return p;
    }
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if ((board[i][j] == WHITE) || (board[i][j] == BLACK)) {

                if (i - 1 >= 1 && j - 1 >= 1 && board[i - 1][j - 1] == EMPTY) {
                    temp = board[i - 1][j - 1];
                    board[i - 1][j - 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i - 1, j - 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i - 1][j - 1] = temp;
                    if (p.highScore <= alpha) return p;
                }

                if (i - 1 >= 1 && board[i - 1][j] == EMPTY) {
                    temp = board[i - 1][j];
                    board[i - 1][j] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i - 1, j, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i - 1][j] = temp;
                    if (p.highScore <= alpha) return p;
                }

                if (i - 1 >= 1 && j + 1 < 20 && board[i - 1][j + 1] == EMPTY) {
                    temp = board[i - 1][j + 1];
                    board[i - 1][j + 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i - 1, j + 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i - 1][j + 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                if (j - 1 >= 1 && board[i][j - 1] == EMPTY) {
                    temp = board[i][j - 1];
                    board[i][j - 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i, j - 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i][j - 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                if (j + 1 < 20 && board[i][j + 1] == EMPTY) {
                    temp = board[i][j + 1];
                    board[i][j + 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i, j + 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i][j + 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                if (i + 1 < 20 && j - 1 >= 1 && board[i + 1][j - 1] == EMPTY) {
                    temp = board[i + 1][j - 1];
                    board[i + 1][j - 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i + 1, j - 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i + 1][j - 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                if (i + 1 < 20 && board[i + 1][j] == EMPTY) {
                    temp = board[i + 1][j];
                    board[i + 1][j] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i + 1, j, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i + 1][j] = temp;
                    if (p.highScore <= alpha) return p;
                }

                if (i + 1 < 20 && j + 1 < 20 && board[i + 1][j + 1] == EMPTY) {
                    temp = board[i + 1][j + 1];
                    board[i + 1][j + 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i + 1, j + 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i + 1][j + 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                beta = min(beta, p.highScore);
            }
        }
    }
    return p;
}

int omok_rule(int x, int y, int color) {
    int result = 0;
    int temp = 0;
    if (board[x][y]) temp = board[x][y];
    else board[x][y] = color;
    for (int dir = 0; dir < 8; dir++) {
        if (board[x][y] == BLACK) {
            if (x - 2 >= 1 && y - 2 >= 1 && dir == 0 && board[x - 1][y - 1] == BLACK && board[x - 2][y - 2] == BLACK) result++;
            if (x - 2 >= 1 && dir == 1 && board[x - 1][y] == BLACK && board[x - 2][y] == BLACK) result++;
            if (x - 2 >= 1 && y + 2 < 20 && dir == 2 && board[x - 1][y + 1] == BLACK && board[x - 2][y + 2] == BLACK) result++;
            if (y - 2 >= 1 && dir == 3 && board[x][y - 1] == BLACK && board[x][y - 2] == BLACK) result++;
            if (y + 2 < 20 && dir == 4 && board[x][y + 1] == BLACK && board[x][y + 2] == BLACK) result++;
            if (x + 2 < 20 && y - 2 >= 1 && dir == 5 && board[x + 1][y - 1] == BLACK && board[x + 2][y - 2] == BLACK) result++;
            if (x + 2 < 20 && dir == 6 && board[x + 1][y] == BLACK && board[x + 2][y] == BLACK) result++;
            if (x + 2 < 20 && y + 2 < 20 && dir == 7 && board[x + 1][y + 1] == BLACK && board[x + 2][y + 2] == BLACK) result++;
        }
        else if (board[x][y] == WHITE) {
            if (x - 2 >= 1 && y - 2 >= 1 && dir == 0 && board[x - 1][y - 1] == WHITE && board[x - 2][y - 2] == WHITE) result++;
            if (x - 2 >= 1 && dir == 1 && board[x - 1][y] == WHITE && board[x - 2][y] == WHITE) result++;
            if (x - 2 >= 1 && y + 2 < 20 && dir == 2 && board[x - 1][y + 1] == WHITE && board[x - 2][y + 2] == WHITE) result++;
            if (y - 2 >= 1 && dir == 3 && board[x][y - 1] == WHITE && board[x][y - 2] == WHITE) result++;
            if (y + 2 < 20 && dir == 4 && board[x][y + 1] == WHITE && board[x][y + 2] == WHITE) result++;
            if (x + 2 < 20 && y - 2 >= 1 && dir == 5 && board[x + 1][y - 1] == WHITE && board[x + 2][y - 2] == WHITE) result++;
            if (x + 2 < 20 && dir == 6 && board[x + 1][y] == WHITE && board[x + 2][y] == WHITE) result++;
            if (x + 2 < 20 && y + 2 < 20 && dir == 7 && board[x + 1][y + 1] == WHITE && board[x + 2][y + 2] == WHITE) result++;
        }
    }
    if (x - 1 >= 1 && y - 1 >= 1 && x + 1 < 20 && y + 1 < 20 && board[x][y] == BLACK && board[x - 1][y] == BLACK && board[x][y - 1] == BLACK && board[x + 1][y] == BLACK && board[x][y + 1] == BLACK) result = 5;
    if (x - 1 >= 1 && y - 1 >= 1 && x + 1 < 20 && y + 1 < 20 && board[x][y] == WHITE && board[x - 1][y] == WHITE && board[x][y - 1] == WHITE && board[x + 1][y] == WHITE && board[x][y + 1] == WHITE) result = 5;
    if(temp == 0)
        board[x][y] = EMPTY;
    return result;
}
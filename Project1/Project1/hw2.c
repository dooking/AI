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
            printf("* %d %d *\n", p2.x, p2.y);
            omok_play(color, p2.x, p2.y);
        }

        if (color == BLACK) color = WHITE;
        else color = BLACK;


    }
}
void omok_start(void) {
    int i;
    for (i = 0; i < 80; i++) printf("*");
    puts("\n");
    for (i = 0; i < 30; i++) printf(" ");
    printf("Playing Gomoku \n\n");
    printf(" -> Implement an alpha-beta search with iterative deepening search \n\n");
    printf(" -> There is a preset time limit for each move in 10 seconds \n\n");
    printf(" -> You can choose 'Black' or 'White' \n\n");
    printf(" -> Press any key to start the game \n\n");
    for (i = 0; i < 80; i++) printf("*");
    printf("\n                                               컴퓨터학과");
    printf("\n                                  2016320143  김동현");
    Sleep(1000);
    Sleep(1000);
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
    printf("!! %d %d !!\n", x, y);
    board[x][y] = color;
}
void omok_user(int color, int* x, int* y)
{
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
        for (int i = 0; i < 3; i++)
            p = omok_max(0, i, alpha, beta, x, y, color);
            if (p.highScore >= 5000) {
                return p;
            }
        //p = omok_max(5, x, y, color);
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
    int di = 0;
    int dj = 0;
    int attack;
    int defend;
    int chance;
    int exp[9] = { 0, };
    int max_exp = 0;
    int temp;
    int temp_high;
    if (count == 2) {
        temp2x = x;
        temp2y = y;
    }
    printf("저기: %d %d %d %d %d %d %d %d \n", count, alpha, beta, x, y, c.highScore, temp2x, temp2y);
    if (count == depth) {
        c.x = temp2x;
        c.y = temp2y;
        for (int dir = 1; dir <= 8; dir++) {
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;
            if (di + 1 < 20 && board[di + 1][dj] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == computer) {
                    attack += 1;
                    di = di - 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dir == 1 && board[di - 1][dj] == EMPTY) {
                    chance--;
                    di = di - 1;
                }
                else if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 1) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (dj - 1 >= 1 && board[di][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (dj + 1 < 20 && dir == 2 && board[di][dj + 1] == computer) {
                    attack += 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && dj + 1 < 20 && dir == 2 && board[di][dj + 1] == EMPTY) {
                    chance--;
                    dj = dj + 1;
                }
                else if (dj + 1 < 20 && dir == 2 && board[di][dj + 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 2) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (di - 1 >= 1 && board[di + 1][dj] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dir == 3 && board[di + 1][dj] == computer) {
                    attack += 1;
                    di = di + 1;
                }
                else if (chance == 1 && di + 1 < 20 && dir == 3 && board[di + 1][dj] == EMPTY) {
                    chance--;
                    di = di + 1;
                }
                else if (di + 1 < 20 && dir == 3 && board[di + 1][dj] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 3) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (dj + 1 < 20 && board[di][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == computer) {
                    attack += 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == EMPTY) {
                    chance--;
                    dj = dj - 1;
                }
                else if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 4) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (di + 1 < 20 && dj + 1 < 20 && board[di - 1][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == computer) {
                    attack += 1;
                    di = di - 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == EMPTY) {
                    chance--;
                    di = di - 1;
                    dj = dj - 1;
                }
                else if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 5) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (di + 1 < 20 && dj - 1 >= 1 && board[di - 1][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == computer) {
                    attack += 1;
                    di = di - 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == EMPTY) {
                    chance--;
                    di = di - 1;
                    dj = dj + 1;
                }
                else if (di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 6) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (di - 1 >= 1 && dj + 1 < 20 && board[di + 1][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == computer) {
                    attack += 1;
                    di = di + 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == EMPTY) {
                    chance--;
                    di = di + 1;
                    dj = dj - 1;
                }
                else if (di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 7) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = temp2x;
            dj = temp2y;

            if (di - 1 >= 1 && dj - 1 >= 1 && board[di + 1][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dj + 1 < 20 && dir == 8 && board[di + 1][dj + 1] == computer) {
                    attack += 1;
                    di = di + 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && di + 1 < 20 && dj + 1 <= 20 && dir == 8 && board[di + 1][dj + 1] == EMPTY) {
                    chance--;
                    di = di + 1;
                    dj = dj + 1;
                }
                else if (di + 1 < 20 && dj + 1 < 20 && dir == 8 && board[di + 1][dj + 1] == user) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 8) {
                if (attack == 5) {
                    c.highScore = 100000;
                    return c;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (attack == 4) {
                    if (chance) {
                        c.highScore = 50000;
                        return c;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        c.highScore = 5000;
                        return c;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
        }
        for (int i = 1; i < 9; i++) {
            if (max_exp < exp[i]) {
                max_exp = exp[i];
            }

            printf("! %d,%d ", i, exp[i]);
        }
        c.highScore = max_exp;

        printf("! %d %d %d !\n", c.highScore, c.x, c.y);
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
                    printf("● %d %d \n", c.highScore, beta);
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
    int di = 0;
    int dj = 0;
    int attack;
    int defend;
    int chance;
    int exp[9] = { 0, };
    int max_exp = 0;
    int temp;
    int temp_high;
    if (count == 1) {
        p.x = x;
        p.y = y;
        tempx = x;
        tempy = y;
    }

    printf("여기: %d %d %d %d %d %d %d %d \n", count, alpha, beta, x, y, p.highScore, p.x, p.y);
    if (count == depth) {

        p.x = tempx;
        p.y = tempy;
        for (int dir = 1; dir < 9; dir++) {
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;
            if (di + 1 < 20 && board[di + 1][dj] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == user) {
                    attack += 1;
                    di = di - 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dir == 1 && board[di - 1][dj] == EMPTY) {
                    chance--;
                    di = di - 1;
                }
                else if (di - 1 >= 1 && dir == 1 && board[di - 1][dj] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 1) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (dj - 1 >= 1 && board[di][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (dj + 1 < 20 && dir == 2 && board[di][dj + 1] == user) {
                    attack += 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && dj + 1 < 20 && dir == 2 && board[di][dj + 1] == EMPTY) {
                    chance--;
                    dj = dj + 1;
                }
                else if (dj + 1 < 20 && dir == 2 && board[di][dj + 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 2) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (di - 1 >= 1 && board[di + 1][dj] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dir == 3 && board[di + 1][dj] == user) {
                    attack += 1;
                    di = di + 1;
                }
                else if (chance == 1 && di + 1 < 20 && dir == 3 && board[di + 1][dj] == EMPTY) {
                    chance--;
                    di = di + 1;
                }
                else if (di + 1 < 20 && dir == 3 && board[di + 1][dj] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 3) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (dj + 1 < 20 && board[di][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == user) {
                    attack += 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == EMPTY) {
                    chance--;
                    dj = dj - 1;
                }
                else if (dj - 1 >= 1 && dir == 4 && board[di][dj - 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 4) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (di + 1 < 20 && dj + 1 < 20 && board[di - 1][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == user) {
                    attack += 1;
                    di = di - 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == EMPTY) {
                    chance--;
                    di = di - 1;
                    dj = dj - 1;
                }
                else if (di - 1 >= 1 && dj - 1 >= 1 && dir == 5 && board[di - 1][dj - 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 5) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (di + 1 < 20 && dj - 1 >= 1 && board[di - 1][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == user) {
                    attack += 1;
                    di = di - 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == EMPTY) {
                    chance--;
                    di = di - 1;
                    dj = dj + 1;
                }
                else if (di - 1 >= 1 && dj + 1 < 20 && dir == 6 && board[di - 1][dj + 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 6) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (di - 1 >= 1 && dj + 1 < 20 && board[di + 1][dj - 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == user) {
                    attack += 1;
                    di = di + 1;
                    dj = dj - 1;
                }
                else if (chance == 1 && di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == EMPTY) {
                    chance--;
                    di = di + 1;
                    dj = dj - 1;
                }
                else if (di + 1 < 20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 7) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
            attack = 1;
            defend = 0;
            chance = 1;
            di = tempx;
            dj = tempy;

            if (di - 1 >= 1 && dj - 1 >= 1 && board[di + 1][dj + 1] == user) defend++;
            for (int k = 0; k < 5; k++) {
                if (di + 1 < 20 && dj + 1 <= 20 && dir == 8 && board[di + 1][dj + 1] == user) {
                    attack += 1;
                    di = di + 1;
                    dj = dj + 1;
                }
                else if (chance == 1 && di + 1 <= 20 && dj + 1 < 20 && dir == 8 && board[di + 1][dj + 1] == EMPTY) {
                    chance--;
                    di = di + 1;
                    dj = dj + 1;
                }
                else if (di + 1 < 20 && dj + 1 < 20 && dir == 8 && board[di + 1][dj + 1] == computer) {
                    defend++;
                    break;
                }
                else break;
            }
            if (dir == 8) {
                if (attack == 5) {
                    p.highScore = 100000;
                    return p;
                }
                else if (defend == 2) {
                    exp[dir] = -100000;
                }
                else if (defend == 1) {
                    exp[dir] = -500;
                }
                else if (attack == 4) {
                    if (chance) {
                        p.highScore = 50000;
                        return p;
                    }
                    else {
                        exp[dir] = 10000;
                    }
                }
                else if (attack == 3) {
                    if (chance) {
                        p.highScore = 5000;
                        return p;
                    }
                    else {
                        exp[dir] = 1000;
                    }
                }
                else if (attack == 2) {
                    if (chance) {
                        exp[dir] = 500;
                    }
                    else {
                        exp[dir] = 100;
                    }
                }
                else if (attack == 1) {
                    exp[dir] = 10;
                }
            }
        }
        for (int i = 1; i < 9; i++) {
            if (max_exp < exp[i]) {
                max_exp = exp[i];
            }
            printf("@ %d,%d ", i, exp[i]);
        }
        printf("\n");
        p.highScore = max_exp;
        printf("@ %d %d %d %d %d @\n", x, y, p.highScore, p.x, p.y);
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

                if (i + 1 < 20 && j + 1 <20 && board[i + 1][j + 1] == EMPTY) {
                    temp = board[i + 1][j + 1];
                    board[i + 1][j + 1] = user;
                    temp_high = p.highScore;
                    p = omok_max(count + 1, depth, alpha, beta, i + 1, j + 1, computer);
                    p.highScore = min(temp_high, p.highScore);
                    board[i + 1][j + 1] = temp;
                    if (p.highScore <= alpha) return p;
                }
                beta = min(beta, p.highScore);
                printf("★ %d %d", beta, p.highScore);
            }
        }
    }
    return p;
}
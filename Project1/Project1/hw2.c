
#define _CRT_SECURE_NO_WARNINGS
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#include <stdio.h>
#include <windows.h>
void omok_start(void);
void omok_board(void);
int omok_choose(void);
int omok_winner(void);
void omok_user(int, int*, int*);
void omok_computer(int, int*, int*);
void omok_play(int, int, int);
void omok_min(int , int , int , int)
void omok_max(int , int , int , int)
void omok_utility(int , int ,int);
int board[20][20] = {0, };
int alpha = -10000000;
int beta = +10000000;
int main(void) {
	int player,winner = 0;
	int color = BLACK;
	int x, y = 0;

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
			omok_user(color, &x, &y);
			omok_play(color, x, y);
		}
		else {
			omok_computer(color, &x, &y);
			omok_play(color, x, y);
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
	printf("\n			  		                              컴퓨터학과");
	printf("\n			  			              2016320143  김동현");
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
							di= di - 1;
						}
						else if (cnt == 5) return WHITE;
						else break;
					}
					cnt = 1;
					di = i;
					dj = j;
					while (1) {
						if (dj+1 <=20 && dir == 2 && board[di][dj+1] == WHITE) {
							cnt += 1;
							dj =dj+1;
						}
						else if (cnt == 5) return WHITE;
						else break;
					}					
					cnt = 1;
					di = i;
					dj = j;
					while (1) {
						if (di+1<=20 && dir == 3 && board[di+1][dj] == WHITE) {
							cnt += 1;
							di = di+1;
						}
						else if (cnt == 5) return WHITE;
						else break;
					}					
					cnt = 1;
					di = i;
					dj = j;
					while (1) {
						if (dj-1>=1 && dir == 4 && board[di][dj - 1] == WHITE) {
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
						if (di- 1 >= 1 && dj-1 >= 1&& dir == 5 && board[di-1][dj - 1] == WHITE) {
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
						if (di - 1 >= 1 && dj + 1 <= 20 && dir == 6 && board[di-1][dj + 1] == WHITE) {
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
						if (di+1<=20 && dj - 1 >= 1 && dir == 7 && board[di + 1][dj - 1] == WHITE) {
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
						if (di+1<=20 && dj + 1 <=20 && dir == 8 && board[di+1][dj+1] == WHITE) {
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
void omok_play(int color , int x, int y)
{
	board[x][y] = color;
}
void omok_user(int color, int *x, int *y) 
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
void omok_computer(int color, int* x, int* y)
{
	if (color == WHITE) {
		*x = omok_max(5, x, y, WHITE);
	}
	else {
		*y = omok_max(5,x, y, BLACK);
	}
}
void omok_max(int depth,int maxX,int maxY, int color) {
	if (count == depth) return omok_utility(maxX,maxY,color);
	v = -10000000;
	int count = 0;
	for(int i=0;; i<20; i++)
		for(int j=0; j<20; j++)
			if (board[i][j] == WHITE || BLACK) {
				v = omok_min(count +1,i-1, j-1)
				if (v >= beta) return v;
				v = omok_min(count + 1, i-1, j)
				if (v >= beta) return v;
				v = omok_min(count + 1, i-1, j+1)
				if (v >= beta) return v;
				v = omok_min(count + 1, i, j-1)
				if (v >= beta) return v;
				v = omok_min(count + 1, i, j+1)
				if (v >= beta) return v;
				v = omok_min(count + 1, i+1, j-1)
				if (v >= beta) return v;
				v = omok_min(count + 1, i+1, j)
				if (v >= beta) return v;
				v = omok_min(count + 1, i+1, j+1)
				if (v >= beta) return v;
				alpha = max(alpha, v);
				return v;
			}
}
void omok_min(int depth,int minX,int minY,int color) {
	if (count == depth) return omok_utility(minX, minY,color);
	v = +10000000;
	for (int i = 0;; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (board[i][j] == WHITE || BLACK) {
				v = omok_max(count + 1, i - 1, j - 1)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i - 1, j)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i - 1, j + 1)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i, j - 1)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i, j + 1)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i + 1, j - 1)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i + 1, j)
				if (v <= alpha) return v;
				v = omok_max(count + 1, i + 1, j + 1)
				if (v <= alpha) return v;
				beta = min(alpha, v);
				return v;
			}
}
void omok_utility(int dx, int dy,int color) {
	int exp[8] = { 0, };
	int computer = color;
	int human = abs(3 - color);
	for (int dir = 0; dir <= 7; dir++) {
		di = dx;
		dj = dy;
		while (1) {
			if (di - 1 >= 1 && dir == 0 && board[di - 1][dj] == computer) {
				exp[dir] += 1;
				di = di - 1;
			}
			else if (exp[dir] == 4) return 100000;
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



#include <stdio.h>
#include <windows.h>
#include <conio.h>

/*
   (( OMOK )) Author : r3j0
   Last Backup : 2022-04-28 PM 07:48
*/

// Set Arrow key
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define SPACE 32

// Set play mode
#define MODE 1
// 1 : (B)Player	vs	(W)Player
// 2 : (B)Player	vs	(W)AI
// 3 : (B)AI		vs	(W)Player
// 4 : (B)AI		vs	(W)AI

// Set the color
void tcolor(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Move Cursor
void gotoxy(int x, int y)
{ // middle : 21, 10, left up : 3, 1
	COORD Cur;
	Cur.X = 3 + (x * 2);
	Cur.Y = 1 + y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// printing omok board (ui)
void print_board(int board[][19], int point[]) {
	printf("   ");
	tcolor(15, 0);
	for (int i = 1; i < 20; i++) {
		printf("%2d", i);
	}
	printf("\n");
	for (int i = 1; i < 20; i++) {
		tcolor(15, 0);
		printf("%2d ", i);
		for (int j = 1; j < 20; j++) {
			tcolor(0, 15);
			if (board[i - 1][j - 1] == 1) {
				if (point[0] == i - 1 && point[1] == j - 1)
					tcolor(0, 12);
				printf("¡Ü");
			}
			else if (board[i - 1][j - 1] == 2) {
				if (point[0] == i - 1 && point[1] == j - 1)
					tcolor(0, 12);
				printf("¡Û");
			}
			else {
				if (point[0] == i - 1 && point[1] == j - 1)
					tcolor(0, 12);
				printf("  ");
			}
		}
		printf("\n");
	}
}

void point_home(void) {
	tcolor(15, 0);
	gotoxy(0, 21);
}

void print_turn(int t) {
	tcolor(15, 0);
	gotoxy(0, 19);
	if (t == 0)
		printf("Turn : Black");
	else
		printf("Turn : White");
}

int main(void) {

	int board[19][19] = { 0, };
	char key; // input the arrow key
	int now_point[2] = { 9,9 }; // [0] : y, [1] : x

	int turn = 0; // 0 : black, 1 : white

	print_board(board, now_point);
	print_turn(turn);
	point_home();
	while (1) {
		key = _getch();
		if (_kbhit()) {
			key = _getch();
			gotoxy(now_point[1], now_point[0]);
			tcolor(0, 15);
			if (board[now_point[1]][now_point[0]] == 1)
				printf("¡Ü");
			else if (board[now_point[1]][now_point[0]] == 2)
				printf("¡Û");
			else
				printf("  ");
			if (key == UP) { // UP
				if (now_point[0] != 0) {
					now_point[0]--;
				}
			}
			else if (key == DOWN) { // DOWN
				if (now_point[0] != 18) {
					now_point[0]++;
				}
			}
			else if (key == LEFT) { // LEFT
				if (now_point[1] != 0) {
					now_point[1]--;
				}
			}
			else if (key == RIGHT) { // RIGHT
				if (now_point[1] != 18) {
					now_point[1]++;
				}
			}

			gotoxy(now_point[1], now_point[0]);
			tcolor(0, 12);
			if (board[now_point[1]][now_point[0]] == 1)
				printf("¡Ü");
			else if (board[now_point[1]][now_point[0]] == 2)
				printf("¡Û");
			else
				printf("  ");

			print_turn(turn);
			point_home();
		}
		if (key == SPACE) {
			if (board[now_point[1]][now_point[0]] == 0) {
				gotoxy(now_point[1], now_point[0]);
				if (turn == 0) {
					turn = 1;
					board[now_point[1]][now_point[0]] = 1;
				}
				else if (turn == 1) {
					turn = 0;
					board[now_point[1]][now_point[0]] = 2;
				}
				tcolor(0, 12);
				if (board[now_point[1]][now_point[0]] == 1)
					printf("¡Ü");
				else if (board[now_point[1]][now_point[0]] == 2)
					printf("¡Û");
				else
					printf("  ");

				print_turn(turn);
				point_home();
			}
		}
		if (key == ESC) {
			break;
		}
	}

	return 0;
}
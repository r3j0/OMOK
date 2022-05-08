#include <stdio.h>
#include <windows.h>
#include <conio.h>

/*
	(( OMOK )) Author : r3j0
	Last Backup : 2022-05-08 PM 04:48
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

// DEBUG Mode : define DEBUG
#define DEBUG

#ifdef DEBUG
char debugName[1000][100] = {
	"main/turn",
	"main/now_point[0]",
	"main/now_point[1]",
	"line_number/left-right",
	"line_number/up-down",
	"line_number/leftup-rightdown",
	"line_number/rightup-leftdown"
};
/*
	0 : main/turn
	1 : main/now_point[0]
	2 : main/now_point[1]

	3 : line_number/left-right
	4 : line_number/up-down
	5 : line_number/leftup-rightdown
	6 : line_number/rightup-leftdown
*/
int debug[1000] = { 0, };
int debug_size = 7;
#endif

#ifdef DEBUG
void debugPrint();
#endif
void tcolor(int foreground, int background);
void gotoxy(int x, int y);
void gotoBoardxy(int x, int y);

void print_board(int board[][19], int point[]);

void point_home(void);
void print_turn(int t);

int check_victory(int board[][19], int point[], int t);
int line_number(int board[][19], int point[], int t, int dir);
void victory_stone_color(int board[][19], int point[], int t);

int main(void) {

	int board[19][19] = { 0, }; // [0] : y, [1] : x
	char key; // input the arrow key
	int now_point[2] = { 9,9 }; // [0] : y, [1] : x

	int turn = 0; // 0 : black, 1 : white
	int vic = 0; // 0 : no, 1 : black win, 2 : white win

	print_board(board, now_point);
	print_turn(turn);
	point_home();

	while (1) {
#ifdef DEBUG
		debug[0] = turn;
		debug[1] = now_point[0];
		debug[2] = now_point[1];
		debugPrint();
#endif
		key = _getch();
		if (_kbhit()) {
			key = _getch();
			gotoBoardxy(now_point[1], now_point[0]); // previous cursor color reset
			tcolor(0, 15);
			if (board[now_point[0]][now_point[1]] == 1)
				printf("¡Ü");
			else if (board[now_point[0]][now_point[1]] == 2)
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

			gotoBoardxy(now_point[1], now_point[0]); // now cursor color set
			tcolor(0, 12);
			if (board[now_point[0]][now_point[1]] == 1)
				printf("¡Ü");
			else if (board[now_point[0]][now_point[1]] == 2)
				printf("¡Û");
			else
				printf("  ");

			print_turn(turn);
			point_home();
		}
		if (key == SPACE) {
			if (board[now_point[0]][now_point[1]] == 0) { // overlap
				gotoBoardxy(now_point[1], now_point[0]);

				vic = check_victory(board, now_point, turn); // check victory

				if (turn == 0) {
					turn = 1;
					board[now_point[0]][now_point[1]] = 1;
				}
				else if (turn == 1) {
					turn = 0;
					board[now_point[0]][now_point[1]] = 2;
				}
				tcolor(0, 12); // stone print, color set
				if (board[now_point[0]][now_point[1]] == 1)
					printf("¡Ü");
				else if (board[now_point[0]][now_point[1]] == 2)
					printf("¡Û");
				else
					printf("  ");

				point_home();

#ifdef DEBUG
				debug[0] = turn;
				debug[1] = now_point[0];
				debug[2] = now_point[1];
				debugPrint();
#endif

				if (vic == 1) { // win black
					turn = 0;
					victory_stone_color(board, now_point, turn);
					tcolor(15, 0);
					gotoxy(1, 23);
					printf("Black Win!");
					gotoxy(1, 26);
					return 0;
				}
				else if (vic == 2) { // win white
					turn = 1;
					victory_stone_color(board, now_point, turn); 
					tcolor(15, 0);
					gotoxy(1, 23);
					printf("White Win!");
					gotoxy(1, 26);
					return 0;
				}

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

#ifdef DEBUG
void debugPrint() {
	gotoxy(50, 2);
	for (int i = 0; i < debug_size; i++) {
		gotoxy(50, i + 2);
		printf("                          ");
		gotoxy(50, i + 2);
		printf("%s : %d", debugName[i], debug[i]);
	}
	point_home();
}
#endif

// Set the color
void tcolor(int foreground, int background) { // foreground : ±ÛÀÚ »ö±ò, background : ¹è°æ »ö±ò
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/*
0 - black			1 - Blue			2- Green			3 - Cyan
4 - Red				5 - Magenta			6 - Brown			7 - LigntGray
8 - Darkgray		9 - Lightblue		10 - Light Green	11 - Light Cyan
12 - Light Red		13 - Light Magenta	14 - Yellow			15 - White
*/

// Move Cursor
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// Move Cursor - board
void gotoBoardxy(int x, int y)
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
	for (int i = 1; i < 20; i++) { // number - x
		printf("%2d", i);
	}
	printf("\n");
	for (int i = 1; i < 20; i++) {
		tcolor(15, 0);
		printf("%2d ", i); // number - y
		for (int j = 1; j < 20; j++) { // stone, blank
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

void point_home(void) { // cursor reset
	tcolor(15, 0);
	gotoBoardxy(0, 21);
}

void print_turn(int t) { // print turn
	tcolor(15, 0);
	gotoBoardxy(0, 19);
	if (t == 0)
		printf("Turn : Black");
	else
		printf("Turn : White");
	point_home();
}

int check_victory(int board[][19], int point[], int t) {
	for (int i = 1; i <= 4; i++) {
		if (line_number(board, point, t, i) >= 4) { // OMOK
			return t + 1;
		}
	}
	return 0;
}

int line_number(int board[][19], int point[], int t, int dir) {
	int lap = t == 0 ? 1 : 2; // turn stone - in order to check
	int i = 1;
	int count = 0;

	/* direction
	1 : left-right
	2 : up-down
	3 : leftup-rightdown
	4 : rightup-leftdown
	*/
	
	if (dir == 1) { // 1. left-right
		// left
		i = 1;
		count = 0;
		while (point[1] - i >= 0) {
			if (board[point[0]][point[1] - i] != lap) {
				break;
			}
			count++; i++;
		}
		// right
		i = 1;
		while (point[1] + i < 19) {
			if (board[point[0]][point[1] + i] != lap) {
				break;
			}
			count++; i++;
		}
#ifdef DEBUG
		debug[3] = count;
#endif
		return count;
	}
	else if (dir == 2) { // 2. up-down
		// up
		i = 1;
		count = 0;
		while (point[0] - i >= 0) {
			if (board[point[0] - i][point[1]] != lap) {
				break;
			}
			count++; i++;
		}
		// down
		i = 1;
		while (point[0] + i < 19) {
			if (board[point[0] + i][point[1]] != lap) {
				break;
			}
			count++; i++;
		}
#ifdef DEBUG
		debug[4] = count;
#endif
		return count;
	}
	else if (dir == 3) { // 3. leftup-rightdown
		// leftup
		i = 1;
		count = 0;
		while (point[0] - i >= 0 && point[1] - i >= 0) {
			if (board[point[0] - i][point[1] - i] != lap) {
				break;
			}
			count++; i++;
		}
		// rightdown
		i = 1;
		while (point[0] + i < 19 && point[1] + i < 19) {
			if (board[point[0] + i][point[1] + i] != lap) {
				break;
			}
			count++; i++;
		}
#ifdef DEBUG
			debug[5] = count;
#endif
		return count;
	}
	else if (dir == 4) { // 4. rightup-leftdown
		// rightup
		i = 1;
		count = 0;
		while (point[0] - i >= 0 && point[1] + i < 19) {
			if (board[point[0] - i][point[1] + i] != lap) {
				break;
			}
			count++; i++;
		}
		// leftdown
		i = 1;
		while (point[0] + i < 19 && point[1] - i >= 0) {
			if (board[point[0] + i][point[1] - i] != lap) {
				break;
			}
			count++; i++;
		}
#ifdef DEBUG
		debug[6] = count;
#endif
		return count;
	}
}


void victory_stone_color(int board[][19], int point[], int t) {
	int lap = t == 0 ? 1 : 2;
	int cnt = 1;
	int highlight_color = 10;

	gotoBoardxy(point[1], point[0]);
	tcolor(0, highlight_color); // stone print, color set
	if (t == 0)
		printf("¡Ü");
	else if (t == 1)
		printf("¡Û");

	for (int i = 1; i <= 4; i++) {
		if (line_number(board, point, t, i) >= 4) { // OMOK
			gotoBoardxy(point[1], point[0]); 
			if (i == 1) { // 1. left-right
				// left
				cnt = 1;
				while (point[1] - cnt >= 0 && board[point[0]][point[1] - cnt] == lap) {
					gotoBoardxy(point[1] - cnt, point[0]);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0]][point[1] - cnt] == 1)
						printf("¡Ü");
					else if (board[point[0]][point[1] - cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}
				
				// right
				cnt = 1;
				while (point[1] + cnt < 19 && board[point[0]][point[1] + cnt] == lap) {
					gotoBoardxy(point[1] + cnt, point[0]);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0]][point[1] + cnt] == 1)
						printf("¡Ü");
					else if (board[point[0]][point[1] + cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}
			}
			else if (i == 2) { // 2. up-down
				// up
				cnt = 1;
				while (point[0] - cnt >= 0 && board[point[0] - cnt][point[1]] == lap) {
					gotoBoardxy(point[1], point[0] - cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] - cnt][point[1]] == 1)
						printf("¡Ü");
					else if (board[point[0] - cnt][point[1]] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}

				// down
				cnt = 1;
				while (point[0] + cnt < 19 && board[point[0] + cnt][point[1]] == lap) {
					gotoBoardxy(point[1], point[0] + cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] + cnt][point[1]] == 1)
						printf("¡Ü");
					else if (board[point[0] + cnt][point[1]] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}
			}
			else if (i == 3) { // 3. leftup-rightdown
				// leftup
				cnt = 1;
				while (point[0] - cnt >= 0 && point[1] - cnt >= 0 && board[point[0] - cnt][point[1] - cnt] == lap) {
					gotoBoardxy(point[1] - cnt, point[0] - cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] - cnt][point[1] - cnt] == 1)
						printf("¡Ü");
					else if (board[point[0] - cnt][point[1] - cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}

				// rightdown
				cnt = 1;
				while (point[0] + cnt < 19 && point[1] + cnt < 19 && board[point[0] + cnt][point[1] + cnt] == lap) {
					gotoBoardxy(point[1] + cnt, point[0] + cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] + cnt][point[1] + cnt] == 1)
						printf("¡Ü");
					else if (board[point[0] + cnt][point[1] + cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}
			}
			else if (i == 4) { // 4. rightup-leftdown
				// rightup
				cnt = 1;
				while (point[0] - cnt >= 0 && point[1] + cnt < 19 && board[point[0] - cnt][point[1] + cnt] == lap) {
					gotoBoardxy(point[1] + cnt, point[0] - cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] - cnt][point[1] + cnt] == 1)
						printf("¡Ü");
					else if (board[point[0] - cnt][point[1] + cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}

				// leftdown
				cnt = 1;
				while (point[0] + cnt < 19 && point[1] - cnt >= 0 && board[point[0] + cnt][point[1] - cnt] == lap) {
					gotoBoardxy(point[1] - cnt, point[0] + cnt);
					tcolor(0, highlight_color); // stone print, color set
					if (board[point[0] + cnt][point[1] - cnt] == 1)
						printf("¡Ü");
					else if (board[point[0] + cnt][point[1] - cnt] == 2)
						printf("¡Û");
					else
						printf("  ");
					cnt++;
				}
			}
		}
	}
}
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "stai.h"

/*
	(( OMOK )) Author : r3j0
	Last Backup : 2022-07-21 PM 02:09

	1. rewrite database
	2. add function that ai uses database
*/

// Set Arrow key	
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define SPACE 32

// Set play mode
#define MODE 4
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
	"line_number/rightup-leftdown",
	"line_number_blank/left-right",
	"line_number_blank/up-down",
	"line_number_blank/leftup-rightdown",
	"line_number_blank/rightup-leftdown",
	"main/ai_x",
	"main/ai_y",
	"main/black_ai_add_max_size",
	"main/white_ai_add_max_size",
	"search_ovelap/black_min",
	"search_ovelap/white_min"
};
/*
	0 : main/turn
	1 : main/now_point[0]
	2 : main/now_point[1]

	3 : line_number/left-right
	4 : line_number/up-down
	5 : line_number/leftup-rightdown
	6 : line_number/rightup-leftdown

	7 : line_number_blank/left-right
	8 : line_number_blank/up-down
	9 : line_number_blank/leftup-rightdown
	10 : line_number_blank/rightup-leftdown

	11 : main/ai_x
	12 : main/ai_y

	13 : main/black_ai_add_max_size
	14 : main/white_ai_add_max_size

	15 : search_ovelap/black_min
	16 : search_ovelap/white_min
*/
int debug[1000] = { 0, };
int debug_size = 17;
#endif
 
// Database
char rec[5000] = "";
char now_rec[5000] = "";
char path[256] = "C:\\Users\\박정근\\Desktop\\Code\\OMOK\\database.txt";
char now_path[256] = "C:\\Users\\박정근\\Desktop\\Code\\OMOK\\now.txt";
#define DATABASE 1
// 0 : Record On 1 : Record Off

double dbChanceBlack[19][19] = { 0, };
double dbChanceWhite[19][19] = { 0, };

int dbChance_all[19][19] = { 0, };

int dbChanceBlack_vic[19][19] = { 0, };
int dbChanceWhite_vic[19][19] = { 0, };

// AI Standard Algorithm
int black_ai_add[19][19] = { 0, };
int white_ai_add[19][19] = { 0, };
#define AI_ADD_DEBUG 3
// 0 : Print Black
// 1 : Print White
// 2 : Print All
// 3 : print NO // Database Print

// AI Find Add Max
int black_ai_add_max[361][2] = { 0, };
int white_ai_add_max[361][2] = { 0, };
int black_ai_add_max_size = 0;
int white_ai_add_max_size = 0;

int black_min = 0;
int white_min = 0;

#define ATTACK_ADD 7	
// 공격 가중치

int start = 0;
#define INF_PRO 0
//무한루프 1 : 진행 0 : 미진행

//엔터진행 ( #define ENTER )
#define ENTER

#ifdef DEBUG
void debugPrint();
void debugAiAddPrint();
void debugDatabasePrint(int b[][19]);
void debugBoard(int b[][19]);
#endif
void tcolor(int foreground, int background);
void gotoxy(int x, int y);
void gotoBoardxy(int x, int y);

void print_board(int board[][19], int point[]);

void point_home(void);
void print_turn(int t);

void victory_stone_color(int board[][19], int point[], int t);
int checkDraw(int b[][19]);
int check_victory(int board[][19], int point[], int t);

void reset(void);
int record_search_overlap(void);

int main(void) {

#ifdef DEBUG
	system("mode con cols=200 lines=50");
#else
	system("mode con cols=50 lines=30");
#endif

	do {
		int board[19][19] = { 0, }; // [0] : y, [1] : x
		char key; // input the arrow key
		int now_point[2] = { 9,9 }; // [0] : y, [1] : x

		int turn = 0; // 0 : black, 1 : white
		int vic = 0; // 0 : no, 1 : black win, 2 : white win

		//Sleep(1000);
		srand((int)time(NULL));
		reset();
		system("cls");

		print_board(board, now_point);
		print_turn(turn);
		point_home();

		while (1) {
#ifdef DEBUG
			debug[0] = turn;
			debug[1] = now_point[0];
			debug[2] = now_point[1];
			debugPrint(); debugAiAddPrint(); debugDatabasePrint(board); debugBoard(board);
#endif

			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					dbChanceBlack[i][j] = 0;
					dbChanceWhite[i][j] = 0;

					dbChance_all[i][j] = 0;

					dbChanceBlack_vic[i][j] = 0;
					dbChanceWhite_vic[i][j] = 0;
				}
			}

			FILE* fp = fopen(path, "r");
			char read_str[5000];
			char read_str_comp[5000];
			int now_rec_size_comp = strlen(now_rec);

			int _redeb = 0;
			for (int i = 0; i < 46; i++) {
				gotoxy(165, 1 + i);
				printf("                   ");
			}

			while (!feof(fp)) {

				fgets(read_str, 5000, fp);
				if (feof(fp))
					break;
				strcpy(read_str_comp, read_str);
				read_str_comp[now_rec_size_comp] = '\0';
				if (!strcmp(read_str_comp, now_rec)) {
					char whovic = read_str[strlen(read_str) - 2];
					int nextwhoturn = read_str[now_rec_size_comp + 1] - '0';
					int firstx10 = read_str[now_rec_size_comp + 3] - '0';
					int firstx1 = read_str[now_rec_size_comp + 4] - '0';
					int firsty10 = read_str[now_rec_size_comp + 5] - '0';
					int firsty1 = read_str[now_rec_size_comp + 6] - '0';
					
					int result_readx = firstx10 * 10 + firstx1;
					int result_ready = firsty10 * 10 + firsty1;

					dbChance_all[result_ready][result_readx]++;

					if (whovic == 'B')
						dbChanceBlack_vic[result_ready][result_readx]++;
					else if (whovic == 'W')
						dbChanceWhite_vic[result_ready][result_readx]++;
					else {
						printf("ERROR");
						return 0;
					}

					// debug
					gotoxy(165, 1 + (_redeb++));
					if (whovic == 'B')
						tcolor(15, 0);
					else
						tcolor(0, 15);
					printf("%c (%d, %d)", whovic, result_readx, result_ready);
					printf("        ");
					gotoxy(165, 1 + (_redeb++));
					for (int i = 0; i < 20; i++) {
						printf("%c", read_str[now_rec_size_comp + i]);
						if (read_str[now_rec_size_comp + i] == '\0')
							break;
					}
					gotoxy(165, 1 + (_redeb++));
					if (whovic == 'B')
						printf("%d / %d (All)", dbChanceBlack_vic[result_ready][result_readx], dbChance_all[result_ready][result_readx]);
					else
						printf("%d / %d (All)", dbChanceWhite_vic[result_ready][result_readx], dbChance_all[result_ready][result_readx]);

					if (_redeb > 45)
						_redeb = 0;
					tcolor(15, 0);
				}
			}
			fclose(fp);

			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					if (dbChance_all[i][j] == 0) {
						dbChanceBlack[i][j] = 0;
						dbChanceWhite[i][j] = 0;
					}
					else {
						dbChanceBlack[i][j] = (((double)dbChanceBlack_vic[i][j] / dbChance_all[i][j]) * 100);
						dbChanceWhite[i][j] = (((double)dbChanceWhite_vic[i][j] / dbChance_all[i][j]) * 100);
					}
				}
			}

			debugDatabasePrint(board);
			
			if (MODE == 1 || (MODE == 2 && turn == 0) || (MODE == 3 && turn == 1)) { // Player Input Mode
				key = _getch();
				if (_kbhit()) {
					key = _getch();
					gotoBoardxy(now_point[1], now_point[0]); // previous cursor color reset
					tcolor(0, 15);
					if (board[now_point[0]][now_point[1]] == 1)
						printf("●");
					else if (board[now_point[0]][now_point[1]] == 2)
						printf("○");
					else
						printf("  ");

					if (start == 1) {
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
					}

					gotoBoardxy(now_point[1], now_point[0]); // now cursor color set
					tcolor(0, 12);
					if (board[now_point[0]][now_point[1]] == 1)
						printf("●");
					else if (board[now_point[0]][now_point[1]] == 2)
						printf("○");
					else
						printf("  ");

					print_turn(turn);
					point_home();
				}
				if (key == SPACE) {

					if (board[now_point[0]][now_point[1]] == 0) { // overlap
						gotoBoardxy(now_point[1], now_point[0]);
						start = 1;

						if (turn == 0) {
							turn = 1;

							char x[10] = "0";
							char y[10] = "0";

							char x_1[10];
							char x_2[10];
							char y_1[10];
							char y_2[10];

							char rego[10] = "[1]";

							itoa(now_point[1] / 10, x_1, 10);
							itoa(now_point[1] % 10, x_2, 10);
							itoa(now_point[0] / 10, y_1, 10);
							itoa(now_point[0] % 10, y_2, 10);
							strcat(x_1, x_2);
							strcpy(x, x_1);
							strcat(y_1, y_2);
							strcpy(y, y_1);
							strcat(rego, x);
							strcat(rego, y);
							strcat(rec, rego);

							strcpy(now_rec, rec);
							FILE* fp = fopen(now_path, "w");
							fputs(now_rec, fp);
							fclose(fp);

							black_ai_add[now_point[0]][now_point[1]] = 1;
							white_ai_add[now_point[0]][now_point[1]] = 1;

							add_board(board, now_point, 1); // White 가 Black 이 놓은 걸 보고 가중치 추가

							board[now_point[0]][now_point[1]] = 1;
						}
						else if (turn == 1) {
							turn = 0;

							char x[10];
							char y[10];

							char x_1[10];
							char x_2[10];
							char y_1[10];
							char y_2[10];

							char rego[10] = "[2]";

							itoa(now_point[1] / 10, x_1, 10);
							itoa(now_point[1] % 10, x_2, 10);
							itoa(now_point[0] / 10, y_1, 10);
							itoa(now_point[0] % 10, y_2, 10);
							strcat(x_1, x_2);
							strcpy(x, x_1);
							strcat(y_1, y_2);
							strcpy(y, y_1);
							strcat(rego, x);
							strcat(rego, y);
							strcat(rec, rego);

							strcpy(now_rec, rec);
							FILE* fp = fopen(now_path, "w");
							fputs(now_rec, fp);
							fclose(fp);

							black_ai_add[now_point[0]][now_point[1]] = 2;
							white_ai_add[now_point[0]][now_point[1]] = 2;

							add_board(board, now_point, 0); // Black 이 White가 놓은 걸 보고 가중치 추가

							board[now_point[0]][now_point[1]] = 2;
						}
						tcolor(0, 12); // stone print, color set
						if (board[now_point[0]][now_point[1]] == 1)
							printf("●");
						else if (board[now_point[0]][now_point[1]] == 2)
							printf("○");
						else
							printf("  ");

						point_home();

#ifdef DEBUG
						debug[0] = turn;
						debug[1] = now_point[0];
						debug[2] = now_point[1];
						debugPrint(); debugAiAddPrint(); debugDatabasePrint(board); debugBoard(board);
#endif

						vic = check_victory(board, now_point, turn == 1 ? 0 : 1); // check victory

						if (vic == 1) { // win black
							turn = 0;
							victory_stone_color(board, now_point, turn);
							tcolor(15, 0);
							gotoxy(1, 23);
							printf("Black Win!");
							gotoxy(1, 24);
#if DATABASE == 0			
							strcat(rec, "B");
							if (record_search_overlap()) {
								FILE* fp = fopen(path, "a");
								fputs(rec, fp);
								fputs("\n", fp);
								fclose(fp);
							}
#endif
							return 0;
						}
						else if (vic == 2) { // win white
							turn = 1;
							victory_stone_color(board, now_point, turn);
							tcolor(15, 0);
							gotoxy(1, 23);
							printf("White Win!");
							gotoxy(1, 24);
#if DATABASE == 0
							strcat(rec, "W");
							if (record_search_overlap()) {
								FILE* fp = fopen(path, "a");
								fputs(rec, fp);
								fputs("\n", fp);
								fclose(fp);
							}
#endif
							return 0;
						}

						int c = checkDraw(board);
						if (c == 1) {
							break;
						}

						print_turn(turn);
						point_home();
					}
#ifdef DEBUG
					debug[0] = turn;
					debug[1] = now_point[0];
					debug[2] = now_point[1];
					debugPrint(); debugAiAddPrint(); debugDatabasePrint(board); debugBoard(board);
#endif
				}
				if (key == ESC) {
					break;
				}
			}
			else { // AI Input Mode
				int x = 0, y = 0;
				int point[2];

				// Enter Progressing
#ifdef ENTER
				key = _getch();
				if (key == ESC) {
					break;
				}
#endif

				if (MODE == 2 || (MODE == 4 && turn == 1)) {
					search_ovelap(board, 0);
					search_ovelap(board, 1);

					if (black_min <= -1 * ATTACK_ADD) {
						int see = rand() % black_ai_add_max_size;
						x = black_ai_add_max[see][1];
						y = black_ai_add_max[see][0];
					}
					else {
						int see = rand() % white_ai_add_max_size;
						x = white_ai_add_max[see][1];
						y = white_ai_add_max[see][0];
					}
#ifdef DEBUG
					debug[15] = black_min;
					debug[16] = white_min;
#endif

					turn = 0;

					char x_c[10], x_v[10], x_r[10];
					char y_c[10], y_v[10], y_r[10];

					int x_1 = x / 10;
					int x_2 = x % 10;
					int y_1 = y / 10;
					int y_2 = y % 10;

					itoa(x_1, x_c, 10);
					itoa(x_2, x_v, 10);
					itoa(y_1, y_c, 10);
					itoa(y_2, y_v, 10);

					char rego[10] = "[2]";

					strcat(x_c, x_v);
					strcpy(x_r, x_c);
					strcat(y_c, y_v);
					strcpy(y_r, y_c);
					strcat(rego, x_r);
					strcat(rego, y_r);
					strcat(rec, rego);

					strcpy(now_rec, rec);
					FILE* fp = fopen(now_path, "w");
					fputs(now_rec, fp);
					fclose(fp);

					black_ai_add[y][x] = 2;
					white_ai_add[y][x] = 2;

					point[0] = y;
					point[1] = x;

					add_board(board, point, 0); // Black 이 White가 놓은 걸 보고 가중치 추가

					if (board[y][x] != 0)
						break;
					board[y][x] = 2;
				}
				else if (MODE == 3 || (MODE == 4 && turn == 0)) {
					search_ovelap(board, 1);
					search_ovelap(board, 0);
					if (start == 0) {
						x = 9;
						y = 9;
						start = 1;
					}
					else {

						if (white_min <= -1 * ATTACK_ADD) {
							int see = rand() % white_ai_add_max_size;
							x = white_ai_add_max[see][1];
							y = white_ai_add_max[see][0];
						}
						else {

							int see = rand() % black_ai_add_max_size;
							x = black_ai_add_max[see][1];
							y = black_ai_add_max[see][0];
						}
					}

#ifdef DEBUG
					debug[15] = black_min;
					debug[16] = white_min;
#endif

					turn = 1;

					char x_c[10], x_v[10], x_r[10];
					char y_c[10], y_v[10], y_r[10];

					int x_1 = x / 10;
					int x_2 = x % 10;
					int y_1 = y / 10;
					int y_2 = y % 10;

					itoa(x_1, x_c, 10);
					itoa(x_2, x_v, 10);
					itoa(y_1, y_c, 10);
					itoa(y_2, y_v, 10);

					char rego[10] = "[1]";

					strcat(x_c, x_v);
					strcpy(x_r, x_c);
					strcat(y_c, y_v);
					strcpy(y_r, y_c);
					strcat(rego, x_r);
					strcat(rego, y_r);
					strcat(rec, rego);

					strcpy(now_rec, rec);
					FILE* fp = fopen(now_path, "w");
					fputs(now_rec, fp);
					fclose(fp);

					black_ai_add[y][x] = 1;
					white_ai_add[y][x] = 1;

					point[0] = y;
					point[1] = x;

					add_board(board, point, 1); // White 가 Black 놓은 걸 보고 가중치 추가


					if (board[y][x] != 0)
						break;
					board[y][x] = 1;
				}

				gotoBoardxy(x, y);
				tcolor(0, 15); // stone print, color set
				if (board[y][x] == 1)
					printf("●");
				else if (board[y][x] == 2)
					printf("○");
				else
					printf("  ");

				point_home();
				// -- 
#ifdef DEBUG
				debug[0] = turn;
				debug[11] = x;
				debug[12] = y;
				debug[13] = black_ai_add_max_size;
				debug[14] = white_ai_add_max_size;
				debugPrint(); debugAiAddPrint(); debugDatabasePrint(board); debugBoard(board);
#endif

				vic = check_victory(board, point, turn == 1 ? 0 : 1); // check victory

				if (vic == 1) { // win black
					turn = 0;
					victory_stone_color(board, point, turn);
					tcolor(15, 0);
					gotoxy(1, 23);
					printf("Black Win!");
					gotoxy(1, 24);
#if DATABASE == 0
					strcat(rec, "B");
					if (record_search_overlap()) {
						FILE* fp = fopen(path, "a");
						fputs(rec, fp);
						fputs("\n", fp);
						fclose(fp);
					}
#endif
					break;
				}
				else if (vic == 2) { // win white
					turn = 1;
					victory_stone_color(board, point, turn);
					tcolor(15, 0);
					gotoxy(1, 23);
					printf("White Win!");
					gotoxy(1, 24);
#if DATABASE == 0
					strcat(rec, "W");
					if (record_search_overlap()) {
						FILE* fp = fopen(path, "a");
						fputs(rec, fp);
						fputs("\n", fp);
						fclose(fp);
					}
#endif
					break;
				}

				int c = checkDraw(board);
				if (c == 1) {
					break;
				}

				print_turn(turn);
				point_home();
			}
		}
	} while (INF_PRO);

	return 0;
}

#ifdef DEBUG
void debugPrint() {
	gotoxy(50, 2);
	for (int i = 0; i < debug_size; i++) {
		gotoxy(50, i + 2);
		printf("                                ");
		gotoxy(50, i + 2);
		printf("%s : %d", debugName[i], debug[i]);
	}

	point_home();
}

void debugAiAddPrint() {
#if AI_ADD_DEBUG == 0 || AI_ADD_DEBUG == 2
	gotoxy(100, 2);
	tcolor(0, 15);
	printf(" ● ");
	for (int i = 1; i < 20; i++) { // number - x
		printf("%3d", i);
	}
	gotoxy(100, 3);
	for (int i = 1; i < 20; i++) {
		tcolor(0, 15);
		printf("%3d", i); // number - y
		tcolor(15, 0);
		for (int j = 1; j < 20; j++) {
			if (black_ai_add[i - 1][j - 1] == 1) {
				printf(" ");
				tcolor(0, 15);
				printf("●");
				tcolor(15, 0);
			}
			else if (black_ai_add[i - 1][j - 1] == 2) {
				printf(" ");
				tcolor(0, 15);
				printf("○");
				tcolor(15, 0);
			}
			else
				printf("%3d", black_ai_add[i - 1][j - 1]*-1);
		}
		gotoxy(100, 3 + i);
	}

	tcolor(15, 0);
#endif
#if AI_ADD_DEBUG == 1 || AI_ADD_DEBUG == 2
	gotoxy(100, 25);
	tcolor(0, 15);
	printf(" ○ ");
	for (int i = 1; i < 20; i++) { // number - x
		printf("%3d", i);
	}
	gotoxy(100, 26);
	for (int i = 1; i < 20; i++) {
		tcolor(0, 15);
		printf("%3d", i); // number - y
		tcolor(15, 0);
		for (int j = 1; j < 20; j++) {
			if (white_ai_add[i - 1][j - 1] == 1) {
				printf(" ");
				tcolor(0, 15);
				printf("●");
				tcolor(15, 0);
			}
			else if (white_ai_add[i - 1][j - 1] == 2) {
				printf(" ");
				tcolor(0, 15);
				printf("○");
				tcolor(15, 0);
			}
			else
				printf("%3d", white_ai_add[i - 1][j - 1]*-1);
		}
		gotoxy(100, 26 + i);
	}

	tcolor(15, 0);
#endif

	point_home();
}
void debugDatabasePrint(int b[][19]) {
#if AI_ADD_DEBUG == 3
	gotoxy(100, 2);
	tcolor(0, 15);
	printf(" ● ");
	for (int i = 1; i < 20; i++) { // number - x
		printf("%3d", i);
	}
	gotoxy(100, 3);
	for (int i = 1; i < 20; i++) {
		tcolor(0, 15);
		printf("%3d", i); // number - y
		tcolor(15, 0);
		for (int j = 1; j < 20; j++) {
			if (b[i - 1][j - 1] == 1) {
				printf(" ");
				tcolor(0, 15);
				printf("●");
				tcolor(15, 0);
			}
			else if (b[i - 1][j - 1] == 2) {
				printf(" ");
				tcolor(0, 15);
				printf("○");
				tcolor(15, 0);
			}
			else {
				printf("%3.0f", dbChanceBlack[i - 1][j - 1]);
			}
		}
		gotoxy(100, 3 + i);
	}

	tcolor(15, 0);

	gotoxy(100, 25);
	tcolor(0, 15);
	printf(" ○ ");
	for (int i = 1; i < 20; i++) { // number - x
		printf("%3d", i);
	}
	gotoxy(100, 26);
	for (int i = 1; i < 20; i++) {
		tcolor(0, 15);
		printf("%3d", i); // number - y
		tcolor(15, 0);
		for (int j = 1; j < 20; j++) {
			if (b[i - 1][j - 1] == 1) {
				printf(" ");
				tcolor(0, 15);
				printf("●");
				tcolor(15, 0);
			}
			else if (b[i - 1][j - 1] == 2) {
				printf(" ");
				tcolor(0, 15);
				printf("○");
				tcolor(15, 0);
			}
			else {
				printf("%3.0f", dbChanceWhite[i - 1][j - 1]);
			}
		}
		gotoxy(100, 26 + i);
	}

	tcolor(15, 0);
#endif

	point_home();
}
void debugBoard(int b[][19]) {
	gotoxy(1, 25);
	tcolor(15, 0);
	printf("  ");
	for (int i = 1; i < 20; i++) { // number - x
		printf("%2d", i);
	}
	printf("\n");
	for (int i = 1; i < 20; i++) {
		printf("%2d ", i); // number - y
		for (int j = 1; j < 20; j++) { // stone, blank
			printf("%2d", b[i - 1][j - 1]);
		}
		printf("\n");
	}
}
#endif

// Set the color
void tcolor(int foreground, int background) { // foreground : 글자 색깔, background : 배경 색깔
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
				printf("●");
			}
			else if (board[i - 1][j - 1] == 2) {
				if (point[0] == i - 1 && point[1] == j - 1)
					tcolor(0, 12);
				printf("○");
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
void victory_stone_color(int board[][19], int point[], int t) {
	int lap = t == 0 ? 1 : 2;
	int cnt = 1;
	int highlight_color = 10;

	gotoBoardxy(point[1], point[0]);
	tcolor(0, highlight_color); // stone print, color set
	if (t == 0)
		printf("●");
	else if (t == 1)
		printf("○");

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
						printf("●");
					else if (board[point[0]][point[1] - cnt] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0]][point[1] + cnt] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] - cnt][point[1]] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] + cnt][point[1]] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] - cnt][point[1] - cnt] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] + cnt][point[1] + cnt] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] - cnt][point[1] + cnt] == 2)
						printf("○");
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
						printf("●");
					else if (board[point[0] + cnt][point[1] - cnt] == 2)
						printf("○");
					else
						printf("  ");
					cnt++;
				}
			}
		}
	}
}
int check_victory(int board[][19], int point[], int t) {
	for (int i = 1; i <= 4; i++) {
		if (line_number(board, point, t, i) >= 4) { // OMOK
			return t + 1;
		}
	}
	return 0;
}
int checkDraw(int b[][19]) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (b[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}
void reset(void) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			black_ai_add[i][j] = 0;
			white_ai_add[i][j] = 0;
		}
	}
	
	strcpy(rec, "");
	strcpy(now_rec, "");
	
	for (int i = 0; i < 361; i++) {
		for (int j = 0; j < 2; j++) {
			black_ai_add_max[i][j] = 0;
			white_ai_add_max[i][j] = 0;
		}
	}
	black_ai_add_max_size = 0;
	white_ai_add_max_size = 0;

	black_min = 0;
	white_min = 0; 

	start = 0;

#ifdef DEBUG
	for (int i = 0; i < 1000; i++)
		debug[i] = 0;
#endif
}
int record_search_overlap(void) {
	FILE* rsop = fopen(path, "r");
	char rso[5000];
	int rso_comp = strlen(rec);
	while (!feof(rsop)) {

		fgets(rso, 5000, rsop);
		rso[rso_comp] = '\0';
		if (!strcmp(rso, rec)) {
			return 0;
		}
	}
	fclose(rsop);
	return 1;
}
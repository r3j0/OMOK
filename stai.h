
// AI Standard Algorithm
extern int black_ai_add[19][19];
extern int white_ai_add[19][19];

// AI Find Add Max
extern int black_ai_add_max[361][2];
extern int white_ai_add_max[361][2];
extern int black_ai_add_max_size;
extern int white_ai_add_max_size;

extern int black_min;
extern int white_min;

int line_number(int board[][19], int point[], int t, int dir);
int line_number_blank(int board[][19], int point[], int t, int dir);
void add_board(int b[][19], int p[], int t);
void search_ovelap(int b[][19], int t);
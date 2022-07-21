#include "stai.h"

// Count line stone number without blank
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

// Count line stone number with blank
int line_number_blank(int board[][19], int point[], int t, int dir) {
	int lap = t == 0 ? 2 : 1; // turn stone - in order to check
	int i = 1;
	int count = 0;
	int blank = 0;
	int blank_max = 0;

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
		blank = 0;
		while (point[1] - i >= 0) {
			if (board[point[0]][point[1] - i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0]][point[1] - i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
		// right
		i = 1;
		blank = 0;
		while (point[1] + i < 19) {
			if (board[point[0]][point[1] + i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0]][point[1] + i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
#ifdef DEBUG
		debug[7] = count;
#endif
		return count;
	}
	else if (dir == 2) { // 2. up-down
		// up
		i = 1;
		count = 0;
		blank = 0;
		while (point[0] - i >= 0) {
			if (board[point[0] - i][point[1]] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] - i][point[1]] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
		// down
		i = 1;
		blank = 0;
		while (point[0] + i < 19) {
			if (board[point[0] + i][point[1]] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] + i][point[1]] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
#ifdef DEBUG
		debug[8] = count;
#endif
		return count;
	}
	else if (dir == 3) { // 3. leftup-rightdown
		// leftup
		i = 1;
		count = 0;
		blank = 0;
		while (point[0] - i >= 0 && point[1] - i >= 0) {
			if (board[point[0] - i][point[1] - i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] - i][point[1] - i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
		// rightdown
		i = 1;
		blank = 0;
		while (point[0] + i < 19 && point[1] + i < 19) {
			if (board[point[0] + i][point[1] + i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] + i][point[1] + i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
#ifdef DEBUG
		debug[9] = count;
#endif
		return count;
	}
	else if (dir == 4) { // 4. rightup-leftdown
		// rightup
		i = 1;
		count = 0;
		blank = 0;
		while (point[0] - i >= 0 && point[1] + i < 19) {
			if (board[point[0] - i][point[1] + i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] - i][point[1] + i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
		// leftdown
		i = 1;
		blank = 0;
		while (point[0] + i < 19 && point[1] - i >= 0) {
			if (board[point[0] + i][point[1] - i] != lap) {
				if (blank > blank_max) {
					break;
				}
				if (board[point[0] + i][point[1] - i] == 0) {
					blank++;
					i++;
					continue;
				}
				else {
					break;
				}
			}
			blank = 0;
			count++; i++;
		}
#ifdef DEBUG
		debug[10] = count;
#endif
		return count;
	}
}

// Add ai point
void add_board(int b[][19], int p[], int t) {
	if (t == 0) // black 에 추가
	{
		/*
			(1) 8방향 가중치 -1
			1. left
			2. leftup
			3. up
			4. rightup
			5. right
			6. rightdown
			7. down
			8. leftdown

			(2) 줄 갯수 가중치
		*/

		// 1. left
		if (p[1] > 0) {
			if (black_ai_add[p[0]][p[1] - 1] <= 0) {
				black_ai_add[p[0]][p[1] - 1] -= 1;
			}
		}
		// 2. leftup
		if (p[0] > 0 && p[1] > 0) {
			if (black_ai_add[p[0] - 1][p[1] - 1] <= 0) {
				black_ai_add[p[0] - 1][p[1] - 1] -= 1;
			}
		}
		// 3. up
		if (p[0] > 0) {
			if (black_ai_add[p[0] - 1][p[1]] <= 0) {
				black_ai_add[p[0] - 1][p[1]] -= 1;
			}
		}
		// 4. rightup
		if (p[0] > 0 && p[1] < 18) {
			if (black_ai_add[p[0] - 1][p[1] + 1] <= 0) {
				black_ai_add[p[0] - 1][p[1] + 1] -= 1;
			}
		}
		// 5. right 
		if (p[1] < 18) {
			if (black_ai_add[p[0]][p[1] + 1] <= 0) {
				black_ai_add[p[0]][p[1] + 1] -= 1;
			}
		}
		// 6. rightdown
		if (p[0] < 18 && p[1] < 18) {
			if (black_ai_add[p[0] + 1][p[1] + 1] <= 0) {
				black_ai_add[p[0] + 1][p[1] + 1] -= 1;
			}
		}
		// 7. down
		if (p[0] < 18) {
			if (black_ai_add[p[0] + 1][p[1]] <= 0) {
				black_ai_add[p[0] + 1][p[1]] -= 1;
			}
		}
		// 8. leftdown
		if (p[0] < 18 && p[1] > 0) {
			if (black_ai_add[p[0] + 1][p[1] - 1] <= 0) {
				black_ai_add[p[0] + 1][p[1] - 1] -= 1;
			}
		}

		int s[4];
		for (int i = 1; i <= 4; i++) {
			s[i - 1] = line_number_blank(b, p, t, i);
		}

		// left-right
		if (s[0] == 2) {
			int i = 1;
			while (p[1] - i >= 0) {
				if (b[p[0]][p[1] - i] != 0) {
					if (b[p[0]][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0]][p[1] - i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[1] + i <= 18) {
				if (b[p[0]][p[1] + i] != 0) {
					if (b[p[0]][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0]][p[1] + i] -= 6;
					break;
				}
			}
		}
		else if (s[0] >= 3) {
			int i = 1;
			while (p[1] - i >= 0) {
				if (b[p[0]][p[1] - i] != 0) {
					if (b[p[0]][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0]][p[1] - i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[1] + i <= 18) {
				if (b[p[0]][p[1] + i] != 0) {
					if (b[p[0]][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0]][p[1] + i] -= 30;
					break;
				}
			}
		}

		// up-down 
		if (s[1] == 2) {
			int i = 1;
			while (p[0] - i >= 0) {
				if (b[p[0] - i][p[1]] != 0) {
					if (b[p[0] - i][p[1]] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1]] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18) {
				if (b[p[0] + i][p[1]] != 0) {
					if (b[p[0] + i][p[1]] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1]] -= 6;
					break;
				}
			}
		}
		else if (s[1] >= 3) {
			int i = 1;
			while (p[0] - i >= 0) {
				if (b[p[0] - i][p[1]] != 0) {
					if (b[p[0] - i][p[1]] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1]] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18) {
				if (b[p[0] + i][p[1]] != 0) {
					if (b[p[0] + i][p[1]] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1]] -= 30;
					break;
				}
			}
		}

		// leftup-rightdown 
		if (s[2] == 2) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] - i >= 0) {
				if (b[p[0] - i][p[1] - i] != 0) {
					if (b[p[0] - i][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1] - i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] + i <= 18) {
				if (b[p[0] + i][p[1] + i] != 0) {
					if (b[p[0] + i][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1] + i] -= 6;
					break;
				}
			}
		}
		else if (s[2] >= 3) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] - i >= 0) {
				if (b[p[0] - i][p[1] - i] != 0) {
					if (b[p[0] - i][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1] - i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] + i <= 18) {
				if (b[p[0] + i][p[1] + i] != 0) {
					if (b[p[0] + i][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1] + i] -= 30;
					break;
				}
			}
		}

		//rightup-leftdown
		if (s[3] == 2) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] + i <= 18) {
				if (b[p[0] - i][p[1] + i] != 0) {
					if (b[p[0] - i][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1] + i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] - i >= 0) {
				if (b[p[0] + i][p[1] - i] != 0) {
					if (b[p[0] + i][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1] - i] -= 6;
					break;
				}
			}
		}
		else if (s[3] >= 3) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] + i <= 18) {
				if (b[p[0] - i][p[1] + i] != 0) {
					if (b[p[0] - i][p[1] + i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] - i][p[1] + i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] - i >= 0) {
				if (b[p[0] + i][p[1] - i] != 0) {
					if (b[p[0] + i][p[1] - i] == 1) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					black_ai_add[p[0] + i][p[1] - i] -= 30;
					break;
				}
			}
		}
	}
	else { // white 에 추가
		/*
			(1) 8방향 가중치 -1
			1. left
			2. leftup
			3. up
			4. rightup
			5. right
			6. rightdown
			7. down
			8. leftdown
		*/

		// 1. left
		if (p[1] > 0) {
			if (white_ai_add[p[0]][p[1] - 1] <= 0) {
				white_ai_add[p[0]][p[1] - 1] -= 1;
			}
		}
		// 2. leftup
		if (p[0] > 0 && p[1] > 0) {
			if (white_ai_add[p[0] - 1][p[1] - 1] <= 0) {
				white_ai_add[p[0] - 1][p[1] - 1] -= 1;
			}
		}
		// 3. up
		if (p[0] > 0) {
			if (white_ai_add[p[0] - 1][p[1]] <= 0) {
				white_ai_add[p[0] - 1][p[1]] -= 1;
			}
		}
		// 4. rightup
		if (p[0] > 0 && p[1] < 18) {
			if (white_ai_add[p[0] - 1][p[1] + 1] <= 0) {
				white_ai_add[p[0] - 1][p[1] + 1] -= 1;
			}
		}
		// 5. right 
		if (p[1] < 18) {
			if (white_ai_add[p[0]][p[1] + 1] <= 0) {
				white_ai_add[p[0]][p[1] + 1] -= 1;
			}
		}
		// 6. rightdown
		if (p[0] < 18 && p[1] < 18) {
			if (white_ai_add[p[0] + 1][p[1] + 1] <= 0) {
				white_ai_add[p[0] + 1][p[1] + 1] -= 1;
			}
		}
		// 7. down
		if (p[0] < 18) {
			if (white_ai_add[p[0] + 1][p[1]] <= 0) {
				white_ai_add[p[0] + 1][p[1]] -= 1;
			}
		}
		// 8. leftdown
		if (p[0] < 18 && p[1] > 0) {
			if (white_ai_add[p[0] + 1][p[1] - 1] <= 0) {
				white_ai_add[p[0] + 1][p[1] - 1] -= 1;
			}
		}

		int s[4];
		for (int i = 1; i <= 4; i++) {
			s[i - 1] = line_number_blank(b, p, t, i);
		}

		// left-right
		if (s[0] == 2) {
			int i = 1;
			while (p[1] - i >= 0) {
				if (b[p[0]][p[1] - i] != 0) {
					if (b[p[0]][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0]][p[1] - i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[1] + i <= 18) {
				if (b[p[0]][p[1] + i] != 0) {
					if (b[p[0]][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0]][p[1] + i] -= 6;
					break;
				}
			}
		}
		else if (s[0] >= 3) {
			int i = 1;
			while (p[1] - i >= 0) {
				if (b[p[0]][p[1] - i] != 0) {
					if (b[p[0]][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0]][p[1] - i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[1] + i <= 18) {
				if (b[p[0]][p[1] + i] != 0) {
					if (b[p[0]][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0]][p[1] + i] -= 30;
					break;
				}
			}
		}

		// up-down 
		if (s[1] == 2) {
			int i = 1;
			while (p[0] - i >= 0) {
				if (b[p[0] - i][p[1]] != 0) {
					if (b[p[0] - i][p[1]] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1]] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18) {
				if (b[p[0] + i][p[1]] != 0) {
					if (b[p[0] + i][p[1]] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1]] -= 6;
					break;
				}
			}
		}
		else if (s[1] >= 3) {
			int i = 1;
			while (p[0] - i >= 0) {
				if (b[p[0] - i][p[1]] != 0) {
					if (b[p[0] - i][p[1]] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1]] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18) {
				if (b[p[0] + i][p[1]] != 0) {
					if (b[p[0] + i][p[1]] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1]] -= 30;
					break;
				}
			}
		}

		// leftup-rightdown 
		if (s[2] == 2) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] - i >= 0) {
				if (b[p[0] - i][p[1] - i] != 0) {
					if (b[p[0] - i][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1] - i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] + i <= 18) {
				if (b[p[0] + i][p[1] + i] != 0) {
					if (b[p[0] + i][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1] + i] -= 6;
					break;
				}
			}
		}
		else if (s[2] >= 3) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] - i >= 0) {
				if (b[p[0] - i][p[1] - i] != 0) {
					if (b[p[0] - i][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1] - i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] + i <= 18) {
				if (b[p[0] + i][p[1] + i] != 0) {
					if (b[p[0] + i][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1] + i] -= 30;
					break;
				}
			}
		}

		//rightup-leftdown
		if (s[3] == 2) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] + i <= 18) {
				if (b[p[0] - i][p[1] + i] != 0) {
					if (b[p[0] - i][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1] + i] -= 6;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] - i >= 0) {
				if (b[p[0] + i][p[1] - i] != 0) {
					if (b[p[0] + i][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1] - i] -= 6;
					break;
				}
			}
		}
		else if (s[3] >= 3) {
			int i = 1;
			while (p[0] - i >= 0 && p[1] + i <= 18) {
				if (b[p[0] - i][p[1] + i] != 0) {
					if (b[p[0] - i][p[1] + i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] - i][p[1] + i] -= 30;
					break;
				}
			}
			i = 1;
			while (p[0] + i <= 18 && p[1] - i >= 0) {
				if (b[p[0] + i][p[1] - i] != 0) {
					if (b[p[0] + i][p[1] - i] == 2) {
						break;
					}
					else {
						i++;
					}
				}
				else {
					white_ai_add[p[0] + i][p[1] - i] -= 30;
					break;
				}
			}
		}
	}
}

// Search max ai point locations
void search_ovelap(int b[][19], int t) {
	if (t == 0) { // ai is black
		black_min = 0;
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (b[i][j] == 0) {
					if (black_ai_add[i][j] < black_min) {
						black_min = black_ai_add[i][j];

						black_ai_add_max[0][0] = i;
						black_ai_add_max[0][1] = j;
						black_ai_add_max_size = 1;
					}
					else if (black_ai_add[i][j] == black_min) {
						black_ai_add_max[black_ai_add_max_size][0] = i;
						black_ai_add_max[black_ai_add_max_size][1] = j;
						black_ai_add_max_size++;
					}
				}
			}
		}
	}
	else { // ai is white
		white_min = 0;
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (b[i][j] == 0) {
					if (white_ai_add[i][j] < white_min) {
						white_min = white_ai_add[i][j];

						white_ai_add_max[0][0] = i;
						white_ai_add_max[0][1] = j;
						white_ai_add_max_size = 1;
					}
					else if (white_ai_add[i][j] == white_min) {
						white_ai_add_max[white_ai_add_max_size][0] = i;
						white_ai_add_max[white_ai_add_max_size][1] = j;
						white_ai_add_max_size++;
					}
				}
			}
		}
	}
}
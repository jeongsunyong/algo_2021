#include <iostream>

using namespace std;

int** spread(int** board, int r, int c, int ac[]) {
	int** board_aft = new int*[r];
	for (int i = 0; i < r; i++) {
		board_aft[i] = new int[c];
		for (int j = 0; j < c; j++) {
			board_aft[i][j] = 0;
		}
	}
	board_aft[ac[0]][0] = -1; board_aft[ac[1]][0] = -1;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (board[i][j] <= 0)
				continue;

			int mm = (board[i][j]) / 5;

			int spread_cnt = 0;

			if (i > 0 && 
				!(j == 0 && i - 1 == ac[0]) &&
				!(j == 0 && i - 1 == ac[1])) {
				board_aft[i - 1][j] += mm;
				spread_cnt++;

			}
			if (i < r - 1 && 
				!(j == 0 && i + 1 == ac[0]) &&
				!(j == 0 && i + 1 == ac[1])) {
				board_aft[i + 1][j] += mm;
				spread_cnt++;
			}
			if (j > 0  && 
				!(j - 1 == 0 && i == ac[0]) &&
				!(j - 1 == 0 && i == ac[1])) {
				board_aft[i][j-1] += mm;
				spread_cnt++;
			}
			if (j < c - 1 &&
				!(j + 1 == 0 && i == ac[0]) &&
				!(j + 1 == 0 && i == ac[1])) {
				board_aft[i][j + 1] += mm;
				spread_cnt++;
			}
			board_aft[i][j] += board[i][j] - (mm*spread_cnt);
		}
	}



	//delete memmory
	for (int i = 0; i < r; i++) {
		delete[] board[i];
	}
	delete[] board;
	
	return board_aft;

}
void clean(int** board, int r, int c, int ac[]) {
	//upside
	int ac_upside = ac[0];
	int pull_direction_up[4][2] = { {0,-1},{+1,0},{0,+1},{-1,0} };
	int x = 0; int y = ac_upside - 1;
	int d = 0;
	while (!(x == 1 && y == ac_upside)) {
		int dx = pull_direction_up[d][0]; int dy = pull_direction_up[d][1];
		board[y][x] = board[y + dy][x + dx];
		y = y + dy;
		x = x + dx;
		if (x + dx >= c || y + dy > ac_upside || x + dx < 0 || y + dy < 0)
			d++;

	}
	board[y][x] = 0;

	//downside
	int ac_downside = ac[1];
	int pull_direction_down[4][2] = { {0,1},{+1,0},{0,-1},{-1,0} };
	x = 0; y = ac_downside + 1;
	d = 0;
	while (!(x == 1 && y == ac_downside)) {
		int dx = pull_direction_down[d][0]; int dy = pull_direction_down[d][1];
		board[y][x] = board[y + dy][x + dx];
		y = y + dy;
		x = x + dx;
		if (x + dx >= c || y + dy >= r || x + dx < 0 || y + dy < ac_downside)
			d++;

	}
	board[y][x] = 0;


}

int main(void) {
	int r, c, t;
	cin >> r >> c >> t;

	int** board = new int* [r];
	int ac[2] = { -1,-1 }; //aircleaner
	for (int i = 0; i < r; i++) {
		board[i] = new int[c];
		for (int j = 0; j < c; j++) {
			cin >> board[i][j];
			if (board[i][j] == -1) {
				ac[0] = (ac[0] == -1) ? i : ac[0];
				ac[1] = (ac[0] != -1) ? i : ac[1];
			}
		}
	}

	for (int i = 0; i < t; i++) {
		board=spread(board, r, c, ac);
		clean(board, r, c, ac);
	}

	int sum = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (board[i][j] <= 0)
				continue;
			sum += board[i][j];
		}
	}
	
	cout << sum << endl;
	

	for (int i = 0; i < r; i++) {
		delete[] board[i];
	}
	delete[] board;
	
	return 0;
}

/*************************** note *****

GOAL : T초가 지난 후 방에 남아있는 미세먼지 양

INFO
	행 : r / 열 : c
	공기청정기 : 2*1 , 항상 1열  가장 윗 행, 아랫 행과 두 칸이상 떨어져 있다.
	6 ≤ R, C ≤ 50, 1 ≤ T ≤ 1,000

SEQUENCE 
	(1) 미세전지 확산 : 상하좌우 4방향
		확산량 : A/5 (int) , 잔존량 : A - 확산량*확산이일어난방향수
		공기청정기/막힌방향으로 확산X
	(2) 공기청정기 작동
		위쪽 공기청정기 : 반시계방향순환
		아래쪽 공기청정기 : 시계방향순환
		=> 바람의 방향대로 미세먼지 한칸씩이동
		공기청정기로 들어간 미세먼지는 소멸

***************************************/

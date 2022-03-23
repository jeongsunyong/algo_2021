//백준_16234_인구이동
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void borderCheck(int x, int y, int** board, int** visited, vector<int*> &unions, int N, int L, int R) {
	if (x > 0) {
		if (abs(board[y][x] - board[y][x - 1]) >= L && abs(board[y][x] - board[y][x - 1]) <= R && visited[y][x-1]==0) {
			int* tmp = new int[2];
			tmp[0] = x-1;
			tmp[1] = y;
			unions.push_back(tmp);
			visited[y][x-1] = 1;
			borderCheck(x - 1, y, board, visited, unions, N, L, R);
		}
	}
	if (y > 0) {
		if (abs(board[y][x] - board[y-1][x]) >= L && abs(board[y][x] - board[y-1][x]) <= R && visited[y-1][x] == 0) {
			int* tmp = new int[2];
			tmp[0] = x;
			tmp[1] = y-1;
			unions.push_back(tmp);
			visited[y-1][x] = 1;
			borderCheck(x, y-1, board, visited, unions, N, L, R);
		}
	}
	if (x < N - 1) {
		if (abs(board[y][x] - board[y][x + 1]) >= L && abs(board[y][x] - board[y][x + 1]) <= R && visited[y][x + 1] == 0) {
			int* tmp = new int[2];
			tmp[0] = x + 1;
			tmp[1] = y;
			unions.push_back(tmp);
			visited[y][x + 1] = 1;
			borderCheck(x + 1, y, board, visited, unions, N, L, R);
		}
	}
	if (y < N - 1) {
		if (abs(board[y][x] - board[y + 1][x]) >= L && abs(board[y][x] - board[y + 1][x]) <= R && visited[y + 1][x] == 0) {
			int* tmp = new int[2];
			tmp[0] = x;
			tmp[1] = y + 1;
			unions.push_back(tmp);
			visited[y + 1][x] = 1;
			borderCheck(x, y + 1, board, visited, unions, N, L, R);
		}
	}
}
int main(void) {
	//init
	int N, L, R;
	cin >> N >> L >> R;

	int** board = new int*[N];
	int** visited = new int*[N];
	for (int i = 0; i < N; i++) {
		board[i] = new int[N];
		visited[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			visited[i][j] = 0;
		}
	}

	int flag = 1;
	int day = 0;
	while (flag) {
		int mv_cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] != 0)
					continue;
				vector<int*> unions;
				visited[i][j] = 1;
				int* tmp = new int[2];
				tmp[0] = j;
				tmp[1] = i;
				unions.push_back(tmp);
				borderCheck(j, i, board, visited, unions, N, L, R);
				int num_unions = unions.size();
				if (num_unions >= 2) {
					mv_cnt++;
					int pop = 0;
					for (int a = 0; a < num_unions; a++) {
						pop+=board[unions[a][1]][unions[a][0]];
					}
					pop /= num_unions;
					for (int a = 0; a < num_unions; a++) {
						board[unions[a][1]][unions[a][0]] = pop;
					}
				}
			}//end for j
		}//end for i
		if (mv_cnt == 0) {
			flag = 0;
		}else {
			day++;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = 0;
			}
		}
	}//end while


	cout << day << endl;
	return 0;
}

/******************************note*********

- GOAL : 인구 수가 주어졌을 때, 인구 이동이 며칠동안 발생하는지 구하는 프로그램 작성
- SEQUENCE : 
		codition : if 두 국가 인구차이 diff >=L && diff <= R 
			(1) 조건 만족 시, 국경선 하루동안 open : 이동시작
			(2) 인접한 칸을 이용해 이동 가능하다면 : 연합
			(3) 연합을 이루는 각 칸 인구수 : 연합인구수 / 연합이루는 칸 개수(소수점:버림)
			(4) 국경선 close

*******************************************8*/

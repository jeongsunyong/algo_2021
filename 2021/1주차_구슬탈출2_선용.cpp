
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

using namespace std;

int min_cnt = 9999;

int tilt_left(char**board, int* cur_r, int* cur_b) //왼쪽 기울이기
{
	int r_x = cur_r[0] - 1, r_y = cur_r[1];
	int b_x = cur_b[0] - 1, b_y = cur_b[1];
	int cross_r = 0, cross_b = 0;


	while (board[b_y][b_x] != '#' && board[b_y][b_x] != 'O')//파란구슬 이동
	{
		if (b_y == r_y && b_x == cur_r[0])
			cross_b = 1;
		b_x--;
	}
	if (board[b_y][b_x] == 'O')
		return -1;

	while (board[r_y][r_x] != '#' && board[r_y][r_x] != 'O')//빨간구슬 이동
	{
		if (b_y == r_y && r_x == cur_b[0])
			cross_r = 1;
		r_x--;
	}
	if (board[r_y][r_x] == 'O')
		return 1;


	if (cur_r[0] == r_x + cross_r)
		return -1;

	cur_r[0] = ++r_x + cross_r;
	cur_b[0] = ++b_x + cross_b;
	return 0;
}
int tilt_right(char**board, int* cur_r, int* cur_b) //오른쪽 기울이기
{
	int r_x = cur_r[0] + 1, r_y = cur_r[1];
	int b_x = cur_b[0] + 1, b_y = cur_b[1];
	int cross_r = 0, cross_b = 0;

	while (board[b_y][b_x] != '#' && board[b_y][b_x] != 'O')
	{
		if (b_y == r_y && b_x == cur_r[0])
			cross_b = 1;
		b_x++;
	}
	if (board[b_y][b_x] == 'O')
		return -1;

	while (board[r_y][r_x] != '#' && board[r_y][r_x] != 'O')
	{
		if (b_y == r_y && r_x == cur_b[0])
			cross_r = 1;
		r_x++;
	}
	if (board[r_y][r_x] == 'O')
		return 1;

	if (cur_r[0] == r_x - cross_r)
		return -1;

	cur_r[0] = --r_x - cross_r;
	cur_b[0] = --b_x - cross_b;
	return 0;
}
int tilt_up(char**board, int* cur_r, int* cur_b)//위쪽 기울이기
{
	int r_x = cur_r[0], r_y = cur_r[1] - 1;
	int b_x = cur_b[0], b_y = cur_b[1] - 1;
	int cross_r = 0, cross_b = 0;

	while (board[b_y][b_x] != '#' && board[b_y][b_x] != 'O')
	{
		if (b_x == r_x && b_y == cur_r[1])
			cross_b = 1;
		b_y--;
	}
	if (board[b_y][b_x] == 'O')
		return -1;

	while (board[r_y][r_x] != '#' && board[r_y][r_x] != 'O')
	{
		if (b_x == r_x && r_y == cur_b[1])
			cross_r = 1;
		r_y--;
	}
	if (board[r_y][r_x] == 'O')
		return 1;

	if (cur_r[1] == r_y + cross_r)
		return -1;

	cur_r[1] = ++r_y + cross_r;
	cur_b[1] = ++b_y + cross_b;
	return 0;
}
int tilt_down(char**board, int* cur_r, int* cur_b)//아래쪽 기울이기
{
	int r_x = cur_r[0], r_y = cur_r[1] + 1;
	int b_x = cur_b[0], b_y = cur_b[1] + 1;
	int cross_r = 0, cross_b = 0;

	while (board[b_y][b_x] != '#' && board[b_y][b_x] != 'O') 
	{
		if (b_x == r_x && b_y == cur_r[1])
			cross_b = 1;
		b_y++;
	}
	if (board[b_y][b_x] == 'O')
		return -1;

	while (board[r_y][r_x] != '#' && board[r_y][r_x] != 'O')
	{
		if (b_x == r_x && r_y == cur_b[1])
			cross_r = 1;
		r_y++;
	}
	if (board[r_y][r_x] == 'O')
		return 1;

	if (cur_r[1] == r_y - cross_r)
		return -1;

	cur_r[1] = --r_y - cross_r;
	cur_b[1] = --b_y - cross_b;
	return 0;
}

void simulation(char**board, int* cur_r, int* cur_b, int prev_rx, int prev_ry, int prev_bx, int prev_by, int cnt)
{
	if (min_cnt == 1 || cnt > 10)
		return;

	int cur_rx = cur_r[0]; int cur_ry = cur_r[1];
	int cur_bx = cur_b[0]; int cur_by = cur_b[1];
	//cur_r[좌우][상하]
	if ((board[cur_r[1]][cur_r[0] + 1] != '#'  && prev_rx - cur_rx <= 0) ||
		(board[cur_b[1]][cur_b[0] + 1] != '#'  && prev_bx - cur_bx <= 0))//오른쪽 
	{
		int flag = 0;
		flag = tilt_right(board, cur_r, cur_b);
		switch (flag)
		{
		case 0:
			prev_rx = cur_rx;
			prev_ry = cur_ry;
			prev_bx = cur_bx;
			prev_by = cur_by;
			simulation(board, cur_r, cur_b, prev_rx, prev_ry, prev_bx, prev_by, cnt + 1);
			cur_r[0] = cur_rx, cur_r[1] = cur_ry;
			cur_b[0] = cur_bx, cur_b[1] = cur_by;
			break;
		case 1:
			if (min_cnt > cnt)
				min_cnt = cnt;
			break;
		default:
			break;
		}
		if (min_cnt == 1)
			return;

	}
	if ((board[cur_r[1]][cur_r[0] - 1] != '#' && prev_rx - cur_rx >= 0) ||
		(board[cur_b[1]][cur_b[0] - 1] != '#' && prev_bx - cur_bx >= 0))//왼쪽
	{
		int flag = 0;
		flag = tilt_left(board, cur_r, cur_b);
		switch (flag)
		{
		case 0:
			prev_rx = cur_rx;
			prev_ry = cur_ry;
			prev_bx = cur_bx;
			prev_by = cur_by;
			simulation(board, cur_r, cur_b, prev_rx, prev_ry, prev_bx, prev_by, cnt + 1);
			cur_r[0] = cur_rx, cur_r[1] = cur_ry;
			cur_b[0] = cur_bx, cur_b[1] = cur_by;
			break;
		case 1:
			if (min_cnt > cnt)
				min_cnt = cnt;
			break;
		default:
			break;
		}
		if (min_cnt == 1)
			return;
	}
	if ((board[cur_r[1] + 1][cur_r[0]] != '#' && prev_ry - cur_ry <= 0) ||
		(board[cur_b[1] + 1][cur_b[0]] != '#' && prev_by - cur_by <= 0))//아래쪽
	{
		int flag = 0;
		flag = tilt_down(board, cur_r, cur_b);

		switch (flag)
		{
		case 0:
			prev_rx = cur_rx;
			prev_ry = cur_ry;
			prev_bx = cur_bx;
			prev_by = cur_by;
			simulation(board, cur_r, cur_b, prev_rx, prev_ry, prev_bx, prev_by, cnt + 1);
			cur_r[0] = cur_rx, cur_r[1] = cur_ry;
			cur_b[0] = cur_bx, cur_b[1] = cur_by;
			break;
		case 1:
			if (min_cnt > cnt)
				min_cnt = cnt;
			break;
		default:
			break;
		}
		if (min_cnt == 1)
			return;
	}
	if ((board[cur_r[1] - 1][cur_r[0]] != '#' && prev_ry - cur_ry >= 0) ||
		(board[cur_b[1] - 1][cur_b[0]] != '#' && prev_by - cur_by >= 0))//위쪽
	{
		int flag = 0;
		flag = tilt_up(board, cur_r, cur_b);
		switch (flag)
		{
		case 0:
			prev_rx = cur_rx;
			prev_ry = cur_ry;
			prev_bx = cur_bx;
			prev_by = cur_by;
			simulation(board, cur_r, cur_b, prev_rx, prev_ry, prev_bx, prev_by, cnt + 1);
			cur_r[0] = cur_rx, cur_r[1] = cur_ry;
			cur_b[0] = cur_bx, cur_b[1] = cur_by;
			break;
		case 1:
			if (min_cnt > cnt)
				min_cnt = cnt;
			break;
		default:
			break;
		}
		if (min_cnt == 1)
			return;
	}

}
void findRB(char** board, int* r, int* b, int M, int N)//위치 초기화
{
	for (int i = 1; i < M - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			switch (board[i][j])
			{
			case 'R':
				r[0] = j;
				r[1] = i;
				break;
			case 'B':
				b[0] = j;
				b[1] = i;
				break;
			default:
				break;
			}
		}
	}
}

int main(void)
{
	int M = 0, N = 0;
	scanf("%d %d", &M, &N); //N : 세로(행) , M :가로(열)
	char** board = new char*[M];
	for (int i = 0; i < M; i++)
	{
		board[i] = new char[N];
		scanf("%s", board[i]);
	}

	min_cnt = 9999;
	int cur_r[2] = { 0 };// 0:열넘버(x) , 1:행넘버(y)
	int cur_b[2] = { 0 };
	int hole[2] = { 0 };
	findRB(board, cur_r, cur_b, M, N);
	simulation(board, cur_r, cur_b, cur_r[0], cur_r[1], cur_b[0], cur_b[1], 1);

	if (min_cnt > 10)
		min_cnt = -1;

	cout << min_cnt << endl;
	return 0;
}

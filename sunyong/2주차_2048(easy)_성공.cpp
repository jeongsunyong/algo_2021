#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


void copy_array(int** src, int** dst, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dst[i][j] = src[i][j];
		}
	}
}

int move_left(int** board, int** board_l, int N)
{
	int maxval = 0;
	for (int i = 0; i < N; i++)//행인덱스
	{
		int idx = 0;
		for (int j = 0; j < N; j++)//열인덱스
		{
			if (board[i][j] == 0)
				continue;
			int cnt = 1;
			int zero = 0;
			for (int k = j+1; k < N; k++)//현재대상 같은 수 (merge가능한지)조사
			{
				if (board[i][j] == board[i][k])
				{
					cnt++;
				}
				else if (board[i][k] == 0)
				{
					zero++;
				}
				else
					break;
			}
			for (int k = 0; k < cnt / 2; k++)//같은 수 있다면 merge된값 삽입
			{
				board_l[i][idx] = board[i][j] * 2;
				if (board_l[i][idx] > maxval)
					maxval = board_l[i][idx];
				idx++;
			}
			if (cnt % 2 == 1)//같은 수 홀수개일경우 한 값은 원래값으로들어감 
			{
				board_l[i][idx] = board[i][j];
				if (board_l[i][idx] > maxval)
					maxval = board_l[i][idx];
				idx++;
			}
			j = j + cnt +zero - 1;

		}
		while (idx < N)
		{
			board_l[i][idx] = 0;
			idx++;
		}
	}
	return maxval;
}
int move_right(int** board, int** board_r, int N)
{
	int maxval = 0;
	for (int i = N-1; i>=0; i--)//행인덱스
	{
		int idx = N-1;
		for (int j = N-1 ; j >=0; j--)//열인덱스
		{
			if (board[i][j] == 0)
				continue;
			int cnt = 1;
			int zero = 0;
			for (int k = j - 1; k >= 0; k--)//현재대상 같은 수 (merge가능한지)조사
			{
				if (board[i][j] == board[i][k])
				{
					cnt++;
				}
				else if (board[i][k] == 0)
				{
					zero++;
				}
				else
					break;
			}
			for (int k = 0; k < cnt / 2; k++)//같은 수 있다면 merge된값 삽입
			{
				board_r[i][idx] = board[i][j] * 2;
				if (board_r[i][idx] > maxval)
					maxval = board_r[i][idx];
				idx--;
			}
			if (cnt % 2 == 1)//같은 수 홀수개일경우 한 값은 원래값으로들어감 
			{
				board_r[i][idx] = board[i][j];
				if (board_r[i][idx] > maxval)
					maxval = board_r[i][idx];
				idx--;
			}
			j = j - cnt - zero + 1;

		}
		while (idx >= 0)
		{
			board_r[i][idx] = 0;
			idx--;
		}
	}
	return maxval;
}
int move_up(int** board, int** board_u, int N)
{
	int maxval = 0;
	for (int j = 0; j < N; j++)//행인덱스
	{
		int idx = 0;
		for (int i = 0; i < N; i++)//열인덱스
		{
			if (board[i][j] == 0)
				continue;
			int cnt = 1;
			int zero = 0;
			for (int k = i + 1; k < N; k++)//현재대상 같은 수 (merge가능한지)조사
			{
				if (board[i][j] == board[k][j])
				{
					cnt++;
				}
				else if (board[k][j] == 0)
				{
					zero++;
				}
				else
					break;
			}
			for (int k = 0; k < cnt / 2; k++)//같은 수 있다면 merge된값 삽입
			{
				board_u[idx][j] = board[i][j] * 2;
				if (board_u[idx][j] > maxval)
					maxval = board_u[idx][j];
				idx++;
			}
			if (cnt % 2 == 1)//같은 수 홀수개일경우 한 값은 원래값으로들어감 
			{
				board_u[idx][j] = board[i][j];
				if (board_u[idx][j] > maxval)
					maxval = board_u[idx][j];
				idx++;
			}
			i = i + cnt + zero - 1;

		}
		while (idx < N)
		{
			board_u[idx][j] = 0;
			idx++;
		}
	}
	return maxval;

}
int move_down(int** board, int** board_d, int N)
{
	int maxval = 0;
	for (int j = N-1; j >= 0; j--)//행인덱스
	{
		int idx = N-1;
		for (int i = N-1; i >= 0; i--)//열인덱스
		{
			if (board[i][j] == 0)
				continue;
			int cnt = 1;
			int zero = 0;
			for (int k = i - 1; k >= 0; k--)//현재대상 같은 수 (merge가능한지)조사
			{
				if (board[i][j] == board[k][j])
				{
					cnt++;
				}
				else if (board[k][j] == 0)
				{
					zero++;
				}
				else
					break;
			}
			for (int k = 0; k < cnt / 2; k++)//같은 수 있다면 merge된값 삽입
			{
				board_d[idx][j] = board[i][j] * 2;
				if (board_d[idx][j] > maxval)
					maxval = board_d[idx][j];
				idx--;
			}
			if (cnt % 2 == 1)//같은 수 홀수개일경우 한 값은 원래값으로들어감 
			{
				board_d[idx][j] = board[i][j];
				if (board_d[idx][j] > maxval)
					maxval = board_d[idx][j];
				idx--;
			}
			i = i - cnt - zero + 1;

		}
		while (idx >= 0)
		{
			board_d[idx][j] = 0;
			idx--;
		}
	}
	return maxval;
}


int simulation(int** board, int N, int depth)
{
	depth++;
	int **board_copy = new int*[N];// 있어야 할 이유
	int **board_l = new int*[N];
	int **board_r = new int*[N];
	int **board_u = new int*[N];
	int **board_d = new int*[N];
	for (int i = 0; i < N; i++)
	{
		board_copy[i] = new int[N];
		board_l[i] = new int[N];
		board_r[i] = new int[N];
		board_u[i] = new int[N];
		board_d[i] = new int[N];
	}
	copy_array(board, board_copy, N);
	copy_array(board, board_l, N);
	copy_array(board, board_r, N);
	copy_array(board, board_u, N);
	copy_array(board, board_d, N);

	int m1, m2, m3, m4;
	m1=move_left(board_copy,board_l,N);
	m2=move_right(board_copy,board_r,N);
	m3=move_up(board_copy,board_u,N);
	m4=move_down(board_copy,board_d,N);

	int maxm = (((m3 > m4) ? m3 : m4) > ((m1 > m2) ? m1 : m2)) ?
		((m3 > m4) ? m3 : m4) : ((m1 > m2) ? m1 : m2);


	if (depth < 5)
	{
		m1=simulation(board_l, N, depth);
		m2=simulation(board_r, N, depth);
		m3=simulation(board_u, N, depth);
		m4=simulation(board_d, N, depth);
		int maxm2 = (((m3 > m4) ? m3 : m4) > ((m1 > m2) ? m1 : m2)) ?
			((m3 > m4) ? m3 : m4) : ((m1 > m2) ? m1 : m2);

		return ((maxm>maxm2)?maxm:maxm2);
	}
	if (depth == 5)
		return maxm;

}

int main(void)
{
	//메모리 초기화 및 예제 입력부
	int N;
	scanf("%d", &N);
	int** board = new int*[N];
	for (int i = 0; i < N; i++)
	{
		board[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &board[i][j]);
		}
	}

	int max_block = 0;
	//5회 simulate
	//상하좌우 네 방향 중 한 방향으로 이동, 같을 값을 갖는 경우 merge
	//같은 값 3개 이상 존재 시 이동 방향쪽이 우선merge,
	max_block = simulation(board,N,0);
	cout << max_block << endl;
	//simulation 5회시 최대 블럭값 
	

	return 0;

}

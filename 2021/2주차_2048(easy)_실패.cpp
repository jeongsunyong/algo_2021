//통과 X

#include <iostream>
#include <algorithm>

using namespace std;

int simulation(int N, int*board,int cnt)
{
	cnt++;

	int** boards_4 = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		boards_4[i] = new int[N*N+1];
	}
	int* board_origin = new int[N*N+1];
	copy(board, board + (N * N), board_origin);

	int direction[] = { N,1,1,N };

	for (int t = 0; t <= 2; t = t + 2)//t:0,1 : left,right t 2,3 : up,down 
	{
		int x = direction[t];
		int y = direction[t + 1];
		copy(board_origin, board_origin + (N * N), board);

		for (int i = 0; i < N; i++)//열단위
		{
			//////////////////////////////////////////////////////////////////////////////////////////////////////숫자merge
			int cur = -1;
			int pre = -1;
			int pre_idx = -1;
			int cur_idx = -1;
			int recent = 0;

			for (int j = 0; j < N; j++)
			{
				if (board[i*x + j * y] != 0)//이전&현재 값,인덱스 갱신
				{
					pre_idx = cur_idx;
					pre = cur;
					cur_idx = i * x + j * y;
					cur = board[cur_idx];
				}
				if (cur == pre && pre != -1 && board[i*x + j * y] != 0)//현재값과 이전값이 같다면 (!=0)
				{
					if (recent == 0)//최근 병합 기록 X -> 병합
					{
						board[i*x + j * y] = cur + pre;
						board[pre_idx] = -1;//현재 블록에 값을 합치고 이전 블록은 -1로 표시
						recent = 1;
					}
					else //최근 병합했고, 현재값과 이전 값이 같다면 병합기록 초기화
						recent = 0;
				}
				else if (pre != cur && recent == 1 && cur != -1)//그외 상관 없는 다른 숫자 나오면 병합기록 초기화
					recent = 0;
			}

			////////////////////////////////////////////////////////merge결과정렬(행 단위로)
			int idx = N;
			int stat = 0;
			int swaped = 0;

            //기존 숫자 병합을 0인덱스 -> N인덱스 기준(left to right 혹은 up to down)★
			for (int j = N - 1; j >= 0; j--)//자리정리 (l->r) //right로 정렬하기.(down으로 정렬하기)
			{//j : 현재 정렬되지 않은 board 훑기. , idx : boards_4[]에 정렬될 인덱스.
				if (board[i*x + j * y] == 0)//0:패스
				{
					continue;
				}
				else if (board[i*x + j * y] == -1 )//-1 일 때(병합되었음)
				{
					if (stat == 2 && boards_4[t][i*x + (idx + 1)*y] * 2 == boards_4[t][i*x + (idx)*y]) //status : 이전 블록 존재 여부
					{//이전 두 개의 블록이 2배의 차이인지 조사( 0 -> N인덱스 기준에서는 2 2 2-> -1 4 2가 되므로 2 4로 바꿔줘야함)
						boards_4[t][i*x + (idx)*y] = boards_4[t][i*x + (idx + 1)*y];
						boards_4[t][i*x + (idx + 1)*y] = boards_4[t][i*x + (idx + 1)*y] * 2; //두 블럭 숫자 바꿔줌
						swaped = 1;//바꿔줌 표시
					}
					stat--;
				}
				else //숫자일 때 : idx:블럭이 들어갈 위치에 숫자 넣어줌
				{
					idx--;
					boards_4[t][i*x + idx * y] = board[i*x + j * y];
					if (swaped == 1 && stat == 2)//이전에 바뀐 기록 있고 이전블록 2개 존재한다면(swap 이후 1개의 블럭 추가) swap기록 초기화
					{
						swaped = 0;
					}
					if (stat <= 1)// 나온 블럭 갯수 2개까지 표시
						stat++;

				}
			}
			while (idx > 0)//블럭 정렬 후 빈자리 0으로 채움.
			{
				idx--;
				boards_4[t][i*x + idx * y] = 0;
			}

			idx = 0;
			for (int j = 0; j < N; j++)//자리정리(r->l) //left로 정렬하기 (up으로 정렬하기)
			{
				if (board[i*x + j * y] != 0 && board[i*x + j * y] != -1) //r->l기준으로 병합했으므로 순차적으로 -1 , 0 제외하고 넣어줌
				{
					boards_4[t + 1][i*x + idx * y] = board[i*x + j * y];
					idx++;
				}

			}
			while (idx < N)//블로ㅓㄱ 정렬 후 빈자리 0으로 채움 
			{
				boards_4[t + 1][i*x + idx * y] = 0;
				idx++;
			}
		}
	}

	int curmax = 0;//현재 최대 값
	/////////////////
	if (cnt < 5)//5 이전까지는 다음 4방향 simulation 후 최대값 중 최대값 선택해 return
	{
		for (int i = 0; i < 4; i++)
		{
			int premax = simulation(N, boards_4[i], cnt);
			if (premax > curmax)
				curmax = premax;
		}
	}
	if (cnt == 5)//5일때는 현재 simulation left / down중 최대값 전달
	{
		for (int i = 0; i < N*N; i++)
		{
			int tmp = (boards_4[0][i] > boards_4[2][i]) ? boards_4[0][i] : boards_4[2][i];
			if (tmp > curmax)
			{
				curmax = tmp;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		delete[] boards_4[i];
	}
	delete[] boards_4;

	return curmax;

}


int main(void)
{
	int N = 0;
	scanf("%d", &N);

	int* board = new int[N*N+1];
	int* board_origin = new int[N*N+1];
	for (int i = 0; i < N*N; i++)
	{
		scanf("%d", &board[i]);
	}

	cout<<simulation(N, board, 0);
	
	return 0;
}

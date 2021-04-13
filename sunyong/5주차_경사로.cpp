#include <stdio.h>
#include <iostream>

using namespace std;

int main(void)
{
	int N = 0, L = 0;

	cin >> N >> L;
	int** map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}

	int road = 0;

	//x방향
	for (int i = 0; i < N; i++)
	{
		int cnt = 0; //같은거 카운트
		int conseq = 1; //연속 플래그
		int reverse = 0; // 역(높은숫자->낮은숫자)
		int h = map[i][0]; //높이
		for (int j = 0; j < N; j++)
		{

			if (map[i][j] == h)//같으면 갯수++
			{
				cnt++;
			}
			else if (map[i][j] == h + 1 && cnt >= L && reverse==0)//높은 레벨로 갈 때 경사로 가능판단
			{
				h = h + 1;
				cnt = 1;
			}
			else if (map[i][j] == h - 1 && (reverse == 0 || (reverse == 1 && cnt >= L)))//낮은레벨로 갈 때 경사로 가능 판단
			{
				h = h - 1;
				cnt = 1;
				reverse = 1;
			}
			else
			{
				conseq = 0;
				break;
			}

			if (reverse == 1 && cnt >= L)//역으로 갔을 때 경사로 설치
			{
				reverse = 0;
				cnt = 0; //중복 놓지 못하므로 cnt=0으로 초기화해줌
			}
		}

		if (reverse == 1)
			conseq = 0;

		if (conseq == 1)
			road++;
	}

	//y방향
	for (int i = 0; i < N; i++)
	{
		int cnt = 0;
		int conseq = 1;
		int reverse = 0;
		int h = map[0][i];
		for (int j = 0; j < N; j++)
		{
			if (map[j][i] == h)
			{
				cnt++;
			}
			else if (map[j][i] == h + 1 && cnt >= L && reverse == 0)
			{
				h = h + 1;
				cnt = 1;
			}
			else if (map[j][i] == h - 1 && (reverse == 0 || (reverse == 1 && cnt >= L)))
			{
				h = h - 1;
				cnt = 1;
				reverse = 1;
			}
			else
			{
				conseq = 0;
				break;
			}

			if (reverse == 1 && cnt >= L)
			{
				reverse = 0;
				cnt = 0;
			}
		}

		if (reverse == 1)
			conseq = 0;

		if (conseq == 1)
			road++;
	}

	cout << road << endl;
}

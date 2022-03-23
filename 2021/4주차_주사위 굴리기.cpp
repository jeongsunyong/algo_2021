#include <iostream>

using namespace std;

int main(void)
{
	int M = 0, N = 0; //가로(열)M 세로(행)N
	int x = 0, y = 0; //x:북남(행) y동서(열)
	int k = 0;

	cin >> N >> M >>x >>y >>k;
	int* map = new int[N*M];
	int* command = new int[k];
	for (int i = 0; i < N; i++)//지도 입력, 북->남, 서->동 순으로 주어짐, <=10
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[M*i + j];
		}
	}

	for (int i = 0; i < k; i++)
	{
		cin >> command[i];
	}

	int dice[3][3] = { {0,0,0},{0,0,0},{0,0,0}};
	int dice_back = 0;

	for (int i = 0; i < k; i++)
	{
		int dx = 0;
		int dy = 0;
		switch (command[i]) { //command - > 이동 방향
		case 1:
			dy = 1;
			break;
		case 2:
			dy = -1;
			break;
		case 3:
			dx = -1;
			break;
		case 4:
			dx = 1;
			break;
		}
		
		if (dx + x < 0 || dx + x >= N || dy + y < 0 || dy + y >= M)
		{
			continue;
		} //범위 넘어가면 무시
        
		x += dx;
		y += dy;
		int tmp = 0;
		if (dy == 1) { //roll_e (동)
			tmp = dice_back;
			dice_back = dice[1][2];
			dice[1][2] = dice[1][1];
			dice[1][1] = dice[1][0];
			dice[1][0] = tmp;
		}
		else if (dy == -1) { //roll_w (서)
			tmp = dice_back;
			dice_back = dice[1][0];
			dice[1][0] = dice[1][1];
			dice[1][1] = dice[1][2];
			dice[1][2] = tmp;
		}
		else if (dx == 1) {//roll_s (남)
			tmp = dice_back;
			dice_back = dice[2][1];
			dice[2][1] = dice[1][1];
			dice[1][1] = dice[0][1];
			dice[0][1] = tmp;
		}
		else if (dx == -1) {//roll_n (북)
			tmp = dice_back;
			dice_back = dice[0][1];
			dice[0][1] = dice[1][1];
			dice[1][1] = dice[2][1];
			dice[2][1] = tmp;
		}

		if (map[x*M + y] == 0)//0일때
		{
			map[x*M + y] = dice_back;
		}
		else //0 아닐때
		{
			dice_back = map[x*M + y];
			map[x*M + y] = 0;
		}
		cout << dice[1][1] << endl;//front출력
	}
	return 0;
}

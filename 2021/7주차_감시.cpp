#include <iostream>
#include <vector>
using namespace std;

class CCTV
{
public:
	int pos_x;
	int pos_y;
	int type;
	int rot_times;
	CCTV(int x, int y, int t)
	{
		pos_x = x;
		pos_y = y;
		type = t;
		if (t == 1 || t == 3 || t == 4)
			rot_times = 4;
		else if (t == 2)
			rot_times = 2;
		else if (t == 5)
			rot_times = 1;
	}
};
int** copyroom(int** room, int N, int M)
{
	int** nextroom = new int*[N];
	for (int i = 0; i < N; i++)
	{
		nextroom[i] = new int[M];
		for (int j = 0; j < M; j++)
		{
			nextroom[i][j] = room[i][j];
		}
	}
	return nextroom;
}

int search(int** room, vector<CCTV> cctv_list, int N, int M, int cnum)
{
	int minimum = 9999;

	int i = cnum;
	for (int j = 0; j < cctv_list[i].rot_times; j++)
	{
		int c_x = cctv_list[i].pos_x;
		int c_y = cctv_list[i].pos_y;

		int** room_next = copyroom(room, N, M);
		//상
		if (cctv_list[i].type == 5 ||
			(cctv_list[i].type == 1 && j == 0) ||
			(cctv_list[i].type == 2 && j == 0) ||
			(cctv_list[i].type == 4 && j != 0) ||
			(cctv_list[i].type == 3 && (j == 0 || j == 3))
			)
		{
			for (int y = c_y-1; y >= 0; y--)
			{
				if (room_next[y][c_x] == 6)
					break;
				else if (room_next[y][c_x] == 0)
					room_next[y][c_x] = -1;
			}
		}
		//하
		if (cctv_list[i].type == 5 ||
			(cctv_list[i].type == 1 && j == 1) ||
			(cctv_list[i].type == 2 && j == 0) ||
			(cctv_list[i].type == 4 && j != 1) ||
			(cctv_list[i].type == 3 && (j == 1 || j == 2))
			)
		{
			for (int y = c_y+1; y < N; y++)
			{
				if (room_next[y][c_x] == 6)
					break;
				else if (room_next[y][c_x] == 0)
					room_next[y][c_x] = -1;
			}
		}
		//좌
		if (cctv_list[i].type == 5 ||
			(cctv_list[i].type == 1 && j == 2) ||
			(cctv_list[i].type == 2 && j == 1) ||
			(cctv_list[i].type == 4 && j != 2) ||
			(cctv_list[i].type == 3 && (j == 2 || j == 3))
			)
		{
			for (int x = c_x-1; x >= 0; x--)
			{
				if (room_next[c_y][x] == 6)
					break;
				else if (room_next[c_y][x] == 0)
					room_next[c_y][x] = -1;
			}

		}
		//우
		if (cctv_list[i].type == 5 ||
			(cctv_list[i].type == 1 && j == 3) ||
			(cctv_list[i].type == 2 && j == 1) ||
			(cctv_list[i].type == 4 && j != 3) ||
			(cctv_list[i].type == 3 && (j == 0 || j == 1))
			)
		{
			for (int x = c_x+1; x < M; x++)
			{
				if (room_next[c_y][x] == 6)
					break;
				else if (room_next[c_y][x] == 0)
					room_next[c_y][x] = -1;
			}
		}

		//현재 rot 상태에서 minimum값
		int min_region = 0;
		for (int a = 0; a < N; a++)
		{
			for (int b = 0; b < M; b++)
			{
				if (room_next[a][b] == 0)
					min_region++;
			}
		}

		if (min_region < minimum)
		{
			minimum = min_region;
		}

		if (cnum < cctv_list.size() - 1)
		{
			min_region = 9999;
			//다른 카메라들 rot한 minimum값들 조사
			min_region = search(room_next, cctv_list, N, M, cnum + 1);
			if (min_region < minimum)
			{
				minimum = min_region;
			}
		}
	}
	return minimum;
}

int main(void)
{
	int N, M;
	cin >> N >> M;
	int** room = new int*[N];
	for (int i = 0; i < N; i++)
	{
		room[i] = new int[M];
	}

	vector<CCTV> cctv_list;
	int cam_cnt = 0;
  int minimum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> room[i][j];
			if (room[i][j] >= 1 && room[i][j] <= 5)
			{
				cctv_list.push_back(CCTV(j, i, room[i][j]));
				cam_cnt++;
			}
      if (room[i][j] == 0)
				minimum++;
		}
	}

	if(cam_cnt!=0)
	{
		minimum = search(room, cctv_list, N, M, 0);
	}
	cout << minimum << endl;

	return 0;

}

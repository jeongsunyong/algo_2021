#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <math.h>
#define pi 3.141592

using namespace std;
typedef struct rot
{
	int t;
	char d;
}rot;

class pos
{
public:
	int x;
	int y;
	pos(int posx = 0, int posy = 0)
	{
		x = posx;
		y = posy;
	}
};

int main(void)
{
	int N = 0, K = 0, L = 0;

	scanf("%d", &N);//보드의크기
	scanf("%d", &K);//사과의개수
	int** board = new int*[N];//보드생성
	for (int i = 0; i < N; i++)
	{
		board[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < K; i++)//사과입력
	{
		int apple_x = 0, apple_y = 0;
		scanf("%d %d", &apple_y, &apple_x);
		board[apple_y-1][apple_x-1] = 1;
	}// board: 0:빈공간 1:사과


	scanf("%d", &L);//방향 변환 횟수
	rot* change_direction;
	change_direction = new rot[L];
	for (int i = 0; i < L; i++)
	{
		scanf("%d %c", &change_direction[i].t, &change_direction[i].d);
	}
  
	int tmp_x = 0, tmp_y = 0;
	int idx_cd = 0;
	float theta = 90 * (pi / 180);
	int cur_t = 0;
	vector<pos> snake;
	pos cur_d(1, 0);//초기값 right
	snake.push_back(pos(0, 0));//초기뱀의위치
  
	while (1)
	{
		cur_t++;

		int idx_x = snake.back().x + cur_d.x;
		int idx_y = snake.back().y + cur_d.y;
		if (idx_x >= N || idx_x < 0 || idx_y >= N || idx_y < 0) //벽에닿는경우
		{
			break;
		}
		if (board[idx_y][idx_x] == -1)//자신의 몸에 닿는 경우
		{
			break;
		}

		if (board[idx_y][idx_x] == 0)//아무것도 없는경우
		{
			board[idx_y][idx_x] = -1;
			snake.push_back(pos(idx_x, idx_y));
			board[snake.front().y][snake.front().x] = 0;
			snake.erase(snake.begin());
		}
		else if (board[idx_y][idx_x] == 1)
		{
			board[idx_y][idx_x] = -1;
			snake.push_back(pos(idx_x, idx_y));
		}
        
		if (change_direction[idx_cd].t == cur_t)//방향변환
		{
			switch (change_direction[idx_cd].d) {
			case 'L':
				tmp_x = int(cos(-theta)*cur_d.x - sin(-theta)*cur_d.y); //-90도회전(왼쪽)
				tmp_y = int(sin(-theta)*cur_d.x + cos(-theta) * cur_d.y);
				cur_d.x = tmp_x; 
				cur_d.y = tmp_y;
				break;
			case 'D':
				tmp_x = int(cos(theta)*cur_d.x - sin(theta)*cur_d.y);//90도회전(오른쪽)
				tmp_y = int(sin(theta)*cur_d.x + cos(theta) * cur_d.y);
				cur_d.x = tmp_x;
				cur_d.y = tmp_y;
				break;
			default:
				break;
			}
			idx_cd++;
		}
	}
	cout << cur_t << endl;
	return 0;
}

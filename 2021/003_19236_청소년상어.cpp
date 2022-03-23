//2021_07_18 / 19236_청소년상어
#include <iostream>
#include <vector>

using namespace std;
int d_x[8] = { 0,-1,-1,-1,0,1,1,1 };
int d_y[8] = { -1,-1,0,1,1,1,0,-1 };

int simulation(int** board, int* d, int cur_x, int cur_y, int cur_n, int cur_d) {
	
	int** fish_list = new int*[16];
	for (int i = 0; i < 16; i++) {
		fish_list[i] = new int[2]; //x,y
		fish_list[i][0] = -1;
		fish_list[i][1] = -1;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { //-1,-1 : eaten
			if (board[i][j] == -1)
				continue;
			fish_list[board[i][j]][0] = j;
			fish_list[board[i][j]][1] = i;
		}
	}

	//1.고기먹기
	int fish_to_eat = board[cur_y][cur_x];
	cur_d = d[fish_to_eat];
	cur_n += fish_to_eat+1;
	fish_list[fish_to_eat][0] = -1;
	fish_list[fish_to_eat][1] = -1;
	board[cur_y][cur_x] = -1;

	//2.물고기 이동 : 작은 순서대로.
	for (int i = 0; i < 16; i++){
		int x = fish_list[i][0];
		int y = fish_list[i][1];
		if (x == -1)
			continue;
		int n = i;
		int d_num = d[n];

		d_num = d_num - 1;
		for(int j=0;j<=8;j++){
			d_num = (d_num + 1) % 8;
			int dx = d_x[d_num];
			int dy = d_y[d_num];
			if (dx+x >= 4 || dx+x < 0 || dy+y >= 4 || dy+y < 0) //1.board out case
				continue;
			if (dx + x == cur_x && dy + y == cur_y) //2. shark case
				continue;

			int x_aft = x + dx;
			int y_aft = y + dy;

			board[y][x] = board[y_aft][x_aft];//두 물고기 혹은 빈칸과 물고기 위치switch
			board[y_aft][x_aft] = n;
				
			d[n] = d_num;//새 방향 갱신
			fish_list[n][0] = x_aft; fish_list[n][1] = y_aft;
			if (board[y][x] != -1) {
				fish_list[board[y][x]][0] = x; fish_list[board[y][x]][1] = y;
			}
				
			break;
		}

	}
	
	//3.상어 이동
	//cur_d : 상어의 현 방향
	//cur_x & cur_y : 상어 현 x,y 좌표
	//cur_n : 상어 현재 point
	int dx = d_x[cur_d];
	int dy = d_y[cur_d];

	//*1 //*2 //*3 case 계산
	int max_result = cur_n;
	for (int i = 1; i < 4; i++) {
		if (cur_x + dx*i >= 4 || cur_x + dx*i < 0 || cur_y + dy*i >= 4 || cur_y + dy*i < 0) { 
			if (i == 1) { //이동불가케이스
				return cur_n;
			}else
				break;
		}
		if (board[cur_y + dy * i][cur_x + dx * i] == -1) //empty case
			continue;

		//이동 가능 시,
		int** board_copy = new int*[4];
		for (int a = 0; a < 4; a++) {
			board_copy[a] = new int[4];
			for (int b = 0; b < 4; b++) {
				board_copy[a][b] = board[a][b];
			}
		}

		int* d_copy = new int[16];
		for (int a = 0; a < 16; a++) {
			d_copy[a] = d[a];
		}
		int result = simulation(board_copy, d_copy, cur_x + dx*i, cur_y + dy*i, cur_n, cur_d);
		if (result > max_result)
			max_result = result;
	}

	return max_result;
};

int main(void) {

	int** board = new int*[4];
	for (int i = 0; i < 4; i++) {
		board[i] = new int[4];
	}


	int* d= new int[16]; //물고기 idx : 0 - 15
	int dir_tmp = -1;
	int num_tmp = -1;
	for (int i = 0; i < 16; i++) {
		cin >> num_tmp;
		cin >> dir_tmp;
		num_tmp--;
		dir_tmp--;
		//direction배열
		d[num_tmp] = dir_tmp; //어떤 숫자가 어떤 방향과 매핑되는지
		//board배치
		board[int(i / 4)][i % 4] = num_tmp;

	}

	int result = simulation(board,d, 0,0,0,0);
	cout << result << endl;
	
}

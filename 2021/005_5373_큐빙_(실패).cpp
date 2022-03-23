//210726 백준_5373_큐빙 : 실패
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

char color[6] = { 'w','y','r','o','g','b'};
				// 0,  1,  2,  3,  4,  5

void cube_init(int n, int cube[6][3][3], int** direction);
void rotation(int** direction, int i, int cube[6][3][3]);
void rot_round(int d, int v, int cube[6][3][3]);
void cubing(int n, int cube[6][3][3], int** direction);
vector<int> print_upside(vector<int> result, int cube[6][3][3]);

int main(void) {
	int t;//testcase갯수
	cin >> t;
	vector<int> result;
	for (int a = 0; a < t; a++) {
		int n = 0;
		int cube[6][3][3] = {
			{//0 : U (white)
				{0,0,0},{0,0,0},{0,0,0}
			},
			{//1 : D (yellow)
				{1,1,1},{1,1,1},{1,1,1}
			},
			{//2 : F (red)
				{2,2,2},{2,2,2},{2,2,2}
			},
			{//3 : B (orange)
				{3,3,3},{3,3,3},{3,3,3}
			},
			{//4 : l (green)
				{4,4,4},{4,4,4},{4,4,4}
			},
			{//5 : r (blue)
				{5,5,5},{5,5,5},{5,5,5}
			},
		};
		cin >> n;
		int** direction = new int*[n];
		cube_init(n, cube, direction);

		cubing(n, cube, direction);
		result = print_upside(result,cube);
	}
	for (int a = 0; a < result.size(); a++) {
		cout << color[result[a]];
		if ((a+1) % 3 == 0 && a != 0)
			cout << endl;
	}
}

vector<int> print_upside(vector<int> result,int cube[6][3][3]) {
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			result.push_back(cube[0][a][b]);
		}
	}
	return result;
};
void rot_round(int d, int v, int cube[6][3][3]) {
	int tmp[3] = { 0,0,0 };
	switch (d) {
	case 0: //2/5/3/4
		if (v == 1) {
			tmp[0] = cube[2][0][0], tmp[1] = cube[2][0][1], tmp[2] = cube[2][0][2];
			cube[2][0][0] = cube[5][0][0], cube[2][0][1] = cube[5][0][1], cube[2][0][2] = cube[5][0][2];
			cube[5][0][0] = cube[3][0][0], cube[5][0][1] = cube[3][0][1], cube[5][0][2] = cube[3][0][2];
			cube[3][0][0] = cube[4][0][0], cube[3][0][1] = cube[4][0][1], cube[3][0][2] = cube[4][0][2];
			cube[4][0][0] = tmp[0], cube[4][0][1] = tmp[1], cube[4][0][2] = tmp[2];
		}
		else {
			tmp[0] = cube[2][0][0], tmp[1] = cube[2][0][1], tmp[2] = cube[2][0][2];
			cube[2][0][0] = cube[4][0][0], cube[2][0][1] = cube[4][0][1], cube[2][0][2] = cube[4][0][2];
			cube[4][0][0] = cube[3][0][0], cube[4][0][1] = cube[3][0][1], cube[4][0][2] = cube[3][0][2];
			cube[3][0][0] = cube[5][0][0], cube[3][0][1] = cube[5][0][1], cube[3][0][2] = cube[5][0][2];
			cube[5][0][0] = tmp[0], cube[5][0][1] = tmp[1], cube[5][0][2] = tmp[2];
		}
		break;
	case 1:
		if (v == 1) {
			tmp[0] = cube[2][2][0], tmp[1] = cube[2][2][1], tmp[2] = cube[2][2][2];
			cube[2][2][0] = cube[4][2][0], cube[2][2][1] = cube[4][2][1], cube[2][2][2] = cube[4][2][2];
			cube[4][2][0] = cube[3][2][0], cube[4][2][1] = cube[3][2][1], cube[4][2][2] = cube[3][2][2];
			cube[3][2][0] = cube[5][2][0], cube[3][2][1] = cube[5][2][1], cube[3][2][2] = cube[5][2][2];
			cube[5][2][0] = tmp[0], cube[5][2][1] = tmp[1], cube[5][2][2] = tmp[2];
		}
		else {
			tmp[0] = cube[2][2][0], tmp[1] = cube[2][2][1], tmp[2] = cube[2][2][2];
			cube[2][2][0] = cube[5][2][0], cube[2][2][1] = cube[5][2][1], cube[2][2][2] = cube[5][2][2];
			cube[5][2][0] = cube[3][2][0], cube[5][2][1] = cube[3][2][1], cube[5][2][2] = cube[3][2][2];
			cube[3][2][0] = cube[4][2][0], cube[3][2][1] = cube[4][2][1], cube[3][2][2] = cube[4][2][2];
			cube[4][2][0] = tmp[0], cube[4][0][1] = tmp[1], cube[4][2][2] = tmp[2];
		}
		break;
	case 2:
		if (v == 1) {
			tmp[0] = cube[0][2][0], tmp[1] = cube[0][2][1], tmp[2] = cube[0][2][2];
			cube[0][2][0] = cube[4][2][2], cube[0][2][1] = cube[4][1][2], cube[0][2][2] = cube[4][0][2];
			cube[4][2][2] = cube[1][0][2], cube[4][1][2] = cube[1][0][1], cube[4][0][2] = cube[1][0][0];
			cube[1][0][2] = cube[5][0][0], cube[1][0][1] = cube[5][1][0], cube[1][0][0] = cube[5][2][0];
			cube[5][0][0] = tmp[0], cube[5][1][0] = tmp[1], cube[5][2][0] = tmp[2];
		}
		else {
			tmp[0] = cube[0][2][0], tmp[1] = cube[0][2][1], tmp[2] = cube[0][2][2];
			cube[0][2][0] = cube[5][0][0], cube[0][2][1] = cube[5][1][0], cube[0][2][2] = cube[5][2][0];
			cube[5][0][0] = cube[1][0][2], cube[5][1][0] = cube[1][0][1], cube[5][2][0] = cube[1][0][0];
			cube[1][0][2] = cube[4][2][2], cube[1][0][1] = cube[4][1][2], cube[1][0][0] = cube[4][0][2];
			cube[4][2][2] = tmp[0], cube[4][1][2] = tmp[1], cube[4][0][2] = tmp[2];
		}
		break;
	case 3:
		if (v == 1) {
			tmp[0] = cube[0][0][2], tmp[1] = cube[0][0][1], tmp[2] = cube[0][0][0];
			cube[0][0][2] = cube[5][2][2], cube[0][0][1] = cube[5][1][2], cube[0][0][0] = cube[5][0][2];
			cube[5][2][2] = cube[1][2][0], cube[5][1][2] = cube[1][2][1], cube[5][0][2] = cube[1][2][2];
			cube[1][2][0] = cube[4][0][0], cube[1][2][1] = cube[4][1][0], cube[1][2][2] = cube[4][2][0];
			cube[4][0][0] = tmp[0], cube[4][1][0] = tmp[1], cube[4][2][0] = tmp[2];
		}
		else {
			tmp[0] = cube[0][0][2], tmp[1] = cube[0][0][1], tmp[2] = cube[0][0][0];
			cube[0][0][2] = cube[4][0][0], cube[0][0][1] = cube[4][1][0], cube[0][0][0] = cube[4][2][0];
			cube[4][0][0] = cube[1][2][0], cube[4][1][0] = cube[1][2][1], cube[4][2][0] = cube[1][2][2];
			cube[1][2][0] = cube[5][2][2], cube[1][2][1] = cube[5][1][2], cube[1][2][2] = cube[5][0][2];
			cube[5][2][2] = tmp[0], cube[5][1][2] = tmp[1], cube[5][0][2] = tmp[2];
		}
		break;
	case 4:
		if (v == 1) {
			tmp[0] = cube[2][0][0], tmp[1] = cube[2][1][0], tmp[2] = cube[2][2][0];
			cube[2][0][0] = cube[0][0][0], cube[2][1][0] = cube[0][1][0], cube[2][2][0] = cube[0][2][0];
			cube[0][0][0] = cube[3][2][2], cube[0][1][0] = cube[3][1][2], cube[0][2][0] = cube[3][0][2];
			cube[3][2][2] = cube[1][0][0], cube[3][1][2] = cube[1][1][0], cube[3][0][2] = cube[1][2][0];
			cube[1][0][0] = tmp[0], cube[1][1][0] = tmp[1], cube[1][2][0] = tmp[2];
		}
		else {
			tmp[0] = cube[2][0][0], tmp[1] = cube[2][1][0], tmp[2] = cube[2][2][0];
			cube[2][0][0] = cube[1][0][0], cube[2][1][0] = cube[1][1][0], cube[2][2][0] = cube[1][2][0];
			cube[1][0][0] = cube[3][2][2], cube[1][1][0] = cube[3][1][2], cube[1][2][0] = cube[3][0][2];
			cube[3][2][2] = cube[0][0][0], cube[3][1][2] = cube[0][1][0], cube[3][0][2] = cube[0][2][0];
			cube[0][0][0] = tmp[0], cube[0][1][0] = tmp[1], cube[0][2][0] = tmp[2];
		}
		break;
	case 5:
		if (v == 1) {
			tmp[0] = cube[2][0][2], tmp[1] = cube[2][1][2], tmp[2] = cube[2][2][2];
			cube[2][0][2] = cube[1][0][2], cube[2][1][2] = cube[1][1][2], cube[2][2][2] = cube[1][2][2];
			cube[1][0][2] = cube[3][2][0], cube[1][1][2] = cube[3][1][0], cube[1][2][2] = cube[3][0][0];
			cube[3][2][0] = cube[0][0][2], cube[3][1][0] = cube[0][1][2], cube[3][0][0] = cube[0][2][2];
			cube[0][0][2] = tmp[0], cube[0][1][2] = tmp[1], cube[0][2][2] = tmp[2];
		}
		else {
			tmp[0] = cube[2][0][2], tmp[1] = cube[2][1][2], tmp[2] = cube[2][2][2];
			cube[2][0][2] = cube[0][0][2], cube[2][1][2] = cube[0][1][2], cube[2][2][2] = cube[0][2][2];
			cube[0][0][2] = cube[3][2][0], cube[0][1][2] = cube[3][1][0], cube[0][2][2] = cube[3][0][0];
			cube[3][2][0] = cube[1][0][2], cube[3][1][0] = cube[1][1][2], cube[3][0][0] = cube[1][2][2];
			cube[1][0][2] = tmp[0], cube[1][1][2] = tmp[1], cube[1][2][2] = tmp[2];
		}
		break;
	default:
		break;
	}
}

void rotation(int** direction, int i, int cube[6][3][3]) {
	int rotation_plane = direction[i][0];
	float rot_theta = direction[i][1] * (M_PI / 2)* -1;
	int tmp[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
	
	for (int b = 0; b < 3; b++) { // b : y'
		for (int a = 0; a < 3; a++) { // a : x'
			int x = (a * int(cos(rot_theta)) - b * sin(rot_theta));
			int y = (a * sin(rot_theta) + b * int(cos(rot_theta)));
			if (rot_theta < 0)
				y += 2;
			else
				x += 2;
			tmp[x][y] = cube[rotation_plane][a][b];
		}
	}
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			cube[rotation_plane][a][b] = tmp[a][b];
		}
	}
}
void cubing(int n, int cube[6][3][3], int** direction) {
	for (int i = 0; i < n; i++) {
		rotation(direction, i, cube);
		int d = direction[i][0];
		int v = direction[i][1];
		rot_round(d, v, cube);
	}
};
void cube_init(int n, int cube[6][3][3], int** direction) {//큐브를 돌린 횟수 n
	for (int i = 0; i < n; i++) {
		direction[i] = new int[3];
		char tmp[5];
		cin >> tmp;
		switch (tmp[0]) {
		case 'U':
			direction[i][0] = 0;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1; //부호 인덱스
			break;
		case 'D':
			direction[i][0] = 1;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1;
			break;
		case 'F':
			//(0,*,*)
			direction[i][0] = 2;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1;
			break;
		case 'B':
			//(2,*,*)
			direction[i][0] = 3;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1;
			break;
		case 'L':
			//(*,0,*)
			direction[i][0] =4;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1;
			break;
		case 'R':
			//(*, 2, *)
			direction[i][0] = 5;
			direction[i][1] = (tmp[1] == '+') ? 1 : -1;
			break;
		default:
			break;
		}
	}
};

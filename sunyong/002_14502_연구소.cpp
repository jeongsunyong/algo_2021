#include <iostream>
#include <vector>

using namespace std;

void virusSpread(int** map, int n, int m, int y, int x, int** visited) {
	if (map[y][x] == 1 || visited[y][x] == 1)
		return;
	
	//감염
	map[y][x] = 2;
	visited[y][x] = 1;

	if(y + 1 < n)
		virusSpread(map, n, m, y + 1, x, visited);
	if (y - 1 >= 0)
		virusSpread(map, n, m, y - 1, x, visited);
	if (x + 1 < m)
		virusSpread(map, n, m, y, x + 1, visited);
	if (x - 1 >= 0)
		virusSpread(map, n, m, y , x - 1, visited);
}

int checkSafe(int** map, int n, int m, vector<int*> virusPos ) {

	int** visited;
	visited = new int*[n];
	for (int i = 0; i < n; i++) {
		visited[i] = new int[m];
		for (int j = 0; j < m; j++) {
			visited[i][j] = 0;
		}
	}

	for (int i = 0; i < virusPos.size(); i++) {
		virusSpread(map, n, m, virusPos[i][0], virusPos[i][1], visited);
	}

	int safe = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0)
				safe++;
		}
	}
	return safe;
}

int main(void) {
	
	int n, m;
	cin >> n >> m;
	
	int** map;
	map = new int*[n];
	for (int i = 0; i < n; i++) {
		map[i] = new int[m];
	}


	vector<int*> virusPos; //바이러스 위치 저장
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				int* tmp;
				tmp = new int[2];
				tmp[0] = i;
				tmp[1] = j;
				virusPos.push_back(tmp);
			}
		}
	}

	int max_safe = 0;

	//모든 케이스 시뮬레이션 루프
	for (int w1 = 0; w1 < m*n; w1++) { //wall_1 
		int x1 = w1 % m;
		int y1 = w1 / m;

		for (int w2 = w1+1; w2 < m*n; w2++) { //wall_2
			int x2 = w2 % m;
			int y2 = w2 / m;

			for (int w3 = w2+1; w3 < m*n; w3++) { //wall_2
				int x3 = w3 % m;
				int y3 = w3 / m;

				//벽 3개 세울 수 없는 경우면 pass
				if (!(map[y1][x1] == 0 && map[y2][x2] == 0 && map[y3][x3] == 0)) 
					continue;


				//복사map
				int** map_copy;
				map_copy = new int*[n];
				for (int i = 0; i < n; i++) {
					map_copy[i] = new int[m];
				}

				//값 복사
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						map_copy[i][j] = map[i][j];
					}
				}

				map_copy[y1][x1] = 1;
				map_copy[y2][x2] = 1;
				map_copy[y3][x3] = 1;

				int safe = checkSafe(map_copy, n, m, virusPos);
				if (safe > max_safe)
					max_safe = safe;
			}
		}

	}

	cout << max_safe << endl;

	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void springNsummer(vector<int>** trees, int** ns, int n) {
	int** ns_add = new int*[n];
	for (int i = 0; i < n; i++) {
		ns_add[i] = new int[n];
		for (int j = 0; j < n; j++) { 
			ns_add[i][j] = 0; 
		}
	}

	//spring
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (trees[i][j].size() < 1)
				continue;

			sort(trees[i][j].begin(), trees[i][j].end());
			int dead = 0;
			for (int a = 0; a < trees[i][j].size();a++) {
				if (ns[i][j] >= trees[i][j][a]) {
					ns[i][j] -= trees[i][j][a];
					trees[i][j][a]++;
				}
				else {
					dead = a;
					for (int b = trees[i][j].size()-1; b >= dead; b--) {
						ns_add[i][j] += (trees[i][j][b]/2);
						trees[i][j].pop_back();
					}
				}
			}
		}
	}
	//summer
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ns[i][j] += ns_add[i][j];
		}
	}

};
void fall(vector<int>** trees, int n) {
	int** trees_add = new int*[n];
	for (int i = 0; i < n; i++) {
		trees_add[i] = new int[n];
		for (int j = 0; j < n; j++) {
			trees_add[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (trees[i][j].size() <= 0)
				continue;
			int num_t = trees[i][j].size();
			for (int a = 0; a < num_t; a++) { //5의 배수 나무의경우 인접8칸에 번식
				if (trees[i][j][a] % 5 == 0) {
					if (i > 0)
						trees_add[i - 1][j]++;
					if (j > 0)
						trees_add[i][j - 1]++;
					if (i < n - 1)
						trees_add[i + 1][j]++;
					if (j < n - 1)
						trees_add[i][j + 1]++;
					if (i > 0 && j > 0)
						trees_add[i - 1][j - 1]++;
					if (i > 0 && j < n-1)
						trees_add[i - 1][j + 1]++;
					if (i < n-1 && j > 0)
						trees_add[i + 1][j - 1]++;
					if (i < n-1 && j < n-1)
						trees_add[i + 1][j + 1]++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int a = 0; a < trees_add[i][j]; a++) {
				trees[i][j].push_back(1);
			}
		}
	}
};
void winter(int** ns, int** A, int n ) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ns[i][j] += A[i][j];
		}
	}
};

int main() { //1,1인덱스 -> 0 0으로 고쳐야함
	int n, m, k;
	cin >> n >> m >> k;
	//양분정보 A배열 초기화
	int** A = new int*[n];
	for (int i = 0; i < n; i++) { 
		A[i] = new int[n];
		for (int j = 0; j < n; j++) { cin >> A[i][j]; };
	};

	//각 땅 보드 초기화
	vector<int>** trees = new vector<int>*[n];
	int** ns = new int*[n];
	for (int i = 0; i < n; i++) {
		trees[i] = new vector<int>[n];
		ns[i] = new int[n];
		for (int j = 0; j < n; j++) { 
			vector<int> tmp; 
			trees[i][j] = tmp;
			ns[i][j] = 5;//initial nourishment : 5
		}
	}

	//각 땅 나무 정보 초기화
	for (int i = 0; i < m; i++) {
		int y; int x; int tree_age;
		cin >> y >> x >> tree_age;
		trees[y-1][x-1].push_back(tree_age);
	}

	for (int i = 0; i < k; i++) {
		springNsummer(trees, ns,  n);
		fall(trees,  n);
		winter(ns,  A, n);

	}

	int num_of_tree = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			num_of_tree += trees[i][j].size();
		}
	}
	cout << num_of_tree << endl;
	
}

/************************** note

GOAL : K년이 지난 후 땅에 살아있는 나무 개수 구하기

INIT : 각 칸 양분 5

SEQUENCE
	(1)봄 : 나이만큼 양분 + , 나이++
			하나의 칸에 여러 나무 존재 시, 나이 어린 나무부터 양분먹음
				자신의 나이만큼 양분을 먹을 수 없는 나무는 죽음
	(2)여름 : 봄에 죽은 나무 양분으로 변함 : 죽은나무나이/2 양분 추가
	(3)가을 : 나무 번식 : 나이가 5의 배수일경우 번식, 인접8개칸에 나이1인 나무 생김.
	(4)겨울 : 땅에 양분 추가(입력)


* (r,c) = (위에서부터 1 y, 왼쪽에서부터 1 x)



***************************/

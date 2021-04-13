#include <iostream>


using namespace std;

inline int max(int a, int b) { 
	int m = a; 
	if (m < b) { 
		m = b; 
	}; 
	return m; 
}
int dfs(int** couns, int start, int n, int pay) {//couns : 상담일정표 //table:확정된시간표 //start, n : 상담 후 
	int max_pay = pay;
	for (int i = start; i < n; i++) {
		
		int rems = n - i; //남은 날짜
		if (couns[i][0] > rems ) { //퇴사 이후 종료면,
			continue;
		}
		
		//일반케이스
		int cur_pay = dfs(couns, i + couns[i][0], n, pay + couns[i][1]);

		max_pay = max(cur_pay, max_pay);

	}
	return max_pay;
}
int main(void) {

	int n = 0;
	cin >> n;
	int** couns;
	couns = new int*[n];
	for (int i = 0; i < n; i++) {
		couns[i] = new int[2];
	}
	for (int i = 0; i < n; i++) {
		cin >> couns[i][0] >> couns[i][1];
	}


	int* table = new int[n];
	for (int i = 0; i < n; i++) { table[i] = 0; }
	
	int maximum = dfs(couns,0, n, 0);
	cout << maximum << endl;




	delete[] couns;
	return 0;

}

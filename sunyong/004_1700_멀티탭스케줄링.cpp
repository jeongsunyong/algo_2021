#include <iostream>
#include <vector>

using namespace std;

int main(void) {

	int n = 0;
	int k = 0;

	cin >> n >> k;

	vector<int> arr;
	int input = 0;
	for (int i = 0; i < k; i++) {
		cin >> input;
		arr.push_back(input);
	}

	vector<int> tab;
	int cnt = 0;
	for (int i = 0; i < k; i++) { // 꽂는 순번 loop
		//중복확인
		int not_full = -1;
		for (int a = 0; a < tab.size(); a++) {
			if (tab[a] == arr[i]) {
				not_full = 1;
				break;
			}
		}
		if (not_full == 1)
			continue;

		if (tab.size() >= n) { //꽉찼을 때 
			int latest = arr[i];
			int latest_next = 0;
			int idx = 0;
			
			//가장 최신 찾기
			for (int a = 0; a < n; a++) //tab loop
			{
				int next = k;
				for (int b = i+1; b < k; b++) { //남아있는 기기들 체크
					if (tab[a] == arr[b]) {
						next = b;
						break;
					}
				}
				if (next > latest_next) {
					latest = tab[a];
					latest_next = next;
					idx = a;
				}
			}
			tab[idx] = arr[i];
			cnt++;
		}
		else {//꽉 안찼을 때 
			tab.push_back(arr[i]);
		}
	}


	cout << cnt << endl;
}

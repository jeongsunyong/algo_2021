#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool vec_sort(vector<int>a, vector<int>b)
{
	return a[0] < b[0];
}

int main(void)
{
	int N = 0;
	cin >> N;
	int** S = new int*[N];
	for (int i = 0; i < N; i++)
	{
		S[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> S[i][j];
		}
	}
	vector<vector<int>> avilities;
	for (int i = 0; i < N; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			vector<int> tmp;
			tmp.push_back(S[i][j] + S[j][i]);
			tmp.push_back(i);
			tmp.push_back(j);
			avilities.push_back(tmp); // 0 : avility값, 1 : 팀원i 2:팀원j
		}
	}
	vector<vector<int>> diff;
	for (int i = 0; i < N*(N - 1) / 2; i++)
	{
		for (int j = i; j < N*(N - 1) / 2; j++)
		{
			if (i == j)
				continue;
			vector<int> tmp;
			tmp.push_back(abs(avilities[i][0]-avilities[j][0]));
			tmp.push_back(avilities[i][1]);//인덱스들
			tmp.push_back(avilities[i][2]);//인덱스들
			tmp.push_back(avilities[j][1]);//인덱스들
			tmp.push_back(avilities[j][2]);//인덱스들
			diff.push_back(tmp);
		}
	}
	

	sort(diff.begin(), diff.end(),vec_sort);


	//능력치 차이의 최소값 구하기

	int min_diff = 0;
	int* picked = new int[N];
	for (int i = 0; i < N; i++)
	{
		picked[i] = 0;
	}

	int cnt = 0;
	for (int i = 0; i < diff.size(); i++)
	{
		if (picked[diff[i][1]] == 0&& picked[diff[i][2]] == 0&& picked[diff[i][3]] == 0&& picked[diff[i][4]] == 0)
		{
			cout << diff[i][0] << endl;
			min_diff += diff[i][0];
			picked[diff[i][1]] = 1;
			picked[diff[i][2]] = 1;
			picked[diff[i][3]] = 1;
			picked[diff[i][4]] = 1;
			cnt++;
		}
	}

	cout << min_diff << endl;

	return 0;
}

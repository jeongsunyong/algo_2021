#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{

	int N = 0, B = 0, C = 0;
	cin >> N;
	int* A = new int[N];

	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	cin >> B >> C;

	long long cnt = 0;
	int top = 0;
	sort(A, A + N);
	for (int i = 0; i < N; i++)
	{
		A[i] = A[i] - B;
		if (A[i] <= 0)
			top++;
		cnt++;
	}

	int m = 1;
	while (1)
	{
		if (A[top] > C)
			m = int(A[top] / C);
		else
			m = 1;
		for (int i = top; i < N; i++)
		{
			A[i] = A[i] - m*C;
			if (A[i] <= 0)
				top++;
			cnt=cnt + m;
		}
		if (top >= N)
			break;
	}
	cout << cnt << endl;

	return 0;
}

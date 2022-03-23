#include <iostream>
#include <string>
using namespace std;

class baqu
{

public:
	string topni;//topni: 0~7 / 0->12시방향, 시계방향순서
	char right;
	char left;
	baqu()
	{
		cin >> topni;
		right = topni[2];
		left = topni[6];
	}
	
	void rotation(int direction)//회전
	{
		if (direction == 1)//시계
		{
			int tmp = topni[7];
			for (int i = 6; i >= 0; i--)
			{
				topni[(i + 1)] = topni[i];
			}
			topni[0] = tmp;
		}
		else if (direction == -1)//반시계
		{
			int tmp = topni[0];
			for (int i = 1; i < 8; i++)
			{
				topni[(i - 1)] = topni[i];
			}
			topni[7] = tmp;
		}
		right = topni[2];
		left = topni[6];
	}
};

int main(void)
{
	baqu B[4];
	int K = 0;
	cin >> K;
	int* R_num = new int[K];
	int* R_dir = new int[K];

	for (int i = 0; i < K; i++)
	{
		cin >> R_num[i];
		cin >> R_dir[i];
	}


	for (int i = 0; i < K; i++)
	{
		int turn = R_num[i]-1; //인덱스 1~4- > 0~3
		int direction = R_dir[i];
		int change_flag[4] = { 0 };//회전 조건 여부 검사 후 4개 바퀴 한번에 돌릴것

		change_flag[turn] = direction;
		for (int j = turn; j <= 2; j++)//오른쪽쭉
		{
			if (B[j].right != B[j + 1].left)
			{
				direction = direction * -1;
				change_flag[j + 1] = direction;
			}
			else
				break; //연속회전차단
		}

		direction = R_dir[i];
		for (int j = turn; j >= 1; j--)//왼쪽 쭉
		{
			if (B[j].left != B[j - 1].right)
			{
				direction = direction * -1;
				change_flag[j - 1] = direction;
			}
			else
				break;
		}
		
		for (int j = 0; j < 4; j++)//회전
		{
			if (change_flag[j] != 0)
				B[j].rotation(change_flag[j]);
		}
	}

	int point = (int)(B[0].topni[0]-48) * 1 + 
		int(B[1].topni[0]-48) *2 + 
		int(B[2].topni[0]-48) *4 + 
		int(B[3].topni[0]-48) *8;

	cout << point << endl;

	return 0;
}

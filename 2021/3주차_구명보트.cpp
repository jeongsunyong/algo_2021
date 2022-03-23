#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(),people.end());//정렬
    int top=0;
    int rear=people.size()-1;
    while(top<=rear)
    {
        int sum=people[rear];//뒤에서부터추가
        rear--;
        while(people[top] + sum<=limit)//앞에서부터 추가
        {
            sum=sum+people[top];
            top++;
        }
        
        answer++;
    }
    return answer;
}

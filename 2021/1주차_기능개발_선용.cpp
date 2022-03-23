#include <string>
#include <vector>
#include <iostream>

using namespace std;
//배포되어야하는 순서대로 배치 작업의 진도 배열 progresses : 100%일 때 서비스에 반영.
//각 작업 개발속도 정수배열 speeds
//각 배포마다 몇 개의 기능이 배포되는지 return
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int dist=0;
    while(dist<=progresses.size())
    {
        while(progresses[dist]<100)
        {
            for(int i=dist;i<progresses.size();i++)
            {
                progresses[i]=progresses[i]+speeds[i];
            }
        }
        int cnt=dist;
        int n=0;
        while(progresses[cnt]>=100)
        {
            n++;
            cnt++;
            if( cnt>= progresses.size())
                break;
        }
        dist=cnt;
        answer.push_back(n);
        if( cnt>= progresses.size())
                break;
    }
    return answer;
}

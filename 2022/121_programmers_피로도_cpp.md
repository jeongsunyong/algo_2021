
## [피로도](https://school.programmers.co.kr/learn/courses/30/lessons/87946#)
* 소요 시간 :  30분 
### 성공코드
```cpp
#define loop(i,a,b) for (int i = (a); i < (b); i++)
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int dfs(int k, vector<vector<int>> dungeons,int i,int cnt, int* visited){ //완전탐색
    int max_cnt=cnt;
    if(i>=dungeons.size()){ // 던전 모두 탐색 시 종료.
        return cnt;
    }
    
    loop(j,0,dungeons.size()){ //0부터 던전개수만큼 탐색한다.
        int k_next=k; //다음 피로도
        int cnt_next=cnt; //다음 탐험 던전 횟수
        int lock=0; // 이번 loop에서 방문 여부
        if(k_next>=dungeons[j][0] and visited[j]==0){
            k_next-=dungeons[j][1];
            cnt_next+=1;
            visited[j]=1;
            lock=1;
        }
        max_cnt=max(max_cnt,dfs(k_next,dungeons,i+1,cnt_next,visited)); //탐색 후 최대 카운트를 취한다.
        if(lock==1){//이번 loop에서 방문했을 경우에만 방문 여부 체크 해제.
            visited[j]=0;
        }
    }
    return max_cnt;
}
int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    int visited[9]={0,0,0,0,0,0,0,0,0};
    int max_cnt=dfs(k,dungeons,0,0,visited);
    answer=max_cnt;
    return answer;
}

/*
inputs 
    k : 유저의 현대 피로도 
    dungeons : [던전별 최소 피로도, 소모 피로도]
goal
    유저가 탐험할 수 있는 최대 던전 수 return

-> 정렬문제가 아님. 순차적으로 어떻게 접근해도 불가능함.
-> 모든 방문을 해야함
    idea ) visited를 표시하고, 매번 전체를 훑음, 그리고 visited가 전부O거나 방문가능x이면 return
    : 80->50->30
      80->30->50
      30->50->80
      30->80->50
      50->30->80
      50->80->30
      모두 탐색되어야함.
*/
```

----------------------------------------------------------------------------
### comment 
8/7 코드리뷰    
dfs를 이용하여 모든 경우의 수를 센다.
처음에 접근할 때 정렬해서 작은 것 순서로 방문하는게 최대가 아닐까 생각도 했는데,   
진입 가능 피로도가 크고 실제 소모 피로도가 매우 작은 것을 방문하는 것과   
진입 가능 피로도가 작고 실제 소모 피로도가 작은 것을 방문하는 것,   
우선순위를 정렬할 수 없다.   
그러므로 완전 탐색이 필요.   

#
#
 ### learned lesson
 
* ** C++ map
    dictionary 역할을 하는 C++의 STL

#
#
 
 
 
 


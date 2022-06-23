
## [실패율](https://programmers.co.kr/learn/courses/30/lessons/42889)
* 소요 시간 :  20분 
### 성공코드
```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

map<int,int> cnt_fail; //<stage, 정체인원수>
map<int,int> cnt_chal; //<stage, 도전인원수>
bool comp(int a,int b){ // comp : 실패율에 따른 정렬을 위한 bool함수
    float rate_a= cnt_chal[a]>0?float(cnt_fail[a])/cnt_chal[a]:0;
    float rate_b=cnt_chal[b]>0?float(cnt_fail[b])/cnt_chal[b]:0;
    if(rate_a==rate_b){
        if(a>b)
            return false;
        else
            return true;
    }
    else if(rate_a>rate_b)
        return true;
    else
        return false;
    
}
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    for(int i=1;i<=N;i++){
        cnt_fail[i]=0;
        cnt_chal[i]=0;
        answer.push_back(i);
    }
    for(vector<int>::iterator i=stages.begin();i!=stages.end();i++){
        for(int chal=1;chal<=*i;chal++){
            cnt_chal[chal]++;
        }
        cnt_fail[*i]++;
    }
    
    sort(answer.begin(),answer.end(),comp);
    
    return answer;
}

/*
goal
    실패율이 높은 스테이지부터 내림차순으로 스테이지 번호가 담겨있는 배열 return
    실패율 : 스테이지에 도달했으나 아직 클리어하지 못한 플레이어 수 / 스테이지에 도달한 플레이어 수 
input  
    N : 전체 스테이지 개수
    stages : 게임을 이용하는 사용자가 현재 멈춰있는 스테이지의 번호가 담긴 배열
    
*/
```

----------------------------------------------------------------------------
### comment 
6/23 코드리뷰    
stages에 저장되어있는 해당 유저가 정체되어있는 stage정보를 이용,    
1(first stage)부터 해당 stage까지 도전횟수를 카운팅, 정체되어있는 해당 stage에는 실패횟수를 카운팅.
각 카운팅은 스테이지별 map에 저장한다.(cnt_chal, cnt_fail)    
해당 정보를 가지고 정렬한다.    

#
#
 ### learned lesson
 
* ** C++ map
    dictionary 역할을 하는 C++의 STL

#
#
 
 
 
 


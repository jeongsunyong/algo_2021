
## [로또의 최고 순위와 최저 순위](https://programmers.co.kr/learn/courses/30/lessons/77484)
* 소요 시간 :  20분 
### 성공코드
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool comp(int a, int b){
    if(a>=b)
        return false;
    else
        return true;
}

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    sort(lottos.begin(),lottos.end(),comp);
    sort(win_nums.begin(),win_nums.end(),comp);
    
    int free=0;
    int lidx=0;
    int widx=0;
    int win_cnt=0;
    while(lidx<6 && widx<6){
        if (lottos[lidx]==0){
            free++;
            lidx++;
            continue;
        }
        else if(lottos[lidx]<win_nums[widx]){
            lidx++;
            continue;
        }
        else if(lottos[lidx]==win_nums[widx]){
            lidx++;
            widx++;
            win_cnt++;
            continue;
        }
        else if(lottos[lidx]>win_nums[widx]){
            widx++;
            continue;
        }
        
    }
    
    //최고등수
    answer.push_back(min(7-(win_cnt+free),6));
    //최저등수
    answer.push_back(min(7-(win_cnt),6));
    return answer;
    
}


/*
goal
    당첨 가능한 최고 순위와 최저 순위 
input
    lottos : 구매한 로또 번호를 담은 배열
        0은 알아볼 수 없는 숫자
    win_nums : 당첨 번호
    
    * lotto, win nums는 모두 길이 6인 정수 배열.

*/
```

----------------------------------------------------------------------------
### comment 
4/22 코드리뷰    
6개의 숫자 리스트 2개 중 일치하는 것을 세는데, 0인 경우 임의 지정이 가능하므로 최고 케이스에는 나머지 모두를 일치시켜주고, 최저 케이스에는 나머지 모두와 불일치 하도록 함.   


#
#
 ### learned lesson
 
* ** 
#
#
 
 
 
 


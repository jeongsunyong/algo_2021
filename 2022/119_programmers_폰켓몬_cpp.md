
## [폰켓몬](https://programmers.co.kr/learn/courses/30/lessons/1845)
* 소요 시간 :  15분 
### 성공코드
```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
goal : N/2마리 pkm 선택 방법 수 중 가장 많은 종류 pkm 선택
input :
    N : pkm 마리 수(배열크기)
    nums : pkm종류 번호 배열

*/
void printSet(set<int> s){
    set<int>::iterator i;
    for(i=s.begin(); i!= s.end();i++){
        cout<<*i<<endl;
    }
}
int solution(vector<int> nums)
{
    int n=nums.size();
    int answer = 0;
    set<int> s(nums.begin(),nums.end());
    //printSet(s);
    int s_size=s.size();
    answer=s_size>int(n/2)?int(n/2):s_size;
    return answer;
}
```

----------------------------------------------------------------------------
### comment 
6/20 코드리뷰    
중복을 제거해준 후 폰켓몬 종류 수 가 N/2보다 많다면 최대 선택개수인 N/2를 반환, 그렇지 않다면 종류 개수를 반환한다.

#
#
 ### learned lesson
 
* ** [C++ Set](https://pangtrue.tistory.com/37)
  C++에서는 SET이라는 컨테이너를 제공한다. (STL)
  SET은 노드 기반 컨테이너이며,
  균형 이진트리로 구현되더있다.
  key인 원소들의 집합으로 이루어진 컨테이너이며 중복이 혀용되지 않는다.
  default 정렬 기준은 오름차순.
  ![image](https://user-images.githubusercontent.com/46209571/174537986-3398c2a0-a690-4551-96c6-cd99f4e9bb31.png)
  
#
#
 
 
 
 


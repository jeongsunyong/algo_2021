
## [이진변환 반복하기](https://school.programmers.co.kr/learn/courses/30/lessons/70129?language=cpp)
* 소요 시간 :  20분 
### 성공코드
```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void d(int c, string& s){ // c를 이진수로 변환 후, s로 대체해주는  
    s="";
    int a=0;
    while(c>=1){
        a=c%2;
        c=int(c/2);
        s=to_string(a)+s;
    }
}
vector<int> solution(string s) {
    vector<int> answer;
    int rem_zero=0; // zero 개수 카운트 변수
    int d_cnt=0;// 이진변환 카운트 변수
    while( s!="1") {
        rem_zero+=s.length(); // 전체 s에서 1과 0의 개수를 더해준다
        s.erase(remove(s.begin(), s.end(), '0'), s.end());
        int c=s.length();
        rem_zero-=c; // 1의 개수를 뺴준다. (제거된 0의 개수만 남게됨)
        d(c,s);
        d_cnt+=1;
    }
    
    answer.push_back(d_cnt);
    answer.push_back(rem_zero);
    
    return answer;
}


/* note
input : s 0과1로 이루어진 문자열
operation
    이진변환
        1. x의 모든 0을 제거
        2. x를 x의길이 x를 2진법으로 표현한 문자열로 바꿈.
goal : 이진변환 횟수와 변환 과정에서 제거된 0의 개수

*/
```

----------------------------------------------------------------------------
### comment 

특정 동작(0 제거, 길이의 이진수로 대체) 을 반복하며 카운팅해주는 문제이다.   
s가 "1"이 될 때 까지, 0을 제거하고 문자열을 길이의 이진수로 대체하는 것을 반복.   
C++ 복습겸 풀이.    


#
#
 ### learned lesson
참고
  - [C++ 특정 문자열 제거] (https://wooono.tistory.com/475)
  - [C++ int to string] (https://blockdmask.tistory.com/334)
  - [C++ 두 문자열 비교] (https://www.techiedelight.com/ko/compare-two-strings-in-cpp/)
#
#
 
 
 
 


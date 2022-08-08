
## [행렬의 곱셈](https://school.programmers.co.kr/learn/courses/30/lessons/12949)
* 소요 시간 :  20분 
### 성공코드
```cpp
#define loop(i,a,b) for (int i = (a); i < (b); i++)
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer;
    int r1=arr1.size();
    int c1=arr1[0].size();
    int r2=arr2.size();
    int c2=arr2[0].size();
    
    loop(r,0,r1){ // arr1의 행 number
        vector<int> row;
        answer.push_back(row);
        loop(c,0,c2){ //arr2의 열 number 
            int dot=0;
            loop(i,0,c1){
                dot+=arr1[r][i] * arr2[i][c]; //내적
            }
            answer[r].push_back(dot); 
        }
    }
    
    return answer;
}

/*
inputs
    arr1,arr2 : 2차원 행렬
goal : arr1에 arr2를 곱한 결과를 반환
*/
```

----------------------------------------------------------------------------
### comment 
8/8 코드리뷰    
행렬의 곱셈.


#
#
 ### learned lesson


#
#
 
 
 
 


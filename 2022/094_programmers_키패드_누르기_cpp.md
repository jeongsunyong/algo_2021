
## [키패드 누르기](https://programmers.co.kr/learn/courses/30/lessons/67256)
* 소요 시간 :  30분 
### 성공코드
```cpp
#define loop(i,a,b) for(int i=a; i<b;i++)

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int** nums=new int*[10];
    int x=0,y=0;
    nums[0]=new int[2];
    nums[0][0]=1;nums[0][1]=3;
    loop(key,1,10){
        nums[key]=new int[2];
        nums[key][0]=x;
        nums[key][1]=y;
        x++;
        if(x>=3){
            x=0;y++;
        }
    }
    
    int cur_left_x=0;
    int cur_left_y=3;
    int cur_right_x=2;
    int cur_right_y=3;

    loop(i,0,numbers.size()){
        int num_x=nums[numbers[i]][0];
        int num_y=nums[numbers[i]][1];
        if (numbers[i]%3==1){
            answer+='L';
            cur_left_x=num_x;
            cur_left_y=num_y;
        }
        else if (numbers[i]%3==0 and numbers[i]!=0){
            answer+='R';
            cur_right_x=num_x;
            cur_right_y=num_y;
        }
        else{
            int r_dist=abs(cur_right_x-num_x)+abs(cur_right_y-num_y);
            int l_dist=abs(cur_left_x-num_x)+abs(cur_left_y-num_y);
            if (r_dist<l_dist){
                cur_right_x=num_x;
                cur_right_y=num_y;
                answer+='R';
            }
            else if(r_dist>l_dist){
                cur_left_x=num_x;
                cur_left_y=num_y;
                answer+='L';
            }
            else if(r_dist==l_dist){
                if (hand[0]=='l'){
                    cur_left_x=num_x;
                    cur_left_y=num_y;
                    answer+='L';
                }
                else if (hand[0]=='r'){
                    cur_right_x=num_x;
                    cur_right_y=num_y;
                    answer+='R';
                }
            }
        }
    }
    
    /*
    1 2 3
    4 5 6
    7 8 9
    . 0 .
    */

    
    
    return answer;
}



/*
goal
    number 배열 순서대로 번호를 누를 때 각 번호를 누른 엄지손가락 L/R문자열로 반환.
input
    hand: right/left : 각각 오른손잡이, 왼손잡이
operation
    -초기값
        왼손 엄지 * 
        오른손 엄지 #
    - 손가락은 상하좌우 이동(거리 1씩)
    - 1,4,7 입력 시 왼손 엄지 사용
    - 3,6,9 입력 시 
*/
```

----------------------------------------------------------------------------
### comment 
4/22 코드리뷰    
정해진 숫자일경우 정해진 손가락으로 눌러주고, 아닌 경우에는 거리를 계산해서 숫자를 선택해준다.   


#
#
 ### learned lesson
 
* ** 
#
#
 
 
 
 


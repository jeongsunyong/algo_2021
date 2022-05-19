## [메뉴 리뉴얼](https://programmers.co.kr/learn/courses/30/lessons/68645#)
* 소요 시간 : 약 1시간

### 성공코드
```python

def solution(n):
    answer = []
    d=[[-1,1],[1,0],[-1,-1]] # ↙ → ↖
    didx=0
    snail_triangle=[]
    for i in range(n):
        snail_triangle.append(list())
    
    num=0
    for i in range(1,n+1):
        num+=i
    
    cnt=0 # 이동 횟수
    rot=n # 회전에 필요한 이동수
    y=-1
    tmp_arr=[]
    for i in range(1,num+1):
        if cnt==rot: 
            rot-=1
            didx=(didx+1)%3
            cnt=0
        cnt+=1
        dy=d[didx][0]
        dy=d[didx][1]
        y+=dy
    
        if num==i and len(tmp_arr)==0:
            snail_triangle[y].append(i)
            break
        if dy==0 and cnt==rot:
            tmp_arr.append(i)
            snail_triangle[y].append(tmp_arr)
            tmp_arr=[]
        elif dy==0 or (dy==1 and cnt==rot):
            tmp_arr.append(i)
        elif dy==1:
            snail_triangle[y].append(i)
        elif dy==-1:
            snail_triangle[y].append(-i)
    
    for floor in snail_triangle:
        right=[]
        left=[]
        mid=[]
        for block in floor:
            if type(block)==list:
                mid=block
                continue
            elif block<0:
                right.append(-1*block)
            elif block>0:
                left.append(block)
        floor= left+mid+sorted(right,reverse=True)
        answer+=floor
    
    return answer

"""
input

goal
    n : 삼각형 변의 길이.
rotation
    ↙  ↖
      →
      
think
n=1일 때
    1
n=2일 때
    1
  2   3
n=3일 때
    1
  2   6
3    4   5
n=4일 때
    1
   2 9
  3 10 8
4  5  6  7

n= 7일 때
           1
         2  18
       3 19  17
     4 20  27 16
    5 21  28  26 15
  6 22 23  24  25 14
7  8  9  10  11  12  13
접근 1) 각 층별로 연관관계 있을지
접근 2) 순차적으로 달팽이모양 2차원배열 생성해서 인덱스 규칙으로 접근해야할지.
ex) 2층 : n=2부터
n=2일때
2 3
n=3일 때
2 6
n=4일 때
2 9
n=5일 때
2 12
n=6일 때
2 15
.
.
2 -> 3(n-1)

ex) 3층 n=3부터
n=3일때
3 4 5
n=4일때
3 10 8
n=5일때
3 13 11
n=6일때
3 16 14
3 -> 3(n-1)+1 -> 3(n-1)-1 

ex ) 4층 n=4부터
n=4일때
4 5 6 7
n=5일 때
4 14 15 10
n=6일 때
4 17 21 13
n=7일 때
4 20  27 16

4-> 3*(n)-1 -> ...

* (n=floor일 때는 n,n+1,...2n-1)

규칙찾기 어려움. 존재하더라도 복잡한 규칙일듯함


방2)
[[],[],[]..]
최종수
n=1
1
n=2
3
n=3
6
n=4
10
n=5
15
n=6
21
n=7

"""
```


----------------------------------------------------------------------------
### comment 
5/19 코드리뷰    

첫 접근은 정답배열의 각 위치에 맞는 값의 규칙성을 찾고자했지만,    
순차적으로 달팽이삼각형 구조에 값을 넣고 추후에 순서대로 참조하는 것이 더 간단한 방법이라고 판단되어 해당 방법으로 풀이.   
규칙을 찾아봤을 때, 이동은 ↙ → ↖을 반복하고, 각 방향마다 n, n-1, n-2...번씩 이동한다. (꺾을 때 마다 이동값이 -1)   
(1)  각 층에 알맞는 값들을 넣는 방법    
이 규칙에 따라 최종 도달값(num)까지 loop를 돌며 달팽이구조의 배열에 값을 넣어준다.   
이 때 순서대로 각 층을 snail_pyramid[floor] 라고 할 때, floor값은 작은 값부터 넣어주게된다. 실질적으로는 하지만 upside를 향할 때 해당 층을 방문한다면 맨 끝(오른쪽)부터 채워진다.
그러므로 이 케이스를 구분할 필요가 있다.   
(2) 각 층에서 달팽이 규칙에 맞게 정렬    
그러므로 dy=0, 오른쪽으로 이동할 때 (→) , downside로 가면서 방문할 때, upside로 가면서 방문할 때를 각각 양수, 배열, 음수로 저장하여   
최종 때 양수는 왼쪽으로, 배열은 중간으로, 음수는 역순으로 값을 복구하여 concate해준다.  
-> 달팽이 규칙에 맞게 정렬된다.   

#
#
 ### learned lesson
 * 구현


#
#
 
 

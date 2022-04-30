## [배열 돌리기1](https://www.acmicpc.net/problem/16926)
* 소요 시간 :  30분

### 성공 코드
```python
import sys

if __name__ == '__main__':
    #입력
    n,m,r = list(map(int,sys.stdin.readline().rstrip().split(" ")))
    board = [list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]

    #r회 반복
    for _ in range(r):
        #반시계방향 회전
        #origin = [list(row) for row in board]
        for square in range(min(n,m)//2): #사각형의 개수
            store=board[square][square]
            for j in range(0+square,m-square-1):
                board[square][j]=board[square][j+1]
            for i in range(0+square, n - square-1):
                board[i][m-1-square]=board[i+1][m-1-square]
            for j in reversed(range(0+square+1,m-square)):
                board[n-1-square][j]=board[n-1-square][j-1]
            for i in reversed(range(0+square+1,n-square)):
                board[i][square]=board[i-1][square]
            board[square+1][square] = store
    for row in board:
        print(" ".join(map(str,row)))


"""
goal
    배열 r번 회전시킨 결과 출력
input
    n,m : 배열의 크기, n : 행 m : 열
    r : 회전 수
    board : 배열의 원소값들
rotation
    반시계방향으로회전. 

    1 1 1 1 1
    1 2 2 2 1
    1 2 3 2 1
    1 2 2 2 1
    1 1 1 1 1 
    
    1 1 1 1 1 1 1 1 1
    1 2 2 2 2 2 2 2 1
    1 2 2 2 2 2 2 2 1
    1 1 1 1 1 1 1 1 1 
    
    1 1 1 1 
    1 2 2 1
    1 2 2 1 
    1 2 2 1 
    1 2 2 1 
    1 2 2 1 
    1 2 2 1
    
    사각형은 min(m,n)//2만큼 회전.
    
    1 1 1 1 1
    1 2 2 2 1
    1 2 3 2 1
    1 2 3 2 1
    1 2 2 2 1
    1 1 1 1 1 
    
    n  사각수
    5-> 1. (내부에 3 : 2회전에 포함되지 않는 원소 존재하긴하지만 회전을 안해줘도 됨.
    4->2
    3->1
    2-> 1
    
    1 : square
    1 . . .
    .
    .
    
    2:square
    1 1 1
    1 2 .
    1 .
 

"""
```



----------------------------------------------------------------------------
### comment 
4/30 코드리뷰   
소용돌이 형태가 아닌 사각형 테두리 선 형태로 회전한다. 
-> 각 사각형 테두리 범위를 구하고, 테두리 개수만큼 반복해서 변경해준다.     
첫 원소를 선정해서 임시저장하고,    
해당 원소부터 다른 값을 당겨온다.     
마지막에 당겨진 값에 임시저장했던 첫 원소 저장  .  

#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 


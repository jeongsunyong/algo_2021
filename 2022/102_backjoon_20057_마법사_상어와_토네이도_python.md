## [마법사 상어와 토네이도](https://www.acmicpc.net/problem/20057)
* 소요 시간 :  1시간50분 

### 성공 코드
```python
import sys

def spread(board,n,dx,dy,x,y,out):
    target_y=dy+y
    target_x=dx+x
    sand=board[target_y][target_x] # target sand 총량 , x,y값은 mask의 가운데
    sand_remain=sand

    # spread shape : -1,0 case
    if dx==-1 and dy==0:
        spread_mask=[[0,0,0.02,0,0],[0,0.1,0.07,0.01,0],[0.05,0,0,0,0],[0,0.1,0.07,0.01,0],[0,0,0.02,0,0]] #x,y,a는 0 처리.
    # spread shape : 0,1 case
    if dx==0 and dy==1:
        spread_mask=[[0,0,0,0,0],[0,0.01,0,0.01,0],[0.02,0.07,0,0.07,0.02],[0,0.1,0,0.1,0],[0,0,0.05,0,0]] #x,y,a는 0 처리.
    # spread shape : 1,0 case
    if dx==1 and dy==0:
        spread_mask=[[0,0,0.02,0,0],[0,0.01,0.07,0.1,0],[0,0,0,0,0.05],[0,0.01,0.07,0.1,0],[0,0,0.02,0,0]] #x,y,a는 0 처리.
    # spread shape : 0,-1 case
    if dx==0 and dy==-1:
        spread_mask=[[0,0,0.05,0,0],[0,0.1,0,0.1,0],[0.02,0.07,0,0.07,0.02],[0,0.01,0,0.01,0],[0,0,0,0,0]] #x,y,a는 0 처리.

    # spread하는 경우, x모래양 변경x -> 비율 1로 매핑. y-> 모래양 0, a-> 나머지.
    for i in range(5): #0,1,2,3,4 -> -2,-1,0,1,2
        for j in range(5):
            b_i=i-2 #board에서의 i dy값
            b_j=j-2 #board에서의 j dx값
            if target_y+b_i < 0 or target_y+b_i >=n or target_x+b_j < 0 or target_x+b_j >= n: # 범위를 벗어나는경우, 벗어난 값 counting.
                out[0]+= int(sand*spread_mask[i][j])
                sand_remain-=int(sand*spread_mask[i][j])
            else: # 범위를 벗어나지 않는 경우, mask 비율에 해당하는 모래 양을 더해준다.
                board[target_y+b_i][target_x+b_j]+=int(sand*spread_mask[i][j])
                sand_remain-=int(sand*spread_mask[i][j])
    board[target_y][target_x]=0
    if target_y+dy < 0 or target_y+dy >= n or target_x+dx < 0 or target_x+dx >= n:
        out[0]+=sand_remain
    else:
        board[target_y+dy][target_x+dx]+=sand_remain

if __name__ == '__main__':
    n=int(sys.stdin.readline().rstrip())
    board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    board_origin=[list(row) for row in board]
    out=[0]
    d = [[-1,0] , [0,1] , [1,0], [0,-1]]
    x=n//2
    y=n//2

    rot_cnt=0 # 회전한 횟수 기록 변수
    cur_d=0 # 현재 방향 변수
    step=1 # step size
    cnt=0 # 현재 step 이동횟수

    # 1.storm 이동
    while not (x==0 and y==0):
        if cnt>=step: # 현재 step만큼 이동 시 방향 변경.
            rot_cnt+=1
            cur_d=(cur_d+1)%4
            cnt=0
            if rot_cnt>=2: #  2번 회전마다 기준step 증가.
                step=min(step+1,n) # 마지막에는 3회.(격자의 크기 이하로 제한)
                rot_cnt=0

        #이동방향
        dx = d[cur_d][0]
        dy = d[cur_d][1]

        #2. spread 진행
        spread(board, n, dx, dy, x, y,out)

        x+=dx
        y+=dy

        cnt+=1

    print(out[0])

"""
goal
    격자 밖으로 나간 모래양(손실양)
input
    n : 격자의 크기(square) (3 ≤ n ≤ 499), n은홀수
    board : 모래밭
        board[i][j] : xj,yi행의 모래 양
        가운데 칸에 있는 모래의 양은 0

#구현사항
    1) storm이 이동하는 나선이동 구현
    
storm : 
    storm은 (n/2,n/2)에서 출발해 (0,0) 도달 시 소멸. , 반시계방향 나선 회전한다. 
        (-1,0) , (0,1) , (1,0), (0,-1)
    
    모래가 이미 있는 곳으로 이동 시 모래 양 더해짐. 
    토네이도가 한 칸 이동할 때 마다 일정 비율로 흩날린다. 
    * 이동 방향에 따른 모래 분산 비율
            0.02
        0.1 0.07 0.01
    0.05 a  타겟  소스
        0.1 0.07 0.01
            0.02
           
            0.02
        0.01 0.07 0.1    
        s     t     a   0.05    
        0.01 0.07 0.1
            0.02
            
             0.05  
         0.1  a  0.1
   0.02 0.07 타겟 0.07 0.02
        0.01 소스 0.01
        
        0.01 s 0.01
   0.02 0.07 t 0.07 0.02     
        0.1  a  0.1
            0.05
            
    x->y 이동 시 y의 모래들이 이동하게된다.
        - 시작점이 아닌 이동점의 모래가 흩날리게됨,
        - a는 타겟이 고정비율에 흩어진 후 남은 모래들이 모두 이동. 
        - 계산 시 소수점 아래는 버린다.
          -> 버림된다면 해당 값은 a에 더해져야한다.

"""
```



----------------------------------------------------------------------------
### comment 
4/30 코드리뷰    

pypy3 제출. 통과   
#1 : 소용돌이 좌표 이동 구현   
#2 : 해당 좌표에서 모래 분산 구현   
순서로 구현. 

좌표 이동의 경우, 
가운데부터 시작해 1칸 이동할 때 마다 방향을 바꾸고,   
2번 방향을 바꾸면 방향을 바꾸기 위한 칸의 수가 증가한다(step size 증가)  
-> 초기 stepsize를 1로 놓고, 이동횟수(cnt)를 이동마다 증가시켜,    
stepsize에 도달하면 회전시켜준다, 이 때 rotation을 카운팅해줌 .      
rotation 이 2회 되었을 때는 stepsize를 증가시켜줌. 단 이때 마지막(stepsize==n)에는 2회가 아닌 3회 모두 
모두 n번 이동해야하므로 min(step+1,n)으로 작성.     
위와 같이 좌표 이동 구현.

모래 분산의 경우 주어진 비율을 마스킹,(가운데를 이동하려는 target position으로 설정)해    
곱한 값을 해당 좌표에 더해준다.   
이 때 spread_mask는 각 케이스(상,하,좌,우 이동) 마다 다르게 if 분기처리해주었음.  
좀 더 효율적인 방법으로는 하나를 작성해서 케이스마다 회전시키는 방법이 깔끔할 듯 하다.  

어쨌든,   
마스킹한 값을 더해주되, 해당 좌표가 board범위를 벗어나면 out에 더해 기록해주고, 아니면 해당 좌표에 더해줌.   
마스크 좌표는 5칸 마스크를 가운데를 0,0으로 설정하기 위해 loop (i , 0~5) 값에 -2를 더해 -2~2가 되도록 함.    


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 

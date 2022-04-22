092_backjoon_17143_낚시왕_python.md
## [낚시왕](https://www.acmicpc.net/problem/17143)
* 소요 시간 :  4시간 





----------------------------------------------------------------------------
### comment 
4/22 코드리뷰    

### 시행착오 (주의점)
```python
d=[['space'],[0,-1],[0,1],[1,0],[-1,0]]
    for i in range(m):
        shark=list(map(int,sys.stdin.readline().rstrip().split(" ")))
        sharks.append({
            ..
            'd':list(d[shark[3]]), #방향 #'d':d[shark[3]], ★
            ..
        })
        board[sharks[-1]['y']][sharks[-1]['x']]=sharks[-1]

```
처음에 답이 안나와서 로직쪽을 살펴보니 어디가 문제인지 정확하게 모르겠어, 값을 출력하며 확인한 오류.    
숫자로 주어지는 방향을 d라는 배열로 매핑했는데,     
값을 할당할 때, d를 리스트로 감싸주지 않는다면 않는다면 어떻게될까     

```python
 dx = shark['d'][0]
                dy = shark['d'][1]
                if shark['x']+dx>=c or shark['x']+dx <0 or shark['y']+dy>=r or shark['y']+dy<0: # 벽 방향으로 나아갈 때, 방향 전환
                    shark['d'][0] *= -1
                    shark['d'][1] *= -1
```
값을 순회하며 d값을 바꿔줄 때, 서로 다른 shark에 대해 매핑된 shark['d']가 동일 공간을 가리키게되므로 (얕은복사) , 같은 방향을 가지는 모든 shark들의 방향이 바뀌게된다.   
해당 객체를 가리키도록 할당 시 동일 주소값을 가리키게되는 것이지 새로운 객체를 할당하는 것이 아니기 때문.   

new_board에 shark객체를 저장해서 sharks배열과 동일한 객체를 가리키고 따로 동기화 해줄 필요 없도록 했는데,  
해당 내용 사용시 이용한 것이 객체를 원시 값이 아닌 reference로 (주소값) 참조함을 이용한 것(stack에 있는 주소값을 참조, heap영역 동일 공간을 포인팅하게됨)   
d도 배열,리스트,객체라는 것을 간과했어 실수했다.    
기초를 까먹지 말자.    


### 실패코드1차(시간초과)
```python
import sys

if __name__ == '__main__':
    r,c,m =list(map(int,sys.stdin.readline().rstrip().split(" ")))
    board=[[False]*c for i in range(r)]
    sharks=[]
    d=[['space'],[0,-1],[0,1],[1,0],[-1,0]]
    for i in range(m):
        shark=list(map(int,sys.stdin.readline().rstrip().split(" ")))
        sharks.append({
            'y':shark[0]-1, #y좌표 , 0인덱스
            'x':shark[1]-1, #x좌표 , 0인덱스
            's':shark[2], #속력
            'd':list(d[shark[3]]), #방향
            'z':shark[4] # 크기
        })
        board[sharks[-1]['y']][sharks[-1]['x']]=sharks[-1]

    size_sum=0
    for fish_max_x in range(0,c): # 1. 한 칸씩 이동.
        x=fish_max_x
        #2. 낚시왕 낚시
        for y in range(0,r):
            if board[y][x]: # 가장 가까운 상어 낚시
                size_sum+=board[y][x]['z']
                board[y][x]['z']=-1
                board[y][x]=False
                break
        #3.상어 이동
        new_sharks=[]
        aft_shark=[]
        new_board = [[False] * c for i in range(r)]
        for shark in sharks:
            if shark['z']==-1: #잡아먹힌경우
                continue
            for mv in range(shark['s']):
                dx = shark['d'][0]
                dy = shark['d'][1]
                if shark['x']+dx>=c or shark['x']+dx <0 or shark['y']+dy>=r or shark['y']+dy<0: # 벽 방향으로 나아갈 때, 방향 전환
                    shark['d'][0] *= -1
                    shark['d'][1] *= -1
                    dx = shark['d'][0]
                    dy = shark['d'][1]

                shark['x']+=dx
                shark['y']+=dy

            if new_board[shark['y']][shark['x']]==False:
                new_board[shark['y']][shark['x']]=[shark]
            elif new_board[shark['y']][shark['x']]:
                new_board[shark['y']][shark['x']].append(shark)

        for shark in sharks: #  이동 후 겹치는 경우 높은 크기 상어만 남겨놓는다.
            if shark['z']==-1:
                continue
            if len(new_board[shark['y']][shark['x']])>1:
                new_board[shark['y']][shark['x']].sort(key=lambda x:-x['z'])
                new_board[shark['y']][shark['x']]=[new_board[shark['y']][shark['x']][0]]
        for shark in sharks: # new shark 배열 저장
            if shark['z']==-1:
                continue
            if new_board[shark['y']][shark['x']][0]['z'] == shark['z'] :
                new_sharks.append(shark)
        for shark in new_sharks: # list wrap 제거
            new_board[shark['y']][shark['x']]=new_board[shark['y']][shark['x']][0]

        board=new_board
        sharks=new_sharks

    print(size_sum)


"""
goal
    낚시왕이 잡은 상어 크기의 합 
input
    r,c,m (2<=r,c<=100, 0<=m<=R*c)
        r:격자판의 행 크기
        c:격자판의 열 크기
        m:상어의 수.
    상어의 정보
 
operation
    낚시왕의 초기위치 : 0,0 : 가장 오른쪽에 도달하면 이동을 멈춘다.
    매 1초마다 sequnce
        1. 낚시왕 오른족으로 한 칸 이동
        2. 낚시왕이 있는 열(column)의 상어 중 땅과 가장 가까운 상어를 잡음
        3. 상어 이동
    
    * 상어가 벽을만나고 이동하고자 하면 방향을 반대로 바꿔서 이동한다. (2칸이고 이동속도가 4라면 방향전환 3회.) (3칸이고 이동속도가 4라면 1회) (3칸이고 이동속도가 5라면 2회) 
    * 상어가 동일 칸으로 이동하는 경우 크기가 큰 상어가 나머지 상어를 잡아먹는다.(크기가 증가하거나 하진 않음)
    * 같은 크기 상어는 존재하지 않는다.
"""

```
시간 초과.   
s가 1<=s<=1000이므로, 모든 이동 시 for문을 통해 이동해주게 되면 시간복잡도가 크다.   
그러므로 수학적으로 계산해서 이동해주는 방법으로 구현.   


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 
 


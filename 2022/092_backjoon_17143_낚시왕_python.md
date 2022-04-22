## [낚시왕](https://www.acmicpc.net/problem/17143)
* 소요 시간 :  4시간 

###성공 코드
```python
import sys

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

        dx = shark['d'][0]
        dy = shark['d'][1]
        total_mv=shark['s']
        if dy==0: #x방향 이동
            if dx==1:
                rot=(total_mv+shark['x'])//(c-1)
                if rot%2==1:
                    shark['x']=c-1-(total_mv+shark['x'])%(c-1)
                if rot%2==0:
                    shark['x']=(total_mv+shark['x'])%(c-1)
                shark['d'][0]=dx*pow(-1,rot)
            elif dx==-1:
                rot=(total_mv-shark['x'])//(c-1) + 1
                if rot%2==1:
                    shark['x']=(total_mv-shark['x'])%(c-1)
                if rot%2==0:
                    shark['x']=(c-1)-(total_mv-shark['x'])%(c-1)
                shark['d'][0]=dx * pow(-1,rot)

        elif dx==0:
            if dy == 1:
                rot = (total_mv + shark['y']) // (r - 1)
                if rot % 2 == 1:
                    shark['y'] = (r - 1 - (total_mv + shark['y']) % (r - 1))
                if rot % 2 == 0:
                    shark['y'] = (total_mv + shark['y']) % (r - 1)
                shark['d'][1] = dy * pow(-1, rot)
            elif dy == -1:
                rot=(total_mv - shark['y']) // (r - 1) + 1
                if rot % 2 == 1:
                    shark['y'] = (total_mv - shark['y']) % (r - 1)
                if rot % 2 == 0:
                    shark['y'] = (r - 1) - (total_mv - shark['y']) % (r - 1)
                shark['d'][1] = dy * pow(-1, rot)

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
```



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
어려웠던 부분은 한 번에 적용되는 식을 찾으려다보니 어렵게 생각하게되고 실수가 많았다.  
내 머리로는 그냥 차근차근 접근하는 것이 좋을 것 같다.  
짜임새 있는 코드는 나중에 수정할 것. 일단 그냥 쉬운 방법으로 접근하는 것이 시간을 낭비하지 않는 방법이다.   
최종적으로는 dx, dy케이스를 나누고, 오른쪽으로 이동하는 경우, 왼쪽으로 이동하는 경우를 나누고, 거기서 또    
rotation이 짝수번 회전하는 경우, 홀수번 회전하는 경우로 나누어서 분기처리해주었다.   

```python
"""
s : 총 이동량
x : 현재 위치
c : 칸 수
dx 방향
s x c dx

################################### 1. x -방향 이동(dx== -1)
################################### 1.1 회전
x는 왼쪽 방향으로 이동한다.
o (x-1)칸만큼 회전 안하고 이동 가능. ->, 마지막 칸에 닿으면 회전한다.
o x칸 이동 시 회전,
    if total_mv == x:
        회전+1 
    if total_mv == x+c-1 :
        회전+2
    if total_mv == x+ 2(c-1):
        회전+3
       
    (total_mv-x)//(c-1) + 1 : 회전 수
    ★★★★★ rot=(total_mv-x)//(c-1) +1
################################### 1.2 최종 위치
    그렇다면 최종 위치는 ? 
    example)
        s x c dx
        1 1 6 -1
        => 0
    
        2 1 6 -1d일 때,
        ==> 최종위치 1 : rot = 1 ( (2-1)//5== 0 )
        rot = 1일 때
        (s-x)=1
        => 1이되어야함
    
        (s-x)%(c-1)=1, rot==1일 때,
        이동 횟수는  (s-x)%(c-1)
    
        8,1,6,1일 때,
        ==>최종위치 4 : rot = 2( (8-1)//5 ==1 ) #  (8-1)//(c-1)+1 = 2
            =>이 때, c-1-x= 3, (5-2=3), rot=2
            mv(s)== 8이고, 2회전 제외 시 순수 이동은 2.
            짝수 번 회전이므로 전체 칸수에서 회전 후 남은 이동횟수를 빼준다. 
       ★★★rot%2==1일 때 최종위치 = (s-x)%(c-1)
       ★★★rot%2==0일 때 최종위치 = (c-1 - (s-x)%(c-1)

################################### 2. x +방향 이동(dx== +1)
################################### 2.1 회전
s x c dx
6 1 6 -1
-> 다음 x는? : 3
1에서 시작해서
1 2 3 4 5 6 (이동 횟수)  
2 3 4 5 4 3

c-1-x칸 만큼은 회전 안하고 이동 가능.   
마지막 칸에 닿으면 회전.
    if total_mv == c-1-x 
        :회전 +1 
    total mv가 c-1-x이면 dx=1일때,
    c-1-x + (c-1)이면? 딱 끝에 닿으므로 회전한다.
    
    if total_mv == c-1-x  : rot=1
    if total_mv == 2(c-1)-x : rot=2 
    if total_mv == 3(c-1)-x : rot=3
    . . .
    ★★★★★ rot = (total_mv+x)//(c-1)
################################### 2.2 회전
    그럼 이동은?
    (total_mv+x)%(c)?
    x=4, s=3이라면?
    최종 이동은 3이어야함
    7%5= 2이다. (5-2)=3
    
    그럼 total_mv== 10일때 (rot=2)
    x=4, s=10이라면?
    최종이동은 4여야함.
    14 % 5 ==4
    
    x=4, s=12라면? (rot = 3)
    최종이동은 4여야함.
    16%5= 1
    
    rot에 따라 변경
    ★★★rot%2 ==1이면 c-1- (s+x)%c
    ★★★rot%2 ==0이면 (s+x)%c

```
위는 생각 정리했던 노트.   
   
x+방향 이동은 y+방향이동이라 변수만 거의 바꿔주는 식으로 했었기 때문에 생각 노트는 +방향, -방향 2갈래로 나누어 생각함.   
또한 회전하는 경우 마지막칸에 도달 시 회전해줘야하는지, 다음 칸으로 이동하려고 할 때 회전을 해줘야하는지, 시행착오가 많았는데, 어짜피 회전 해준 후 이동하지 않아도  
결과에 영향이 없어서 마지막 칸에 도달하면 회전하는 것으로 처리함. (인덱스로 해당 방향만큼 이동할 때 회전을 해줘야하는것이 직관적이지 않고 어렵게 느껴져서)   
체계적으로 풀지 않고 좀 정리가 안되어서 부족함을 많이 느꼈고    
이런 문제의 경우 일단 단순하게 나열하고 시간이 남으면 다듬던가 하는게 좋을 것 같다.    



#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 
 



## [아기 상어](https://www.acmicpc.net/problem/16236)
* 소요 시간 :  3시간

### 성공코드
```python
import sys
from collections import deque

n=int(sys.stdin.readline().rstrip())
board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
shark = {
    'x': 0,
    'y': 0,
    'size': 2,
    'exp': 0,
    'mv_cnt':0
}

for i,row in enumerate(board):
    for j,num in enumerate(row):
        if num==9:
            shark['x']=j
            shark['y']=i
            board[i][j]=0

while True:
    visited = list([0] * n for i in range(n))

    q = deque([])
    q.append([shark['x'], shark['y'], 0])  # x좌표, y좌표, 탐색누적시간

    fishes=[]
    min_t=9999
    #가까운 물고기 탐색.
    while q:
        x,y,t=q.popleft()
        if x<0 or y<0 or x>=n or y>=n:
            continue
        if visited[y][x]==1:
            continue
        if board[y][x] > shark['size']: # 큰 물고기 : 지나가지 못함
            continue
        visited[y][x] = 1

        #작은 물고기 케이스 : 먹고 종료.
        if board[y][x] != 0 and board[y][x] < shark['size']:
            if min_t >= t:
                fishes.append([x,y,t])
                t=min(t,min_t)

        if t<min_t:
            q.append([x,y-1,t+1])#상
            q.append([x-1,y,t+1])#좌
            q.append([x+1,y,t+1])#우
            q.append([x,y+1,t+1])#하

    fishes.sort(key=lambda x:(x[2],x[1],x[0]))
    if len(fishes)>0:
        shark['exp']+=1
        if shark['exp']>=shark['size']:
            shark['size']+=1
            shark['exp']=0
        shark['mv_cnt']+=fishes[0][2]
        shark['y']=fishes[0][1]
        shark['x']=fishes[0][0]
        board[shark['y']][shark['x']]=0
    else:
        break

print(shark['mv_cnt'])

```

----------------------------------------------------------------------------
### comment 
4/21 코드리뷰    


### 1차 실패코드(실패)
```python
n=int(sys.stdin.readline().rstrip())
    board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    shark = {
        'x': 0,
        'y': 0,
        'size': 2,
        'exp': 0,
        'mv_cnt':0
    }

    for i,row in enumerate(board):
        for j,num in enumerate(row):
            if num==9:
                shark['x']=j
                shark['y']=i
                board[i][j]=0

    while True:
        #print(board,shark)
        possible_flag = False
        #먹을 수 있는 물고기 존재 탐색
        for i,row in enumerate(board):
            for j,num in enumerate(row):
                if board[i][j]!=0 and board[i][j]<shark['size']:
                    possible_flag=True
                    break
            if possible_flag==True:
                break
        if not possible_flag:
            break

        visited = list([0] * n for i in range(n))

        q = deque([])
        q.append([shark['x'], shark['y'], 0])  # x좌표, y좌표, 탐색누적시간

        #가까운 물고기 탐색.
        while q:
            x,y,t=q.popleft()
            if x<0 or y<0 or x>=n or y>=n:
                continue
            if visited[y][x]==1:
                continue
            if board[y][x] > shark['size']: # 큰 물고기 : 지나가지 못함
                continue
            visited[y][x] = 1

            #작은 물고기 케이스 : 먹고 종료. 
            if board[y][x] != 0 and board[y][x] < shark['size']: 
                shark['exp']+=1                                   ######wrong
                if shark['exp']>=shark['size']:                   ######wrong
                    shark['size']+=1                              ######wrong
                    shark['exp']=0                                ######wrong
                shark['mv_cnt']+=t                                ######wrong
                shark['y']=y                                      ######wrong
                shark['x']=x                                      ######wrong
                board[y][x]=0                                     ######wrong
                break

            q.append([x,y-1,t+1])#상
            q.append([x-1,y,t+1])#좌
            q.append([x+1,y,t+1])#우
            q.append([x,y+1,t+1])#하

    print(shark['mv_cnt'])
```  
1차 시도. bfs를 통해 거리가 상->좌->우->하 순서로 탐색, (동일 카운트면 상,좌,우,하 순서로 우선순위이므로) -> 작은 물고기를 만나면 먹고 종료한다.     
-> 실패.     
그 이유는 만약,   

6 6 6 6 6    
1 6 상 6 6    
6 2 2 2 1    
6 1 6 6 6    
일 때, 상어(size=2)는   
  
6 6 6 6 6    
1 6 0 6 6    
6 2 상 2 1    
6 1 6 6 6    
이동 후, 좌-> 우 순서로 탐색하게된다.     
이때 q에 append되는 순서는 (1,2) -> (3,2) -> (1,3) -> (4,2)    
순이다.  
이 떄, 동일 거리 중 4,2가 1,3보다 먼저여야한다(더 위에 존재) 그러나 탐색을 나중에 하므로 (1,3)을 만났을 때 조건에 맞으므로 해당 방향으로 이동하고 stop한다.   
-> wrong   

### 2차 실패코드(시간초과)
```python
    n=int(sys.stdin.readline().rstrip())
    board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    shark = {
        'x': 0,
        'y': 0,
        'size': 2,
        'exp': 0,
        'mv_cnt':0
    }

    for i,row in enumerate(board):
        for j,num in enumerate(row):
            if num==9:
                shark['x']=j
                shark['y']=i
                board[i][j]=0

    while True:
        possible_flag = False                           #######wrong
        #먹을 수 있는 물고기 존재 탐색                   #######wrong
        for i,row in enumerate(board):                  #######wrong
            for j,num in enumerate(row):                #######wrong
                if board[i][j] !=0 and board[i][j]<shark['size']: #######wrong
                    possible_flag=True                  #######wrong
                    break                               #######wrong
            if possible_flag==True:                      #######wrong
                break                                   #######wrong
        if not possible_flag:                           #######wrong
            break                                       #######wrong

        visited = list([0] * n for i in range(n))

        q = deque([])
        q.append([shark['x'], shark['y'], 0])  # x좌표, y좌표, 탐색누적시간

        fishes=[] ###############변경
        min_t=9999 ###########변경
        #가까운 물고기 탐색.
        while q:
            x,y,t=q.popleft()
            if x<0 or y<0 or x>=n or y>=n:
                continue
            if visited[y][x]==1:
                continue
            if board[y][x] > shark['size']: # 큰 물고기 : 지나가지 못함
                continue
            visited[y][x] = 1

            #작은 물고기 케이스 : 먹지 않고 fish배열에 저장
            if board[y][x] != 0 and board[y][x] < shark['size']: ###########변경
                if min_t >= t:
                    fishes.append([x,y,t])
                    t=min(t,min_t)

            if t<min_t: #################변경
                q.append([x,y-1,t+1])#상
                q.append([x-1,y,t+1])#좌
                q.append([x+1,y,t+1])#우
                q.append([x,y+1,t+1])#하

        fishes.sort(key=lambda x:(x[2],x[1],x[0])) #############변경
        if len(fishes)>0: ##################변경
            shark['exp']+=1
            if shark['exp']>=shark['size']:
                shark['size']+=1
                shark['exp']=0
            shark['mv_cnt']+=fishes[0][2]
            shark['y']=fishes[0][1]
            shark['x']=fishes[0][0]
            board[shark['y']][shark['x']]=0

    print(shark['mv_cnt'])

```
min_t를 저장해서 먹을 수 있는 물고기를 만나면 fish배열에 저장하고, 해당 t까지만 탐색하도록 하고,    
탐색이 완료되면 배열을 정렬( 카운트, 동일카운트라면 위쪽->왼쪽 순) 하여 가장 우선순위 fish를 선택, 먹는작업 해줌.   
-> 시간초과.  
fish배열이 0개이면 먹을 수 있는 fish가 없으므로 종료하면 되는데,   
이전에는 매 step마다 먹을 수 있는 fish여부를 전체 순회했음(최대 20 * 20)   
-> wrong. 시간복잡도가 늘어남.  
해당 부분 삭제 후 통과.   


#
#
 ### learned lesson
 
* ** bfs
* 
#
#
 
 
 
 


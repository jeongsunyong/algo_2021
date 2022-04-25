## [연구소3](https://www.acmicpc.net/problem/17142)
* 소요 시간 :  4시간 

### 성공 코드
```python

```



----------------------------------------------------------------------------
### comment 
4/25 코드리뷰    

### 1차 실패 코드(시간초과)
```python
import sys
from collections import deque

def simulation(board,n,v):
    # simulation . 바이러스 선택 시, 바이러스가 전체에 퍼질 수 있는지 조사한다.
    fin_t=51*51 # 전체 탐색했을 경우 갱신 후 반환해줌.
    last_t=0 #마지막 탐색

    visited=[[0]*n for i in range(n)]
    q=deque([list(a+[0]) for a in v])
    for a in v:
        visited[a[1]][a[0]]=1

    while q:
        x,y,t=q.popleft()
        if board[y][x]==1:
            continue

        if y+1<n:
            if visited[y + 1][x] == 0:
                q.append([x, y + 1, t + 1])
                visited[y+1][x]=1
                if board[y+1][x]==0:
                    last_t = max(last_t, t+1)
        if y-1>=0:
            if visited[y-1][x] == 0:
                q.append([x, y - 1, t + 1])
                visited[y-1][x]=1
                if board[y-1][x]==0:
                    last_t = max(last_t, t+1)
        if x+1<n:
            if visited[y][x + 1] == 0:
                q.append([x + 1, y, t + 1])
                visited[y][x+1]=1
                if board[y][x + 1] == 0:
                    last_t = max(last_t, t+1)
        if x-1>=0:
            if visited[y][x - 1] == 0:
                q.append([x - 1, y, t + 1])
                visited[y][x-1]=1
                if board[y][x - 1] == 0:
                    last_t = max(last_t, t+1)

    for i in range(n):
        for j in range(n):
            if board[i][j]==0 and visited[i][j]==0:
                return fin_t

    fin_t=last_t
    return fin_t

def dfs(board,n,m,idx,cnt,vspace, v,viruses):
    global t
    if cnt>=m:
        #바이러스 전체 퍼질 수 있는지 조사
        t=min(simulation(board,n,v),t)
        return

    for i in range(idx,vspace-m+cnt+1):
        x,y=viruses[i]
        board[y][x]=-1
        dfs(board,n,m,i,cnt+1,vspace,list(v+[viruses[i]]),viruses)
        board[y][x]=2

if __name__ == '__main__':
    n,m=list(map(int,sys.stdin.readline().rstrip().split(" ")))
    board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    viruses=[]
    vspace=0
    for i,row in enumerate(board):
        for j,space in enumerate(row) :
            if space==2:
                viruses.append([j,i])#x,y
                vspace+=1

    t=51*51
    dfs(board,n,m,0,0,vspace,[],viruses)

    if t==51*51:
        t=-1

    print(t)


"""
goal
    모든 빈 칸에 바이러스를  퍼뜨리는 최소 시간 (모든 빈칸에 바이러스를 퍼뜨릴 수 없는 경우 -1 출력)
input
    n:연구소의 크기( 4<=n<=50 )
    m:놓을 수 있는 바이러스 개수(1<=m<=10)
    board:연구소의 상태
        0:빈칸
        1:벽
        2:바이러스를 놓을 수 있는 위치 (m<=2의개수<=10)
    
virus
    활성상태/비활성상태
    - 초기 : 비활성상태.
    - 활성 상태인 바이러스는 상하좌우 인접 모든 빈칸으로 동시 복제되며 1초가 걸린다
    - 바이러스 m개를 활성상태로 변경.
    - 활성 바이러스가 비활성 바이러스로 가면 비활성 바이러스가 활성으로 변한다.

    goal : 바이러스가 비활성상태라면 
"""
```
시간초과 실패.
재풀이할 것.

#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 
 


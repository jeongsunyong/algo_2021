## [새로운 게임 2](https://www.acmicpc.net/problem/17837)
* 소요 시간 :  1시간30분 

### 성공 코드
```python
import sys

n,k = list(map(int,sys.stdin.readline().rstrip().split(" ")))
board = [list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
pieces=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(k)]
d=[[1,0],[-1,0],[0,-1],[0,1]]
pieces=[ {'x':p[1]-1,
          'y':p[0]-1,
          'd':list(d[p[2]-1]) } for p in pieces]

board_p = [[ {'pieces':[]} # 말 리스트
             for j in range(n) ] for i in range(n)] # 각 칸에 어떤 말들이 있는지 저장하는 보드. 칸마다 리스트로 되어있다.( board_p[i][j][0] = 바닥, board_p[i][j][-1] = 맨 위 )

for pid, p in enumerate(pieces):
    board_p[p['y']][p['x']]['pieces'].append(pid)

t=0
stop_flag=False
while True:
    t+=1

    # 1번 말부터 k번 말까지 말 올려놓기.
    for pid,p in enumerate(pieces):
        x=p['x']
        y=p['y']
        dx,dy=p['d']

        #이동 대상 : 해당 말부터 top까지(맨위)
        mv_pieces=[]

        #현재 말 인덱스 찾기
        idx=0
        for pidx,pid_target in enumerate(board_p[y][x]['pieces']):
            if pid_target==pid:
                idx=pidx
        mv_pieces=board_p[y][x]['pieces'][idx:]

        # 체스판을 벗어나는 경우
        if x+dx<0 or y+dy<0 or x+dx>=n or y+dy>=n:
            p['d'][0]*=-1
            p['d'][1]*=-1
            dy = p['d'][1]
            dx = p['d'][0]
            if x + dx < 0 or y + dy < 0 or x + dx >= n or y + dy >= n:
                continue
            if board[y + dy][x + dx] == 2:
                continue
        ## 이동하려는 칸이 파란색(2)인 경우
        elif board[y+dy][x+dx]==2:
            p['d'][0] *= -1
            p['d'][1] *= -1
            dy=p['d'][1]
            dx=p['d'][0]
            if x + dx < 0 or y + dy < 0 or x + dx >= n or y + dy >= n:
                continue
            if board[y+dy][x+dx]==2:
                continue

        #이동 대상을 해당 칸에 옮긴다.
        if board[y+dy][x+dx]==1: # 빨간색인경우 이동 후 순서 바꿔준다.
            board_p[y + dy][x + dx]['pieces'] += reversed(mv_pieces)
        elif board[y+dy][x+dx]==0:
            board_p[y+dy][x+dx]['pieces']+=mv_pieces
        board_p[y][x]['pieces']=board_p[y][x]['pieces'][0:idx]

        # 이동된 말들 말 정보에서 좌표 갱신.
        for moved_p in mv_pieces:
            pieces[moved_p]['x']=x+dx
            pieces[moved_p]['y']=y+dy

        if len(board_p[y+dy][x+dx]['pieces'])>=4:
            stop_flag=True
            break

    if stop_flag:
        break

    if t>=1000:
        t=-1
        print(t)
        break

if t>=0:
    print(t)
```



----------------------------------------------------------------------------
### comment 
4/28 코드리뷰    
board_p : 원소가배열로 구성되있는 2차원 배열. 각 체스판(보드)에 현재 말들이 있는 리스트를 나타냄.      
board_p에 말을 옮겨가며 4개가 겹치면 stop해주는 방식으로 구현.   

1차 제출 : 실패
```python
import sys

if __name__ == '__main__':
    n,k = list(map(int,sys.stdin.readline().rstrip().split(" ")))
    board = [list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    pieces=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(k)]
    d=[[1,0],[-1,0],[0,-1],[0,1]]
    pieces=[ {'x':p[1]-1,
              'y':p[0]-1,
              'd':list(d[p[2]-1]) } for p in pieces]

    board_p = [[ {'pieces':[], # 말 리스트
                  'top':-1} # -1일경우, 맨 아래가 바닥. 1일경우 맨 위가 바닥.
                 for j in range(n) ] for i in range(n)] # 각 칸에 어떤 말들이 있는지 저장하는 보드. 칸마다 리스트로 되어있다.( board_p[i][j][0] = 바닥, board_p[i][j][-1] = 맨 위 )

    for pid, p in enumerate(pieces):
        board_p[p['y']][p['x']]['pieces'].append(pid)

    t=0
    stop_flag=False
    while True:
        t+=1

        # 1번 말부터 k번 말까지 말 올려놓기.
        for pid,p in enumerate(pieces):
            x=p['x']
            y=p['y']
            dx,dy=p['d']

            #이동 대상 : 해당 말부터 top까지(맨위)
            mv_pieces=[]

            if board_p[y][x]['top']==-1: # top이 리스트의 맨 끝일경우
                #현재 말 인덱스 찾기
                idx=0
                for pidx,pid_target in enumerate(board_p[y][x]['pieces']):
                    if pid_target==pid:
                        idx=pidx
                mv_pieces=board_p[y][x]['pieces'][idx:]
            elif board_p[y][x]['top']==1: # top이 리스트의 맨 앞일경우
                # 현재 말 인덱스 찾기
                idx = 0
                for pidx, pid_target in enumerate(board_p[y][x]['pieces']):
                    if pid_target == pid:
                        idx = pidx
                mv_pieces = board_p[y][x]['pieces'][0:idx+1]

            # 체스판을 벗어나는 경우
            if x+dx<0 or y+dy<0 or x+dx>=n or y+dy>=n:
                p['d'][0]*=-1
                p['d'][1]*=-1
                dy = p['d'][1]
                dx = p['d'][0]
                if x + dx < 0 or y + dy < 0 or x + dx >= n or y + dy >= n:
                    continue
                if board[y + dy][x + dx] == 2:
                    continue
            ## 이동하려는 칸이 파란색(2)인 경우
            elif board[y+dy][x+dx]==2:
                p['d'][0] *= -1
                p['d'][1] *= -1
                dy=p['d'][1]
                dx=p['d'][0]
                if x + dx < 0 or y + dy < 0 or x + dx >= n or y + dy >= n:
                    continue
                if board[y+dy][x+dx]==2:
                    continue

            #이동 대상을 해당 칸에 옮긴다.
            board_p[y+dy][x+dx]['pieces']+=mv_pieces
            if board_p[y][x]['top']==-1:
                board_p[y][x]['pieces']=board_p[y][x]['pieces'][0:idx]
            elif board_p[y][x]['top']==0:
                if len(board_p[y][x]['pieces'])>idx:
                    board_p[y][x]['pieces'] = board_p[y][x]['pieces'][idx+1:]
                else:
                    board_p[y][x]['pieces']=[]

            # 이동된 말들 말 정보에서 좌표 갱신.
            for moved_p in mv_pieces:
                pieces[moved_p]['x']=x+dx
                pieces[moved_p]['y']=y+dy
            # 빨간색인경우 이동 후 순서 바꿔준다.
            if board[y+dy][x+dx]==1:
                board_p[y][x]['top']*= -1

            if len(board_p[y+dy][x+dx]['pieces'])>=4:
                stop_flag=True
                break

        if stop_flag:
            break

        if t>=1000:
            t=-1
            print(t)
            break

    if t>=0:
        print(t)




"""
goal
    게임이 종료되는 턴의 번호 출력
input
    N : 체스판의 크기 (4 ≤ N ≤ 12)
    K : 말의 개수 (4 ≤ K ≤ 10)
    board : 체스판의 정수
        0 : 흰색
        1 : 빨간색
        2 : 파란색
    pieces : 말 정보 [ 행/ 열 / 이동] -> 1 idx
                                이동방향 1: (1,0),  2: (-1,0),  3: (0,-1),  4: (0,1)
    
operation
    1 turn
        : 1번 말부터 k번 말까지 순서대로 이동, 말이 4개 이상 쌓이는 순간 종료
        - A번 말 이동 시 말이 존재하는 경우 top에 A번 말 위치
        - 자신의 위에 있는 말과 함께 이동한다. 
        - 아래에 있는 말은 함께 이동하지 않는다. 아래에 있는 말이 이동할 때 위에 있는 말은 함께 이동한다. 
        
    * 이동하려는 칸이 흰색일경우
        그대로 이동
    * 이동하려는 칸이 빨간색일경우
        이동 후 쌓여있는 말 순서 변경. (flag로 전환할 것)
    * 이동하려는 칸이 파란색일경우
        A번 말 이동방향 반대로 하고 한칸 이동. 단, 방향변경 후 또 이동하려는 칸이 파란색이라면 이동하지 않고 가만히.(체스판 벗어나는 경우 동일)
        
"""
```

처음에 이동 시 빨간 칸으로 갈 때 해당 칸에 있는 전체 말들의 순서를 역전시켜줘야하는 것으로 잘못 생각해서   
top 개념을 넣어서 1/-1로 구분, top 값에 따라 맨 뒤가 바닥, 맨 앞이 바닥 여부를 판정해서 처리해줬었다.   
그러나 빨간 칸으로 갈 때 이동하고자 하는 mv대상들만 반전시켜서 넣어주는 것이므로   
해당 개념은 필요가 없고 reversed 배열만 더해주면 됨.   


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 
 


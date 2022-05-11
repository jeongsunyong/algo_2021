## [프렌즈4블록](https://programmers.co.kr/learn/courses/30/lessons/17679#)
* 소요 시간 : 약 1시간

### 성공코드
```python
def check(board,m,n,x,y,del_mask) : 
    """
    # .
    . .  #(현재) 기준으로 해당 영역을 조사한다. 
    """
    if x+1>=n or y+1>=m : 
        return
    if board[y][x]==board[y+1][x]==board[y][x+1]==board[y+1][x+1]:
        del_mask[y][x]=1
        del_mask[y+1][x]=1
        del_mask[y][x+1]=1
        del_mask[y+1][x+1]=1

def gravity(board,m,n,col):
    for row in reversed(range(1,m)):#검사대상
        if board[row][col]=='-':#현재 검사대상이 공백일경우
            for r in reversed(range(0,row)): #가장 가까운 비공백란에서 끌어온다.
                if board[r][col] != '-':
                    board[row][col]=board[r][col]
                    board[r][col]='-'
                    break

def solution(m, n, board):
    answer = 0
    cnt=0
    cnt_pre=-1
    for i,row in enumerate(board):
        board[i]=list(row)
    
    while cnt is not cnt_pre :
            
        cnt_pre=cnt
        del_mask=[[0]*n for i in range(m)]
        for y in range(m):
            for x in range(n):
                if board[y][x]!='-':
                    check(board,m,n,x,y,del_mask)
        for y in range(m):
            for x in range(n):
                if del_mask[y][x]==1:
                    board[y][x]='-'
                    cnt+=1  
        for col in range(n):
            gravity(board,m,n,col)
    
        
    answer=cnt
    return answer


"""
goal
    지워지는 블록의 개수.
input
    m : 높이(행길이)
    n : 너비(열개수)
    board : 게임판
operation
    블럭이 지워지는 케이스 : 2*2형태로 배치되어있는 case
    
"""
```


----------------------------------------------------------------------------
### comment 
5/11 코드리뷰    
처음 board자료의 형태가 row는 string으로 주어졌는데, string은 immutable하기때문에 참조로 값 변경이불가느하다   
list로 변경.   
만약 조건에 맞는 area에대해 전체 같은 것들을 제거해줘야한다면, check후에 bfs로 제거해주면 되지만 네모칸만 제거해줘야하므로 check된 대상들에대해 del_mask를 만들어 제거한다.   
이 때, mask를 만들지 않고 바로 제거한다면 ? 제거되는 area를 시작점으로하는 영역의 탐지가 불가능하므로, 옳지않음.    


#
#
 ### learned lesson
 
* ** 
*   
* 
#
#
 
 

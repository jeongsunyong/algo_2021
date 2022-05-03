## [행렬 테두리 회전하기](https://programmers.co.kr/learn/courses/30/lessons/77485?language=python3)
* 소요 시간 : 약 40분

### 성공코드
```python
def rotation(r,c,query,board,res):
    y1,x1,y2,x2=[pos-1 for pos in query]
    store=board[y1][x1]
    nums=[]
    for y in range(y1,y2): # ^
        board[y][x1]=board[y+1][x1]
        nums.append(board[y][x1])
    for x in range(x1,x2): # <-
        board[y2][x]=board[y2][x+1]
        nums.append(board[y2][x])
    for y in reversed(range(y1+1,y2+1)): # v
        board[y][x2]=board[y-1][x2]
        nums.append(board[y][x2])
    for x in reversed(range(x1+1,x2+1)): #->
        board[y1][x]=board[y1][x-1]
        nums.append(board[y1][x-1])
    
    board[y1][x1+1]=store
    nums.append(board[y1][x1+1])
    
    nums.sort()
    res.append(nums[0])
    
    
def solution(rows, columns, queries):
    answer = []
    board=[[j+i*columns for j in range(1,columns+1)] for i in range(rows)]
    
    for query in queries:

        rotation(rows,columns,query,board,answer)

    return answer


"""
goal
input
    rows : 행의 크기
    columns : 열의 크기
    queries : 회전들의 목록
        query : (x1,y1,x2,y2)로 표현 (1idx)
            x1,y1부터 y1,y2영역까지 직사각형에서 테두리에 있는 숫자들을 한 칸씩 시계방향으로 회전.
    
    board : 행렬


"""
```


----------------------------------------------------------------------------
### comment 
5/3 코드리뷰   
행렬의 영역을 받고, 가장작은 x1,y1부터 x2,y2까지 영역 중 테두리를 회전시킨다.(시계방향)       
변경되는 좌표 값은 nums배열에 저장해주고, 회전을 마치고 정렬해 가장 작은 값을 취해줌.      
이동과 정렬은 row, col이 최대 100 * 100 이고 쿼리는 최대 10,000이지만,     
테두리만큼 이동 및 정렬하므로 최대 쿼리(10,000) * 둘레길이(200(row+col) * 2)로 시간복잡도는 그렇게 크지 않음.      
만약 시간복잡도 제한이 좀 더 빡빡하다면 heapq를 쓰면 정렬 복잡도가 더 작아질 수 있다.     

#
#
 ### learned lesson
 
* ** 구현
* 
#
#
 
 

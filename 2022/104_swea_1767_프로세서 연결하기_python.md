## [프로세서 연결하기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf&categoryId=AV4suNtaXFEDFAUf&categoryType=CODE&problemTitle=&orderBy=INQUERY_COUNT&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1)
* 소요 시간 :  1시간 30분

### 성공 코드
```python

def dfs(cells,cores,n,cidx,connected_cnt,line_cnt,num_core,res):
    if cidx >= num_core:
        if res['max_cores']<connected_cnt:
            res['max_cores']=connected_cnt
            res['min_len']=line_cnt
        elif res['max_cores']==connected_cnt and res['min_len']>line_cnt:
            res['min_len']=line_cnt
        return

    core=cores[cidx]
    cx=core[0]
    cy=core[1]

    already_connected=False
    if cx==0 or cy==0 or cx==n-1 or cy==n-1 :
        already_connected=True

    # no adding lines case
    dfs(cells,cores,n,cidx+1,connected_cnt,line_cnt,num_core,res)

    if already_connected :
        return


    #upside case
    up_possible=True
    for i in range(0,cy):
        if cells[i][cx]!=0:
            up_possible=False
    if up_possible:
        for i in range(0,cy): cells[i][cx]=-1
        dfs(cells, cores, n,cidx + 1, connected_cnt + 1, line_cnt+cy,num_core,res)
        for i in range(0, cy): cells[i][cx] = 0
    #downside case
    down_possible=True
    for i in range(cy+1,n):
        if cells[i][cx]!=0:
            down_possible=False
    if down_possible:
        for i in range(cy+1,n): cells[i][cx]=-1
        dfs(cells, cores, n,cidx + 1, connected_cnt + 1, line_cnt+n-cy-1,num_core,res)
        for i in range(cy+1,n): cells[i][cx] = 0
    #leftside case
    left_possible=True
    for j in range(0,cx):
        if cells[cy][j]!=0:
            left_possible=False
    if left_possible:
        for j in range(0,cx): cells[cy][j]=-1
        dfs(cells, cores, n,cidx + 1, connected_cnt + 1, line_cnt+cx,num_core,res)
        for j in range(0,cx): cells[cy][j] = 0
    #rightside case
    right_possible=True
    for j in range(cx+1,n):
        if cells[cy][j]!=0:
            right_possible=False
    if right_possible:
        for j in range(cx+1,n): cells[cy][j]=-1
        dfs(cells, cores, n,cidx + 1, connected_cnt + 1, line_cnt+n-cx-1,num_core,res)
        for j in range(cx+1,n): cells[cy][j] = 0

T = int(input())
for test_case in range(1, T + 1):
    n=int(input())
    cells=[list(map(int,input().rstrip().split(" "))) for loop_cnt in range(n)]
    cores=[]
    for i,row in enumerate(cells):
        for j,cell in enumerate(row):
            if cell==1:
                cores.append([j,i])
                num_core=len(cores)
    res={
        'max_cores':0,
        'min_len':n*n+1
    }
    dfs(cells,cores,n,0,0,0,num_core,res)
    
    print(f"#{test_case} {res['min_len']}")

```



----------------------------------------------------------------------------
### comment 
4/30 코드리뷰   
프로세스가 연결되는 모든 경우를 구하는 문제.     
DFS로 풀이. (탐색대상인 core가 최대 12개)     
주의점은 모든 코어가 연결되지 않을수도 있다는 점.   
하나의 코어에대해 dfs에서 up,down,left,right side case를 탐색하도록 구현했는데,   
연결되지 않는 케이스도 고려해야한다. (연결되지 못하는게 아니라, 연결 안하는 케이스도 세기 위함. )    
또 up,down,left,right도 라인 경로에 빈공간이 아닌 영역이 있다면 해당 케이스는 탐색하지 않는다.   


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션,dfs
* 
#
#
 
 
 


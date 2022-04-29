## [마법사 상어와 파이어스톰](https://www.acmicpc.net/problem/20058)
* 소요 시간 :  1시간30분 

### 성공 코드
```python
import sys
sys.setrecursionlimit(10**4)

def checkSize(board, j, i, visited, n):
    visited[i][j] = 1
    cnt = 1
    if i - 1 >= 0:
        if visited[i - 1][j] == 0 and board[i - 1][j] > 0:
            cnt += checkSize(board, j, i - 1, visited, n)
    if i + 1 < pow(2, n):
        if visited[i + 1][j] == 0 and board[i + 1][j] > 0:
            cnt += checkSize(board, j, i + 1, visited, n)
    if j - 1 >= 0:
        if visited[i][j - 1] == 0 and board[i][j - 1] > 0:
            cnt += checkSize(board, j - 1, i, visited, n)
    if j + 1 < pow(2, n):
        if visited[i][j + 1] == 0 and board[i][j + 1] > 0:
            cnt += checkSize(board, j + 1, i, visited, n)

    return cnt

if __name__ == '__main__':
    n,q=list(map(int,sys.stdin.readline().rstrip().split(" ")))
    board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(pow(2,n))]
    levels=list(map(int,sys.stdin.readline().rstrip().split(" ")))

    # a. firestorm
    for l in levels:
        #1.단계 L결정
        div=pow(2,l)
        #2. 모든 부분 격자를 시계 방향으로 90도 회전.
        y=0
        while y<pow(2,n):
            x=0
            while x<pow(2,n):
                origin = [list(row[x:x+div]) for row in board[y:y+div]]
                #print(f"x,y {x} {y} / div : {div}")
                #print(origin)
                for i in range(div):
                    for j in range(div):
                        board[y+i][x+j]=origin[div-j-1][i]
                x += div
            y += div

        #3. 얼음이 2칸 이하로 인접해있는 칸은 얼음 양 -1.
        origin=[list(row) for row in board]
        for i in range(pow(2,n)):
            for j in range(pow(2,n)):
                cnt=0
                if i-1>=0:
                    if origin[i-1][j]>0:
                        cnt+=1
                if i+1<pow(2,n):
                    if origin[i+1][j]>0:
                        cnt+=1
                if j-1>=0:
                    if origin[i][j-1]>0:
                        cnt+=1
                if j+1<pow(2,n):
                    if origin[i][j+1]>0:
                        cnt+=1
                if cnt<3:
                    board[i][j]=max(0,board[i][j]-1)

    # b. 결과 계산
    visited=[[0]*pow(2,n) for i in range(pow(2,n))]
    sum_ice=0
    max_size=0
    # 얼음 크기의 합
    for row in board:
        for ice in row:
            sum_ice+=ice

    # 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸 개수
    for i,row in enumerate(board):
        for j,ice in enumerate(row):
            if visited[i][j]==0 and board[i][j]>0:
                cnt=checkSize(board,j,i,visited,n)
                max_size=max(cnt,max_size)

    print(sum_ice)
    print(max_size)



"""
#goal
    남아있는 얼음 A[r][c]의 합, 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수.
            (인접한 얼음이 있는 칸들은 연결되어있으며 덩어리는 연결된 칸의 집합임.)
#input
    n : 격자 크기 척도(2^n) (2<=n<=6)
    q : 마법사 상어가 시전한 단계 개수 = 파이어스톰 시전 횟수 (1<=q<=1000)
    board : 얾음의 양이 담겨있는 격자
        board[r][c] : (r,c)에 담겨있는 얼음의 양 (1<= board[r][c]<=100)
#firestorm    
    1.단계 L 결정
    2.격자를 (2^L) * (2^L)크기로 나눈다.
    3. 모든 부분 격자를 시계 방향으로 90도 회전.
    4. 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양 1 감소. (상하좌우)
    
rotation
    ex) div=2
        origin
        1(0,0) 2(1,0)
        9(0,1) 10(1,1)
        ->
        board
        9(0,0) 1(1,0)
        10(0,1) 2(1,1)
        90도 회전 시 y <-> x로 변경되었음.
        x에서 원래 작은 값이던 애들은 그대로 작은 y값을 가짐. ->  old i (y) : j
        그러나 y값이 원래 작던 애들은 큰 x값을 가지게됨. -> old j (x) : div-i
        
        ->문제 : 반대회전으로 인덱스입력됨.
        반대 회전 생각해봤을 때
        new y : div-j
        new x = i

"""
```



----------------------------------------------------------------------------
### comment 
4/30 코드리뷰    

pypy3 제출. 통과
set recursion하는경우 python3은 10^9까지도 괜찮은데, pyyp3에서는 10^6으로 설정 시 메모리 초과이다.    
그 이유는 pypy3는 더 빠르다. v8엔진의 js처럼 미리 컴파일을 해두는 구조이기 때문이다(JIT) .     
그러나 pypy3은 가비지컬렉터가 python과 달라 더 많은 메모리를 사용하는 구조라고 함.   (learned lessons 링크 참고)

구현은 요구사항 순서대로 구현. 주의점은 얼음이 2칸 이하로 인접해있는 칸은 얼음 양 -1.할 때 max(값,0)해줌.   
그냥 -1하게되면 0인 케이스도 -1하기때문에, max(0,값) 안해줄거면 for문에서 0인경우는 continue해줘야함.   
이런 디테일을 놓치지 말자  

이번 문제는 회전 + 탐색(dfs or bfs)가 핵심인 것 같은데  
회전의 경우 90도 좌표계 변환을 하게되면   
a b 
c d 가 

c a
b d가된다.   

a의 x좌표(0)은 새로운 좌표계에서 y값이된다.(x,0)   
b의 x좌표값(1)도 마찬가지로 (x,1)이 됨.   
c의 x좌표(0)도 마찬가지로 새로운 좌표계에서 y값이되고 d도 마찬가지.     

a의 y좌표(0)은 새로운 좌표계에서 역순이 되고, 2-1-0이 된다.   
a,c를 비교했을 때 y좌표가 더 큰 c가 더 왼쪽, 0에 가까워지고, y좌표가 작은 a가 더 큰쪽, 1에 가까워지므로.   

다만 새로운 배열에 값을 할당할 때,
반대 회전값으로 할당해주어야한다. 

x에서 원래 작은 값이던 애들은 그대로 작은 y값을 가짐. ->  old i (y) : j     
그러나 y값이 원래 작던 애들은 큰 x값을 가지게됨. -> old j (x) : div-i     

->문제 : 반대회전으로 인덱스입력됨.      
반대 회전 생각해봤을 때     
90도 회전했을 때 새로운 배열로 값을 옮기는 인덱스는   
new y : div-j     
new x = i     


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* [pypy에서는 정확한 크기를 할당하는 것이 아니라 대략적으로 크기를 할당한다.](https://imksh.com/46)
* 
#
#
 
 
 

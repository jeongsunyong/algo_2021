
## [등굣길](https://programmers.co.kr/learn/courses/30/lessons/42898)
* 소요 시간 :  20분

### 성공코드
```python
def solution(m, n, puddles):
    answer = 0
    puddle_map=[[0]*(m+1) for i in range(n+1)]
    dp=[[0]*(m+1) for i in range(n+1)]
    puddles=[[p[0]-1,p[1]-1] for p in puddles]
    for p in puddles:
        puddle_map[p[1]][p[0]]=1
    
    dp[0][0]=1
    for i in range(n):
        for j in range(m):
            if puddle_map[i][j]==1:
                continue
            if i-1>=0:
                dp[i][j]=(dp[i][j]+dp[i-1][j])%1000000007
            if j-1>=0:
                dp[i][j]=(dp[i][j]+dp[i][j-1])%1000000007
    answer=dp[n-1][m-1]
    return answer

"""
goal 오른,아래쪽으로만 움직여 집에서 학교까지 갈 수 있는 최단경로 수
input
    m,n : 격자의크기 1<=m,n<=100 , m==n==1인경우는 x
    puddles : 물이 잠긴 지역들

아래,오른쪽으로만 이동하므로 해당 경로까지 도달하는 경우의 수는 항상 최단이다.
    

"""
```

----------------------------------------------------------------------------
### comment 
4/15 코드리뷰    

아래 오른쪽으로만 이동했을 때 최소 이동 경로의 개수 구하기.   
단방향 이동이므로 해당 칸으로 이동하는 경우의 수는 모두 동일 카운트이다.   
ex) 0.n으로 이동하는 경우의 수는 n번 이동하는 경우 뿐이고, n,0도 마찬가지이다.   
1,n으로 이동하는 경우의 수는 0,n까지 도달 후 1회 x이동하거나 1,0까지 도달 후 n회 y이동 두 가지 경우 합으로 표현가능하고 m,n으로 이동하는 경우의 수의 이동횟수는 m+n.   
puddle(물웅덩이)를 만났을 경우에는 해당 칸에 도달 할 수 있는 경우의 수는 0으로, 우회경로는 최소경로를 만족하지 않아 카운트에서 제외시켜줘야하므로   
해당 칸의 경우의 수를 0으로 넣으면 dp배열은 왼쪽, 위쪽 카운트를 더한 카운트로 최소경로개수를 구할 수 있다.   


#
#
 ### learned lesson
 
* ** dp
#
#
 
 
 
 


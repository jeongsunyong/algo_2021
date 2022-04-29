## [원판 돌리기](https://www.acmicpc.net/problem/17822)
* 소요 시간 :  2시간 



### 성공 코드
```python
import sys
from collections import deque

def findAdjacency(num,cir,circles,visited,n,m):
    q = deque([])
    base_number=circles[cir][num]
    q.append([num,cir])
    changed_flag=False
    #1. 인접1조사
    while q:
        j,i=q.popleft()
        if i >= n or i < 0 or j >= m or j < 0:
            continue
        if visited[i][j]==1 or circles[i][j]==-1:
            continue
        if circles[i][j] != base_number:
            continue

        if not (num==j and cir==i):
            changed_flag=True

        visited[i][j]=1
        circles[i][j]=-1
        q.append([(j+1)%m, i])
        q.append([(j-1) % m, i])
        q.append([j, i+1])
        q.append([j, i-1])

    if changed_flag==False:
        circles[cir][num]=base_number
    return changed_flag


if __name__ == '__main__':
    n,m,t=list(map(int,sys.stdin.readline().rstrip().split(" ")))
    circles=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]
    rotations=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(t)]
    direction=[1,-1]
    for rot in rotations: # 각 회전 수행
        x=rot[0]
        d=direction[rot[1]]
        k=rot[2]

        num=x-1

        # 번호가 x의 배수인 원판 회전
        while num<n:
            #방향:d, k번 회전
            circle_rot=list(circles[num])
            for j, c in enumerate(circles[num]) :
                circle_rot[(j + k*d)%m]=c
            circles[num]=circle_rot
            num+=x

        # 원판 인접 조사 및 값 조작
        visited=[[0]*m for i in range(n)]
        changed_flag=False
        for i,cir in enumerate(circles):
            for j,num in enumerate(cir):
                if visited[i][j]==0 and circles[i][j] != -1:
                    if findAdjacency(j,i,circles,visited,n,m):
                        changed_flag=True

        if not changed_flag:
            #평균구하기
            ccnt=0
            nsum=0
            for circle in circles:
                for num in circle:
                    if num != -1:
                        ccnt+=1
                        nsum+=num
            if ccnt==0:
                continue
            navg=nsum/ccnt
            for circle in circles:
                for j,num in enumerate(circle):
                    if num != -1 and  num > navg:
                        circle[j]-=1
                    elif num != -1 and num < navg :
                        circle[j]+=1

    sum_num=0
    for circle in circles:
        for num in circle:
            if num!=-1:
                sum_num+=num



    print(sum_num)

"""
#goal
    원판을 t번 회전시킨 후 원판에 적힌 수의 합
#input
    n : 원판의 개수.(각 원판은 반지름이 1~n)
    m : 원판의 적혀있는 숫자 개수
    t : 총 회전 횟수
    circles : 원판에 적힌 수 (n개)
        circles[i][j] : i번째 원판에 적힌 j번째 수    
    rotations
        x : 번호가 x의 배수인 원판을 (1dx)
        d : d방향으로 (d==0 : 시계방향 , d==1 : 반시계방향)
        k :k칸 회전시킨다

#circles adjacency (circle,number)
    - 1,cir은 2,cir와 m,cir 과 인접 (circular) -> cir,num는 (num-1,cir) & (num+1,cir)와 인접
        동일 원판에 적힌 숫자는 circular하게 인접한다 
    - num,1은 num,2와 인접 , num,n은 num,n-1과 인접 (not circular)
        서로 다른 원판에 적힌 동일 숫자는 non-circular하게 인접한다.
    
#rotation
    1.번호가 x배수인 원판을 d방향으로 k칸 회전.
    2.원판에 수가 남아있다면 인접하며 수가 같은 것들을 찾고, 
            인접하며 수가 같으면 지운다. 
            없는경우 원판에 적힌 수의 평균을 구하고 평균보다 큰 수는 -1, 작은 수에는 +1을 해준다.  

"""
```



----------------------------------------------------------------------------
### comment 
4/29 코드리뷰    

원판들에 대해 회전 -> 인접 판단 및 숫자 조작을 t회 수행해준다.   
원판 회전은 circular하게 요구사항에 따라 회전   
숫자 조작 시,  
각 칸마다 bfs를 수행해주되, 다음 칸 탐색 조건을 첫 진입 칸과 같은 숫자들에 대해 인접으로 판단, 탐색해준다.   
탐색된 영역은 -1로 변경.(숫자제거)   
이 때 자신만 탐색한 경우는 숫자 제거를 하지 않도록 해준다.   
인접수가 해당 조사 시 하나라도 나와서 숫자가 제거 된 경우가 일반 케이스,  
이번 회전에서 숫자 제거가 되지 않았다면 제거되지 않은 숫자의 평균을 구해서 크면 -1, 작으면 +! 수행해줌.   

이후 -1이 아닌 수의 합을 출력한다. 



#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 

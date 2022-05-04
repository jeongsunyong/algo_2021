## [거리두기 확인하기](https://programmers.co.kr/learn/courses/30/lessons/81302?language=python3)
* 소요 시간 : 약 25분

### 성공코드
```python
from collections import deque

def solution(places):
    answer = []
    for place in places:
        applicants=[]
        for i,row in enumerate(place):
            for j,block in enumerate(row):
                if block=='P':
                    applicants.append([j,i])

        dist_flag=True
        for a in applicants:
            if not dist_flag:
                break
            ax=a[0]
            ay=a[1]
            q=deque([[ax,ay,0]]) #pos, cnt
            visited=[[0]*5 for i in range(5)]
            while q:
                x,y,dist=q.popleft()
                if x<0 or x>=5 or y<0 or y>=5:
                    continue
                if visited[y][x]==1:
                    continue
                if place[y][x]=='X':
                    continue
                if dist>2:
                    continue
                if place[y][x]=='P' and not(y==ay and x==ax):
                    dist_flag=False
                    break
                visited[y][x]=1
                q.append([x+1,y,dist+1])
                q.append([x-1,y,dist+1])
                q.append([x,y+1,dist+1])
                q.append([x,y-1,dist+1])

        if dist_flag==True:
            answer.append(1)
        else:
            answer.append(0)
                
                
    return answer


"""
goal
    대기실별 거리두기 지키고있다면 1, 아니면 0
input
    places : 대기실 구조(들)
        P : 응시자가 앉아있는 자리
        O : 빈테이블
        X : 파티션
    대기실은 5*5  의 5개  

rule
    - 응시자들끼리는 맨해턴거리가 2 이하로 앉지 않도록 함.
    - 응시자가 앉아있는 자리 사이가 파티션으로 막혀 있을 경우에는 허용.
     
    맨해튼거리
     |r1 - r2| + |c1 - c2|
"""
```


----------------------------------------------------------------------------
### comment 
5/4 코드리뷰   
BFS.
조건 상 파티션을 만나면 거리에 상관없이 rule을 지킨 것이 되므로 파티션 접근 시 이후는 탐색하지 않는다.   
맨해튼거리는 1칸 이동 시 1의 거리가 증가하므로 bfs로 탐색하면서 거리를 1씩 늘려가서 조건범위(2)내의 공간들을 탐색.   


#
#
 ### learned lesson
 
* ** bfs
* 
#
#
 
 

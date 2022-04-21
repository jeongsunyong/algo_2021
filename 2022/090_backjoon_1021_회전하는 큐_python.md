
## [회전하는 큐](https://www.acmicpc.net/problem/1021)
* 소요 시간 :  1시간

### 성공코드
```python
import sys
from collections import deque
if __name__ == '__main__':
    n,m=list(map(int,sys.stdin.readline().rstrip().split(" ")))# 큐 크기n, 뽑기갯수 m
    idxs=list(map(int,sys.stdin.readline().rstrip().split(" "))) #뽑으려는 수 위치

    q=[i for i in range(1,n+1)]
    q=deque(q)
    
    len_q=len(q)
    front=0
    rear=len_q-1
    cnt=0

    for idx in idxs:
        operation=1
        #operation 판정
        if idx==q[front] :
            operation=1
        elif (abs(q.index(idx)-front)<= len_q/2 and front<q.index(idx)) or (abs(q.index(idx)-front)>=len_q/2 and front>q.index(idx)): 
            operation=2
        else:
            operation=3

        if operation==1:
            del q[front]
            len_q-=1
            if len_q == 0:
                break
            front=front%len_q
            continue

        if operation==2:
            while q[front]!=idx:
                front=(front + 1)%len_q
                rear=(rear + 1)%len_q
                cnt += 1

        elif operation==3:
            while q[front]!=idx:
                front = (front - 1) % len_q
                rear = (rear - 1) % len_q
                cnt += 1

        del q[front]
        len_q -= 1
        if len_q==0:
            break
        front=front%len_q

    print(cnt)

"""
goal
    원소를 주어진 순서대로 뽑아내는데 드는 2번, 3번 연산의 최솟값을 출력
input
    큐 크기n, 뽑기갯수 m
    idxs 뽑으려는 수 위치
operation
    첫 번째 원소 뽑아냄
    왼쪽으로 한 칸 이동
    오른쪽으로 한 칸 이동
    
"""

```

----------------------------------------------------------------------------
### comment 
4/20 코드리뷰    
queue에 숫자를 순서대로 뽑아내야한다.  
해당 숫자를 뽑아내기 위한 최소 이동 횟수는 현재 front에서 오른쪽으로 회전(연산2) 혹은 왼쪽으로 회전(연산3)   
중 하나이다    
그러므로 첫 번째 원소를 바로 뽑아낼 수 있다면 operation 1을,
불가능하다면 2가 최소 이동인지 3이 최소 이동인지 판단 후,   
front를 옮겨준다.  
이동 마다 cnt를 증가시켜주고 마지막에 반환.   





#
#
 ### learned lesson
 
* ** 데크
* 
#
#
 
 
 
 


# Lessons13.Fibonacci numbers
## [13.1 FibFrog](https://app.codility.com/programmers/lessons/13-fibonacci_numbers/fib_frog/)
* 소요 시간 : 3시간

### 성공 코드
```python

```

--------------------------------------------------------------------
### 2.21 comment    

```python
def solution(A):
    N=len(A)
    fibs=[1,1]
    fib_flags=[0]*(N+3)
    fib_flags[1]=1
    for i in range(0,N+2):
        fib=fibs[i]+fibs[i+1]
        if fib > N+2:
            break
        fibs.append(fib)
        fib_flags[fib]=1

    leaves=[idx for idx,flag in enumerate(A) if flag==1]
    leaves.append(N)
    leaves.reverse()

    pos=-1
    cnt=0

    target=0
    pre_target=0 
    len_leaves=len(leaves)
    while True:
        #0.target이 len_leaves범위를 넘어갔을 때, 판정
        if target>=len_leaves:
            cnt=-1
            break
        leaf=leaves[target]

        #1.앞의 모든 leaf에 대해 jump 불가능 한 경우
        if leaf <= pos:
            pos=-1 #pos 초기화, 해당 target이전부터 재조사
            target=pre_target+1
            pre_target=target
            cnt=0
            if target>=len_leaves:
                cnt=-1
                break
            continue
        
        #2. 현재 pos에서 leaf로 fib jump로 못가면 target leaf 변경.
        if fib_flags[leaf-pos] != 1:
            target+=1
            continue
        #3.가능하면 pos변경.
        else:
            if pos==-1:
                pre_target=target
            pos=leaf
            cnt+=1
            if pos==N:
                break
            else:
                target=0

    return cnt
        
"""
GOAL : 최소 점프 횟수 (target 도달)
배열 A : 정수, size N 
    0 : no leaf;
    1 : a leaf.
개구리 pos
    - init pos : pos-1
    - target pos : N
JUMP
    F(K)만큼만 뛸 수 있다.(any K)
    F(K) : K-th 피보나치수
    init -> target 방향으로만(+)

N is an integer within the range [0..100,000];
each element of array A is an integer that can have one of the following values: 0, 1.
"""


"""
방1
    leaves : 큰 순서대로 조사
    (1)현재 pos에서 leaf로 fib jump로 못가면
    그 다음 leaf로 조사.
    (2)가능하면 pos변경.
        if N==pos
            break
        else
            N-pos부터 시작.

    최초 1만큼 뛴 후 N-2만큼 뛰는것이 정답일 때,
    1 0 1 0 0 0 0 1
    0 1 2 3 4 5 6 7 

    -1 -> 0
    0-> 8 (2)
    알고리즘상으로는
    0->2, 2->7 7->8(3) wrong
    최소 보장되지 X, 잘못된 접근

"""

```

최초 제출 코드 : fail    
접근 방법은 큰 숫자의 leaf(goal : N)부터 접근해서      
해당 위치로 점프 가능할 시 pos를 갱신, 해당 pos부터 다시 큰 숫자의 leaf(goal : N)까지 jump가능한지를 조사.    
불가능하다면 시작 jump지점을 낮춰서 동일 반복해     
pos = N이 될 때 해당 카운트를 반환하는것이었으나,   
leaf:    1 0 1 0 0 0 0 1     
indx:    0 1 2 3 4 5 6 7     
위의경우,   
-1 -> 0   
0-> 8 (2) min cnt이나   
알고리즘상으로는    
-1->2, 2->7 7->8(3) wrong    
최소 보장되지 X, 잘못된 접근    



    
    
#
 ### learned lesson
 
* ** Fibonacci numbers
* Fibonacci numbers


#

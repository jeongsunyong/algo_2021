
# Lessons9. MaxSlice
## [9.2 MaxSliceSum](https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_slice_sum//)
* 소요 시간 : 25분

### 성공 코드
```python
def solution(A):
    start=[]
    s_sum=0
    max_sum=-1000000
    for i,num in enumerate(A):
        if s_sum<0:
            start.append(i)
            s_sum=0
        s_sum+=num
        if s_sum > max_sum:
            max_sum=s_sum

    start.append(len(A))
    for idx in range(len(start)-1):
        s_sum=0
        for i in range(start[idx],start[idx+1]):
            s_sum+=A[i]
            if s_sum>max_sum:
                max_sum=s_sum
    
    return max_sum

"""
    goal : maximum sum of slice
    A : int arr , nonempty size N
    (P,Q) : slice of A

"""
```

--------------------------------------------------------------------
### 2.12 comment    
loop 1) 첫 루프에서 0 미만이 됬을 경우의 범위를 저장.(0 미만까지 더해진 값들은 최댓값에 포함될 수 없음.)
loop 2) 해당 범위들을 조사. (이 때 순차적으로 순회하며 범위 저장하므로 O(N)범위 내에서 조사하게된다.

### Analysis - time complexity

>
  Detected time complexity:
  O(N)  

    
----------------------------------------------
## [9.3 MaxDoubleSliceSum](https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_double_slice_sum/)
* 소요 시간 : 50분

### 성공 코드
```python
def solution(A):
    N=len(A)
    XtoY=[0]*N
    YtoZ=[0]*N
    
    for i in range(1,N-1):
        XtoY[i]=max(0,XtoY[i-1]+A[i])
    for i in reversed(range(1,N-1)):
        YtoZ[i]=max(0,YtoZ[i+1]+A[i])

    max_sum=0

    for i in range(1,N-1):
        max_sum=max(max_sum,XtoY[i-1]+YtoZ[i+1])

    return max_sum

```

--------------------------------------------------------------------
### 2.12 comment    
1차 제출 실패
```python
def solution(A):
    negatives=[0]
    for i in range(2,len(A)):
        num=A[i]
        if num<0:
            negatives.append(i)

    negatives.append(len(A))
    max_sum=-10000
    len_negatives=len(negatives)
    if len_negatives <3 :
        return sum(A)-A[0]-A[-1]
    for idx in range(len_negatives-2):
        s_sum=0
        for i in range(negatives[idx]+1,negatives[idx+2]):
            if i==negatives[idx+1]:
                continue
            s_sum+=A[i]
            if s_sum>max_sum:
                max_sum=s_sum
    
    return max_sum


"""
    goal :double slice 최댓값
    A : integer, non empty, size N arr
    (X,Y,Z) : total of A[X + 1] + A[X + 2] + ... 
    + A[Y - 1] + A[Y + 1] + A[Y + 2] + ... + A[Z - 1].
    ( 0 ≤ X < Y < Z < N)
        : X,Y,Z값을 제외한 X~Z값 (x,z) - y

    N is an integer within the range [3..100,000];
    each element of array A is an integer within the range [-10,000..10,000].
"""
```
음수값을 기준으로 split 해 두 구간 사이 음수값을 한 개 뺀 sum들조사    
=> 8 8 8 -1 8 8 -1 8 8 -1 8 8 일 때,-1 3개를 포함하더라도 끝까지 합하는게 이득이므로 틀린풀이(구간을 나누면 안되고 모든 sum case 에서 음수 하나를 제외시켜준 값 중 최대를 취해야함.   
=> 각 인덱스까지의 합을 누적한다. 
이 때 더해서 음수가 되기까지의 범위는 최댓값에 포함될 수 없으므로 0.
loop1) 1부터 올라가며 조사한다.
loop2) N-1부터 내려가며 조사한다.
이 때 Y에 해당하는 숫자값은 빼고 max를 조사해야하므로
마지막 loop에서 해당 값 전 후의 합 중 최대값을 반환.

### Analysis - time complexity

>
  Detected time complexity:
  O(N)  

    
----------------------------------------------

#
 ### learned lesson
 
* ** MaxSlice
* MaxSlice

#
 
 

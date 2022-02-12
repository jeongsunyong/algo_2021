
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

#
 ### learned lesson
 
* ** MaxSlice
* MaxSlice

#
 
 

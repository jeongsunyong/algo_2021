
# Lessons8. Leader
## [8.2 EquiLeader](https://app.codility.com/programmers/lessons/8-leader/equi_leader/)
* 소요 시간 : 1시간+1시간

### 성공 코드
```python
def solution(A):
    N=len(A)
    left={}
    right={}

    for num in A:
        if num in right:
            right[num]+=1
        else:
            right[num]=1
    
    equi_leader_cnt=0
    len_r=N
    len_l=0
    leader_l=0
    leader_l_cnt=0

    for num in A:
        right[num] -= 1
        len_r -=1
        if num in left:
            left[num]+=1
        else:
            left[num]=1

        len_l+=1
        if left[num] > leader_l_cnt:
            leader_l = num
            leader_l_cnt=left[num]
        
        if right[leader_l] > len_r/2 and leader_l_cnt > len_l/2 :
            equi_leader_cnt+=1

    return equi_leader_cnt
"""
    * GOAL : equi leader 개수 세기
    * A non empty, integer
        size N
    N is an integer within the range [1..100,000];
    each element of array A is an integer within the range [-1,000,000,000..1,000,000,000].

    * equi leader
        an index S such that 0 ≤ S < N - 1 and 
        two sequences A[0], A[1], ..., A[S] and A[S + 1], A[S + 2], ..., A[N - 1] 
        S로 나눠질 때 0~S , S+1~N-1에서 같은 값의 leader를 갖는 idx

"""

```

--------------------------------------------------------------------
### 2.10 comment    
구글링.
dictionary를 쓸 생각을 왜 못했는지 위 구조가 안떠올라서 못풀다가 결국 구글링해서 아이디어 읽고 풀이.  



### Analysis - time complexity

>
  Detected time complexity:
  O(N)  

    
----------------------------------------------

#
 ### learned lesson
 
* ** Leader
* dominant한 원소를 leader라고 한다.

#
 
 

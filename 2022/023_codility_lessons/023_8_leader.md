
# Lessons8. Leader
## [8.1 Dominator](https://app.codility.com/programmers/lessons/8-leader/dominator/)
* 소요 시간 : 20분

### 성공 코드
```python
def solution(A):
    N=len(A)
    pre=2147483648
    dominator_idx=-1
    A_sorted=sorted(A)
    conseq_cnt=0
    for num in A_sorted:
        if num == pre:
            conseq_cnt+=1
        else :
            conseq_cnt=1
        if conseq_cnt > N/2:
            dominator_idx=A.index(num)
            break
        pre = num

    return dominator_idx
        

"""
    GOAL : dominatior 반환 , 없을 시 -1
    A : 
        size N
    dominator of arr : 배열에서 과반수 초과 차지하는 원소
    N is an integer within the range [0..100,000];
    each element of array A is an integer within the range [-2,147,483,648..2,147,483,647].
"""
```

--------------------------------------------------------------------
### 2.10 comment    

1차제출 실패코드

```python
def solution(A):
    N=len(A)
    dominator_idx=-1
    set_A = set(A)
    for num in set_A:
        if A.count(num) > N/2:
            dominator_idx=A.index(num)
            break
    return dominator_idx

```
loop마다 count를해줬는데, 배열 전체 탐색하는 방식이기 때문에 시간복잡도가 O(N).
변경 풀이는 정렬 후 연속num개수를 세서 과반수 초과일 때 break하는 방식으로 작성 후 제출. 통과


### Analysis - time complexity

>
  Detected time complexity:
  O(N*log(N)) or O(N)

    
-----------------------------------------------


#
 ### learned lesson
 
* ** Leader
* dominant한 원소를 leader라고 한다.

#
 
 

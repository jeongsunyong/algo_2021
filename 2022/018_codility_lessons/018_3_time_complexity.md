# Lessons3. Time Complexity
## [3.1 FrogJump](https://app.codility.com/programmers/lessons/3-time_complexity/frog_jmp/)
* 소요 시간 : 10분

### 성공 코드
```python
import math

def solution(X, Y, D): #X:init pos/ Y: target pos / D: jump distance
    return math.ceil((Y-X)/D)
"""
    GOAL : min 점프 횟수 구하기.(X -> Y혹은Y보다큰위치)
    X, Y and D are integers within the range [1..1,000,000,000];
    X ≤ Y.
"""

```

--------------------------------------------------------------------
### 2.5 comment    

#### case - Correctness tests   
> 
    (1) simple : 일반 케이스      
        * simple test   
    (2) extreme_position  : X=Y      
        * no jump needed   
    (3) small_extreme_jump : D>=Y-X              
        * one big jump    

#### case - Performance tests     
>
    (4) many_jump : 큰 규모값 수 케이스    
        * many jumps, D = 2    
    (5) big_extreme_jump : jump횟수 max 케이스    
        * maximal number of jumps        

### Analysis - time complexity

>
  Detected time complexity:
  O(1)    

-------------------------------------------------------------------------------


## [3.2 PermMissingElem](https://app.codility.com/programmers/lessons/3-time_complexity/perm_missing_elem/)
* 소요 시간 : 16분


### 성공 코드
```python
def solution(A):
    A.sort()
    pre=0
    result=1
    for element in A:
        if pre+1 != element:
            result=pre+1
            break
        pre=element
    if pre==len(A):
        result=pre+1

    return result

"""
    GOAL : 연속된 수 배열(random배치) 중 없는 수 찾기
    A : 서로다른수의 N개 element (in [1..(N+1)])배열
        => 1개의 missing element존재

    N is an integer within the range [0..100,000];

    case
        N=0인경우 1반환.(missing할 element가 1뿐)
        missing :N+1인경우 존재할 수 있는지 ? -> within range[1~N+1]: O
            마지막 원소까지 검사했을 경우 pre에 저장, pre+1반환
        missing : 1인경우
            initial pre=0 -> next 2이므로 조건문에의해 1 반환

"""

```


--------------------------------------------------------------------
### 2.5 comment    
* 1회 실패(90%)      
  - case : empty_and_single (RUNTIME ERROR tested program terminated with exit code 1)    
    empty list and single element
    - 최초제출코드
    ```python
        if pre==A[-1]:
        result=pre+1
    ```
    마지막원소까지검사한경우 A[-1]로 검사했으나, 빈 배열이 들어오는 경우 A[-1]참조 시 에러발생.
    


#### case - Correctness tests   
> 
    (1) simple : 일반 케이스      
        * simple test    
    (2) double  : 원소가 2개인 케이스       
        * two elements   
    (3) single : 원소가 1개인 케이스           
        * single element  
    (4) empty_and_single : 빈배열 케이스
        * empty list and single element
    (5) missing_first_or_last : 처음/마지막이 missing된 케이스
        * the first or the last element is missing

#### case - Performance tests     
>
    (6) medium : 중간규모값케이스     
        * medium test, length = ~10,000    
    (7) large : 큰규모값 수 케이스    
        * large test, length = ~100,000   

### Analysis - time complexity

>
  Detected time complexity:    
  O(N) or O(N*log(N))    

-------------------------------------------------------------------------------


## [3.3 TapeEquilibrium](https://app.codility.com/programmers/lessons/3-time_complexity/tape_equilibrium/)
* 소요 시간 : 15분


### 성공 코드
```python
def solution(A):
    prefix=A[0]
    suffix=0
    for i in range(1,len(A)):
        suffix += A[i]

    min_diff=abs(prefix-suffix)
    for i in range(1,len(A)-1):
        prefix+=A[i]
        suffix-=A[i]
        if abs(prefix-suffix) < min_diff:
            min_diff=abs(prefix-suffix)
    
    return min_diff

"""
    * GOAL : min difference값.
    *A : Non Empty, N개의정수 배열
    diff[P] => 
        A[0], A[1], ..., A[P - 1] and
        A[P], A[P + 1], ..., A[N - 1]. (P : 0<P<N) 

    N is an integer within the range [2..100,000];
    each element of array A is an integer within the range [-1,000..1,000].

    *case
        - N==2일때 0 / 1 케이스 반환.
        전체케이스 순회하므로 특이케이스x
"""
```


--------------------------------------------------------------------
### 2.5 comment    

#### case - Correctness tests   
> 
    (1) small : 일반 케이스      
        * small elements   
    (2) double  : 원소가 2개인 케이스       
        * two elements    
    (3) simple_positive  : positive case        
        * simple test with positive numbers, length = 5   
    (4) simple_negative  : negative case       
        * simple test with negative numbers, length = 5     
    (5) simple_boundary  : 한쪽 원소 1개일 때 정답인 케이스        
        * only one element on one of the sides  
   

#### case - Performance tests     
>
    (6) medium : 일반 케이스     
        * random medium, numbers from -1,000 to 50, length = ~10,000     
    (5) large : 큰규모값 수 케이스    
        * large sequence, length = ~100,000        
    (6) large_extreme : extreme    
        * large test with maximal and minimal values, length = ~100,000 
### Analysis - time complexity

>
  Detected time complexity:
  O(N)


#
 ### learned lesson
 
* ** 시간복잡도 (Time Complexity)
#
 
 
 
 
 



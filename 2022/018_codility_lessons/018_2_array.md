# Lessons2. Arrays
## [2.1 CyclicRotation](https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/)
* 소요 시간 : 20분

### 성공 코드
```python
def solution(A, K):
    if len(A) != 0: #2회차
        rot_cnt=K%len(A)
    #rot_cnt=K%len(A) #최초제출 : fail : extremes case 
    A_result = [A[(idx-rot_cnt)%len(A)] for idx in range(0,len(A))]
    return A_result



"""
    - GOAL : K번 rotation한 결과값 return
        배열 Rotation : 오른쪽으로 한칸씩 shift (* [-1] -> [0])

    - A element in range[-1000,1000] / N(A len)&K(rot cnt) in range[0,100]
    
    if A=[1,2,3,4] & k = 10
    [1,2,3,4] (rot cnt 0)
    [2,3,4,1] (rot cnt 1)
    [3,4,1,2] (rot cnt 2)
    [4,1,2,3] (rot cnt 3)
    [1,2,3,4] (rot cnt 4)
    => rot cnt len(A)회마다 원위치.
    => [1,2,3,4] (rot cnt 8)
        => [4,1,2,3] => [3,4,1,2] : idx 0=>2
    => A_result[i] = A[( i+k%len(A) )%len(A)]
"""

```

--------------------------------------------------------------------
### 2.5 comment    
* 1회 실패(87%)      
  - case : extreme_empty    
    empty array    
    : A가 빈 배열일 경우 q/len(A)는 divison by zero로 runtime error.     

* 음수mod    
  (idx-rot_cnt)%len(A)에서 헷갈렸던 부분.    
  새로운 배열의 인덱스를 인풋배열 rotation count만큼 앞의 인덱스값으로 채워주는 과정에서,     
  idx-rot_cnt가 0-2일 경우 (-2) len(a)만큼 나눈 나머지는 어떻게 동작할것인가.    
  ```python
  >>> -1%4
  3
  >>> -2%4
  2
  >>> -3%4
  1
  ```
  
  참고로 cpp에서는 다음과 같이 동작한다    
  ```cpp
  -1%4 : -1
  -2%4 : -2
  -3%4 : -3
  ```
  

#### case - Correctness tests   
> 
    (1) extreme_empty : 빈 배열 케이스, ★      
        * empty array    
    (2) single : 원소가 1개인 케이스       
        * one element, 0 <= K <= 5    
    (3) double : 원소가 2개인 케이스          
        * two elements, K <= N    
    (4) small : 일반 케이스     
        * small functional tests, K < N     
    (5) medium : 중간규모값 수 케이스   
        * medium random sequence, N = 100      
    (6) maximal : max      
        * maximal N and K      

-------------------------------------------------------------------------------


## [2.2 OddOccurrencesInArray](https://app.codility.com/programmers/lessons/2-arrays/odd_occurrences_in_array/)
* 소요 시간 : 50분

### 1차 제출 코드(66%)
```python

def solution(A):
    A.sort()
    pre=A[0]
    result=-1
    A=A[1:]
    pair_flag=0
    for element in A:
        if pre==element:
            pair_flag=1
        elif pair_flag==0:
            result=pre
            break
        elif pair_flag==1:
            pre=element
            pair_flag=0
    if result==-1:
        result=pre
    return result
"""
    - GOAL : unpaired 원소 반환
        배열에는 홀수숫자들이 2개씩 들어있고 1개의 unpaired 수 존재.
    
    - N(배열길이) in range [1,1,000,000]
    - 원소 in range[1.1,000,000,000]

    case
        1개케이스 : 첫번째 원소(pre 저장 후 loop돌지 않고 result==-1일 때 pre반환.) 반환(0)
        none_pair 마지막에 존재하는 케이스 : 마지막 원소(pair_flag==1인상태에서 pre에 마지막 원소 저장, result==-1일 때 pre 반환)반환.

"""

```

### 성공 코드
```python
def solution(A):
    A.sort()
    pre=A[0]
    result=-1
    A=A[1:]
    cnt=0
    for element in A:
        if pre==element:
            cnt+=1
        elif cnt==0 or cnt%2==0 :
            result=pre
            break
        elif cnt>=1:
            pre=element
            cnt=0
    if result==-1:
        result=pre
    return result
"""        
    *2차풀이 stdout : pair : 같은 수에 대해 한 만 존재하는것이 아니라 다수개 존재 가능.)
    [1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 14, 14, 14, 14, 16, 16, 17, 17, 17, 17, 17, 17, 20, 20, 20, 20, 21, 21, 22, 22, 22, 22, 22, 22, 23, 23, 24, 24, 26, 26, 26, 26, 28, 28, 29, 29, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 34, 34, 35, 35, 39, 39, 42, 42, 42, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 56, 56, 58, 58, 58, 58, 59, 59, 60, 60, 61, 61, 63, 63, 64, 64, 64, 64, 65, 65, 65, 65, 66, 66, 67, 67, 67, 67, 67, 67, 69, 69, 69, 69, 70, 70, 70, 70, 71, 71, 73, 73, 75, 75, 77, 77, 77, 77, 81, 81, 84, 84, 86, 86, 87, 87, 88, 88, 89, 89, 91, 91, 91, 91, 91, 91, 91, 91, 93, 93, 96, 96, 96, 96, 100, 100, 100, 100, 100, 100]
    
"""
```


--------------------------------------------------------------------
### 2.5 comment    
* 1회 실패(66%)      
  - case : small1(WRONG ANSWER got 100 expected 42)    
    small random test n=201
  - case : medium2(WRONG ANSWER got 1999987 expected 500000)
    medium random test n=100,003
  - case : big1(WRONG ANSWER got 2000 expected 700)
    big random test n=999,999, multiple repetitions
    
문제를 제대로 읽지 않아 같은 수가 3개 이상 존재하는 케이스 fail (ex 3,3,3,3,4,4,5)    
요구사항을 정확히 정의하고 풀자.    


#### case - Correctness tests   
> 
    (1) simple : 일반 케이스      
        * simple test n=5    
    (2) extreme_single_item  : 원소가 1개인 케이스       
        * [42]    
    (3) small1 : 작은 규모 수 케이스              
        * small random test n=201    

#### case - Performance tests     
>
    (4) medium : 일반 케이스     
        * medium random test n=100,003     
    (5) big : 큰규모값 수 케이스    
        * big random test n=999,999, multiple repetitions        

### Analysis - time complexity

>
  Detected time complexity:    
  O(N) or O(N*log(N))    


#
 ### learned lesson
 
* ** 배열 ( Array ) 
#
 
 
 
 
 



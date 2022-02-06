# Lessons4. Counting Elements
## [5.1 PassingCars](https://app.codility.com/programmers/lessons/5-prefix_sums/passing_cars/)
* 소요 시간 : 20분
### 성공 코드
```python
def solution(A):
    e_w_cnts=[0,0] # [0] : east / [1] : west
    passing_cnt=0
    for idx,car in enumerate(A):
        e_w_cnts[car]+=1
        if car==1:
            passing_cnt+=e_w_cnts[0]
    if passing_cnt>1000000000:
        passing_cnt=-1

    return passing_cnt

"""
goal : passing cars counting 
    passing cars : 
    pair(P,Q) : 0<=P<Q<N => P(0,east) & Q(1,west)쌍 pass
       P는 왼쪽으로, Q는 오른쪽으로 여행하고 P<Q이면 해당쌍 pass 
Array A
    0 : east
    1 : west
    None Empty

N is an integer within the range [1..100,000];

"""
```
--------------------------------------------------------------------
### 2.6 comment    

#### case - Correctness tests   
> 
    (1) simple
        * single element
    (2) double     
        * two elements      
    (3) simple        
        * simple test   

#### case - Performance tests     
>
    (4) medium        
        * random, length = ~10,000  
    (5) extreme_large     
        * large test with all 1s/0s, length = ~100,000     


### Analysis - time complexity

>
  Detected time complexity:
 O(N)


## [5.2 CountDiv](https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/)
* 소요 시간 : 20분
### 성공 코드
```python
def solution(A, B, K):
    first_mod_zero=0
    cnt=0
    for i in range(A,B+1):
        if i % K == 0 :
            first_mod_zero=i
            cnt+=1
            break
    cnt+=int((B-first_mod_zero)/K)
    if A==B and A%K!=0:
        cnt=0
    return cnt

"""
    * GOAL : a,b 범위에서 k로 나누어 떨어지는 수 리턴하기
        return i => { i | A ≤ i ≤ B, i mod K = 0 }

    * A and B are integers within the range [0..2,000,000,000];
    * K is an integer within the range [1..2,000,000,000];
A ≤ B.
"""
```
--------------------------------------------------------------------
### 2.6 comment    

#### case - Correctness tests   
> 
    (1) simple
        * A = 11, B = 345, K = 17
    (2) minimal     
        * A = B in {0,1}, K = 11      
    (3) extreme_ifempty(A==B)        
        * A = 10, B = 10, K in {5,7,20}    
    (4) extreme_endpoints
        * verify handling of range endpoints, multiple runs

#### case - Performance tests     
>
    (5) big_values        
        * A, B, K in {1,MAXINT}    

### Analysis - time complexity

>
  Detected time complexity:
  O(1)



## [5.3 GenomicRangeQuery](https://app.codility.com/programmers/lessons/5-prefix_sums/genomic_range_query/)
* 소요 시간 : 10분
### 성공 코드
```python
```
--------------------------------------------------------------------
### 2.6 comment    




## [5.4 MinAvgTwoSlice](https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/)
* 소요 시간 : 10분
### 성공 코드
```python
```
--------------------------------------------------------------------
### 2.6 comment    







#
 ### learned lesson
 
* ** Prefix Sums
* a simple yet powerful technique that allows for the fast calculation of sums of
elements in given slice (contiguous segments of array). 
![image](https://user-images.githubusercontent.com/46209571/152669614-862bc492-366d-403c-914f-f1b0b0f2e892.png)


#
 
 
 

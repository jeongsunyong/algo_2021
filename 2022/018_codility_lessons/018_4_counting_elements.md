# Lessons4. Counting Elements
## [4.1 FrogRiverOne](https://app.codility.com/programmers/lessons/4-counting_elements/frog_river_one//)
* 소요 시간 : 10분

### 성공 코드
```python
def solution(X, A):
    init_val=999999
    L=[init_val]*(X+1)
    for t,pos in enumerate(A):
        if L[pos]==init_val:
            L[pos]=t

    L=L[1:]
    res=max(L)
    if res==init_val:
        res=-1    
    return(res)
"""
* GOAL : other side로 점프 가능 가장 빠른 시간 구하기 (no route : -1)
    L[0] : initial pos / L[X+1] : opposite side
        L[1]~L[X]까지 모두 밟으며 가야하고, A[i]는 i time에 활성화되는 L

    N and X are integers within the range [1..100,000];
    each element of array A is an integer within the range [1..X].

    개구리 이속 : no

"""

```

--------------------------------------------------------------------
### 2.5 comment    

#### case - Correctness tests   
> 
    (1) simple : 일반 케이스       
        * simple test    
    (2) single    
        * single element    
    (3) extreme_frog         
        * frog never across the river    
    (4) extreme_leaves              
        * all leaves in the same place        

#### case - Performance tests     
>
    (5) medium        
        * arithmetic sequences, X = 5,000    
    (6) large    
        * arithmetic sequences, X = 30,000        

### Analysis - time complexity

>
  Detected time complexity:
  O(N)

-------------------------------------------------------------------------------


## [4.2 PermCheck](https://app.codility.com/programmers/lessons/4-counting_elements/perm_check/)
* 소요 시간 : 14분

### 성공 코드
```python
def solution(A):
    A.sort()

    pre=A[0]
    A=A[1:]
    seq_flag=1
    for num in A:
        if pre+1 != num :
            seq_flag=0
            break
        pre=num
    return seq_flag


"""
    GOAL : A가 순열인지 체크 ( true 1  / false 0)
    A : NoneEmpty
    N is an integer within the range [1..100,000];
    each element of array A is an integer within the range [1..1,000,000,000].

"""

```


--------------------------------------------------------------------
### 2.5 comment    

counting이 주제이므로 각 인덱스에 대한 배열에 값을 넣어주고 마지막에 loop로 전체 다 존재하는지 판단하는게 정석인 듯 함.    

#### case - Correctness tests   
> 
    (1) simple : 일반 케이스       
        * permutation + one element occurs twice, N = ~100 
    (2) single    
        * single element    
    (3) extreme_min_max        
        * single element with minimal/maximal value   
    (4) double             
        * two elements        
    (5) antiSum1 : production / sum 구해서 1~N의 순열 판단하는것에대한 반례인 듯.            
        * total sum is correct, but it is not a permutation, N <= 10        
    (6) permutations_of_ranges : 1부터시작하지 않는케이스. (현재 풀이에 맞는 반례)            
        * permutations of sets like [2..100] for which the anwsers should be false    

#### case - Performance tests     
>
    (7) medium        
        * permutation + few elements occur twice, N = ~10,000    
    (8) large    
        * sequence 1, 2, ..., N, N = ~100,000 / permutation + one element occurs three times, N = ~100,000     
    (9) extreme_values     
        * all the same values, N = ~100,000     


### Analysis - time complexity

>
  Detected time complexity:    
  O(N) or O(N*log(N))    

-------------------------------------------------------------------------------


## [4.3 MaxCounters](https://app.codility.com/programmers/lessons/4-counting_elements/max_counters/)
* 소요 시간 : 1시간   

### 1차제출 코드(66%)
```python
def solution(N, A):
    counter=[0]*N
    for X in A:
        if 1<=X<=N:
            counter[X-1]+=1
        elif X==N+1:
            counter=[max(counter)]*N

    return counter

"""
    GOAL : operation 후 counter결과

    operations
        (1) increase(X) - counter X is increased by 1,
        (2) max counter - all counters are set to 
                    the maximum value of any counter.

    A:non-empty , size M

    if A[K] = X, (1 ≤ X ≤ N)
        then operation K is increase(X),
    if A[K] = N + 1 
        then operation K is max counter.

    N and M are integers within the range [1..100,000];
    each element of array A is an integer within the range [1..N + 1].

"""
```

### 2차 제출 코드
```python
def solution(N, A):
    counter=[0]*N
    max_cnt=0
    for X in A:
        if 1<=X<=N:
            counter[X-1]+=1
            max_cnt=max(max_cnt,counter[X-1])
        elif X==N+1:
            counter=[max_cnt]*N

    return counter
```

### 성공 코드
```python
def solution(N, A):
    counter=[0]*N
    max_cnt=0
    next_max_cnt=0
    last_max_counter=0
    for i,X in enumerate(A):
        if X==N+1:
            last_max_counter=i
    
    for i,X in enumerate(A):
        if 1<=X<=N:
            if counter[X-1]<max_cnt:
                counter[X-1]=max_cnt
            counter[X-1]+=1
            next_max_cnt=max(next_max_cnt,counter[X-1])
        elif X==N+1:
            max_cnt=next_max_cnt
            if i==last_max_counter:
                counter=[max_cnt]*N

    for i,X in enumerate(A):
        A[i-1]=max_cnt

    return counter

```


--------------------------------------------------------------------
### 2.5 comment    
1차제출:실패(timeout)
▶large_random1
large random test, 2120 max_counter operations✘TIMEOUT ERROR
running time: 1.624 sec., time limit: 0.480 sec.
1.1.624 sTIMEOUT ERROR, running time: 1.624 sec., time limit: 0.480 sec.
▶large_random2
large random test, 10000 max_counter operations✘TIMEOUT ERROR
Killed. Hard limit reached: 6.000 sec.
1.6.000 sTIMEOUT ERROR, Killed. Hard limit reached: 6.000 sec.
▶extreme_large
all max_counter operations✘TIMEOUT ERROR
Killed. Hard limit reached: 6.000 sec.

2차제출:실패(timeout)
▶extreme_large
all max_counter operations✘TIMEOUT ERROR
Killed. Hard limit reached: 7.000 sec.

: all max_counter operations + large의경우 실패.
max_counter를하게되면 전체 N개만큼의 연산을 루프안에서 다시 돌아야한다.(전체카운터를 통일시켜주므로)
=> 해당 연산을 줄이는 것이 키포인트.
: max_counter연산은 마지막 1회에만 해주고, 그 전에는 개별로 차례가 돌아오면 max_counter를 적용시켜준다.
이 때 차례가 안돌아오는 경우가 있었는데, 이 경우에는 max_counter보다 항상 작으며 이후 연산이 없는 것이므로 마지막에 max_counter로 할당시켜준다.

#### case - Correctness tests   
> 
    (1) extreme_small
      all max_counter operations
    (2) single    
        * single counter    
    (3) small_random1        
        * small random test, 6 max_counter operations  

#### case - Performance tests     
>
    (4) medium        
        * medium random test, 500 max_counter operations  
    (5) large    
        * large random test, 10000 max_counter operations     
    (6) extreme_large     
        * all max_counter operations     


### Analysis - time complexity

>
  Detected time complexity:
  O(N + M)    

-------------------------------------------------------------------------------

## [4.4 MissingInteger](https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer/)
* 소요 시간 : 20분

### 성공 코드
```python
def solution(A):
    A.sort()
    cut_idx=0
    for a in A:
        if a<=0:
            cut_idx+=1
    A=A[cut_idx:]
    if len(A)==0:
        return 1
    if A[0]!=1:
        return 1
    elif len(A)==1 :
        return 2

    pre=A[0]
    A=A[1:]
    res=1
    for a in A:
        if a==pre:
            continue
        elif a==pre+1:
            pre=a
        elif a-pre>1:
            break

    res=pre+1
    return res

"""
    A에 존재하지 않는 smallest 양의정수
    N is an integer within the range [1..100,000];
    each element of array A is an integer within the range [-1,000,000..1,000,000].
"""

```


--------------------------------------------------------------------
### 2.5 comment    

(1) sorting 후 음수 걸러내고 1부터 시작하지 않으면 return 1
이후에는 순차적으로 검사해 1씩 증가하지 않을 때 비어있는 (이전 숫자+1) return.

#### case - Correctness tests   
> 
    (1) simple : 일반 케이스       
        * simple test  
    (2) extreme_single    
        * single element    
    (3) extreme_min_max_value          
        * minimal and maximal valuese   
    (4) positive_only             
        * shuffled sequence of 0...100 and then 102...200        
    (5) negative_only            
        * shuffled sequence -100 ... -1        

#### case - Performance tests     
>
    (6) medium        
        * chaotic sequences length=10005 (with minus)     
    (7) large    
        * chaotic + many -1, 1, 2, 3 (with minus)/ shuffled sequence 1, 2, ..., 100000 (without minus)    



### Analysis - time complexity

>
  Detected time complexity:
  O(N) or O(N * log(N))   

#
 ### learned lesson
 
* ** 원소 카운팅(순회) (counting_elements)
#
 
 
 
 
 



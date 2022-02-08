
# Lessons6. Sorting
## [6.1 Distinct](https://app.codility.com/programmers/lessons/6-sorting/distinct/)
* 소요 시간 : 15분

### 성공 코드
```python
def solution(A):
    counter_positive= [0]*1000001 #0 ~ 1,000,000
    counter_negative= [0]*1000001 #-1 ~ -1,000,000

    for num in A:
        if num<0:
            counter_negative[-num]+=1
        else:
            counter_positive[num]+=1
    
    cnt=0
    for i in range(0,1000001):
        if counter_positive[i]>0:
            cnt +=1
        if counter_negative[i]>0:
            cnt +=1
    
    return cnt
    
"""
    GOAL : A의 distinct값 개수를 출력
    N is an integer within the range [0..100,000];
    each element of array A is an integer within the range [-1,000,000..1,000,000].
    
"""
```

### 성공 코드2
```python
def solution(A):
    set_A=set(A)
    cnt=len(set_A)
    return cnt

```
--------------------------------------------------------------------
### 2.8 comment    

Sorting category -> 1차 접근은 counting sort에서 1개 이상인 idx수 조사.    
통과.O(N*log(N)) or O(N)    

풀고보니 distinct 개수만 세는거면 set으로 캐스팅해준 후 길이 구하면 될 것 같아 시도.     
통과.O(N*log(N)) or O(N)     

2번 풀이가 더 짧고 가독성도 좋아보임. 유형을 보고 접근하기보다도 해결법을 먼저 생각해보자.      

참고) set 일부 연산들의 시간복잡도
|Set|
|Operation|Example|Big-O|
|------|---|---|
|Length|len(s)|O(1)|
|Add|s.add(5)|O(1)|
|Containment|x in/not in s|O(1)|
|Remove|s.remove(..)|O(1)|

list,tuple과 다른 점은 contain연산과 remove연산이 O(N)이 아니라 O(1)이라는점 **     
중복되지 않는 조건일경우 set으로 바꾼다면 시간복잡도를 줄일 수 있는 케이스 존재 가능**   


### Analysis - time complexity

>
  Detected time complexity:
  O(N*log(N)) or O(N)

-------------------------------------------------

## [6.2 MaxProductOfThree](https://app.codility.com/programmers/lessons/6-sorting/max_product_of_three/)
* 소요 시간 : 30분

### 성공 코드
```python
def solution(A):
    product_A=1
    A.sort(key=lambda x: abs(x)) # 절대값 크기순 정렬
    A.reverse() #역순정렬
    positive_rank=[]
    positive_cnt=0
    negative_rank=[]
    negative_cnt=0
    for num in A: # positive, negative분리 (정렬순유지)
        if num>=0 :
            positive_cnt+=1
            positive_rank.append(num)
        elif num<0 :
            negative_cnt+=1
            negative_rank.append(num)
            
    if positive_cnt>=3 and negative_cnt>=2 : #일반 케이스
        product_A=max(positive_rank[0]*positive_rank[1]*positive_rank[2] , negative_rank[0]*negative_rank[1]*positive_rank[0])
    elif len(A)==3: # N=3 케이스
        product_A=A[0]*A[1]*A[2]
    elif positive_cnt==0: # positive zero 케이스, N>3
        product_A=negative_rank[-1]*negative_rank[-2]*negative_rank[-3]
    elif negative_cnt==0: # negative zero 케이스, N>3
        product_A=positive_rank[0]*positive_rank[1]*positive_rank[2]
    elif positive_cnt == 1: # positive 1 케이스, N>3
        product_A=positive_rank[0]*negative_rank[0]*negative_rank[1]
    elif negative_cnt == 1: # negative 1 케이스, N>3
        product_A=positive_rank[0]*positive_rank[1]*positive_rank[2]
    elif positive_cnt == 2: # positive 2 케이스, N>3
        product_A=positive_rank[0]*negative_rank[0]*negative_rank[1]

    return product_A

```

--------------------------------------------------------------------
### 2.8 comment    

절대값순으로 sorting 후 positive / negative로 분리,
일반적으로 positive top 3 or positive top 1 & negative top 2 중 최대값 취하지만,
positive, negative가 2개이하, 1개 이하일 케이스 분리해 처리해줌.
유의점은 negative 1개 선택이 필수적인경우 (positive zero / N=3 & negative==1)는 rank의 낮은순을 선택해야 큰 수가 된다(-1*-1*-1 > -2*-2*-2)

#### case - Correctness tests   
> 
    (1) one_triple    
        * three elements    
    (2) simple      
        * simple tests    

#### case - Performance tests     
>
    (4) medium        
        * random medium, length = ~10,000   
    (5) extreme_large      
        * (-2, .., -2, 1, .., 1) and (MAX_INT)..(MAX_INT), length = ~100,000     

채점에서 테스트 케이스 자체가 세분화되어 나와있지는 않지만 if문 분기 되어 있는 7가지에대한 시간 소요 있었음.        
분기가 아니라 일반론적으로 처리되는 깔끔한 로직 짤 수 있으면 좋을 것 같다.   

### Analysis - time complexity

>
  Detected time complexity:
  O(N * log(N))




-----------------------------------------------

#
 ### learned lesson
 
* ** Sorting
* sort

#
 
 

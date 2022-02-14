
# Lessons11. Sieve of Eratosthenes
## [11.1 CountNonDivisible](https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_non_divisible/)
* 소요 시간 : 1시간
* 
### 성공 코드
```python
import math
def solution(A):
    N=len(A)
    res=[0]*N

    counter=[0]*(2*N+1)
    for num in A:
        counter[num]+=1

    res_save=[-1]*(2*N+1)
    for i in range(0,N):
        if res_save[A[i]] != -1:
            res[i]=res_save[A[i]]
            continue
        for a_k in range(1,math.floor(math.sqrt(A[i]))+1):
            if A[i]%a_k == 0:
                res[i]+=counter[a_k]
                if a_k*a_k != A[i]:
                    res[i]+=counter[int(A[i]/a_k)]
        res[i]= N - res[i] 
        res_save[A[i]]=res[i]

    return res

```

--------------------------------------------------------------------
### 2.13 comment    
최초 제출코드
```python
def solution(A):
    N=len(A)
    res=[0]*N

    for i in range(0,N):
        for k in range(0,N):
            if i==k:
                continue
            if A[i]%A[k]!=0:
                res[i]+=1

    return res
"""
    goal : non-divisors 개수 배열 반환
    A : arr, size N
    res[i] : A[i]%A[k]!=0 인 원소 개수.   (0<=i<N), (k|k in [0,N-1]) 

    N is an integer within the range [1..50,000];
    each element of array A is an integer within the range [1..2 * N].
"""
```
최초 제출 실패. 에라토스테네스의 체를 알고 접근했지만 직관적으로 떠오르지 않아서    
일단 보자마자 생각나는 방법으로 제출. O(N ** 2)으로 correctness 100%, performance 0%    
제

실패코드 2
```python
  ```python
import math
def solution(A):
    N=len(A)
    res=[0]*N

    counter=[0]*(2*N+1)
    for num in A:
        counter[num]+=1

    for i in range(0,N):
        for a_k in range(1,math.floor(math.sqrt(A[i]))+1):
            if A[i]%a_k == 0:
                res[i]+=counter[a_k]
                res[i]+=counter[int(A[i]/a_k)]
        res[i]= N - res[i] - counter[A[i]]

    return res

    """
        non-divisor만 구하면 됨. 
        O(N)으로는 불가능.
    """
```
오류1:제곱수인경우에대한 체크 빠짐
오류2: counter[A[i]]빼줌 (이유는 N개에서 0으로 나눠지는개수만큼 - 자기자신 빼줘야한다고 생각했는데 1과 쌍이므로 필요없었음)

실패코드3
```python
import math
def solution(A):
    N=len(A)
    res=[0]*N

    counter=[0]*(2*N+1)
    for num in A:
        counter[num]+=1

    for i in range(0,N):
        for a_k in range(1,math.floor(math.sqrt(A[i]))+1):
            if A[i]%a_k == 0:
                res[i]+=counter[a_k]
                if a_k*a_k != A[i]:
                    res[i]+=counter[int(A[i]/a_k)]
        res[i]= N - res[i] 

    return res

```
performance에서 50%.

=> 최종적으로 구글링.
이미 나온 result의경우 save해서 사용 가능.
=>시간복잡도 감소
나는 codility medium보다 아래 수준인것같다..
접근은 얼추 맞는 방향으로 하는 경우도 있는데 세부적으로 디버깅을 여러번 하게되고 세세한걸 잘 못함.
코드 손대기 전에 생각을 먼저 논리적으로 하고 짜는 연습을 하자.
디버깅 하면서 푸니까 지치는것같기도 하고 효율이 떨어지는 것 같기도 하고 생각하는 실력은 많이 안느는듯.

### Analysis - time complexity

>
  Detected time complexity:
  O(N * log(N)) 

    
    
#
 ### learned lesson
 
* ** sieve_of_eratosthenes
* sieve_of_eratosthenes
> 에라토스테네스의 체 : 소수를 구하는 수학적인 방식이다.
> The algorithm takes its name from the
process of sieving—in a simple way we remove multiples of consecutive numbers.
: consecutive한 수들의 배수들을 체로 걸러내는듯한 프로세스기 때문에 체라는 표현을 사용하는 알고리즘.
> Initially, we have the set of all the numbers {2, 3, . . . , n}. At each step we choose the
smallest number in the set and remove all its multiples.
: 존재하는 num set에서 작은수부터 배수를 지워나간다 ( 2,4,6,8,.... -> 3,9,15,....->5,25,...)
> Notice that every composite number has a divisor of at most √n. In particular, it has a divisor which is a prime number. It
is sufficient to remove only multiples of prime numbers not exceeding √n. In this way, all composite numbers will be removed.
: 합성수들은 보통 sqrt(n)범위 내에서 제거된다(약수로 2~sqrt(n) 존재하므로) => 소수만 남게되는 결과.

#
 

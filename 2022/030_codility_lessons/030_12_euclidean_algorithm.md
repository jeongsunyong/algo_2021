# Lessons12.Euclidean algorithm
## [12.2 CommonPrimeDivisors](https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/)
* 소요 시간 : 2시간

### 성공 코드(구글링코드)
```python
import math
def solution(A, B):
    Z=len(A)
    cnt=0
    for k in range(Z):
        flag=True

        a=A[k]
        b=B[k]
        G=math.gcd(a,b)
        while a != 1:
            g = math.gcd(a,G)
            if g==1:
                flag=False
                break
            a//=g

        while b!=1:
            g=math.gcd(b,G)
            if g==1:
                flag=False
                break
            b//=g
        
        if flag:
            cnt+=1

    return cnt
```

--------------------------------------------------------------------
### 2.17 comment    

```python
import math   
def solution(A, B):
    Z=len(A)
    prime_range=math.ceil(math.sqrt(2147483647))
    prime_check=[True]*(prime_range+1)
    for i in range(2,prime_range+1):
        if prime_check[i]==True:
            for j in range(i+i,prime_range+1,i):
                prime_check[j]=False
    primes=[]
    for i in range(2,prime_range+1):
        if prime_check[i]==True:
            primes.append(i)

    cnt=0
    for k in range(Z):
        if B[k]%A[k]==0 or A[k]%B[k]==0:
            if B[k]>=A[k]:
                divisor=B[k]/A[k]
                if A[k]%divisor == 0:
                    cnt+=1
                else:
                    check=1
                    for p in primes:
                        if p > divisor:
                            break
                        if A[k]%p != 0 and divisor%p==0:
                            check=0
                            break
                    cnt+=check
                    
            else:
                divisor=A[k]/B[k]
                if B[k]%divisor == 0:
                    cnt+=1
                else:
                    check=1
                    for p in primes:
                        if p > divisor:
                            break
                        if B[k]%p != 0 and divisor%p==0:
                            check=0
                            break
                    cnt+=check
    return cnt

```

최초 제출 코드: fail, correctness85%로 wrong answer.      
: 가장 첫 번째 분기문인    
```python
if B[k]%A[k]==0 or A[k]%B[k]==0:
``` 
에서 3,5,5 / 3,3,5로 어느 한쪽이 다른 한쪽의 약수인 케이스만 생각해서 잘못된 결과를 도출했었고 접근 자체가 틀렸었음.    
이후 구글링에서 최소공배수를 이용하는 방법으로 아이디어를 얻고 재풀이.




### Analysis - time complexity

>
  Detected time complexity:
  O(Z * log(max(A) + max(B)) ** 2)

    
    
#
 ### learned lesson
 
* ** Euclidean algorithm
* Euclidean algorithm


#

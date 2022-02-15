
# Lessons11. Sieve of Eratosthenes
## [11.2 CountSemiprimes](https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_semiprimes/)
* 소요 시간 : 2시간

### 성공 코드
```python
import math
def solution(N, P, Q):
    #1.소수저장 : sqrt(N)까지)
    primes=[]
    prime_check=[True]*(50001)
    prime_check[0]=False
    prime_check[1]=False
    for i in range(2,math.floor(math.sqrt(N))+1):
        if prime_check[i]==True:
            primes.append(i)
            for j in range(i+i,int(N/2)+1,i):
                prime_check[j]=False
    for i in range(math.floor(math.sqrt(N))+1,int(N/2)+1):
        if prime_check[i]==True:
            primes.append(i)
    
    semi_prime_check=[False]*(50000+1) # N=50000까지므로 50000까지만 저장하면 됨. 

    #2. 해당 수가 semi prime인지 체크하는 배열 생성
    for num1 in primes:
        for num2 in primes:
            if num1*num2 <= N:
                semi_prime_check[num1*num2]=True
            else:
                break

    #3. 해당 idx까지의 semi_prime 개수 배열 생성
    cnt=0
    cnt_arr=[0]*(N+1)
    for i in range(0,N+1):
        if semi_prime_check[i]==True:
            cnt+=1
        cnt_arr[i]=cnt

    #4. query result 생성
    M=len(P)
    res=[0]*M
    for k in range(0,M):
        res[k]=cnt_arr[Q[k]]-cnt_arr[P[k]-1]

    #4. return answer
    return res
```

--------------------------------------------------------------------
### 2.15 comment    
1차제출
```python
import math
def solution(N, P, Q):
    #1.소수저장 : sqrt(N)까지)
        #근거 each element of arrays P and Q is an integer within the range [1..N];
    primes=[]
    prime_check=[True]*(50001)
    prime_check[0]=False
    prime_check[1]=False
    for i in range(2,math.floor(math.sqrt(N))+1):
        if prime_check[i]==True:
            primes.append(i)
            for j in range(i+i,int(N/2)+1,i):
                prime_check[j]=False
    for i in range(math.floor(math.sqrt(N))+1,int(N/2)+1):
        if prime_check[i]==True:
            primes.append(i)

    #2. 소수 * 소수 저장
    semi_primes=[]
    for num1 in primes:
        for num2 in primes:
            semi_primes.append(num1*num2)
    
    semi_primes=set(semi_primes)

    #3. 해당 수가 semiprime인지 체크하는 배열 생성
    M=len(P)
    semi_prime_check=[False]*(50001)
    for i in range(1,N+1):
        if i in semi_primes:
            semi_prime_check[i]=True

    #4. 범위마다 순회하며 소수개수 채크.
    res=[0]*M
    for k in range(0,M):
        for num in range(P[k],Q[k]+1):
            if semi_prime_check[num]:
                res[k]+=1
    #5. return answer
    return res


"""
    goal : 0~M-1 Query범위에서 semiprime 개수 array 반환. 
    semiprime : prime_number(소수)의 곱.
    P,Q : non-empty, size M int arr

    Query k  : range[P[k],Q[k]] 1<=P[k]<=Q[k]<=N

    N is an integer within the range [1..50,000];
    M is an integer within the range [1..30,000];
    each element of arrays P and Q is an integer within the range [1..N];
    P[i] ≤ Q[i].


    # math.ceil(math.sqrt(N))+1 헷갈림
    첫번째루프 케이스조사 ( semi prime을 구해야하므로 sqrt(N)까지의     제곱근을 구하고, 해당 제곱근들간 곱을 구할 예정 (최대 N))
    ex) N 25
        -> 5까지
    ex) N 24
        -> 5까지 (sqrt(N) < 5 and ceil(sqrt(N))=5 => (0,ceil(sqrt(N))+1))은 5까지.
    ex N 17 -> 5까지( 4<sqrt(N)<5) ceil(sqrt(N))=5 , 범위는 5까지.
    
    => floor+1이 되어야 4<= x<5가 5범위까지, 5<=x<6이 6범위까지 조사함.
    => 소수조사의경우
        n=24일 때, 5*5까지 조사할 필요 없음.
        4*4 조사할 필요 없음. 4는 소수가 아니기때문에
            둘의 곱으로 semiprime이 나올 수 없다
        => 3*3까지 나오면 됨.
        => floor + 1
        
"""
```
performance 20% correctness 100%,
#1 시간복잡도 sqrt(N)) * range(i+i,int(N/2)
#2 시간복잡도 len(primes) * len(primes) => log(N)아래로 추정.
#3 O(N)
#4 최악의경우 O(M * N)

최대 sqrt(N) * N정도라고 생각하는데
```
detected time complex : O(N * log(log(N)) + M * N) or O(M * N**3) or O(M * N ** (3/2))
```
로 나옴.    
N^3이 어떻게 나오는지?    
len(primes) < N     
#1의 경우 첫 번째 루프는 sqrt(N)이고, 내부 루프는 step이 i이고 N/2까지므로 최대 O(N)이다. => O(N^2)초과할 수 없음.    
#2의경우 len(primes) x len(primes) -> O(N^2)보다 작음.    
2~3에서 list to set이있는데 O(len(semi_primes))기때문에 고려해보아야하는데    
  len(primes) < N , semi primes < N x N이므로 O(N^2)보다 작을 것으로 예상하기는 함.    
#3의경우     
바깥루프는 O(N)이고 내부에서는 in연산자를 사용하는데,     
set에서는 내부가 해시로 구현되어있어 in연산자가 O(1)로 알고있어 O(N^3)이 나오지 않을 것으로 예상.    
=> 만약 여기서 in연산자가 O(N^2)가 걸리면 여기서 O(N^3)이 나올 수 있을 것 같아 조사필요.★   
  => ★ set에서 in연산은 O(1)이지만 해쉬 충돌이 많아 성능이 떨어지는 경우 O(n)까지 걸릴 수 있다고 한다.    
    
#4의경우 M * (len(Q[k]-P[k]))인데 1<= P,Q <= N이므로 O(N)보다 작을것이고, O N x M일 것.     



#2차제출 : #3 루프 제거, 소수x소수 리스트 생성이 아닌 semi_prime체크 맵으로 생성
```python
import math
def solution(N, P, Q):
    #1.소수저장 : sqrt(N)까지)
    primes=[]
    prime_check=[True]*(50001)
    prime_check[0]=False
    prime_check[1]=False
    for i in range(2,math.floor(math.sqrt(N))+1):
        if prime_check[i]==True:
            primes.append(i)
            for j in range(i+i,int(N/2)+1,i):
                prime_check[j]=False
    for i in range(math.floor(math.sqrt(N))+1,int(N/2)+1):
        if prime_check[i]==True:
            primes.append(i)

    ##1. 소수 * 소수 저장
    #semi_primes=[]
    #for num1 in primes:
    #    for num2 in primes:
    #        semi_primes.append(num1*num2)
    
    semi_prime_check=[False]*(50000+1) # N=50000까지므로 50000까지만 저장하면 됨. 
    for num1 in primes:
        for num2 in primes:
            if num1*num2 <= N:
                semi_prime_check[num1*num2]=True

    #2. 해당 수가 semiprime인지 체크하는 배열 생성
    M=len(P)
    #semi_prime_check=[False]*(50001)
    #for i in range(1,N+1):
    #    if i in semi_primes:
    #        semi_prime_check[i]=True

    #3. 범위마다 순회하며 소수개수 채크.
    res=[0]*M
    for k in range(0,M):
        for num in range(P[k],Q[k]+1):
            if semi_prime_check[num]:
                res[k]+=1
    #4. return answer
    return res
```
performance 40% correctness 100% 로    
▶medium_random    
small random, length = ~300✔OK   
▶large_small_slices    
large with very small slices, length = ~30,000✔OK   
▶large_random1    
large random, length = ~30,000✘TIMEOUT ERROR    
Killed. Hard limit reached: 6.000 sec.   
▶large_random2     
large random, length = ~30,000✘TIMEOUT ERROR    
Killed. Hard limit reached: 6.000 sec.   
▶extreme_large    
all max ranges✘TIMEOUT ERROR    
Killed. Hard limit reached: 6.000 sec.    
performance에서 large_small_slices 케이스가 향상됨.    

detected time complexity는 O(N * log(log(N)) + M * N) or O(M * N ** (3/2))      
로 N^3케이스는 해시값 충돌이 빈번해서 in연산자가 len(primes)xlen(primes) (O(N^2))만큼 측정되었던것이 O.       
      
O(M * N ** (3/2))는 #4루프에서 발생하는것으로 예측됨(M과 연관된 루프가 소수 찾고 저장하는 #1에는 존재하지 않으므로)    
=> 구글링 :  마지막 semi_prime의 개수를 셀 때, 해당 범위를 하나하나 순회하는 것이 아닌,     
0~idx까지의 semi_prime개수를 모두 저장해놓고,0~Q[k]의 semi_prime누적개수 - 0~P[k]-1의 semi_prime 누적 개수를 빼는 방식으로     
시간복잡도 감소해 카운팅 가능.      


### Analysis - time complexity

>
  Detected time complexity:
  O(N * log(log(N)) + M)

    
    
#
 ### learned lesson
 
* ** sieve_of_eratosthenes
* sieve_of_eratosthenes
* set의 in 연산의 경우 O(1)이지만 해쉬 충돌이 많아 성능이 떨어지는 경우 O(n)까지 걸릴 수 있다고 한다.
* list/tuple의 in 연산 : average O(N)

#

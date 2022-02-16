# Lessons12.Euclidean algorithm
## [12.1 ChocolatesByNumbers](https://app.codility.com/programmers/lessons/12-euclidean_algorithm/chocolates_by_numbers/)
* 소요 시간 : 1시간

### 성공 코드
```python
def solution(N, M):
    num=0
    cnt=0
    pre=0
    while cnt<=N:
        #1.0~N범위내의 개수 더해줌 (0,M,2M..)
        chocolate_in_range=int(((N-1)-num)/M)+1
        cnt+= chocolate_in_range
        #2. starting num 갱신
        pre=num
        last_chocolate=num + (chocolate_in_range-1)*M
        num = (last_chocolate+M)%N
        #3.starting point M or 0일경우 break
        if num==M or num==0 or num == pre:
            break

    res=cnt
    return res
```

--------------------------------------------------------------------
### 2.16 comment    
```python
def solution(N, M):
    num=0
    cnt=0
    for i in range(0,N+1):
        if (num==0 and cnt!=0) or (num==M and cnt!=1):
            break
        cnt+=1
        num=(num+M)%N

    res=cnt
    return res
```

최초 제출 코드는 O(N+M)으로 performance에서 실패.     
N이 충분히 크고 O(N)정도로 해결이 안되면 수학적인 방법으로 시간적인 단축이 필요하다.    
-> wrapper를 만나거나 M-1번쨰를 먹기 전까지는 일정한 개수만큼 증가하므로 곱셈처리해 일괄적으로 더해준다.    
-> 이후 시작점을 변경해 다시 같은방법으로 더해준다(시작점이 이전 더했던 시작점으로 다시 돌아오는경우 나머지는 못먹으므로 stop)    


```python
def solution(N, M):
    from math import gcd
    return N//gcd(M,N)
```
위는 최적코드(구글링) .     
보자마자는 이해가 안되서 생각 정리.   

gcd: 공약수     
M과N의 위에서 한번 끝을 만날 때까지는 M만큼 이동하지만,    
끝을 만난 후부터는 마지막 (element + M )%N이 첫 시작점이되고, 그 new start + M +M...->시작점으로부터 M x K만큼 다시 먹는다    

이 때 시작점의 증분은 M,N의 최대공약수와 관련이있다.    
ex) N=9, M=4      
0 4 8 / 3 7 / 2 6 / 1 5  -> 0 (9개)    

ex) N= 12 , M=6    
0 6 -> 0 (2개)    
  
ex) N=12, M=3   
0 3 6 9 -> 0 (4개)   
   
ex) N=8, M=6   
0 6 / 4 / 2  ->0   
최대공약수 2, 8//2= 4    

위 처럼 해당 N/(N,M의최소공약수 만큼) 먹고 다시 원점으로 돌아오게됨.    
이유는? circular가 아니라 쭉 이어져있다고 생각해봤을 때,    
(~~~~ N , ~~~~ 2N , ~~~~ 3N , ~~~~ 4N    )   
탐색이 끝나려면 0에서부터 2N+알파, 3N+알파... kN+알파의 동일한 알파를 만날 때 까지 먹는 개수가 먹을 수 있는 개수이다 . (값[kN+a], 값[(k+1)N+a], 값[(k+2)N+a]...이므로)       
그렇다면 먹는횟수 * M이 kN+알파가 되어야 끝날 수 있다.   
먹는 횟수가 kN이된다는 것은 간단하게는 횟수가 MxN이면 된다.   
끝난다는 의미는 가장 빠르게 kN에 도달하는 숫자를 의미.   
이때 N과M의 공약수들은 kN에 도달할 수 있는 값들이 되고, 최소 공약수가 가장 빠르게 도달할 수 있는 값이 된다.    

ex    
(초콜렛개수-1) * M = kn이되고, 초콜렛개수 = N/M * k' * (반복) 에서 k'/M 이 정수가되야하며,    ( k'는 조건 만족되는 상수, k=반복 * k')    
N/M * k' 에서 k'==M일 때가 조건 만족 최대값이고 만약 M과 N의 공약수가 있다면     
N/(공약수 * m') * k'으로 공약수가 존재할수록, 클수록 최소 k'이 가능.
N=9, M=8이면 먹는 횟수는 9/(8) * 8 = 9이고, kN은 72이다.starting point가 0~7, 8~15, 16(7)~23, 24(6) ~ , 32(5)~ , 40(4) ~ , 48(3)~ , 56(2)~, 64(1)~71
N=8, M=6이면 먹는 횟수는 8/(2)(3) * 3 = 24 이고 kN은 8 * 3=이다. (0~5 , 6 7 8(0) 9(1) 10(2) 11(3) , 12(4) 13(5) 14(6) 15(7) 16(0) 17(1), 18(2) 19(3) 20(4) 21(5) 22(6) 23(7) => 0)
=> N/(M,N의최대공약수) : kN중 가장 빠른 수, 먹을 수 있는 초콜렛 개수.


### Analysis - time complexity

>
  Detected time complexity:
  O(log(N + M))

    
    
#
 ### learned lesson
 
* ** Euclidean algorithm
* Euclidean algorithm


#

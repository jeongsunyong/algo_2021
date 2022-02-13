
# Lessons10. Prime and composite numbers
## [10.1 CountFactors](https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/count_factors/)
* 소요 시간 : 15분

### 성공 코드
```python
import math

def solution(N):
    cnt=0
    for i in range(1,math.ceil(math.sqrt(N))):
        if N%i==0:
            cnt+=2
    
    if N%math.sqrt(N)==0:
        cnt+=1

    return cnt

"""
    goal : factors 개수 반환하기
    N : positive integer
    D : 양수의 factor : N = D*M
    N is an integer within the range [1..2,147,483,647].

    1,2,3,4
    24,12,8,6

    D*M=> 쌍으로 나타나므로, 각 factor는 D,M으로 1회씩 2번 체크된다
    : 최대 N^(1/2)만큼 체크 시 반대쪽도 포함됨.
"""
```

--------------------------------------------------------------------
### 2.13 comment    
최초 제출코드
```python
def solution(N):
    cnt=0
    for i in range(1,N+1):
        if N%i==0:
            cnt+=1
    return cnt
```
최초 제출은 O(N).
한 3분만에 제출한것같은데 역시 fail이었다.   
이전에 소수찾기에서 아리스토텔레스의 체? 그런게 잇던 것 같은데 소수찾기가 아니어서   
시간복잡도를 어떻게 줄일까 하다가   
예시에서 24일경우 N/2 이후인 12이후부터는 약수가 나올 수 없기때문에 N/2제출해보려했으나 상수배라 O(N)은 마찬가지   
이 때 12 이후부터 자기자신 제외 약수가 나올 수 없는 것은 하나의 수 자체일경우 그렇고   
실질적으로는 1 * 24 , 2 * 12로 쌍이 존재.    
=> N^(1/2) (제곱근)까지 체크 시 카운트 * 2로 집계하면 O(N^(1/2))로 찾을 수 있다.    
이 때 제곱근이 정수인경우는 2가 아니라 1개만 카운트해줌    


### Analysis - time complexity

>
  Detected time complexity:
  O(sqrt(N))  

    
----------------------------------------------
## [10.2 MinPerimeterRectangle](https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/min_perimeter_rectangle/)
* 소요 시간 : 20분

### 성공 코드
```python
import math

def solution(N):
    res=1
    for i in range(1,math.ceil(math.sqrt(N))+1):
        if N%i==0:
            res=i
    return (res+int(N/res))*2



"""
    goal: 넓이가 N인 사각형의 perimeter 최솟값
    N : 사각형의 넓이
    perimeter = 2*(A+B)
    N is an integer within the range [1..1,000,000,000].

    a*b=area=N
    a=N/a
    perimeter = 2*(N/a+a)
        =>최소 : a=b , 최대 : N/a, a ->판단필요
    
    일반적 : 정사각형일때 최소 (N이 충분히 크면 극단값이 perimeter 최대값)
    정사각형일 때 : 10*10 = 100
        perimeter : 2(10+10)=40
    극단 : 100 * 1 = 100
        perimeter = 2*(100+1)=201
    중간 : 25*4 = 100
        perimeter = 2(25+4)=58
    6400
        80*80 -> 2*160
        ..
        6400*1 -> 2*6401

    1 1*1 ->유일
    2 2*1 ->유일
    3 3*1 유일
    4
        2*2
        4*1 -> 더큼
    5 5*1->유일
    6
        2*3
        6*1->최대
    =>N/a+a에서 N/a가 a보다 클 때, a+1 - 1보다 N/(a+1)-N/(a)가 더 작다(손실이크다)
        a,b의 차이를 최소화했을 때 : 최솟값

"""
```

--------------------------------------------------------------------
### 2.13 comment    
사각형에서 같은 넓이일 때, 정사각형에 가까울수록 둘레의 최소값이고, 상하,좌우 변의 길이 차이가 클수록 둘레의 값이 크다.

### Analysis - time complexity

>
  Detected time complexity:
  O(sqrt(N))  

    
----------------------------------------------
## [10.3 Flags](https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/flags/)
* 소요 시간 : 20분

### 성공 코드
```python

```

--------------------------------------------------------------------
### 2.13 comment    

### Analysis - time complexity

>
  Detected time complexity:
  O(sqrt(N))  

    
----------------------------------------------
## [10.4 Peaks](https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/peaks/)



#
 ### learned lesson
 
* ** Prime and composite numbers
* Prime and composite numbers

#
 
 

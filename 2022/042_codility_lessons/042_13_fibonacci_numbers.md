# Lessons13.Fibonacci numbers
## [13.2 Ladder](https://app.codility.com/programmers/lessons/13-fibonacci_numbers/fib_frog/)
* 소요 시간 : 1시간 30분

### 성공 코드
```
def solution(A, B):
    L=max(A)+1
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    len_A=len(A)
    res=[0]*len_A
    for i in range(len_A):
        target=A[i]
        res[i]=fibs[B[i]][target]
    
    return res
```

--------------------------------------------------------------------
### 3.1 comment    

### 1차 timeout err코드
```python
def solution(A, B):
    res=[]
    for i,target in enumerate(A):
        modulo=pow(2,B[i])
        f1=0%modulo
        f2=1%modulo
        f3=2%modulo
        for i in range(2,target):
            f1=f2
            f2=f3
            f3=(f2+f1)%modulo
        if target==1:
            f3=1
        res.append(f3)
    
    return res
"""
GOAL : top of ladder 오르기까지 가능한 경우의 수 구하기
    경우의 수 modulo 2^P
ladder : N rungs, 1~N(steps)
    first : 1/2
    rung K -> move to K+1 or k+2
    final : rung N
    A[I] rungs modulo 2^B[I].

    fibonacci의 조합과 관련있을 듯 함. : 1or2의 선택이므로
    ex)
    f0=0
    f1=1
    f2=1,1 / 2
    f3=1,1,1 / 2,1 / 1,2
    f4=1,1,1,1 / 2,1,1 / 1,2,1 / 1,1,2 / 2,2
    f5= 1+2 + 1+1 (3*1 + 1*2)
    f6= 4*1+

    L is an integer within the range [1..50,000];
each element of array A is an integer within the range [1..L];
each element of array B is an integer within the range [1..30].

#각 인덱스만큼 가는 경우의수
        #3이 되기위해서는 + 1만큼가는카운트,2만큼가는 카운트를 더해줘야한다. (그 이유는 i-1만큼 가고 +1 가는 경우의 수 혹은 i-2 만큼 가고 +2만큼 가는 경우의수)
        # 1 1 1, 1 2, 2,1 (3개)

        logic
        (1) 홀수 + 1 무조건 필요
        (2) 짝수 :  각 자리마다 1 1 혹은 2 선택 가능.
        fibonacci step만큼 해당 조합 구해줌.

"""
### 2차 timeout error 코드(75%) O(L^2)
```pyhton
def solution(A, B):
    fibs=[0,1,2]
    for i in range(3,50000+1):
        fibs.append(fibs[i-1]+fibs[i-2])

    res=[]
    for i,target in enumerate(A):
        modulo=pow(2,B[i])
        case_cnt=fibs[target]%modulo
        res.append(case_cnt)
    
    return res
```
```
### 3차 timeout error 코드(50%) O(L^2)
```python
def solution(A, B):
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,50000+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    res=[]
    for i,target in enumerate(A):
        case_cnt=fibs[B[i]][target]
        res.append(case_cnt)

    return res
```

내 계산으로는 O(L x 30)이어야 하는데     
L^2가 왜 나올까 고민.      
우선 3차 fail코드의경우 상수time이 소요되는 전처리부(fibs) 구하는 부분이 일반케이스들에서 통과하는 것으로 보아        

후반부의 참조부에서 timeout에러가 발생하는 것으로 추정됨.    
```python
    for i,target in enumerate(A): # 1~L
        case_cnt=fibs[B[i]][target] # 참조 : O(1)
        res.append(case_cnt) : 맨 뒤에 insert : O(1)
```
-> 참조 시 hash collision이 발생하는 케이스가 있는지? 
-> 혹은 이중list의경우 시간복잡도가 높아지는지?
 
->참조를 수정할 순 없고, 참조한 변수를 새로운 변수에 할당하는 과정이 오래 걸릴 수 있을 것 같아 참조값을 바로 저장하는 방식으로 변경.        
append 하지 않고 res 배열을 미리 길이에 맞게 초기화하여 할당해줌.       
=> 통과.      
정확하게 뭐가 원인이었는지 파악하기위해 테스트해봤는데,     

```python
#첫번째,  append만 삭제케이스 (res 미리 할당)
def solution(A, B):
    L=max(A)+1
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    len_A=len(A)
    res=[0]*len_A
    for i in range(len_A):
        target=A[i]
        cnt=fibs[B[i]][target]
        res[i]=cnt
    
    return res
    
    

#두번째, 변수 할당만 삭제 케이스(바로 append)
def solution(A, B):
    L=max(A)+1
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    len_A=len(A)
    res=[]
    for i in range(len_A):
        target=A[i]
        res.append(fibs[B[i]][target])
    
    return res

### 세 번째, 둘다 케이스
def solution(A, B):
    L=max(A)+1
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    len_A=len(A)
    res=[]
    for i in range(len_A):
        target=A[i]
        cnt=fibs[B[i]][target]
        res.append(cnt)
    
    return res
```
둘다 통과. 해서 혹시하고 둘 다 해봤는데 통과.(O(L))
설마 enumerate가 복잡도가 늘어나는지
```python
def solution(A, B):
    L=max(A)+1
    fibs=[[0,1,2]]
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L+1):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    len_A=len(A)
    res=[]
    for i,a in enumerate(A):
        target=A[i]
        cnt=fibs[B[i]][target]
        res.append(cnt)
    
    return res
```
그건 아님. enumerate 사용해도 통과.      
=> 반대로 3번째 timeout err 코드에서 변경해봄.    
첫 번째 조사 때 50000번까지 모두 조사했었는데,    
max(L)+1까지 만 조사하도록 수정. (1번째 통과코드들과 동일)   
```
def solution(A, B):
    fibs=[[0,1,2]]
    L=max(A)+2
    for m in range(1,31):
        modulo=pow(2,m)
        fibs.append([0%modulo,1%modulo,2%modulo])
        f_m=fibs[-1]
        for i in range(3,L):
            f_m.append((f_m[i-1]+f_m[i-2])%modulo)

    res=[]
    for i,target in enumerate(A):
        case_cnt=fibs[B[i]][target]
        res.append(case_cnt)

    return res
```
-> 통과.    
최악의 경우 어짜피 모두 50000까지 돌것이기 때문에 상관 없을 것이라 생각했었는데,   
max(L)까지만 피보나치를 저장하는거랑   
50000까지 모두 저장하는거랑     
해시collision이 일어날 수 있는 가능성이 달라지는 듯 함.       
아마 50000번 x 30번인 케이스가 최악의 케이스가 아니거나(이건아닐듯)   
이전 테스트케이스들을 돌리면서 컴퓨팅했던게   
hash충돌에 영향을 주지 않을까 생각.      
그래서 결과적으로는 50000번 * 30번 연산 및 저장을 1번 하는것과 여러번 하는 것에 있어서   
1번정도는 거의 해시 충돌이 일어나지 않지만 여러번 하게되면 거의 무조건 일어나는.    
형상이라고 추측 ..   정확히는 모르겠지만 어쨌거나 코드상 직접적인 원인은 공간복잡도에 따른 동일 연산에서 다른 복잡도로 인한 시간복잡도 변화.(동적최대값 저장 and 상수최대값저장 차이)    


 ### learned lesson
 
* ** Fibonacci numbers
* 해시 충돌
파이썬 리스트형은 C배열에 wrapper로 해시테이블로 참조하도록 구성되어있어서 어디에 접근하던 O(1)이다.    
근데 아마 참조하는데 있어서도 해시충돌이 일어나는모양.   
> #### 해시충돌 (위키백과 참고)
>해시 충돌이란 해시 함수가 서로 다른 두 개의 입력값에 대해 동일한 출력값을 내는 상황을 의미한다. 
>해시 함수가 무한한 가짓수의 입력값을 받아 유한한 가짓수의 출력값을 생성하는 경우, 비둘기집 원리에 의해 해시 충돌은 항상 존재한다.
>해시 함수를 사용하여 입력 키 값으로부터 해시 값을 얻어 그것을 인덱스로 사용하는 것은 효율적인 검색 방식 중 하나이다. 
>이와 같은 해시 값으로 이루어진 자료구조를 '해시 테이블'이라고 부른다. 
>서로 다른 입력 키 값이 서로 다른 해시 값(인덱스)으로 매핑될 경우 해시 테이블 조회에 걸리는 시간은 상수 시간이 된다. 
>그러나 여러개의 서로 다른 키 값이 동일한 인덱스로 매핑될 경우, 해시 충돌이 발생하여 해시 테이블의 성능을 떨어뜨리게 된다. 
>이와 같은 해시 충돌을 처리하는 방식 중 가장 많이 쓰이는 것이
>(1)'체이닝'(chaining, 각각의 해시 테이블 인덱스에 해당하는 자료구조를 연결 리스트로 만드는 방법)과 
>(2)'개방 번지화'(open addressing, 해시 테이블 인덱스 중 비어있는 공간을 할당하는 방법)'이다. 
> 그러나 둘다 최악의 경우 조회 복잡도가 원소 개수에 따라 선형 시간이 된다.
#

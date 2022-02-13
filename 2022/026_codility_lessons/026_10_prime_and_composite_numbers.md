
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
* 소요 시간 : 2시간

### 성공 코드
```python
import math
def solution(A):
    peaks=[]
    for i in range(1,len(A)-1):
        if A[i-1] < A[i] and A[i] > A[i+1]:
            peaks.append(i)

    max_cnt=0
    for num_flag in range(1,math.ceil(math.sqrt(len(A)))+1):
        cnt=0
        pre=-num_flag
        for idx in peaks:
            if idx-pre>=num_flag:
                pre=idx
                cnt+=1
                if cnt>= num_flag:
                    break
        if max_cnt<cnt:
            max_cnt=cnt

    return max_cnt
"""
    GOAL : flag 최대 개수.
    A: 숫자배열
        size N, non-empty
    peak : 0<P<N-1인 인덱스P에대해, A[P - 1] < A[P] > A[P + 1]
        양옆보다 큰 수.
    flag 꽂기 rule:
        (1) peak에 꽂을 수 있다.
        (2) K번째 flag : 두 flag간 거리는 K보다 크거나같아야한다.
        * P와 Q인덱스간 거리 : abs(P-Q)
    
    N is an integer within the range [1..400,000];
each element of array A is an integer within the range [0..1,000,000,000].

    arr N개
        -> 최대 flags : sqrt(N)개 :
            because : if 5개의 flag, 5칸씩 5개의 flag 떨어저있어야하므로. 5*5개의 arr size필요, 0, N-1는 peak불가하므로 N-1개가 최대일듯.

"""
```

--------------------------------------------------------------------
### 2.13 comment   
실패 코드(1차제출)
```python
def solution(A):
    peaks=[]
    for i in range(1,len(A)-1):
        if A[i-1] < A[i] and A[i] > A[i+1]:
            peaks.append(i)

    max_cnt=0
    for num_flag in range(1,len(peaks)+1):
        cnt=0
        pre=0
        for idx in peaks:
            if idx-pre>=num_flag:
                pre=idx
                cnt+=1
                if cnt> num_flag:
                    break
        if max_cnt<cnt:
            max_cnt=cnt

    return max_cnt
```
peaks 저장 후 -> peak들만 순회하며 이전인덱스와 거리 차이가 num_flag이상일 때 cnt증가, 갱신해주며 마지막에는 가장 큰 cnt값(flag)를 반환.
timeout err

실패코드(2차제출)
```python
import math

def solution(A):
    max_flag=0
    for distance in range(1,math.ceil(math.sqrt(len(A)))):
        idx=1
        flag=0
        pre=-distance
        while idx < len(A)-1:
            if A[idx-1] < A[idx] and A[idx] > A[idx+1] and idx-pre >= distance:
                flag+=1
                pre=idx
                idx+=distance
            else:
                idx+=1
        if flag>=distance:
            max_flag=flag    

    return max_flag

```
loop1) distance 개수를 변경하면서
loop2) 해당 distance만큼 띄워진 flag들 체크.. -> flag가 기준 distance만큼 꽂을 수 있다면 해당 flags개수로 갱신.

위 케이스 둘 다 timeout err가 떠서
첫번째 제출의 num_flag를 sqrt(N)으로 변경했을 때,
1case 빼고 통과되었다(timeout 해결)

test_case > 
    packed_peaks
    possible to set floor(sqrt(N))+1 flags✘WRONG ANSWER
해당 케이스에서 걸렸었는데, ex ) 25면 맨첫번째, 마지막 인덱스는 peak가 될 수 없으므로  최대 4개까지 flag를 꽂을 수 있다고 생각했었으나 5개의 peak( 2..7..12..17..22 )까지 가능.(5개의 distance는 N-1(4)번만나오면 되기 때문에.

코딜리티가 초 제한이 없어서 O(N)으로 풀어야하는지 O(log(N)), O(sqrt(N))등 시간복잡도 제한을 파악하기 어려워서 어떤 방법으로 접근해서 시간복잡도를 줄여나가야하는지 결정하는게 조금 어려웠던 것 같다.
실제 1번풀이가 접근이맞았었지만 timeout후 다른방법을 시도해봤던건 확신이없어서 였는데
input size가 N is an integer within the range [1..400,000]; 였어서(100 * 100) (* 4) 대충 O(N)까지는 허용되는 듯.


### Analysis - time complexity

>
  Detected time complexity:
  O((N))  

    
----------------------------------------------
## [10.4 Peaks](https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/peaks/)
* 소요 시간 : 1시간30분

### 성공 코드
```python
def solution(A):
    peaks=[]
    for i in range(1,len(A)-1):
        if A[i-1] < A[i] and A[i] > A[i+1]:
            peaks.append(i)

    N=len(A)
    if len(peaks) < 1:
        return 0
    max_cnt=1

    for block_cnt in range(2,N):
        if N%block_cnt != 0:
            continue
    
        in_block_flag=0
        block_size=int(N/block_cnt)
        block_start=0
        block_end=block_size-1
        cnt=0
        for peak in peaks:
            if peak >= block_end:
                if in_block_flag==0 and peak!=block_end:
                    break
                elif in_block_flag==1 or peak==block_end:
                    if peak==block_end:
                        in_block_flag=0
                    block_start+=block_size
                    block_end+=block_size
                    cnt+=1
                    if peak==block_end:
                        in_block_flag=0
                        block_start+=block_size
                        block_end+=block_size
                        cnt+=1
                    
            elif peak >=block_start and peak < block_end:
                in_block_flag=1
        if in_block_flag==1:
            cnt+=1
        if cnt == block_cnt :
            max_cnt=block_cnt
    return max_cnt

"""
    goal: A가 peak를 포함해 분리될 수 있는 최대개수.
    A: 정수배열,size N, non-empty
    peak :  0 < P < N - 1,  A[P - 1] < A[P] and A[P] > A[P + 1].
        (양옆보다 큰 수)

    분리조건: same number elements
            peak포함(블럭내에서 peak의 양옆 포함되어야하는것은 아님)

    N is an integer within the range [1..100,000];
    each element of array A is an integer within the range [0..1,000,000,000].
"""
```

--------------------------------------------------------------------
### 2.13 comment   
flag문제처럼 flag리스트를 따로 빼서 순회.     
block_cnt 개수로 loop를 돌아서 체크, 최대 카운트에 분리가능한경우를 return.    
디버깅of디버깅으로 풀어서    
잘 푼건 아닌 것 같다.     
시간복잡도도 O(N * log(log(N))으로 정답이 아닌듯함.      
정답코드     
```python
def solution(A):
  
    peaks = []
    
    for i in range(1, len(A)-1):
        if A[i] > A[i-1] and A[i] > A[i+1]:
            peaks.append(i)
            
    for i in range(len(peaks),0,-1):
        if len(A) % i == 0:
            block_size = len(A)//i
            block = [False]*i
            block_cnt = 0
            for j in range(len(peaks)):
                idx = peaks[j] // block_size
                if block[idx] == False:
                    block[idx] = True
                    block_cnt += 1
            
            if block_cnt == i:
                return block_cnt
        
    return 0
```
구글링에 검색했을 때 나온 풀이.     
peak size * peak size 내에 해결이 가능하다.     
크게 다르진 않은 것 같기도 하다.      
제출해서 맞은 풀이에서 1번째 루프를 range(len(peak))로 변경했을 시 시간복잡도 변화 x    
구글에서 가져온 코드도 N * log(log(N))로 정상으로 풀은 듯   

### Analysis - time complexity

>
  Detected time complexity:
  O(N * log(log(N)))      



#
 ### learned lesson
 
* ** Prime and composite numbers
* Prime and composite numbers

#
 
 

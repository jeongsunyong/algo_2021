# Lessons1. Iterations
## [1.1 BinaryGap](https://app.codility.com/programmers/lessons/1-iterations/binary_gap/)
* 소요 시간 : 23분

### 성공 코드
```python
def solution(N):
    binary_list=list()
    q=N
    while q > 1 :
        binary_list.append(q%2)
        q=int(q/2)

    binary_list.append(q)
    binary_list.reverse()
    #binary_list=list(map(str,binary_list))
    #binary_n=''.join(binary_list)
    max_cnt=0
    zero_cnt=0
    for b in binary_list:
        if b==0:
            zero_cnt+=1
        elif b==1:
            max_cnt=max(max_cnt,zero_cnt)
            zero_cnt=0

    return max_cnt

"""
* GOAL : 양의정수N에서 longest binary gap의 길이 구하기. (no binarygap : 0)
    binary gap : 
    10 . . . 01 : 1 binary gap
    1001001 : 2 binary gap
    1111 / 1000 : no binary gap

* 생각포인트 ) N in range(1,2147483647)
    : 2,147,483,647의 경우 long long으로 2진수 0 개수 저장가능한지.

* 2진수구하기
if 10 : 1010
10%2 = 0
5%2 = 1
2%2 = 0
1

"""

```

--------------------------------------------------------------------
### 2.5 comment
codility에서는 제출 후 testcase를 제공해서   
평소에 로직 짜고 일부 케이스때문에 실패,수정 후 제출해야 통과하는 일이 잦은 나에게   
케이스를 정리해서 학습하기 좋은 플랫폼이라고 생각.   
    
어떤 케이스들이 있는지 살펴보기    

#### case - Correctness tests   
(1) extremes : 양 끝 값 테스트 케이스     
    * n=1, n=5=101_2 and n=2147483647=2^31-1      
(2) trailing_zeroes : 숫자의 0의 시퀀스에서 이후 다른 숫자(1)이 뒤 따르지 않는 케이스. : 0으로 끝나는 케이스.    
    * n=6=110_2 and n=328=101001000_2    
(3) power_of_2 : 2제곱수 케이스      
    * n=5=101_2, n=16=2^4 and n=1024=2^10    
(4) simple : 일반 케이스     
    * n=9=1001_2 and n=11=1011_2     
(5) medium : 중간규모값 수 케이스   
    * n=51712=110010100000000_2 and n=20=10100_2      
(6) large : 큰 값 케이스     
    * n=1610612737=1100000000000000000000000000001_2      


#
 ### learned lesson
 
* ** 반복문 ( Iteration ) 
#
 
 
 
 
 

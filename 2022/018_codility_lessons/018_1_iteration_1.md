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

#
#
 ### learned lesson
 
* ** 반복문 ( Iteration ) 
#
#
 
 
 
 
 


## [다음 큰 수](https://programmers.co.kr/learn/courses/30/lessons/12911)
* 소요 시간 :  15분

### 성공코드
```python
def solution(n):
    answer = 0
    print(n)
    binary_n=''
    q=n
    while q>=1:
        binary_n+=str(q%2)
        q=q//2
    one_cnt=binary_n.count('1')
    for i in range(n+1,1000001):
        binary_n=''
        q=i
        while q>=1:
            binary_n+=str(q%2)
            q=q//2
        if binary_n.count('1')==one_cnt:
            answer=i
            break
        
    return answer
```

----------------------------------------------------------------------------
### comment 
4/16 코드리뷰    

2진수 변환 숫자의 1 개수가 같으면서 n보다 더 큰 최소의 자연수 구하기.  
처음 접근은 2진수로 변환해서 문자열로 규칙성이나 조작해서 바로 정답을 찾을 수 있을것이라 예상했었는데 방법이 안떠올라서  
n+1부터 최대 수 1,000,000까지 loop를 돌면서 2진수로 변환, 1 count를 세줌.   count연산은 시간복잡도가 O(n)이다   
그러므로 최악의경우 1,000,000 * (1,000,000의 이진수자릿수)일텐데, 효율성에서 통과함.   
이유는 1,000,000의 이진수 자리수는 11110100001001000000로 20자리수밖에 안되기 때문. 또한 대부분 큰 범위 오차 없이 2진수 변환 시 1이 같은수를 찾아내므로(100이내) 시간복잡도는 이상적인 시간복잡도에 비해 현저하게 낮다 .    

#
#
 ### learned lesson
 
* ** 
#
#
 
 
 
 


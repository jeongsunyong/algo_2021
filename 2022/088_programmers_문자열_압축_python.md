
## [문자열 압축](https://programmers.co.kr/learn/courses/30/lessons/60057?language=python3#)
* 소요 시간 :  1시간

### 성공코드
```python
def solution(s):
    answer = 0
    n=len(s)
    min_len=1001
    for i in range(1,n//2+1):
        start=0
        cnt=1
        comp_s=''
        i_res=''
        while start+i-1<n:
            comp_s=s[start:start+i]
            if comp_s==s[start+i:start+i+i]:
                cnt+=1
            else:
                if cnt>1:
                    i_res+=str(cnt)+comp_s
                else:
                    i_res+=comp_s
                cnt=1
            start+=i
        
        if start<=n-1:
            if cnt>1:
                i_res+=str(cnt)+comp_s
            else:
                i_res+=s[start:]
        
        if len(i_res)<min_len:
            min_len=len(i_res)
    
    if len(s)==1:
        min_len=1
    answer=min_len
    return answer
```

----------------------------------------------------------------------------
### comment 
4/18 코드리뷰    

문자열 압축 개수를 순회하며 전체 경우를 비교해준다.   
이 때 압축 가능 개수는 전체의 1/2까지(1/2개가 넘는다면 압축할 동일 문자열 존재 x)   
각 압축가능 개수 i개마다 전체 문자열을 순회하면서 start~start+i, start+i~start+2 * i 를 비교, 같다면 카운트, 아니면 바로 문자열을 붙여준다.   
다음 문자열이 같지 않을 때, 카운트가 2 이상이라면 이전에 누적된 동일문자열이 존재하는것이므로 해당 문자열은 문자열을 붙여주고 넘어간다.  
loop가 start+i-1 < n 까지 도는데, 마지막에 i개 이하로 남게되거나 딱 맞는경우 루프를 진행하지 않으므로(다음이 없기 때문에 인덱스에러)    
루프 탈출 후 마지막에 잔여 문자열들을 더해줌.   
그리고 압축한 문자가 min len보다 작을경우 갱신해주고, 마지막에는 min_len을 반환한다.    

테스트케이스5번이 실패했었는데,    
다른사람의 질문을 참고해 s문자열의 길이가 1인 경우 루프에 진입하지 않음 발견     
-> 마지막에 len(s)==1인경우 예외처리. 통과.   


#
#
 ### learned lesson
 
* ** 
#
#
 
 
 
 


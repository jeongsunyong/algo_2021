
## [입국심사](https://programmers.co.kr/learn/courses/30/lessons/43238)
* 소요 시간 :  30분

### 성공코드
```python
def solution(n, times):
    answer = 0
    m=len(times)
    start=min(times)
    end=max(times)*n
    mid=0
    while start<=end: # stop조건 : start가 end보다 커질 때.
        mid=(start+end)//2
        passed_cnt=0
        for t in times:
            passed_cnt+=mid//t
        if passed_cnt>=n: # 해당 초에 더 많은 사람들 통과 가능 시 (이 때, n일 경우에도 더 작은 범위를 조사해줘야함)
            end=mid-1
        elif passed_cnt<n: # 해당 초에 통과 불가능시 : 더 큰 시간 필요.
            start=mid+1

    answer=start
    return answer

"""
goal
    모든 사람이 심사를 받는데 걸리는 시간
input
    n : 입국 심사 대기 수  1<=n<=1,000,000,000
    times : 한 명 심사 걸리는 시간 배열
    m = len(times):심사관 수 (1<=m<=100,000)
    
    
"""
```

----------------------------------------------------------------------------
### comment 
4/15 코드리뷰    

이분탐색은 범위가 많이 헷갈리는 것 같다.   
start 반환 이유 : start가 end보다 커질 때 종료되고, 이 때의 end값은 passed_cnt가 n일 때의 최소값이다.   
만약 mid값이 정확히 최소값일 때(passed_cnt가 n이되는 최소 시간) start,end갱신 분기는     
end=mid-1이되고, mid값은 최소값-1이된다.   
이 때, start가 mid보다 커질 때 stop조건이며, 이는 start가 정확히 최소값이 되는 그 지점이 되었음을 의미.   
만약 시작부터 계속 작은 값이 나왔기 때문에start=mid+1분기만 탔을 때,   
end=mid-1을 타지 않았음은 해당 start값으로도 passed_cnt==n이 되기 시간이 부족하다는 것이므로    
start가 end값으로 넘어가 stop될 때 start값이 최소 만족n값.(end초기값은 심사 최대시간x인원수이므로)    

answer=end로 반환하는 경우 범위를 생각해보면

```python
"""
        if passed_cnt>=n: # 해당 초에 더 많은 사람들 통과 가능 시 (이 때, n일 경우에도 더 작은 범위를 조사해줘야함)
            if mid==end:
                break
            end=mid
        elif passed_cnt<n: # 해당 초에 통과 불가능시 : 더 큰 시간 필요.
            start=mid+1

    answer=end   
"""
```
위와 같이 end 갱신값을 mid로 두어 end의 최종 값이 passed_cnt>=n인 최소값으로 둔다.      
이 때 정답이 end가 더 큰 방향에서 passed_cnt==n인 케이스로 좁혀나갈 때, 정답 a에대해 mid가 a로 수렴할 수 있다. (ex start=6, end=6로 수렴하면 start<=end가 while조건이므로 무한루프)   
그래서 if mid==end이면 break하는 조건문 추가. 해당코드는 통과한다.    

```python
while start<end: # stop조건 : start와 end가 같아질 때,
        mid=(start+end)//2
        passed_cnt=0
        for t in times:
            passed_cnt+=mid//t
        if passed_cnt>=n: # 해당 초에 더 많은 사람들 통과 가능 시 (이 때, n일 경우에도 더 작은 범위를 조사해줘야함)
            end=mid
        elif passed_cnt<n: # 해당 초에 통과 불가능시 : 더 큰 시간 필요.
            start=mid+1

    answer=end  
    return answer
```  
이때 if mid==end : break 가 깔끔하지 않아서 없애보면   
start<end를 while조건으로 놓으면,  
end는 passed_cnt=n인 최소 mid값을 가지게되고,  
start는 루프를 돌다 이 값을 넘어가게된다. 이 때 end 반환  시 검사 통과인원이 n 인 최소 시간을 반환.   


#
#
 ### learned lesson
 
* ** 이분탐색
#
#
 
 
 
 


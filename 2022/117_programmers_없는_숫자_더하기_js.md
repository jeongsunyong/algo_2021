## [없는 숫자 더하기](https://programmers.co.kr/learn/courses/30/lessons/86051?language=javascript)
* 소요 시간 : 약 10분

### 성공코드
```js
function solution(numbers) {
    var answer = -1;
    let total=0
    for(let i=1;i<10;i++){total+=i;}
    numbers.forEach((number)=>{
        total-=number
    })
    
    answer=total;
    return answer;
}
```



----------------------------------------------------------------------------
### comment 
6/12 코드리뷰
total에 0부터 9까지 합한 숫자를 할당하고, number에서 있는 숫자들을 뺀다.
-> 없는 숫자의 합

#
#
 ### learned lesson
 
* 
#
#
 
 

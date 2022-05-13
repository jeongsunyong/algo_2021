## [JadenCase 문자열 만들기
](https://programmers.co.kr/learn/courses/30/lessons/12951?language=javascript)
* 소요 시간 : 약 20분

### 성공코드
```js
function solution(s) {
    var answer = ''
    let splited= s.split(" ")
    js_list=[]
    console.log(splited)
    splited.forEach((item) =>{
        js_str=item.toLowerCase()
        if(js_str.length >1)
            js_list.push(js_str[0].toUpperCase()+js_str.substr(1))
        else
            js_list.push(js_str.toUpperCase())
    })
    
    answer=js_list.join(" ")
    return answer;
}


/*
goal
    Jadencase로 바꾼 문자열
input
    s : 문자열
JadenCase
    : 모든 단어의 첫 문자가 대문자이고, 그 외의 알파벳은 소문자인 문자열.

*/
```


----------------------------------------------------------------------------
### comment 
5/12 코드리뷰    
javascript 연습.까먹지 않기 위해 간단한 문제 풀이.

#
#
 ### learned lesson
 
* ** javascript 복습
* 문자열 함수
```js
str.split(" ") : 파라미터인 spliter를 기준으로 문자열을 분리한다. 결과는 list
str.substr(idx1, (idx2)) : idx1부터 해당 문자열의 substr을 반환한다, 두번째 인자 지정 시 문자열 끝범위 지정 가능.
str.toUppserCase() : 모든 문자열에대해 대문자로 변환한 결과.
str.toLowerCase() : 모든 문자열에 대해 소문자로 변환한 결과
str.length : 문자열의 길이. 
str.indexOf : 왼쪽부터 가장 처음 존재하는 지정 문자 인덱스(위치) 반환


```
* 어레이 함수
```js
array.join(" ") 파라미터인 spliter를 원소간 구분자로 더해 배열을 문자열로 합친다.
array.map( function(item) ) : array의 아이템들에 대해 일괄적으로 변경된 값을 매핑한다(return으로 변경될 원소 표현)
array.foreach ( function(item) ): array의 아이템들에 대해 함수 결과 실행.
array.filter ( function(item) ) : 함수 조건에 해당하는 요소가 있는 배열을 새로 생성한다. return으로 조건을 나타낸다.(bool) 유사하게 하나의 원소만 검색하는 역할을 하는 find함수가 있음. 

```

* 형변환 / math
```
num.toString(16) : 16진수 문자열로 변경, 인자 없을 시 10진수로.
parseInt(str) : 문자를 integer 숫자로 변환해줌.
Math.pow(num,2) : num의 2제곱
Math.round(num) : 반올림
Math.ceil(num) : 올림
Math.floor(num) : 버림
Math.sqrt(num) : 제곱근
Math.min(num1,num2) : 최소값 (max : 최대값)

```
*   
* 
#
#
 
 

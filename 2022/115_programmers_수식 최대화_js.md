## [수식 최대화](https://programmers.co.kr/learn/courses/30/lessons/67257?language=javascript)
* 소요 시간 : 약 40분

### 성공코드
```js
function solution(expression) {
    let answer = 0;
    op_list=['+','-','*']
    op_comb=[]
    
    // operator 우선순위 combination
    for(let first=0;first<3;first++){
        for(let second=0;second<3;second++){
            for(let third=0;third<3;third++){
                if(first=== second || first===third || second===third)
                    continue
                op_comb.push([op_list[first],op_list[second],op_list[third]])
            }
        }
    }
    
    max_res=0
    
    // 우선순위 combination loop(해당 우선순위에서의 res값 중 max를 찾는다.
    op_comb.forEach((op)=>{
        op1=op[0]
        op2=op[1]
        op3=op[2]
        
        // 우선순위에 따라 split
        splited=expression.split(op3).map((exp1)=>{
            return exp1.split(op2).map((exp2)=>{
                return exp2.split(op1)
            })
        })
        
        // split 가장 depth 높은 순으로 연산 실행.
        res_pre=splited.map((num1)=>{
            if(typeof(num1) =='object'){
                processed=num1.map((num2)=>{
                    if(typeof(num2) =='object'){
                        op_res1=parseInt(num2[0])
                        for(let idx=1 ; idx<num2.length ; idx+=1){
                            num3=parseInt(num2[idx])
                            op_res1=(op1==='*')? op_res1*num3: (op1==='+')? op_res1+num3:op_res1-num3
                        }
                        return op_res1
                    }
                    else{
                        return num2
                    }
                })
                op_res2=parseInt(processed[0])
                for(let idx=1;idx<processed.length;idx+=1){
                    num2=parseInt(processed[idx])
                    op_res2=(op2==='*')? op_res2*num2: (op2==='+')? op_res2+num2:op_res2-num2
                }
                return op_res2
            }
            else{
                return num1
            }
        })
        
        //최종 연산 진행 후 max 
        res=parseInt(res_pre[0])
        for(let idx=1;idx<res_pre.length;idx+=1){
            num=parseInt(res_pre[idx])
            res=(op3==='*')? res*num: (op3==='+')? res+num:res-num
        }
        if(max_res<Math.abs(res))
            max_res=Math.abs(res)
    })
    answer=max_res
    return answer;
}

/*
goal : 우승 시 받을 수 있는 가장 큰 상금 금액
input : expression 
        (3<= len expression <=100)
        숫자와 + , - , *로 이루어진 연산식
        숫자는 0 이상 999 이하의 숫자

rule
    순위는 우선순위를 재정의하여 만들 수 있는 가장 큰 숫자.
    같은 연산자끼리는 앞에있는 것의 우선순위가 높다.
    각 연산자는 서로 다른 순위를 가진다. 
    결과가 음수라면 절댓값을 반환한다.

*/
```



----------------------------------------------------------------------------
### comment 
5/20 코드리뷰    
연산자 +, -, * 에 대해 우선순위를 지정해 연산결과가 가장 높은 값을 반환하는 문제.   

전체를 순회하면서 매번 우선순위 operator 주위 숫자를 연산하는 방법이 떠올랐었는데 비효율적일 것 같아서   
오퍼레이터 위치를 저장해놨다가(dict) 연산해주는 방법을 생각했었는데 -> 숫자 범위와 이후 연결되는 연산관계 연결짓기가 어려움.   
우선순위가 낮은 순서로 split해서 우선순위 표현을 array로 묶어주는 방식을 선택.
우선순위가 높을수록 wrapping되어있으므로 가장 차수가 높은 원소(둘러쌓여있는 괄호 개수, 3차->2차->1차) 순으로 연산을 진행해준다.   
연산 후에는 결과를 숫자로 반환해 다음번 우선순위 연산에 연산 포함되도록 해서 최종적으로는 괄호를 모두 제거.   

연산자가 3개라서 foreach=>foreach ..이런식으로 했는데, 비슷한 문제에서 operator수가 많은 경우라면 ?    
코드를 깔끔하게 작성하려면 그냥 for문이나 재귀함수로 작성하는 것이 깔끔할 것 같다..   

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
 
 

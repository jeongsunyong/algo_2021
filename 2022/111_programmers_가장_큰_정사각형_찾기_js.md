## [가장 큰 정사각형 만들기](https://programmers.co.kr/learn/courses/30/lessons/12905?language=javascript)
* 소요 시간 : 약 50분

### 성공코드(구글링)
```js
function solution(board)
{
    var answer = 1234;
    row_size=board.length
    col_size=board[0].length
    for(let i=1;i<row_size;i++){
        for(let j=1;j<col_size;j++){
            if (board[i-1][j]!=0 && board[i][j-1]!=0 && board[i-1][j-1]!=0 && board[i][j]!=0){
                board[i][j]=Math.min(Math.min(board[i-1][j],board[i][j-1],board[i-1][j-1]))+1
            }
        }
    }
    
    max_size=0
    board.forEach((row)=>{
        row.forEach((num)=>{
            if(max_size<num){
                max_size=num
            }
        })
    })
    
    answer=max_size*max_size
    return answer;
}

/*
    goal
        1로 이루어진 가장 큰 정사각형의 넓이
    input
        board:1,0으로 이루어진 배열
            row,column길이는 1000이하 
    
*/
```

### 실패코드(전체탐색, 시간초과)
```js
가장 큰 정사각형
function solution(board)
{
    var answer = 1234;
    row_size=board.length
    col_size=board[0].length
    max_size=Math.min(row_size,col_size)
    max_square=0
    for(let square_size=max_size;square_size>=1;square_size-=1){ //사각형 판단 시작점 loop : y좌표
        for(let x=0;x<=col_size-square_size;x+=1){ //사각형 판단 시작점 loop : x좌표
            for(let y=0;y<=row_size-square_size;y+=1){
                let is_square=true
                for(let square_x=x; square_x<x+square_size ;square_x+=1){
                   for(let square_y=y;square_y<y+square_size;square_y++){
                        if(board[square_y][square_x]==0){
                                is_square=false
                            }
                   }
                }
                if(is_square==true){
                    max_square=Math.max(square_size,max_square)
                }
            }
        }
        if(max_square!=0){break}
    }
    answer=max_square*max_square
    
    return answer;
}

/*
    goal
        1로 이루어진 가장 큰 정사각형의 넓이
    input
        board:1,0으로 이루어진 배열
            row,column길이는 1000이하 
    
*/
```

### 실패코드(이분탐색,시간초과)
```js
function solution(board)
{
    var answer = 1234;
    row_size=board.length
    col_size=board[0].length
    max_size=Math.min(row_size,col_size)
    max_square=0
    let start=1
    let end =max_size
    let cnt=0
    let mid_pre=-1
    while (start <= end){
        cnt+=1
        if(cnt>=10)
            break
        
        let square_size = Math.floor((start+end)/2)
        let square_flag=false
        
        
        for(let x=0;x<=col_size-square_size;x+=1){ //사각형 판단 시작점 loop : x좌표
            for(let y=0;y<=row_size-square_size;y+=1){ //사각형 판단 시작점 loop : y좌표
                let is_square=true
                for(let square_x=x; square_x<x+square_size ;square_x+=1){
                   for(let square_y=y;square_y<y+square_size;square_y++){
                        if(board[square_y][square_x]==0){
                                is_square=false
                            }
                   }
                }
                if(is_square==true){
                    square_flag=true
                    break
                }
            }
            if (square_flag==true){
                break
            }
        }
        
        if(square_flag==true){
            start=square_size+1
        }
        else if(square_flag==false){
            end=square_size-1
        }
        if (start>end){
            max_square=end
            break
        }
    }
    answer=max_square*max_square
    
    return answer;
}

/*
    goal
        1로 이루어진 가장 큰 정사각형의 넓이
    input
        board:1,0으로 이루어진 배열
            row,column길이는 1000이하 
    
*/
```


----------------------------------------------------------------------------
### comment 
5/13 코드리뷰    
javascript 연습.  
방법이 사각형 매칭해서 찾는 방법을 선택했는데, 시간초과 -> square_size를 이분탐색해서 찾아도 시간초과   
다른 분들의 풀이를 찾아보니 큰 정사각형은 작은 정사각형을 포함하기때문에 DP같은 방법으로 풀이가 가능하다.    
현재 칸을 기준으로 왼오대각선,왼,오방향으로 사각형을 구성할 수 있는 칸이 존재(1 이상)한다면 해당 칸에 +1 체크해준다.       
이 때 +1되는 수는 대각,왼,오 중 가장 작은 수를 가지는 숫자의 +1이다. 그 이유는 네칸을 이용해 사각형을 구성할 때, 더 작은 수를 가지는 사각형은 해당 구성에 참여할 수 없으므로,   
작은 수를 취해줘야 해당 사각형들로 만들어지는 사각형의 길이를 표현할 수 있음.      
또한 0인경우에는 쌓아올린 사각형에 구멍이 생기므로 숫자를 누적해주면 안됨.   그러므로 주변이 0이라면 pass한다.    
최종적으로 board의 수들 중 가장 큰 숫자가 max 한 변의 길이가 된다     

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
 
 

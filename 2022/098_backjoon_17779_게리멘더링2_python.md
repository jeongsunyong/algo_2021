## [게리멘더링2](https://www.acmicpc.net/problem/17779)
* 소요 시간 :  4시간 

### 성공 코드
```python
import sys

n=int(sys.stdin.readline().rstrip())
board=[list(map(int,sys.stdin.readline().rstrip().split(" "))) for i in range(n)]

min_diff=99999999

#x,y loop
for y in range(1,n-1):
    for x in range(1,n-1):

        #d1,d2 loop
        for d1 in range(1,n):
            for d2 in range(1,n):
                if x+d1+d2>=n or y-d1<0 or y+d2>=n:
                    break
                area_sum = [0, 0, 0, 0, 0]
                for i in range(n):
                    for j in range(n):
                        if j <= i + x - y + 2 * d1 and j >= -i + x + y and j >= i + x - y and j >= i+x-y and j <= -i +x+ 2*d2 + y:
                            area_sum[4]+=board[i][j]
                        elif 0<=j and j<=x+d1 and i>=0 and i<y:
                            area_sum[0] += board[i][j]
                        elif x+d1<j and j<n and i>=0 and i<=y+d2-d1:
                            area_sum[1] += board[i][j]
                        elif j>=0 and j<x+d2 and i>=y and i<n :
                            area_sum[2] += board[i][j]
                        elif j>=x+d2 and j<n and i>y+d2-d1 and i<n:
                            area_sum[3] += board[i][j]

                max_sum=max(area_sum)
                min_sum=min(area_sum)
                min_diff=min(min_diff, max_sum-min_sum)

print(min_diff)

"""
goal
input
    n : 재현시의 크기
    board: n*n 구역. 각 칸은 해당 구역 인구 수 의미.

conecpt : 선거구
    - 구역을 다섯 개의 선거구로 나누어야 한다.
    - 선거구는 구역을 적어도 하나 포함해야하며 선거구들끼리는 연결되어있어야한다.

rule : 선거구 나누는 방법
    1. 기준점 x,y와 경계의 길이 d1,d2결정 (d1,d2 >= 1, 1<= x<= x+d1+d2 <= N , 1<=y-d1<y<y+d2<=N)
    ?★ 2.  경계선 (ex d1=3, d2=4)
        (1) (x,y),(x+1,y-1) ~ (x+d1,y-d1) 
              .
             .
            .
        (2) (x,y), (x+1,y+1) ~ (x+d2, y+d2)
            .
             .
              .
               .
        (3) (x+d1, y-d1),(x+d1+1, y-d1+1) ~ (x+d1+d2, y-d1+d2)
                    .
                     .
                      .
                       .
        (4) (x+d2, y+d2) , (x+d2+1, y+d2-1) ~ (x+d2+d1, y+d2-d1)
                      .
                     .
                    .
                    
        ->
        
          .
         . .
        .   .
         .   .
          . .
           . 
          
    3. 경계선과 경계선의 안에 포함되어있는 곳은 5번 선거구.
    4. 5번 선거구에 포함되지 않은 구역(r,c)의 선거구 번호는 다음 기준에 따름 (0 인덱스)
    #### r,c는 r행 c열 -> x=c, y=r
        #####v 5선거구에 포함되지 않는 경우에 한헤 나머지 구역을 배정해준다 . * * * ★
        * 1번 : 0<=r<x+d1, 0<=c<=y (왼쪽 위)
        * 2번 : 0<=r<=x+d2, y< c<=N (오른쪽 위
        * 3번 : x+d1 <= r<= N , 0<=c<=y+d1+d2 (왼쪽 아래)
        * 4번 : x+d2 < r <= N , y-d1+d2 <= c<=N


```



----------------------------------------------------------------------------
### comment 
4/27 코드리뷰    

배열에 저장해서 출력해보며 노가다로 품.  
처음에 시행착오를 겪은 부분이, x,y좌표계가 헷갈렸다.   
우선 예제를 봤을 때에는 (r,c)는 각 행,열 -> y, x idx이다. : 왼쪽 상단이 0,0 -> 0idx     
또 x,y(마름모 시작점) -> x,y idx이다. -> 왼쪽 상단이 0,0 -> 1idx    
d1은 x방향으로의 마름모 길이, d2는 y방향으로 마름모 길이이다.  
이런 부분들이 헷갈려서 많이 헤맸다.  

이 때 중요한점은 x,y좌표계인 board가 0,0 위치가 왼쪽 상단이라는 점.     

선거구(r,c)의 기준   
> 경계
> (x, y) ~ (x+d1, y-d1)
> (x, y) ~ (x+d2, y+d2)
> (x+d1, y-d1) ~ (x+d1+d2, y-d1+d2)
> (x+d2, y+d2) ~ (x+d2+d1, y+d2-d1)

> 선거구
> 1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
> 2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
> 3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
> 4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N


5선거구 안에 드는 구역들의 범위 구하기 -> 각 경계에 대한 직선의 방정식 4개 범위 교집합.    
좌표계나 인덱스를 생각하기 어려워서, 조건이 아닌 그림으로부터 식을 만들었다 .   
```python
(1) j>= -i + x+y
(2) j<= i + x+2*d1-y
(3) j >= i + x-y
(4) j <= -i + x+ 2*d2 + y
```

왼쪽 하단이 0,0으로 생각하게되어서 헷갈렸으나,    
y=ax+b에서     
a는 -1 or 1이므로 수동으로 기울기값 입력,     
b= (x1+x2 - a(y1+y2) )/2 으로 입력.   

이런식으로 범위를 일일이 구해서 마지막에 max-min값을 구해서 최소값을 구함.    

조금 노가다가 많았고 연습이 되었다기보다는 좀 디버깅만 계속 해서 푼 느낌이라    
다음에 풀때는 처음에 설계를 잘 해서 논리적으로 푸는 연습을 하자.    


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 
 


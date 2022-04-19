
## [이차원 배열과 연산](https://www.acmicpc.net/problem/17140)
* 소요 시간 :  1시간30분

### 성공코드
```python
import sys

r,c,k=list(map(int,sys.stdin.readline().rstrip().split(" ")))
A=[ list(map(int, sys.stdin.readline().rstrip().split(" "))) for i in range(3)]
t=0
r-=1
c-=1

def OperationR(A): # 모든 행에 대하여 정렬을 수행한다.
  new_A=[]
  
  for num in A:
      new_A.append(list())

  #배열 재구성(카운트)
  for i,row in enumerate(A):
    num_checked=dict()
    for j,num in enumerate(row):
      if num not in num_checked and num!=0:
        num_checked[num]=True
        new_A[i].append([num,row.count(num)]) 

  #정렬
  max_len=0  
  for i,row in enumerate(new_A):
    if len(row)*2>max_len:
      max_len=len(row)*2
    row.sort(key=lambda x: (x[1],x[0]))
    row_new=[]
    for nums in row:
      row_new.append(nums[0])
      row_new.append(nums[1])
    new_A[i]=row_new

  #0패딩 or 100 cut
  if max_len>100:
    max_len=100
  for row in new_A:
    if len(row)<max_len:
      for i in range(len(row),max_len):
        row.append(0)
    else:
      row=row[:max_len]
      
  res_A=new_A
  return res_A

def OperationC(A):
  new_A=[]
  #배열 재구성(열 인덱스->행인덱스)
  for num in A[0]:
      new_A.append([])
  for i,row in enumerate(A):
    for j,num in enumerate(row):
      new_A[j].append(num)

  #정렬
  new_A=OperationR(new_A)

  res_A=[]
  #배열 재구성(열 행인덱스->열인덱스)
  for num in new_A[0]:
      res_A.append([])
  for i,row in enumerate(new_A):
    for j,num in enumerate(row):
      res_A[j].append(num)

  return res_A
  
while True:
  if len(A)>r and len(A[0])>c: # value check
    if A[r][c]==k:
      break
  t+=1 # 1초 경과
  #1. R연산 조건 확인 후 R 연산 적용
  if len(A) >= len(A[0]) : # 행의 개수가 열의 개수보다 크거나 같은 경우.
    A=OperationR(A)
  elif len(A) < len(A[0]):
    A=OperationC(A)

  if t>100:
    t=-1
    break

print(t)


"""
goal : A[r][c] 값이 k가 되기 위한 연산의 최소 시간. 

input
  r,c,k : target 배열 인덱스 A[r][c], target 값 k
  A : 3*3배열 (1<=A[i]<=100)

operation
- 1초마다 연산 수행
  R연산 : 배열 A의 모든 행에 대해 정렬을 수행 (행의 개수 >= 열의 개수인 경우)
  C연산 : 배열 A의 모들 열에 대해 정렬을 수행 (행의 개수 < 열의 개수인 경우)

-정렬
  정렬[수와 등장 횟수]를 넣는다.
  해당 수 등장 횟수가 커지는 순(오름차순)으로 , (동점일 경우 수가 커지는 순(오름차순)으로 정렬)
- 행,열의 크기가 100을 넘어가는 경우 처음 100개 외 버림.
- 행,열 크기가 커진 곳에는 0을 채움. 수 정렬 시 0은 무시.

"""
```

----------------------------------------------------------------------------
### comment 
4/19 코드리뷰    
초마다 R,C연산을 적용시켜주고 상태를 확인한다.   
R,C연산을 좀 더럽게 구현한 것 같긴 하지만 통과.  
R 연산은,   
1.number가 체크되었는지 딕셔너리를 통해 플래그를 체크하고, 해당 row에서 num개수와 함께 새로운 배열 row에 넣어준다.  
2.그 이후 해당 배열([숫자,카운트])를 카운트의 오름차순 우선 -> 숫자 오름차순 우선 순으로 정렬하고,   
3.정렬 한 숫자에서 숫자,카운트쌍 리스트 괄호를 제거해준다 (그냥 for문으로 해당 두 값 넣어줌. ), 이 때 괄호 제거한 새로운 row의 max길이값을 저장한다.   
4. 100이 넘으면 잘라주고, maxlen보다 작으면 maxlen만큼 0으로 패딩해준다.
5. 반환

C연산은 행렬을 회전한 후 (row->col col->row), R연산 적용 한 결과값을 다시 회전 원복해줌.  






#
#
 ### learned lesson
 
* ** 구현, 정렬, 시뮬레이션
#
#
 
 
 
 



# Lessons6. StacksAndQueues
## [7.1 Brackets](https://app.codility.com/programmers/lessons/7-stacks_and_queues/brackets/)
* 소요 시간 : 15분

### 성공 코드
```python

def solution(S):
    res = 1
    stack=[]
    for character in S:
        if character == '{' or character == '[' or character == '(' :
            stack.append(character)
        else:
            if len(stack)<=0:
                res=0
                break
            open_bracket=stack.pop()
            close_bracket=character
            if not((open_bracket=='{' and close_bracket=='}') or (open_bracket=='[' and close_bracket==']') or (open_bracket=='(' and close_bracket==')')) :
                res = 0
                break

    if len(stack)>0:
        res=0
    return res

"""
    GOAL : S가 p.n일경우 1, 아닐경우 0 반환하기.
    S : string
        size N
    properly nested : = p.n
        아래 조건 중 하나라도 만족 시 p.n
            1.S is empty;
            2.S 형태 "(U)" or "[U]" or "{U}" (U is p.n);
            3.S 형태 "VW" (V && W is p.n).
    N is an integer within the range [0..200,000];
    string S consists only of the following characters: "(", "{", "[", "]", "}" and/or ")".
"""
    
```

--------------------------------------------------------------------
### 2.9 comment    

### Analysis - time complexity

>
  Detected time complexity:
  O(N)

    
-----------------------------------------------
## [7.2 Fish](https://app.codility.com/programmers/lessons/7-stacks_and_queues/fish/)
* 소요 시간 : 30분

### 성공 코드
```python
def solution(A, B):
    stack=[]
    alive_cnt=0
    for p in range(len(B)):
        if(B[p]==1) :
            stack.append(p)
            continue
        if not stack :
            if B[p]==0:
                alive_cnt+=1
            continue

        u_side_fish=stack[-1]
        d_side_fish=p

        while A[u_side_fish] < A[d_side_fish] :
            stack.pop()
            if stack :
                u_side_fish=stack[-1]
            else:
                break
        if not stack :
            alive_cnt+=1

    alive_cnt += len(stack)
    return alive_cnt


"""
    GOAL : 마지막까지 살아남는 물고기 개수 구하기
    A,B : non-empty 배열 : downstream을 따라 배치되어있다. (higher idx : downstream)
        size N
    A[P] : size of fish P =>All element is unique,
    B[P] : direction of fish P
        0 : to upstream
        1 : to downstream

    서로 반대방향 fish : 서로 만나게됨 (중간에 아무 것도 없다면)
        larger fish가 small fish eat.
        ex) P, Q (P<Q ,P,Q방향 opposite)
        * If A[P] > A[Q] then P eats Q, and P will still be flowing downstream,
        * If A[Q] > A[P] then Q eats P, and Q will still be flowing upstream.
        : 0(a) , 1(b) , 0(c)일 경우,
            b와 c만 만난다. (b to downstream, c to upstream.)
            <<--- upstream dirction         downstream direction --->> 
    N is an integer within the range [1..100,000];
    each element of array A is an integer within the range [0..1,000,000,000];
    each element of array B is an integer that can have one of the following values: 0, 1;
    the elements of A are all distinct.
""" 
```

--------------------------------------------------------------------
### 2.9 comment    

파이썬 배열이 비었는지 조사할 때,    
if arr(empty : false) / if not arr 로 조사하는 것이 시간 복잡도를 줄일 수 있는 방법. len: O(N)       
무심코 len()을 조사하는 경우가 있었던 것도 같은데 이번에 풀면서 생각나서 재작성.    


### Analysis - time complexity

>
  Detected time complexity:
  O(N)

    
----------------------------------------------
## [7.3 Nesting](https://app.codility.com/programmers/lessons/7-stacks_and_queues/nesting/)
* 소요 시간 : 8분

### 성공 코드
```python

def solution(S):
    res = 1
    stack=[]
    for character in S :
        if character == '(':
            stack.append(character)
            continue
        if not stack : 
            res = 0
            break
        stack.pop()

    if stack :
        res = 0
        
    return res

```

--------------------------------------------------------------------
### 2.9 comment    
7.1 bracket과 동일 문제. bracket 종류만 3개에서 1개로 줄어들었다.    
풀고 나서 bracket을 다른 방법으로 풀어야하는지 nesting에 무슨 의도가 있는지 구글링해봤는데    
별다른 것 없었어서 코딜리티에서 그냥 연습하라고 비슷한 유형으로 구성한 듯 하다.     
 

### Analysis - time complexity

>
  Detected time complexity:
  O(N)

    
----------------------------------------------
## [7.4 StoneWall](https://app.codility.com/programmers/lessons/7-stacks_and_queues/stone_wall/)
* 소요 시간 : 30분+30분

### 성공 코드
```python
def solution(H):
    block = 0
    stack=[]
    for h in H:
        if not stack:
            stack.append(h)
            continue
        if h==stack[-1]:
            continue
        elif h > stack[-1]:
            stack.append(h)
        while h < stack[-1]:
            stack.pop()
            block+=1
            if not stack : break
        if stack:
            if stack[-1]==h:
                continue
        stack.append(h)
    while stack : 
        stack.pop()
        block+=1
    
    return block

"""
GOAL : 벽을 쌓는 데 필요한 최소 직사각형 block 개수 구하기
    직사각형의 크기는 자유롭게, 배열에 해당하는 높이를 맞춰줘야함.
    H : 벽의 높이 배열(양의정수)
        size N (meter of walls)
    H[I] : I ~ I+1 wall의 높이
        (H[0] : left end / H[N-1] : right end
        if 0 1 2 3 ( N = 4)
        leftend(0) 1~2(1) / 2~3(2) / rightend(3))

    N is an integer within the range [1..100,000];
    each element of array H is an integer within the range [1..1,000,000,000].

    최대한 큰 크기의 직사각형 사용하기 ?
    공통 높이 찾기
    가장 작은 개수라는 것을 보장할 수 있는 방법?

    stack : 자신보다 작은 직사각형이 나오면 end
    ex
     8 8 -> (8 push x )1개의 블럭으로 가능 (0)
     8 5 -> 감소 (5 push 8 pop) 1개의 블럭으로 불가능. (1)
     5 7 -> 증가(7 push) 1개의 블럭 위에 추가로 1개의 블럭 (1)
     7 9 -> 증가(9 push) 1개의 블럭 위에 추가로 1개의 블럭 (1)
     9 8 -> 감소 (8 push 9 pop) -> 8 vs 7 : 8이 더 크므로 1개의 블럭 추가.(2)
     8 7 -> 감소 ( 8 pop) -> 7 vs 7 : 동일한 블럭 존재하므로 묶음(7push x) (3)
     7 4 -> 감소 (4 push 7 pop 5pop) -> 5 vs 4 : 더 작으므로 stack ->모두pop (5)
     4 7 -> 증가 (8 push)
     end
     -> stack pop pop(7 , 4)-> (7)
"""

```

--------------------------------------------------------------------
### 2.9 comment    
  lessons 주제가 stack & queue인데 3개 문제 전부 stack으로 풀어서    
  queue로 풀어야하는건가 접근하려했는데    
  생각하다보니깐 스택이 적합한 것 같아 스택으로 풀이.    
  풀고 나서 서치해봤는데 queue로 푼 사람은 없는 것 같고 다들 비슷하게 queue문제가 안나온것에 대한 의문을 가짐ㅎㅎ..    
  lessons 주제가 있어 스택이나 큐라는 접근방법이 힌트가 되는데,    
  실제 코테 문제로 나오면 생각을 못 할수도 있을 것 같다    
  

### Analysis - time complexity

>
  Detected time complexity: O(N)
  

    
----------------------------------------------

#
 ### learned lesson
 
* ** Stack & Queue
* Stack & Queue

#
 
 

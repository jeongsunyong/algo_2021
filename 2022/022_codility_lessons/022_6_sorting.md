
# Lessons6. Sorting
## [6.4 NumberOfDiscIntersections](https://app.codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/)
* 소요 시간 : 2시간+2시간

### 성공 코드
```python
def solution(A):
    discs = []
    for c, r in enumerate(A):
        discs.append((c-r, -1))
        discs.append((c+r, 1))

    discs = sorted(discs)
    t = 0
    r = 0

    for d in discs:
        if d[1] == 1:
            t -= 1
        else :
            r += t
            t += 1
    
    return r if r <= 10000000 else -1



                
    return cnt
    
    
```

--------------------------------------------------------------------
### 2.9 comment    
구글링 참고.
for i~N 내부에 for i+1~N은 nlogn이라고 알고있었는데, 아닌가보다.(codility상에서 O(N^2)로 실패.
위 풀이는 stack 괄호닫기 문제랑 유사하게 start,end를 한 배열에 넣고,
start 등장마다 disc 개수를 누적하고, end등장 시 disc개수를 하나 빼주는 방식으로 구현하였다.
범위가 시작하고, end범위까지 도달하지 않았을 때 다른 start가 등장했을 때, 해당 범위와 같은 공간을 공유한다는 개념을 이용했는데
end가 바깥 disc의 end이던 방금 나온 start의 end이던 intersect하는 개수만 count하면 되므로 어떤 disc의 start, end인지 구별할 필요가 없었다. 


codility medium난이도는 나한테 대개 어려운 것 같다.
아직 수준이 easy수준인 듯 하고 반성..



### 실패 풀이들
```python
def solution(A):
    res=-1
    r_ranges=[]
    for c,r in enumerate(A):
        r_ranges.append([c-r,c+r])
    #r_ranges.sort(key=lambda x:(x[0],x[1]))
    r_ranges.sort(key=lambda x:(x[1]))
    #pre_start=-2147483648
    #pre_end=-2147483648
    cnt=0
    pre_ends=[]

    for r in r_ranges:
        start=r[0]
        end=r[1]
        for pre_end in pre_ends : 
            if pre_end>= start:
                cnt+=1
        pre_ends.append(end)
    
    if cnt>0:
        res=cnt
    
    return res

```
```python
def solution(A):
    r_ranges=[]
    for c,r in enumerate(A):
        r_ranges.append([c-r,c+r])
    r_ranges.sort(key=lambda x:x[0])

    cnt=0

    N=len(r_ranges)
    for i in range(N):
        for j in range(i+1,N):
            if r_ranges[i][1] <r_ranges[j][0]:
                break
            cnt+=1
            if cnt>10000000:
                return -1
                
    return cnt
    
    
"""
    * GOAL : intersecting disc 개수 반환. (존재x시 -1)

    * A : 양의정수 배열(discs 지름)
        size N 
    * J-th disc : 지름A[J] , 중심(J.0)
    * Intersect : 공통 영역을 가질 때 intersect , 선이 접할 때도 intersect
    * N is an integer within the range [0..100,000];
each element of array A is an integer within the range [0..2,147,483,647].

    * 중심의 y좌표가 0이기때문에,
        중심으로부터 +- 지름영역(선)이 intersect한다면,
        두 disc는 intersect한다.
        => 지름 범위 비교

    범위 비교 시 end빠른 순으로 정렬 후 제거해나가는방법
    #queue=deque() #queue : no => 0,4 5,5 3,6 존재 시, 5,5검사에서 0,4제외하면 3,6과 intersect 체크 못함. (end순으로 정렬한 것이 sequencial한 결과 x)   

    =>역방향 검사
    7,7-> 3,6 -> 5,5 -> 3,4   5,5는 제외 가능. (end순이므로 이후 end보다 늦은 start 없는 것 보장 , 이후 end 더 작음을 보장)
    하지만 3,6에서 loop가 stop한다 해도, 그 이전 원소로 7,7 있을 때,
     3,4와 intersect하진않아서 queue개수만큼 cnt+해주는 방안 불가.
    pre_start와 end비교.

"""
```


### Analysis - time complexity

>
  Detected time complexity:
  O(N*log(N)) or O(N)

    
-----------------------------------------------

#
 ### learned lesson
 
* ** Sorting
* sort

#
 
 

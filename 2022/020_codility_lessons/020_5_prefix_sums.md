
# Lessons5. Prefix Sums
## [5.3 GenomicRangeQuery](https://app.codility.com/programmers/lessons/5-prefix_sums/genomic_range_query/)
* 소요 시간 : 3시간 + 2시간
### 1차 제출
```python
def calc_cost(start,end,start_pre,end_pre):
    cost=0
    if start>end_pre :
        cost=999999
    else : 
        cost = (start-start_pre) + abs(end-end_pre)
    return cost

def solution(S, P, Q):
    res = 0 
    i_f_counter=[0,0,0,0,0]#impact factor counter, 1,2,3,4 idx
    i_f_dict={
        'A':1,
        'C':2,
        'G':3,
        'T':4
    } #impact factor dictionary, A, C, G and T = 1, 2, 3 and 4
    queries=[]
    for i in range(0,len(P)):
        queries.append([P[i],Q[i],0,i])#start,end, ans, original_idx

    queries.sort(key=lambda x: (x[0],x[1]-x[0])) #작은시작순, 짧은길이순으로 정렬

    start_pre=-1
    end_pre=999999
    for k,q in enumerate(queries) :
        start=q[0]
        end=q[1]
        min_cnt=-1
        #1. start 변경 체크
        if start != start_pre:
            cost=calc_cost(start,end,start_pre,end_pre)
            #1.1 counter 갱신
            if end-start <= cost: #method1
                i_f_counter=[0,0,0,0,0]
                for i in range(start,end+1):
                    i_f=i_f_dict[S[i]] #letter to impact_factor
                    i_f_counter[i_f]+=1
            else:
                for i in range(start_pre,start): #start_pre~start-1 제외
                    i_f=i_f_dict[S[i]]
                    i_f_counter[i_f]-=1
                if end <= end_pre : # 범위 축소경우 : 이전 카운팅 제외
                    for i in range(end+1,end_pre+1): #end+1~end_pre 제외
                        i_f= i_f_dict[S[i]]
                        i_f_counter[i_f]-=1
                elif end > end_pre : # 범위 확장의 경우 : 카운팅
                    for i in range(end_pre+1,end+1): #end+1~end_pre 카운팅
                        i_f=i_f_dict[S[i]]
                        i_f_counter[i_f]+=1
        if start == start_pre:
            for i in range(end_pre+1,end+1): #end+1~end_pre 카운팅
                i_f=i_f_dict[S[i]]
                i_f_counter[i_f]+=1

        #2. counter에서 max체크. (0이 아닌 max값) 
        for i,cnt in enumerate(i_f_counter):
            if cnt!=0:
                min_cnt=i
                break

        #4 min값 저장
        queries[k][2]=min_cnt

        #3. pre 갱신.
        start_pre=start
        end_pre=end

    # queries에 저장된 ans값 배열저장
    res=[0]*len(queries)
    for q in queries:
        idx=q[3]
        ans=q[2]
        res[idx]=ans
    return res
```

### 성공 코드
```python
def solution(S, P, Q):
    i_f_dict={
        'A':1,
        'C':2,
        'G':3,
        'T':4
    }
    res = []
    
    for i in range(len(P)):
        min_i=5
        sub_str=S[P[i]:Q[i]+1]
        for letter in i_f_dict:
            if letter in sub_str :
                min_i=min(min_i,i_f_dict[letter])
        res.append(min_i)

    return res
```
--------------------------------------------------------------------
### 2.7 comment    

1차 제출 실패: timeout    
(Detected time complexity:O(N * M))    
▶extreme_sinlge     
single character string✔OK    
▶extreme_double   
double character string✔OK    
▶simple     
simple tests✔OK    
▶small_length_string   
small length simple string✔OK     
▶small_random    
small random string, length = ~300✔OK    
expand allPerformance tests   
▶almost_all_same_letters     
GGGGGG..??..GGGGGG..??..GGGGGG✘TIMEOUT ERROR    
Killed. Hard limit reached: 6.000 sec.   
▶large_random     
large random string, length✘TIMEOUT ERROR    
Killed. Hard limit reached: 6.000 sec.    
▶extreme_large    
all max ranges✔OK    

1차 풀이에서는 시간복잡도를 줄이기 위해 전체 문자열을 검사하지 않고 min값을 찾을 수 있는 방법을 고민했고,    
각 impact factor들의 counter에 누적 개수를 저장, 갱신하는 방법을 선택하였다.    
최대한 갱신 회수를 줄이기 위해 query를 start 위치순으로, 길이순으로 정렬했다.    
```
"""
    #방1)
    queries.sort(key=lambda x: (x[0],x[1]-x[0])) #작은시작순, 짧은길이순
        # 2,3 2,4 2,5 등 추가범위가 최소화됨.
        # but 2..100000 까지 counting 후에 3,4가오면 recounting해줘야함.
            # start범위 변경마다 counter 초기화해주면 최소화가능.
                # 최악) 2,100000 - 3,100000 - 4,100000 - 5,100000 
                    #  
    #방2)
    #queries.sort(key=lambda x: (x[1]-x[0],x[0])) #짧은길이순, 작은시작순.
        # 4,99 3,101, 2,102, 2,110들이 인접 : counting최소.
            # but 2,100 101,700 900,1000 겹치지 않으면 다시 세야함
                #최악) 1,50000 - 50001,100000 - 1,50001, 49999-100000...
 
    # 선택 ) next query 판정 시 연산량에따라 방1), 방2) 판정하는 방법으로
        # 방1)로 정렬하되, 갱신 방법은 start 변경 시(if start_pre != start)
            # end - start와 cost를 비교해 연산량이 작은 갱신 방법을 선택

"""
```
쿼리를 정렬하는 방법 선택 이유는 위와 같다.    
결론적으로는 시간초과로 fail.    

성공코드의경우 구글링을 참고해 풀이하였으며    
중요한 learned lessons : python의 in연산자가 O(1)시간복잡도를 가진다★      
내부적으로 해시를 사용하기 때문에 O(1)로 접근가능하고, 해시충돌로 인한 시간복잡도 최대값은O(N).    
1차 풀이때는 내부를 그 때 그 때 substr을 검사한다는 접근 자체를 배제했기 때문에 in연산자를 쓸 생각을 아예 안했는데,     
각 query마다 substr에서 4개의 문자(ACGT) 여부를 검사, 존재하는 가장 작은 문자의 숫자값을 저장하는 것이 해법이었다.     
python 언어 이해도에 대한 반성.    
현재 문법을 사용할 수 있을 정도로 익힌 수준이고    
append,delete,sort 등 자료구조에서 주로 접하는 메서드의 시간복잡도 뿐만 아니라 in연산같이 아무 의심 없이 쓰던 기능에 대한 시간복잡도 또한 고려사항이라는 것 자체를 깨달았다.     
시간복잡도, 내부구현에대한 지식이 있어야 시간복잡도,공간복잡도 제한이 있는 문제에 적합한 연산자, 메서드(기능)을 사용할 수 있다.    

### Analysis - time complexity

>
  Detected time complexity:
 O(N + M)


## [5.4 MinAvgTwoSlice](https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/)
* 소요 시간 : 1시간
### 성공 코드
```python
def solution(A):
    min_avg=(A[0]+A[1])/2.
    min_start=0
    
    for i in range(2,len(A)): 
        if (A[i]+A[i-1]+A[i-2])/3. < min_avg:
            min_avg=(A[i]+A[i-1]+A[i-2])/3.
            min_start=i-2
        if (A[i]+A[i-1])/2. < min_avg:
            min_avg=(A[i]+A[i-1])/2.
            min_start=i-1
    return min_start

"""
    goal : starting position of minimal average(중복시 젤작은수)
    A: non-empty
        size N
    slice of array A : 
        (P,Q) 0<=P<Q<N

    N is an integer within the range [2..100,000];
    each element of array A is an integer within the range [-10,000..10,000].
"""
```
--------------------------------------------------------------------
### 2.7 comment    

구글링참고.
최초풀이는 
```python
def solution(A):
    min_avg=(A[0]+A[1])/2.
    min_start=0
    ac_sum=(A[0]+A[1])
    ac_cnt=2
    
    for i in range(2,len(A)): 
        if (ac_sum+A[i])/(ac_cnt+1) < min_avg:
            ac_sum+=A[i]
            ac_cnt+=1
            min_avg=ac_sum/ac_cnt
        if (ac_sum-A[min_start])/(ac_cnt-1) < min_avg and ac_cnt-1 > 1:
            ac_sum-=A[min_start]
            ac_cnt-=1
            min_avg=ac_sum/ac_cnt
            min_start-=1
    return min_start
```
이었으나 실패, O(N^2)이하 풀이를 떠올리기엔 시간이 너무 많이 걸릴 것 같아 구글링 참고하여 풀이함.
참고)부분합[https://cheolhojung.github.io/posts/algorithm/Codility-MinAvgTwoSlice.html]
>
    a <= b일 때, a와 b의 평균은 a 이상이 된다. (a = b 일 때, a와 b의 평균은 a, 즉 두 수가 같은 경우는 a 혹은 b가 된다)
    마찬가지로, (a + b) <= (c + d)일 때, (a, b)와 (c, d)의 평균은 (a + b) 이상이 된다.
    결국, 원소가 4개(a, b, c, d)인 그룹은 (a, b)와 (c, d)를 나누었을 때, 각각의 평균의 작은 값 이상이 된다.
    2개인 그룹이 작은 값이 되므로 4개의 그룹은 고려할 필요가 없어진다.
    예외로 원소가 3개인 그룹에서 2개인 그룹과 1개인 그룹의 경우를 확인해야 하지만, 문제에서 주어진 조건에 의하면 그룹의 원소는 최소 2개 이상이므로 2개와 3개인 그룹만 비교한다.



```


#
 ### learned lesson
 
* ** Prefix Sums
* Python 연산자의 시간복잡도
  - sub_str in str : O(1)

#
 
 

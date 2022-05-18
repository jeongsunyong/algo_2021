## [메뉴 리뉴얼]([https://programmers.co.kr/learn/courses/30/lessons/87390?language=python3](https://programmers.co.kr/learn/courses/30/lessons/72411))
* 소요 시간 : 약 30분

### 성공코드
```python
def makeComb(s,num,start,len_s,cstr_len,cstr,comb):
    if cstr_len==num:
        comb[num].append(cstr)
        return
    if start==len_s:
        return
    for i in range(start,len_s):
        cstr_next=str(cstr)+s[i]
        makeComb(s,num,i+1,len_s,cstr_len+1,cstr_next,comb)
            
def solution(orders, course):
    answer = []
    counter=dict()
    comb=dict()
    cand=dict()
    for num in course:
        comb[num]=list()
        counter[num]=dict()
        cand[num]=list()
    for order in orders:
        len_s=len(order)
        for num in course:
            ord_sort=list(order)
            ord_sort.sort()
            ord_sort="".join(ord_sort)
            makeComb(ord_sort,num,0,len_s,0,'',comb)
    
    for num in course:
        for c in comb[num]:
            if c not in counter[num]:
                counter[num][c]=0
            counter[num][c]+=1
            
    for num in course:
        for c in counter[num]:
            if counter[num][c]>1:
                cand[num].append([c,counter[num][c]])
    for num in course:
        cand[num].sort(key=lambda x:-x[1])
    
    for num in course:
        cnt_pre=-1
        for c in cand[num]:
            s=c[0]
            cnt=c[1]
            if cnt<cnt_pre:
                break
            answer.append(s)
            cnt_pre=cnt
    
    answer.sort()
            
    return answer


"""
goal
    추가하게될 코스요리 메뉴 구성 문자열 형태로 (오름차순)
input
     order : 주문한 단품메뉴들 문자열 형식 (2~20)
     course : 코스요리 구성 단품메뉴들의 갯수 (1~10) , 오름차순

코스요리 형태로 재구성
-> 함께 주문한 빈도수가 높은 set(최소 2가지 이상 단품 메뉴)
    2명 이상 손님에게서 주문된 구성만 후보.


"""
```


----------------------------------------------------------------------------
### comment 
5/18 코드리뷰    

메뉴내역을 훑어서 어떤 메뉴 조합이 가장 인기있었는지 선정, 반환하는 문제.   
여기서는 각 주어진 코스의 메뉴 개수만큼 가장 인기있었던 조합 (2개메뉴 best, 3개메뉴 best, ..)를 분류해서 마지막에는 통합, 사전순으로 반환해야한다.   
orders가 20개까지, orders 메뉴 10개까지, course가 10개까지여서 시간복잡도가 무난할 듯 해 조합으로 모든 케이스를 확인해주는 방식을 사용.    
각 num(메뉴에 들어가는 음식 개수 : course의 원소) 별로 dictionary를 만들어서 orders를 순회, 모든 메뉴 조합을 counting하고, 마지막에 해당 dictionary들에 있는 key들 중
가장 카운트가 높은 메뉴(복수개일경우 메뉴들)을 정답배열에 담아 반환한다.   
조합을 구하는 방법은 DFS를 사용하였다.  


#
#
 ### learned lesson
 * DFS, COMBINATION


#
#
 
 

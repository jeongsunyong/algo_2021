def solution(str1, str2):
    answer = 0
    str1=str1.lower()
    str2=str2.lower()
    
    l1=[]
    l2=[]
    
    for i in range(0,len(str1)-1):
        if str1[i:i+2].isalpha() :
            l1.append(str1[i:i+2])
    for i in range(0,len(str2)-1):
        if str2[i:i+2].isalpha() :
            l2.append(str2[i:i+2])    
    
    #합집합
    union_cnt=0
    union_set=set(l1+l2)
    for element in union_set : 
        print(element)
        c1=l1.count(element)
        c2=l2.count(element)
        union_cnt += max(c1,c2)
        
    #교집합
    intsec_cnt=0
    intsec_set=set(l1).intersection(set(l2))
    for element in intsec_set :
        c1=l1.count(element)
        c2=l2.count(element) 
        intsec_cnt += min(c1,c2)
    
    #개수구하기
    j=1.0
    if union_cnt > 0 :
        j = intsec_cnt / union_cnt
    answer = int(j*65536)
    
    return answer


"""
#note
GOAL : 두 문자열의 자카드 유사도


자카드 유사도 = 교집합크기 / 합집합  (합집합 공집합일경우 1)
=> 단어의 원소 중복도 허용. ****
ex) J ( {1,1,2,2,3} , {1,2,2,4,5} )
=> 합집합은 {1,1,2,2,3,4,5} => 합집합은 동일원소 다수개일경우 더 큰개수로 포함.



"""

def solution(s):
    answer = -1
    
    d={}
    for i in s:
        if i not in d:
            d[i]=0
        d[i]=d[i]+1
        
    for i in d:
        if d[i]%2 != 0:
            return 0
    
    pre=[]
    pre.append("*")
    for i in s:
        if pre[-1]==i :
            pre.pop()
            continue
        pre.append(i)

        
    if pre[-1]=="*" :
        answer=1
    else : 
        answer=0
        
    return answer


#note
"""
GOAL : 짝지어 제거하기 성공적 수행 여부 (1 / 0)

짝지어제거하기 : 같은 알파벳이 2개 붙어있는 짝 찾기
        -> 제거 후 반복
        -> 문자열 모두 제거 시 종료
"""

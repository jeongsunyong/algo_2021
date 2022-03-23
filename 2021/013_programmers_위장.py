import itertools

def multList(l):
    result=1
    for val in l:
        result *= val
    return result
  
def solution(clothes):
    answer = 0
    d_clo = {}
    keys=[]
    lens=[]
    
    for c in clothes :
        if c[1] not in d_clo:
            d_clo[c[1]]=[]
            keys.append(c[1])
        d_clo[c[1]].append(c[0])
    dlen=len(d_clo) # 서로 다른 종류 개수
    for key in keys:
        lens.append(len(d_clo[key])+1)

    sum=multList(lens)-1
    
    answer=sum
    return answer


###note
"""
서로 다른 옷의 조합 수 return

"""

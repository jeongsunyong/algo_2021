
def solution(lines):
    answer = 0
    time = [[int(i[11:13])*3600 + int(i[14:16])*60 + float(i[17:23]), float(i[24:-1]), n] for n,i in enumerate(lines)]
    time = [[round(i[0]-i[1]+0.001,4),i[0],i[2]] for i in time] #시작 / 끝 / 끝나는순서로정렬된 순번
    t_start = sorted(time) #시작 기준으로 정렬됨
    maximum=1
    for t in time:#끝기준으로 정렬된 것 순회
        cnt=0
        for s in t_start : #시작기준으로 정렬된것 순회
            if t[1] + 1 > s[0] and t[1]<=s[1]: #현재순번이 끝나는시점 이후에 끝나고 && 현재순번이 끝나는시점 +1초보다 일찍 시작하는 로그들
                cnt=cnt+1
            elif t[0] + 1 < s[1]:
                break
        if cnt>maximum:
            maximum=cnt
    
    answer=maximum
    
    return answer

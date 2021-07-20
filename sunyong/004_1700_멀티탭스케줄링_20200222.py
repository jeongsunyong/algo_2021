n,k=input().split(" ")
n=int(n)
k=int(k)
l = [] 
l = input().split(" ")

l = [int(i) for i in l] #사용순서배열
l_copy=[i for i in l] #사용순서배열copy -> 여기서 for문 돌면서 하나씩빼기

cnt=0
tab=[]
for i in range(0,k):
    if l[i] in tab:
        l_copy.remove(l[i])#순번지난기기 제거
        continue
    if len(tab)>=n:#tab이 full이면
        target=[]
        target_idx=[]
        for j in tab: #tab에있는것중에 사용순서 가장 먼 것 찾기
            if j in l_copy:# 다음 순번에 포함되있을경우
                target.append(j) #탭에있는 순서대로 
                target_idx.append(l_copy.index(j))#탭에있는 것 순서배열의 인덱스 순차적으로.
            else:
                target.append(j)
                target_idx.append(9999)
        max_idx=target_idx.index(max(target_idx))#순서배열인덱스가최대인 타겟배열의인덱스
        tab.remove(target[max_idx]) #다음순서가 max_idx에해당하는 값의 target배열 index   
        cnt+=1
        tab.append(l[i])
    else:
        tab.append(l[i])
    l_copy.remove(l[i])#순번지난기기 제거
    
print(cnt)

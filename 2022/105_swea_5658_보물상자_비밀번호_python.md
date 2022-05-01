## [보물상자 비밀번호](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo&categoryId=AWXRUN9KfZ8DFAUo&categoryType=CODE&problemTitle=&orderBy=INQUERY_COUNT&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1)
* 소요 시간 :  1시간

### 성공 코드
```python

T = int(input())
for test_case in range(1, T + 1):
    n, k = list(map(int, input().rstrip().split(" ")))
    number = input()
    nums = []
    len_p = n // 4 # 암호의 길이
    
    # 1.회전 loop
    for start in reversed(range(0, n)):
        cnt = 0
        cnt_four = 0
        num = ''
        idx = start
        while cnt < n: # 회전한 문자열로부터 4개의 암호 후보를 생성한다.
            num += number[idx]  # 10진수로 변환할 필요 없음. 숫자가 너무 커짐.
            idx = (idx + 1) % n
            cnt += 1
            cnt_four += 1
            if cnt_four % len_p == 0: # 암호의 길이만큼 문자열이 더해지면 초기화.
                nums.append(num)
                num = ''
                cnt_four = 0
    nums = list(set(nums))
    nums.sort(reverse=True) # 큰 순서로 정렬 .
    num_hex = nums[k - 1] # k번째 큰 수 추출
    num_dec = 0
    cnt = 0
    for c in reversed(num_hex): # 결과 10진수 변환
        if c == 'A':
            num_dec += 10 * (16 ** cnt)
        elif c == 'B':
            num_dec += 11 * (16 ** cnt)
        elif c == 'C':
            num_dec += 12 * (16 ** cnt)
        elif c == 'D':
            num_dec += 13 * (16 ** cnt)
        elif c == 'E':
            num_dec += 14 * (16 ** cnt)
        elif c == 'F':
            num_dec += 15 * (16 ** cnt)
        else:
            num_dec += int(c) * (16 ** cnt)
        cnt += 1
    answer = num_dec
    print(f"#{test_case} {answer}")
```



----------------------------------------------------------------------------
### comment 
5/1 코드리뷰   

set은 정렬할 수 없다(순서가 없는 자료구조이다.) 잊지 말것.    
list sort 시 문자열 정렬은 기본적으로 16진수 정렬이 된다.   
0<1....<9 < A<B<C<D<E<F... < a<b ...<f 이다. (ASCCI값 각 48~57  / 65~90 / 97~122)   


#
#
 ### learned lesson
 
* ** 구현,시뮬레이션
* 
#
#
 
 
 



# Lessons9. MaxSlice
## [9.1 MaxProfit](https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_profit/)
* 소요 시간 : 24분

### 성공 코드
```python
def solution(A):
    min_price=200001
    max_profit=0
    for price in A:
        if price < min_price:
            min_price =price
        else:
            max_profit=max(max_profit,price-min_price)

    return max_profit

"""
    GOAL : 가능한 이득 최대값
    A : 주식가격 배열, A[i] : i날짜의 가격 (consecutive)
        size N
    profit or loss : abs(A[Q] - A[P]) (0<=p<=Q<N)

    N is an integer within the range [0..400,000];
    each element of array A is an integer within the range [0..200,000].
"""

```

--------------------------------------------------------------------
### 2.11 comment    
주식 이득 최대값을 구하는 문제.        
최소값을 갱신시켜 현재값 기준으로 최대 이득인지 체크,갱신해 마지막에 값을 반환해줌.    
처음에 min_price, max_price를 갱신시켜서 마지막에 max-min을 반환했는데, 이럴경우에는       
loss까지 같이 체크가되서 profit이던 loss던 절대값이 가장 큰값이 반환됨.      


### Analysis - time complexity

>
  Detected time complexity:
  O(N)  

    
----------------------------------------------

#
 ### learned lesson
 
* ** MaxSlice
* MaxSlice

#
 
 

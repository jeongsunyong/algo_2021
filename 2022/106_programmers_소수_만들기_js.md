## [소수 만들기](https://programmers.co.kr/learn/courses/30/lessons/12977?language=javascript)
* 소요 시간 : 약 30분

### 성공코드
```js
function isPrime(num){
    if(num%2==0 && num!=2)
        return false;
    for(let i=3;i<=Math.sqrt(num);i+=2){
        if(num%i==0 && num!=i)
            return false;
    }
    return true;
}

function solution(nums) {
    let answer = -1;
    sum_of_three=[]
    n=nums.length;
    console.log(n);
    //조합생성
    for(let idx1=0;idx1<n;idx1++){
        for(let idx2=idx1+1;idx2<n;idx2++){
            for(let idx3=idx2+1;idx3<n;idx3++){
                if (idx1==idx2 || idx2==idx3 || idx1==idx3)
                    continue;
                sum_of_three.push(nums[idx1]+nums[idx2]+nums[idx3])
            }
        }
    }
    
    //중복제거 : 경우의 개수이므로 중복 케이스 세줘야함.
    //sot_set=new Set(sum_of_three);
    //sum_of_three=[...sot_set];
    
    //소수판별
    let cnt=0
    sum_of_three.forEach(num => {
        if(isPrime(num)){
           cnt+=1;
        }
    });
    answer=cnt
    return answer;
}

/*
goal
    주어진 숫자 중 3개를 더했을 때 소수가 되는 경우의 개수.
input
    nums : 숫자 배열 (3<=nums.size()<=50)
            1<= nums[i] <=1000 , 중복 x

*/
```


----------------------------------------------------------------------------
### comment 
5/2 코드리뷰   
숫자의 개수는 50개이므로 조합의 개수는 50 * 49 * 48.    
숫자 소수 판별은 nums[i]가 1000이하인데, 제곱근까지만 탐색하면 나누어떨어지는 수를 탐색할 수있으므로 최대 32정도.   
50 * 50 * 50 * 50 범위 내에 들어온다. 시간복잡도 그렇게 크지 않음.    
-> 3개 조합 배열 sum_of_three에 세개 더한 값들 모두 더해주고,   
해당 값들에 대해 소수 판별해줌.   

#
#
 ### learned lesson
 
* ** 소수(primeNumber)
* ** 조합(Combination)
* 
#
#
 
 

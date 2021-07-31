#include <string>
#include <vector>
#include <iostream>
#define MAX_P 10000000

using namespace std;
vector<int> SS;
int SSCheck[MAX_P]={0}; // 소수면 1, 소수가 아닌것으로 판정됬으면 -1, 접근X면 0
int num_ss=0;
bool isSS(int cur){
    for(int i=3;i<cur;i+=2){
        if(cur%i==0){
            return false;
        }
    }
    return true;
}
void findSS(vector<int> nums, int n, int pos, int num){
    //cout<<num<<endl;
    for(int i=0;i<n;i++){
        int cur = pos==1 ? nums[i] : (nums[i]*pos +num);
        ////초기 (1의자리)
        if(pos == 1){
            if(cur%2==0 && cur != 2){ // 소수 가능성 X : 0, 4,6,8
                SSCheck[cur]=-1;
                continue;
            }
            if(cur==5 || cur==2){ //pos 0일 때 제외하고 소수 가능성 X : 5,2
                if(SSCheck[cur]==0){
                    num_ss++;
                    SSCheck[cur]=1;
                }
                continue;
            }
            if(cur==1 || cur== 9){ // 자기 자신은 소수가 아니면서 소수 가능성O
                if(SSCheck[cur]==0){
                    SSCheck[cur]=-1;
                    vector<int> nums_next;
                    for(int a=0;a<n;a++){ //vector복사
                        if(a==i) continue;
                        nums_next.push_back(nums[a]);
                    }
                    findSS(nums_next,n-1,pos*10,cur);
                }
                continue;
            }
            if(cur==3 || cur==7){
                if(SSCheck[cur]==0){
                    SSCheck[cur]=1;
                    num_ss++;
                    vector<int> nums_next;
                    for(int a=0;a<n;a++){ //vector복사
                        if(a==i) continue;
                        nums_next.push_back(nums[a]);
                    }
                    findSS(nums_next,n-1,pos*10,cur);
                }
                continue;
            }
        }//end pos==1 case
        else if(n>1) {//pos >=10 case
            if(nums[i]==0){ // 현재숫자 0, 종이조각 남았을 떄, 넘겨주기만
                vector<int> nums_next;
                for(int a=0;a<n;a++){ //vector복사
                    if(a==i) continue;
                    nums_next.push_back(nums[a]);
                }
                 findSS(nums_next,n-1,pos*10,cur); 
            }
            else{//현재 숫자 0 아닌경우, 중복 및 소수X판정 체크 후, 소수 체크 후 next 넘겨줌.
                if(SSCheck[cur]==0){//중복체크 : -1이면 소수X판정, 1이면 중복
                    if(isSS(cur)){//소수 case
                        SSCheck[cur]=1;
                        num_ss++;
                        vector<int> nums_next;
                        for(int a=0;a<n;a++){ //vector복사
                            if(a==i) continue;
                            nums_next.push_back(nums[a]);
                        }
                        findSS(nums_next,n-1,pos*10,cur);
                    }else{ //소수 X case
                        SSCheck[cur]=-1;
                        vector<int> nums_next;
                        for(int a=0;a<n;a++){ //vector복사
                            if(a==i) continue;
                            nums_next.push_back(nums[a]);
                        }
                        findSS(nums_next,n-1,pos*10,cur);
                    }
                }//end 중복 체크 case
            }//end 현재숫자 0 or not case 
        }//end pos>=10 && 종이조각 남아있는 case
        else if(n<=1){
            if(nums[i]==0){//현재숫자 0, 종이조각 안남았을 때, 체크 필요 X 
                continue;
            }
            else{//현재 숫자 0 아닐때
                if(SSCheck[cur]==0){//중복체크 : -1이면 소수X판정, 1이면 중복
                    if(isSS(cur)){//소수 case
                        SSCheck[cur]=1;
                        num_ss++;
                    }else{ //소수 X case
                        SSCheck[cur]=-1;
                    }
                }//end 중복 체크 case
            }//end 현재숫자 0 or not case
        }//end pos>=10 && 종이조각 없는 case
    }//end for loop
};
int solution(string numbers) {
    int answer = 0;
    int n = numbers.size();
    vector<int> nums;
    for(int i=0;i<n;i++){
        nums.push_back(int(numbers[i]-48));
    }
    findSS(nums,n,1, 1);//int findSS(nums:숫자배열, n : 배열사이즈, pos : 자리수, int num(현재수))
    //cout<<num_ss<<endl;
    answer=num_ss;
    return answer;
}

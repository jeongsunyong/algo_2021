
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
int changeAlpha(char targetAlpha){
    int init=int('A');
    int target=int(targetAlpha);
    int end=int('Z');
    if(target>78){
        return (end+1-target);
    }else{
        return target-init;
    }
}
int solution(string name) {
    int answer = 0;
    int n=name.size();
    int* visited =new int[n];
    for(int i=0;i<n;i++){
        visited[i]=-1;
        if(name[i]!='A'){
            visited[i]=0;
        }
    }
    
    //(0) 첫번째자리 처리
    if(visited[0]==0){  
        answer+=changeAlpha(name[0]);
        visited[0]=1;
    }
    
    int start=0;
    
    int flag=1;
    while(flag){
        //(1) 시작 방향을 정한다 (지금 이동량 더 적은 'A'가 아닌 알파벳 위치 향해)
        int plus_closest=9999;
        int minus_closest=9999;
        int move=0;
        int next_idx=-1;
        for(int i=1;i<=n/2;i++){
            int idx=start+i;
            if(idx>=n)
                idx=idx-n;
            if(visited[idx]==0){ 
                plus_closest=i;
                next_idx=idx;
                break;
            }
        }
        for(int i=1;i<=n/2;i++){
            int idx=start - i;
            if(idx<0)
                idx=n+idx;
            if(visited[idx]==0){
                minus_closest=i;
                if(minus_closest<plus_closest)
                    next_idx=idx;
                break;
            }
        }

        //(2) 가까운 곳으로 이동 후 시작점 변경해 반복
        if(next_idx==-1){
            flag=0;
        }else{
            answer+=min(plus_closest,minus_closest);
            answer+=changeAlpha(name[next_idx]);
            visited[next_idx]=1;
            start=next_idx;
        }
    }//end while
    
    return answer;
}
/************************note  ***********

1.goal : 이름 완성

2.init state : AA...

3. updown : 알파벳교체 / lr : 위치이동

    cout<<int('A')<<65<<endl;
    cout<<int('N')<<78<<endl; //+13 -13
    cout<<int('Z')<<90<<endl; : 91-90


*****************************************/

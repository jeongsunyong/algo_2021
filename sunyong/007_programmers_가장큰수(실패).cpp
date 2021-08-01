#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


bool compare(int a, int b){
    int a_p=a;
    int b_p=b;
    int a_div=1;
    int b_div=1;
    
    int origin_same=0;
    
    while(a_p/a_div>=10){
        a_div= a_div*10;
    }
    while(b_p/b_div>=10){
        b_div=b_div*10;
    }
    
   if(a_p/a_div > b_p/b_div){ //a 앞자리가 더 클경우
        return true;
    }
    else if(a_p/a_div < b_p/b_div){ //b 앞자리가 더 클경우
        return false;
    }
    else if(a_p/a_div == b_p/b_div){//a,b 앞자리가 같을 경우 
       origin_same = a_p/a_div; 
       //case (1) 둘이 자리수 같은 케이스
            //대소관계 비교로 OK
       if(a_div == b_div){
           if(a_div==1 || a_div==1000){//case 1000 1000 or 1 1
               return true; //어느쪽이앞에와도 상관없음
           }else if(a_div==10){ // case 21 22
               if(a_p%a_div > b_p%b_div)
                   return true;
               else
                   return false;
           }else if(a_div==100){ 
               if((a_p%a_div)/10==(b_p%b_div)/10){//case 212 214
                   if(a_p%10 > b_p%10)
                       return true;
                   else
                       return false;
               }
               else{//case 221 226
                   if(a_p%100 > b_p%100)
                       return true;
                   else
                       return false;
               }
           }
           
       }//case (1) 둘이 자리수 다른 케이스
       else if(a_div > b_div){//a 자리수가 더 높음
           a_p=a_p%a_div;
           b_p=b_p%b_div;
           a_div=a_div/10;
           b_div=b_div/10;//483 42에서 -> 83&10 / 2&1된상태
           while(b_div>1){
               if(a_p/a_div != b_p/b_div){
                   if((a_p/a_div) > (b_p/b_div))
                       return true;
                   else
                       return false;
                   a_p=a_p%a_div;
                   b_p=b_p%b_div;
                   a_div=a_div/10;
                   b_div=b_div/10;
               }
           }
           if(a_p/a_div >= origin_same){
               return true;
           }else if (a_p/a_div < origin_same){
               return false;
           }
       }
       else if(a_div < b_div){//b 자리수가 더 높음
           a_p=a_p%a_div;
           b_p=b_p%b_div;
           a_div=a_div/10;
           b_div=b_div/10;//483 42에서 -> 83&10 / 2&1된상태
           while(a_div>1){
               if(a_p/a_div != b_p/b_div){
                   if((a_p/a_div) > (b_p/b_div))
                       return true;
                   else
                       return false;
               }else{
                   a_p=a_p%a_div;
                   b_p=b_p%b_div;
                   a_div=a_div/10;
                   b_div=b_div/10;
               }
           }
           if(b_p/b_div >= origin_same){
               return false;
           }else {
               return true;
           }
       }
    }
}
string solution(vector<int> numbers) {
    string answer = "";
    sort(numbers.begin(),numbers.end(),compare);
    
    for(int i=0;i<numbers.size();i++){
        answer+=to_string(numbers[i]);
    }
    
    return answer;
}

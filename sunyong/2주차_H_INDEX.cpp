#include <string>
#include <vector>
#include <iostream>

using namespace std;
//논문 n 편 중  <<h번이상 인용된 h편들>>인 h최대값 :H-Index ★★★
//원소:0~10000, array 1~1000
//citations : 인용횟수 배열

void insertionSort(vector<int> &citations)
{
    for(int i=1;i<citations.size();i++)
    {
        int tmp=citations[i];
        for(int j=i-1;j>=0;j--)
        {
            if(citations[j] > tmp)
            {
                citations[j+1]=citations[j];
                if(j==0)
                    citations[j]=tmp;
            }
            else
            {
                citations[j+1]=tmp;
                break;
            }
        }
    }
}
int solution(vector<int> citations) {
    int answer = 0;
    insertionSort(citations);
    int flag=0;
    for(int i=citations.size();i>=0;i--)
    {
        //int h=citations[i];
        int h=i;
        for(int j=citations.size()-1;j>=0;j--)
        {
            if(citations.size()-j<h && h > citations[j])
            {
                break;
            }
            if(citations.size()-j>=h && h <= citations[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            answer=h;
            break;
        }
        
    }
    return answer;
}

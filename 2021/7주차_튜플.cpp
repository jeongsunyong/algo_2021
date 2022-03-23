#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool lensort(vector<int>a, vector<int>b)
{
    return a[1]<b[1];
}
vector<int> solution(string s) {
    vector<int> answer;
    //입력: 원소개수n,중복원소X
    //특정 튜플을 표현하는 집합이 담긴 문자열 s가 매개변수로 주어질 때 s가 표현하는 튜플을 배열에 담아return
    int bracket=0;
    
    vector<vector<int>> nums_vec;
    int element_cnt=0;
    for(int i=1;i<s.size()-1;i++)
    {
        if(s[i]=='{')
            bracket++;
        else if(s[i]=='}' && bracket==1)
        {
            bracket--;
            element_cnt++;
        }
    }
    
    for(int i=0;i<element_cnt;i++)
    {
        vector<int> nums;
        nums_vec.push_back(nums);
    }
    
    int vec_idx=0;
    int num=0;
    for(int i=1;i<s.size()-1;i++)
    {
        if(s[i]=='{')
        {
            bracket=1;
            num=0;
        }
        else if(s[i]==','&& bracket==1)
        {
            nums_vec[vec_idx].push_back(num);
            num=0;
        }
        else if(s[i] !='}' &&bracket==1)
        {
            num=num*10 + int(s[i])-48;
            
        }
        else if(s[i]=='}' && bracket==1)
        {
            nums_vec[vec_idx].push_back(num);
            bracket=0;
        }
        else if(s[i]==',' && bracket==0)
        {
            vec_idx++;
        }
    }
    
    vector<vector<int>> len_info;
    for(int i=0;i<element_cnt;i++)
    {
        vector<int> tmp;
        tmp.push_back(i);//0:idx
        tmp.push_back(nums_vec[i].size());//1:length
        len_info.push_back(tmp);
    }
    sort(len_info.begin(), len_info.end(),lensort);
    
    vector<int> result;
    for(int i=0;i<element_cnt;i++)
    {
        int idx=len_info[i][0];//길이짧은것부터 idx
        for(int j=0;j<len_info[i][1];j++)
        {
            int num = nums_vec[idx][j];
            int flag=1;
            for(int k=0;k<result.size();k++)
            {
                if(num==result[k])
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
            {
                result.push_back(num);
                break;
            }
        }
    }
    answer=result;
    return answer;
}

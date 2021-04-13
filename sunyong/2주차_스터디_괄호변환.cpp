#include <string>
#include <vector>
#include <iostream>

using namespace std;

string correction(string w)
{
    int cnt_r=0;
    int cnt_l=0;
    
    int cut=0;
    if(w.empty())
        return w;
    for(int i=0;i<w.size();i++)
    {
        if(w[i]=='(')
            cnt_l++;
        else if(w[i]==')')
            cnt_r++;
        if(cnt_r!=0 && cnt_r==cnt_l)
        {
            cut = i;
            break;
        }
    }
    
    string u=w.substr(0,cut+1);
    string v=w.substr(cut+1,w.size()-cut);

    char* tmp = new char[1000];
    int top=0;

    for(int i=0;i<u.size();i++)
    {
        if(u[i]=='(')
        {
            tmp[top]=0;
            top++;
        }
        else
        {
            if(top>0)
                top--;
        }
    }
    if(top==0)
    {
        string result_1 = u + correction(v);
        return result_1;
    }
    else
    {
        string result_2="(";
        result_2 = result_2 + correction(v) + ")";
        
        string reversed_u="";
        
        for(int i=1;i<u.size()-1;i++)
        {
            if(u[i]=='(')
            {
                reversed_u.push_back(')');
            }
            else
            {
                reversed_u.push_back('(');
            }
        }
        result_2 = result_2 + reversed_u;
        
        return result_2;
    }
}
string solution(string p) {
    string answer = "";
    answer = correction(p);
    
    return answer;
}

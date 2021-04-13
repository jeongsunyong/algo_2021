#include <string>
#include <vector>
#include <iostream>
using namespace std;

int find(string begin, string target, vector<string>words,int* visited, int cnt)
{
    int N=words.size();
    if(!(begin.compare(target)))// 두 단어가 같을 때
    {
        return cnt;
    }
    
    int mcnt=9999;//아무숫자큰값
    
    for(int i=0;i<words.size();i++)//단어들검사
    {
        if(visited[i]==1) 
            continue;
        int diff=0;
        for(int j=0;j<begin.size();j++)
        {
            if(begin[j]!=words[i][j])
                diff++;
        }
        if(diff != 1)
            continue;
           
        //1개만 다를경우(변환 1글자)
        int* visited_next=new int[N];
        for(int i=0;i<N;i++)//복사
        {
            visited_next[i]=visited[i];
        }
        string begin_conv=words[i];
        visited_next[i]=1;
        int cnt_tmp =find(begin_conv,target,words,visited_next,cnt+1);
        mcnt=(mcnt<cnt_tmp)? mcnt:cnt_tmp;
    }
    return mcnt;
    
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    int N=words.size();
    int* visited = new int[N];
    for(int i=0;i<N;i++)
    {
        visited[i]=0;
    }
    
    int cnt = find(begin,target,words,visited,0);
    answer=(cnt==9999)?0:cnt;
    return answer;
}

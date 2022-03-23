#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void swap(int& a,int& b)
{
    int tmp=a;
    a=b;
    b=tmp;
}
bool vec_sort(vector<int>a, vector<int>b)
{
    if(a[0]==b[0])
        return a[1]<b[1];
    return a[0]<b[0];
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    //전처리 (정렬)
    int initial_edge_size=edge.size();
    for(int i=0;i<initial_edge_size;i++)
    {
        vector<int> v={edge[i][1],edge[i][0]};
        edge.push_back(v);
    }
    sort(edge.begin(), edge.end(),vec_sort);
    
    //전처리 (시작노드별 인덱스)
    int* searched = new int[n+1];
    int* idx_start = new int[n+1];
    int* idx_end = new int[n+1];
    for(int i=0;i<=n;i++)
    {
        searched[i]=-1;
        idx_start[i]=0;
        idx_end[i]=-1;
    }
    
    int pre=edge[0][0];
    idx_start[pre]=0;
    for(int i=0;i<edge.size();i++)
    {
        int cur=edge[i][0];
        if(cur!=pre)
        {
            idx_end[pre]=i-1;//노드 끝인덱스 저장
            idx_start[cur]=i;//노드 시작인덱스 저장
        }
        pre=cur;
    }
    idx_end[pre]=edge.size()-1;
    

    int node=1;
    queue<int> Q;
    Q.push(1);
    searched[1]=0;
    while(Q.size()>0)
    {
        node=Q.front();
        Q.pop();
        for(int i=idx_start[node];i<=idx_end[node];i++)
        {
            if(searched[edge[i][1]]==-1)//방문x
            {
                Q.push(edge[i][1]);
                searched[edge[i][1]]=searched[edge[i][0]]+1;
            }
        }
    }
    int maximum=0;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(searched[i]>maximum)
        {
            maximum=searched[i];
            cnt=1;
        }
        else if(searched[i]==maximum)
            cnt++;
    }
    answer = cnt;
    return answer;
}

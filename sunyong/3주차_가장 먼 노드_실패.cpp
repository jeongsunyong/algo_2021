#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    //가장 멀리 떨어진 노드 : 최단경로 , 간선개수가 가장 많은 노드
    // n>=2 && n<=20000
    // E>=1 E<=50000
    
    
    ////
    //ex
    //각 n개의 노드-> 1과 연겨 ㄹ확인
    // 1노드 연결된 값 갱신 cur
    // 갱신 값 while()
    // if searched == 0 -> 값 넣어줌
    //
    
    
    // searched != 0 -> 더이상 값 갱신 필요 X, 
    //
    ////
    int* searched = new int[n+1];
    for(int i=0;i<n;i++)
    {
        searched[i]=0;
    }
    searched[1]=-1;
    
    //
    int cur=1;
    int edge_cnt=0;
    int pre_cur=-1;
    int flag=1;
    
    vector<int> conn;
    vector<int> conn2;
    conn.push_back(1);
    conn2.push_back(0);
    //

    while(conn.size()>0)
    {
        pre_cur=conn2[conn2.size()-1];
        cur = conn[0];
        if(pre_cur != cur)
            edge_cnt++;
        conn.pop_back();
            
        
        for(int i=0;i<edge.size();i++)
        {
            int a=edge[i][0];
            int b=edge[i][1];
            int idx=0;
            if(a==cur || b==cur)
            {
                idx = (a==cur)?b:a;//current와 연결된 node
                if(searched[idx]==0)
                {
                    searched[idx]=edge_cnt;
                    conn.insert(conn.begin(),idx);
                    conn2.insert(conn2.begin(),cur);
                    //cout<<a <<" , "<<b<<endl;
                }

            }
        }
    }
    int max_cnt=0;
    for(int i=0;i<n;i++)
    {
        if(searched[i]==edge_cnt)
            max_cnt++;
    }
    
    answer=max_cnt;
    return answer;
}

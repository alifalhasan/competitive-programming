#include<bits/stdc++.h>

using namespace std;

struct edge
{
    int to,cap,flow;
};

const int N=1e5;

vector<edge>Graph[N+5];
int iter[N+5],level[N+5];

void AddEdge(int from,int to,int cap)
{
    Graph[from].emplace_back((edge){to,cap,(int)Graph[to].size()});
    Graph[to].emplace_back((edge){from,0,(int)Graph[from].size()-1});
}

void BFS(int node)
{
    memset(level,-1,sizeof(level));
    queue<int>q;
    level[node]=0;
    q.emplace(node);
    int i,l;
    while(!q.empty())
    {
        node=q.front();
        q.pop();
        l=(int)Graph[node].size();
        for(i=0;i<l;i++)
        {
            edge &e=Graph[node][i];
            if(e.cap > 0  &&  level[e.to] < 0)
            {
                q.emplace(e.to);
                level[e.to]=level[node]+1;
            }
        }
    }
}

int DFS(int v,int t,int f)
{
    if(v == t)return f;
    int l=(int)Graph[v].size(),check;
    for(int &i=iter[v];i<l;i++)
    {
        edge &e=Graph[v][i];
        if(e.cap > 0  &&  level[v] < level[e.to])
        {
            check=DFS(e.to,t,min(f,e.cap));
            if(check > 0)
            {
                e.cap-=check;
                Graph[e.to][e.flow].cap+=check;
                return check;
            }
        }
    }
    return 0;
}

int FindDinicMaxFlow(int s,int t)
{
    int flow=0,check;
    while(true)
    {
        BFS(s);
        if(level[t] < 0)return flow;
        memset(iter,0,sizeof(iter));
        while((check=DFS(s,t,INT_MAX)) > 0)flow+=check;
    }
}

int main()
{
    return 0;
}

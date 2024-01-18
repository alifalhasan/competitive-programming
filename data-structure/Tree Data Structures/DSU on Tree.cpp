/*
    Given a tree, every vertex has color. Query is how many vertices in subtree of vertex v are colored with color c?
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

vector<int>adj[N+2];
bool bigChildMark[N+2];
vector<pair<int,int>>queries[N+2];
int ans[N+2],color[N+2],colorCnt[N+2],size[N+2];

void DFS(int cur,int par)
{
    size[cur]=1;
    for(int x : adj[cur])
    {
        if(x ^ par)
        {
            DFS(x,cur);
            size[cur]+=size[x];
        }
    }
}

void Add(int cur,int par,int val)
{
    colorCnt[color[cur]]+=val;
    for(int x : adj[cur])
    {
        if((x ^ par)  &&  !bigChildMark[x])Add(x,cur,val);
    }
}

void DFS(int cur,int par,bool keep)
{
    int bigChild=0,mx=0;
    for(int x : adj[cur])
    {
        if((x ^ par)  &&  size[x] > mx)
        {
            mx=size[x];
            bigChild=x;
        }
    }
    for(int x : adj[cur])
    {
        if((x ^ par)  &&  (x ^ bigChild))DFS(x,cur,0);//clearing small childs from cnt
    }
    if(bigChild)DFS(bigChild,cur,1),bigChildMark[bigChild]=1;
    Add(cur,par,1);
    //now cnt[c] is the number of vertices in subtree of vertex cur that has color c.
    for(auto it : queries[cur])ans[it.second]=colorCnt[it.first];
    if(bigChild)bigChildMark[bigChild]=0;
    if(!keep)Add(cur,par,-1);
}

void DSUonTree()
{
    DFS(1,0);
    DFS(1,0,0);
}

int main()
{
    int i,n,q,x,y;
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&color[i]);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&x,&y);
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    scanf("%d",&q);
    for(i=1;i<=q;i++)
    {
        scanf("%d %d",&x,&y);
        queries[x].emplace_back(y,i);
    }
    DSUonTree();
    for(i=1;i<=n;i++)printf("%d\n",ans[i]);
    return 0;
}

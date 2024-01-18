#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

vector<int>adj[N];
int l,timer,inTime[N],outTime[N],up[N][20];

void DFS(int cur,int par)
{
    inTime[cur]=++timer;
    up[cur][0]=par;
    for(int i=1;i<=l;i++)up[cur][i]=up[up[cur][i-1]][i-1];
    for(int x : adj[cur])
    {
        if(x ^ par)DFS(x,cur);
    }
    outTime[cur]=++timer;
}

bool IsAncestor(int x,int y)
{
    return inTime[x] <= inTime[y]  &&  outTime[x] >= outTime[y];
}

int LCA(int x,int y)
{
    if(IsAncestor(x,y))return x;
    if(IsAncestor(y,x))return y;
    for(int i=l;i>=0;i--)
    {
        if(!IsAncestor(up[x][i],y))x=up[x][i];
    }
    return up[x][0];
}

void PreProcess(const int& numberOfNodes,int root)
{
    l=ceil(log2(numberOfNodes)), timer=0;
    DFS(root,root);
}

int main()
{
    return 0;
}

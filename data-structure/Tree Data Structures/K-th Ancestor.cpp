#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

vector<int>adj[N];
int n,LG,dist[N],dp[N][20];

void DFS(int cur,int par)
{
    dist[cur]=dist[par]+1;
    dp[cur][0]=par;
    for(int i=1;i<=LG;i++)dp[cur][i]=dp[dp[cur][i-1]][i-1];
    for(int x : adj[cur])
    {
        if(x ^ par)DFS(x,cur);
    }
}

void PreCal()
{
    LG=ceil(log2(n));
    dist[1]=-1;
    DFS(1,1);
}

int FindKth(int node,int k)
{
    for(int i=LG;i>=0;i--)
    {
        if((1 << i) <= k)
        {
            k-=(1 << i);
            node=dp[node][i];
        }
    }
    return node;
}

int main()
{
    return 0;
}

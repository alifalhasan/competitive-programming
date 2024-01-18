/*
    Check if a graph is bipartite or not.
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

int color[N+2];
bool bipartite;
vector<int>adj[N+2];

void DFS(int x)
{
    if(!bipartite)return;
    for(int y : adj[x])
    {
        if(!bipartite)return;
        if(color[y] == 2)color[y]=1-color[x],DFS(y);
        else if(color[x] == color[y])
        {
            bipartite=false;
            return;
        }
    }
}

int main()
{
    int i,m,n,x,y;
    cin >> n >> m;
    for(i=1;i<=n;i++)color[i]=2;
    while(m--)
    {
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    bipartite=1;
    for(i=1;i<=n  &&  bipartite;i++)
    {
        if(color[i] == 2)color[i]=0,DFS(i);
    }
    if(!bipartite)cout << "IMPOSSIBLE";
    else
    {
        cout << color[1]+1;
        for(i=2;i<=n;i++)cout << ' ' << color[i]+1;
    }
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

const int N=1e4;

int timeCnt;
bool visited[N+3];
vector<int>adj[N+3];
set<pair<int,int> >bridges;
int lowTimedAdjacentNode[N+3],parent[N+3],visitedTime[N+3];

void FindBridges(int node)
{
    if(visitedTime[node] != -1)return;
    visited[node]=true;
    visitedTime[node]=lowTimedAdjacentNode[node]=++timeCnt;
    int i,adjNode;
    for(i=0; i<(int)adj[node].size(); i++)
    {
        adjNode=adj[node][i];
        if(visitedTime[adjNode] == -1)
        {
            parent[adjNode]=node;
            FindBridges(adjNode);
            lowTimedAdjacentNode[node]=min(lowTimedAdjacentNode[node],lowTimedAdjacentNode[adjNode]);
            if(lowTimedAdjacentNode[adjNode] > visitedTime[node])bridges.insert({min(node,adjNode),max(node,adjNode)});
        }
        else if(adjNode != parent[node])lowTimedAdjacentNode[node]=min(lowTimedAdjacentNode[node],visitedTime[adjNode]);
    }
}

int main()
{
    int i,n,m,t,tc,x,y;
    pair<int,int>temp;
    scanf("%d",&t);
    for(tc=1; tc<=t; tc++)
    {
        scanf("%d",&n);
        for(i=1; i<=n; i++)
        {
            adj[i].clear();
            visited[i]=false;
            parent[i]=visitedTime[i]=lowTimedAdjacentNode[i]=-1;
        }
        while(m--)
        {
            scanf("%d %d",&x,&y);
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        timeCnt=0;
        bridges.clear();
        for(i=1; i<=n; i++)
        {
            if(!visited[i])FindBridges(i);
        }
        printf("Case %d:\n",tc);
        printf("%d critical links\n",bridges.size());
        for(auto it=bridges.begin(); it!=bridges.end(); it++)
        {
            temp=*it;
            printf("%d - %d\n",temp.first,temp.second);
        }
    }
    return 0;
}

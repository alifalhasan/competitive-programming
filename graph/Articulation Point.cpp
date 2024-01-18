#include<bits/stdc++.h>

using namespace std;

const int N=1e4;

int timeCnt;
vector<int>adj[N+3];
set<int>cutVertices;
int lowTimedAdjacentNode[N+3],parent[N+3],visitedTime[N+3];

void FindArticulationPoints(int node)
{
    if(visitedTime[node] != -1)return;
    visitedTime[node]=lowTimedAdjacentNode[node]=++timeCnt;
    int i,child=0,adjNode;
    for(i=0; i<(int)adj[node].size(); i++)
    {
        adjNode=adj[node][i];
        if(visitedTime[adjNode] == -1)
        {
            child++;
            parent[adjNode]=node;
            FindArticulationPoints(adjNode);
            lowTimedAdjacentNode[node]=min(lowTimedAdjacentNode[node],lowTimedAdjacentNode[adjNode]);
            if(parent[node] == -1  &&  child > 1)cutVertices.insert(node);
            else if(parent[node] != -1  &&  lowTimedAdjacentNode[adjNode] >= visitedTime[node])cutVertices.insert(node);
        }
        else if(adjNode != parent[node])lowTimedAdjacentNode[node]=min(lowTimedAdjacentNode[node],visitedTime[adjNode]);
    }
}

int main()
{
    int i,n,m,t,tc,x,y;
    scanf("%d",&t);
    for(tc=1; tc<=t; tc++)
    {
        scanf("%d %d",&n,&m);
        for(i=1; i<=n; i++)
        {
            adj[i].clear();
            parent[i]=visitedTime[i]=lowTimedAdjacentNode[i]=-1;
        }
        while(m--)
        {
            scanf("%d %d",&x,&y);
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        timeCnt=0;
        cutVertices.clear();
        FindArticulationPoints(1);
        printf("Case %d: %d\n",tc,cutVertices.size());
    }
    return 0;
}

/*
    This program will find the number of pairs whose distance is exactly a given value.
*/

#include<bits/stdc++.h>

using namespace std;

const int N=5e5;

bool alreadyComposed[N+2];
int parent[N+2],subTreeSize[N+2];
vector<int>adj[N+2],decomposedTree[N+2];

void DFS(int cur)
{
    for(int x : adj[cur])
    {
        if(x ^ parent[cur])
        {
            parent[x]=cur;
            DFS(x);
            subTreeSize[cur]+=1+subTreeSize[x];
        }
    }
}

/****************************************************************/

long long ans,dist,temp,cnt[N+2];

void DFS2(int cur,int par,int val,bool flag)
{
    if(flag)++cnt[val];
    else --cnt[val];
    for(int x : adj[cur])
    {
        if(!alreadyComposed[x]  &&  (x ^ par))DFS2(x,cur,val+1,flag);
    }
}

void Solve(int cur,int par,int val)
{
    if(val > dist)return;
    temp+=cnt[dist-val];
    for(int x : adj[cur])
    {
        if(!alreadyComposed[x]  &&  (x ^ par))Solve(x,cur,val+1);
    }
}

void FindAns(int cur,int par)
{
    temp=0;
    DFS2(cur,par,0,1);
    temp+=cnt[dist];
    for(int x : adj[cur])
    {
        if(!alreadyComposed[x])
        {
            DFS2(x,cur,1,0);
            Solve(x,cur,1);
            DFS2(x,cur,1,1);
        }
    }
    ans+=temp/2;
    DFS2(cur,par,0,0);
}

/*********************************************************/

int Decompose(int cur,int size,int par)
{
    int nextNode,val;
    while(true)
    {
        nextNode=0;
        for(int x : adj[cur])
        {
            if(alreadyComposed[x]  ||  x == parent[cur])continue;
            if(subTreeSize[x] >= size/2)nextNode=x;
        }
        if(size-1-subTreeSize[cur] > size/2  &&  parent[cur]  &&  !alreadyComposed[parent[cur]])nextNode=parent[cur];
        if(nextNode)cur=nextNode;
        else break;
    }
    for(int x=parent[cur];x  &&  !alreadyComposed[x];x=parent[x])subTreeSize[x]-=1+subTreeSize[cur];
    FindAns(cur,par);
    alreadyComposed[cur]=1;
    for(int x : adj[cur])
    {
        if(alreadyComposed[x])continue;
        val=1+subTreeSize[x];
        if(x == parent[cur])val=size-1-subTreeSize[cur];
        decomposedTree[cur].emplace_back(Decompose(x,val,cur));
    }
    return cur;
}

void CentroidDecomposition(int numberOfNodes)
{
    DFS(1);
    int root=Decompose(1,numberOfNodes,0);
}

int main()
{
    int i,n,x,y;
    cin >> n >> dist;
    for(i=1;i<n;i++)
    {
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    CentroidDecomposition(n);
    cout << ans;
    return 0;
}

//https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/

#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

vector<int>adj[N],revAdj[N],domTree[N],bucket[N];
int _time,arr[N],rev[N],sdom[N],par[N],dom[N],dsu[N],label[N];

void Init(const int& n)
{
    _time=0;
    for(int i=1;i<=n;i++)
    {
        adj[i].clear();
        revAdj[i].clear();
        bucket[i].clear();
        domTree[i].clear();
        arr[i]=par[i]=rev[i]=0;
        sdom[i]=dom[i]=dsu[i]=label[i]=i;
    }
}

int Find(int u,int x=0)
{
	if(u == dsu[u])return (x ? -1 : u);
	int v = Find(dsu[u],x+1);
	if(v < 0)return u;
	if(sdom[label[dsu[u]]] < sdom[label[u]])label[u] = label[dsu[u]];
	dsu[u] = v;
	return (x ? v : label[u]);
}

void DFS0(int x)
{
    arr[x]=++_time,rev[_time]=x;
    for(int y : adj[x])
    {
        if(!arr[y])DFS0(y),par[arr[y]]=arr[x];
        revAdj[arr[y]].emplace_back(arr[x]);
    }
}

void BuildDomTree()
{
    int i,y,z;
    DFS0(1);//_time equals number of vertices reachable from root
    for(i=_time;i;i--)
    {
        for(int x : revAdj[i])sdom[i] = min(sdom[i],sdom[Find(x)]);
        if(i > 1)bucket[sdom[i]].emplace_back(i);
        for(int x : bucket[i])
        {
            y=x,z=Find(x);
            if(sdom[y] == sdom[z])dom[y]=sdom[y];
            else dom[y]=z;
        }
        if(i > 1)dsu[i]=par[i];
    }
    for(i=2;i<=_time;i++)
    {
        if(dom[i] != sdom[i])dom[i]=dom[dom[i]];
        domTree[rev[i]].emplace_back(rev[dom[i]]);
        domTree[rev[dom[i]]].emplace_back(rev[i]);
    }
}

int main()
{
    return 0;
}

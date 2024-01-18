/*
    0-based indexing
*/
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+2; ///Should be double double

vector<int>adj[N];

int getNode(int x)   ///Convert a choice to node
{
    int p=abs(x);
    p=(p-1)*2;
    if(x<0)p^=1;
    return p;
}

int getNodeVal(int x)   ///Convert a node to choice
{
    int p=1;
    if(x&1)
    {
        p=-1;
        x-=1;
    }
    x/=2;
    x++;
    p*=x;
    return p;
}


///Always pass getNode() value to the folloing function
///For example if we want to mustTrue 5 then the call will be mustTrue(getNode(5))

void mustTrue(int a)   /// A is True
{
    adj[a^1].emplace_back(a);
}

void xorClause(int a, int b)   /// A ^ B clause
{
    //!a->b !b->a a->!b b->!a
    adj[a^1].emplace_back(b);
    adj[a].emplace_back(b^1);
    adj[b^1].emplace_back(a);
    adj[b].emplace_back(a^1);
}

void orClause(int a, int b)   /// A || B clause
{
    //!a->b !b->a
    adj[a^1].emplace_back ( b );
    adj[b^1].emplace_back ( a );
}

void andClause(int a, int b)   /// A && B clause
{
    mustTrue(a);
    mustTrue(b);
}

/// Out of all possible option, at most one is true
void atMostOneClause(int a[], int n, bool flag)
{
    int i,j;
    if(!flag)   /// At most one can be false
    {
        for(i=0; i<n; i++)a[i] = a[i] ^ 1;
    }
    for(i = 0; i<n; i++)
    {
        for(j = i+1; j<n; j++)
        {
            orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
        }
    }
}

///SCC variables
stack<int>scc;
int component[N],disc[N],low[N],Time, scc_count;

///2-SAT variables
deque<int>sat;
int isSAT[N];

void allClear(int n)
{
    n <<= 1;
    for(int i=0; i < n; i++)
    {
        isSAT[i]=-1;
        adj[i].clear();
        low[i]=disc[i]=component[i]=0;
    }
    Time=0;
    scc_count=0;
    while(!scc.empty())scc.pop();
    sat.clear();
}

void tarjan_SCC(int u)
{
    disc[u]=low[u]=++Time;
    scc.emplace(u);
    for(int i=0; i<adj[u].size(); i++)
    {
        int v=adj[u][i];
        if(disc[v]==0)tarjan_SCC(v);
        if(disc[v]!=-1)low[u]=min(low[u],low[v]);
    }
    if(low[u] == disc[u])
    {
        scc_count++;
        int v;
        do
        {
            v=scc.top();
            scc.pop();
            sat.emplace_back(v);
            component[v]=scc_count;
            disc[v]=-1;
        }
        while(v != u);
    }
}

bool checkSAT(int const& n)
{
    int i,x;
    for(i=1;i<=n;i++)
    {
        x=getNode(i);
        if(!disc[x])tarjan_SCC(x);
        x=getNode(-i);
        if(!disc[x])tarjan_SCC(x);
    }
    while(!sat.empty())   ///Assigning valid values to candidates
    {
        int x=sat.front();
        sat.pop_front();
        if(isSAT[x]==-1)
        {
            isSAT[x]=1;
            x=getNode(-getNodeVal(x)); ///Getting opposite value
            isSAT[x]=0;
        }
    }

    ///Checking whether satisfiability is possible or not
    bool check=1;
    for(i=1; i<=n && check; i++)
    {
        check=(component[getNode(i)] != component[getNode(-i)]);
    }
    return check;
}

int main()
{
    return 0;
}

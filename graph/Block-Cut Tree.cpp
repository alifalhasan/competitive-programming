/*
    Check if AP is empty then the whole graph is biconnected.
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

/********************Biconnected Components********************/

set<int>AP;
stack<int>stk;
vector<int>adj[N];
vector<vector<int>>BCC;
bool visited[N],isAP[N];
int dfsTime,low[N],visitedTime[N];

void FindBCC(int cur,int par)
{
    int temp;
    visited[cur]=1;
    stk.emplace(cur);
    low[cur]=visitedTime[cur]=++dfsTime;
    for(int nxt : adj[cur])
    {
        if(nxt ^ par)
        {
            if(!visited[nxt])
            {
                FindBCC(nxt,cur);
                low[cur]=min(low[cur],low[nxt]);
                if(low[nxt] >= visitedTime[cur])
                {
                    isAP[cur]=(visitedTime[cur] > 1  ||  visitedTime[nxt] > 2);
                    if(isAP[cur])AP.insert(cur);
                    BCC.emplace_back();
                    while(true)
                    {
                        temp=stk.top();
                        stk.pop();
                        BCC.back().emplace_back(temp);
                        if(temp == nxt)break;
                    }
                    BCC.back().emplace_back(cur);
                }
            }
            else low[cur]=min(low[cur],visitedTime[nxt]);
        }
    }
    if(cur == par  &&  adj[cur].empty())
    {
        BCC.emplace_back();
        BCC.back().emplace_back(cur);
    }
}

void BiconnectedComponents(int const& n)
{
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])FindBCC(i,i);
    }
}

/********************Biconnected Components********************/


/********************Block-Cut Tree Construction********************/

vector<int>tree[N<<1];
int nodeCnt,nodeMark[N],elementCnt[N<<1];

void BuildBlockCutTree()
{
    int i,l=BCC.size();
    for(i=1;i<=nodeCnt;i++)
    {
        elementCnt[i]=0;
        tree[i].clear();
    }
    nodeCnt=0;
    for(int x : AP)
    {
        nodeMark[x]=++nodeCnt;
        elementCnt[nodeCnt]=1;
    }
    for(i=0;i<l;i++)
    {
        elementCnt[++nodeCnt]=BCC[i].size();
        for(int x : BCC[i])
        {
            if(!isAP[x])nodeMark[x]=nodeCnt;
            else
            {
                tree[nodeCnt].emplace_back(nodeMark[x]);
                tree[nodeMark[x]].emplace_back(nodeCnt);
            }
        }
    }
}

/********************Block-Cut Tree Construction********************/

void Clear(int const& n)
{
    dfsTime=0;
    AP.clear();
    BCC.clear();
    for(int i=1;i<=n;i++)
    {
        adj[i].clear();
        isAP[i]=visited[i]=0;
    }
    while(!stk.empty())stk.pop();
}

int main()
{
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

bool visited[N];
vector<int>adj[N];
stack<pair<int,int>>st;
int Time,low[N],visitedTime[N];
vector<vector<pair<int,int>>>BCC;

void Clear(int const& n)
{
    Time=0;
    while(!st.empty())st.pop();
    for(int i=1;i<=n;i++)
    {
        adj[i].clear();
        low[i]=visited[i]=visitedTime[i]=0;
    }
}

void Tarjan(int cur,int par)
{
    visited[cur]=1;
    low[cur]=visitedTime[cur]=++Time;
    for(int x : adj[cur])
    {
        if(x ^ par)
        {
            if(!visited[x])
            {
                st.emplace(cur,x);
                Tarjan(x,cur);
                if(low[x] >= visitedTime[cur])//Found a new BCC
                {
                    BCC.emplace_back({});
                    pair<int,int>temp,targetEdge={cur,x};
                    do
                    {
                        temp=st.top();
                        st.pop();
                        BCC.back().emplace_back(temp);
                    }
                    while(temp != targetEdge);
                }
                low[cur]=min(low[cur],low[x]);
            }
            else if(visitedTime[x] < visitedTime[cur])
            {
                st.emplace(cur,x);
                low[cur]=min(low[cur],visitedTime[x]);
            }
        }
    }
}

void FindBCC(int const& n)
{
    for(int i=1;i<=n;i++)
    {
        if(!visitedTime[i])Tarjan(i,0);
    }
}

int main()
{
    return 0;
}

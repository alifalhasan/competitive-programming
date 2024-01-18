#include<bits/stdc++.h>

using namespace std;

const int N=2005;

vector<bool>used;
vector<int>order,component,graph[N],reverseGraph[N];

void runDFS1(int x)
{
    used[x]=true;
    for(int y : graph[x])
    {
        if(!used[y])runDFS1(y);
    }
    order.emplace_back(x);
}

void runDFS2(int x)
{
    used[x]=true;
    component.emplace_back(x);
    for(int y : reverseGraph[x])
    {
        if(!used[y])runDFS2(y);
    }
}

int main()
{
    int i,m,n,x,y;
    cin >> n >> m;
    while(m--)
    {
        cin >> x >> y;
        graph[x].emplace_back(y);
        reverseGraph[y].emplace_back(x);
    }
    used.assign(n+1,false);
    for(i=1;i<=n;i++)
    {
        if(!used[i])runDFS1(i);
    }
    used.assign(n+1,false);
    for(i=1;i<=n;i++)
    {
        x=order[n-i];
        if(!used[x])
        {
            runDFS2(x);
            component.clear();//stores the current strongly connected component
        }
    }
    return 0;
}



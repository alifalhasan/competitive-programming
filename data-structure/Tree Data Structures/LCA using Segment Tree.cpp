#include<bits/stdc++.h>

using namespace std;

const int N=1e3+2;

bool visited[N];
vector<int>euler,adj[N];
int first[N],height[N],tree[4*N];

void DFS(int node,int h)
{
    height[node]=h;
    visited[node]=1;
    first[node]=(int)euler.size();
    euler.emplace_back(node);
    int i,x,l=(int)adj[node].size();
    for(i=0;i<l;i++)
    {
        x=adj[node][i];
        if(!visited[x])
        {
            DFS(x,h+1);
            euler.emplace_back(node);
        }
    }
}

void Build(int node,int l,int r)
{
    if(l == r)
    {
        tree[node]=euler[l];
        return;
    }
    int mid=(l+r) >> 1,check=(node << 1),x,y;
    Build(check,l,mid);
    Build(check+1,mid+1,r);
    x=tree[check],y=tree[check+1];
    if(height[x] < height[y])tree[node]=x;
    else tree[node]=y;
}

int Query(int node,int b,int e,int l,int r)
{
    if(b > r  ||  e < l)return -1;
    if(b >= l  &&  e <= r)return tree[node];
    int mid=(b+e) >> 1,check=(node << 1);
    int left=Query(check,b,mid,l,r);
    int right=Query(check+1,mid+1,e,l,r);
    if(left == -1)return right;
    if(right == -1)return left;
    if(height[left] < height[right])return left;
    return right;
}

int FindLCA(int u,int v)
{
    int l=first[u],r=first[v];
    if(l > r)
    {
        l=l^r;
        r=l^r;
        l=l^r;
    }
    return Query(1,0,euler.size()-1,l,r);
}

int main()
{
    int i,m,n,t,q,x,y,tc;
    cin >> t;
    for(tc=1;tc<=t;tc++)
    {
        cin >> n;
        euler.clear();
        for(i=1;i<=n;i++)
        {
            cin >> m;
            adj[i].clear(),visited[i]=false;
            while(m--)
            {
                cin >> x;
                adj[i].push_back(x);
            }
        }
        DFS(1,0);
        Build(1,0,euler.size()-1);
        cout << "Case " << tc << ":" << '\n';
        cin >> q;
        while(q--)
        {
            cin >> x >> y;
            cout << FindLCA(x,y) << '\n';
        }
    }
    return 0;
}

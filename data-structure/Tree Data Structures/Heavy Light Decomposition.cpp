/*
    Update : Add a value to a node.
    Query : sum of all values(nodes) on the path of (a,b).
*/
#include<bits/stdc++.h>

using namespace std;

const int N=5e5;

/********************Segment Tree********************/

int n,val[N+2];
long long node[4*N+8];

void Build(int nodeNum,int l,int r)
{
    if(l == r)
    {
        node[nodeNum]=val[l];
        return;
    }

    int mid=(l+r) >> 1;
    Build(2*nodeNum,l,mid);
    Build(2*nodeNum+1,mid+1,r);
    node[nodeNum]=node[2*nodeNum]+node[2*nodeNum+1];
}

void Update(int nodeNum,int start,int end,int pos,int x)
{
    if(start == end)
    {
        node[nodeNum]+=x;
        return;
    }
    int mid=(start+end) >> 1;
    if(pos <= mid)Update(2*nodeNum,start,mid,pos,x);
    else Update(2*nodeNum+1,mid+1,end,pos,x);
    node[nodeNum]=node[2*nodeNum]+node[2*nodeNum+1];
}

long long SegmentTreeQuery(int nodeNum,int start,int end,int l,int r)
{
    if(l == start  &&  r == end)return node[nodeNum];
    int mid=(start+end) >> 1;
    if(r <= mid)return SegmentTreeQuery(nodeNum*2,start,mid,l,r);
    if(mid < l)return SegmentTreeQuery(nodeNum*2+1,mid+1,end,l,r);
    return SegmentTreeQuery(nodeNum*2,start,mid,l,mid)+SegmentTreeQuery(nodeNum*2+1,mid+1,end,mid+1,r);
}

/********************Segment Tree********************/

/********************Heavy Light Decomposition********************/

vector<int>adj[N+2];
int curPos,depth[N+2],headofCurrentChain[N+2],heavyChild[N+2],parent[N+2],pos[N+2];

int DFS(int cur)
{
    int childSize,size=1,maxChildSize=0;
    for(int x : adj[cur])
    {
        if(x ^ parent[cur])
        {
            parent[x]=cur;
            depth[x]=depth[cur]+1;
            childSize=DFS(x);
            size+=childSize;
            if(childSize > maxChildSize)
            {
                heavyChild[cur]=x;
                maxChildSize=childSize;
            }
        }
    }
    return size;
}

void Decompose(int cur,int headNode)
{
    pos[cur]=++curPos;
    headofCurrentChain[cur]=headNode;
    if(heavyChild[cur])Decompose(heavyChild[cur],headNode);
    for(int x : adj[cur])
    {
        if(x != parent[cur]  &&  x != heavyChild[cur])Decompose(x,x);
    }
}

void HeavyLightDecomposition()
{
    DFS(1);
    curPos=0;
    Decompose(1,1);
}

long long HLDQuery(int x,int y)
{
    long long ans=0,curVal;
    while(headofCurrentChain[x] != headofCurrentChain[y])
    {
        if(depth[headofCurrentChain[x]] > depth[headofCurrentChain[y]])swap(x,y);
        curVal=SegmentTreeQuery(1,1,n,pos[headofCurrentChain[y]],pos[y]);
        ans+=curVal;
        y=parent[headofCurrentChain[y]];
    }
    if(depth[x] > depth[y])swap(x,y);//x-lca of given (x,y)
    curVal=SegmentTreeQuery(1,1,n,pos[x],pos[y]);
    return ans+curVal;
}

/********************Heavy Light Decomposition********************/

int a[N+2];

int main()
{
    int i,q,x,y,z;
    scanf("%d %d",&n,&q);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&x,&y);
        ++x,++y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    HeavyLightDecomposition();
    for(i=1;i<=n;i++)val[pos[i]]=a[i];
    Build(1,1,n);
    while(q--)
    {
        scanf("%d %d %d",&z,&x,&y);
        if(!z)
        {
            ++x;
            Update(1,1,n,pos[x],y);
        }
        else
        {
            ++x,++y;
            printf("%lld\n",HLDQuery(x,y));
        }
    }
    return 0;
}

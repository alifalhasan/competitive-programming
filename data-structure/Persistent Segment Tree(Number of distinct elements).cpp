#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

struct Node
{
    int cnt,l,r;
    Node()
    {
        cnt=0, l=r=-1;
    }
    Node(int x,int y,int z)
    {
        l=x, r=y, cnt=z;
    }
}node[20*N];

int nodeCnt,a[N],lastOccur[N],root[N];

int Build(int l,int r)
{
    ++nodeCnt;
    if(l == r)return nodeCnt;
    int cur=nodeCnt, mid=(l+r) >> 1;
    node[cur]=Node(Build(l,mid), Build(mid+1,r), 0);
    return cur;
}

int Update(int nodeNum,int start,int end,int idx,int val)
{
    ++nodeCnt;
    if(start == end)
    {
        node[nodeCnt]=Node(-1,-1,node[nodeNum].cnt+val);
        return nodeCnt;
    }
    int cur=nodeCnt, mid=(start+end) >> 1;
    if(idx <= mid)node[cur]=Node(Update(node[nodeNum].l,start,mid,idx,val), node[nodeNum].r, node[nodeNum].cnt+val);
    else node[cur]=Node(node[nodeNum].l, Update(node[nodeNum].r,mid+1,end,idx,val), node[nodeNum].cnt+val);
    return cur;
}

int Query(int nodeNum,int start,int end,int l,int r)
{
    if(r < start  ||  l > end)return 0;
    if(l <= start  &&  end <= r)return node[nodeNum].cnt;
    int mid=(start+end) >> 1;
    return Query(node[nodeNum].l,start,mid,l,r) + Query(node[nodeNum].r,mid+1,end,l,r);
}

int main()
{
    return 0;
}

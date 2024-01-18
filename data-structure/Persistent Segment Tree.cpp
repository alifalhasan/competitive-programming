/*
    This program will return the sum of a range with point update.
*/
#include<bits/stdc++.h>

using namespace std;

const int sz=100005;
int a[sz],lChild[40*sz],rChild[40*sz],value[40*sz],numOfNodes;

int NewLeaf(int val)
{
    int cur=++numOfNodes;
    value[cur]=val;
    lChild[cur]=rChild[cur]=0;
    return cur;
}

int NewParent(int lc,int rc)
{
    int cur=++numOfNodes;
    lChild[cur]=lc;
    rChild[cur]=rc;
    value[cur]=value[lc]+value[rc];
    return cur;
}

int Build(int l,int r)
{
    if(l == r)return NewLeaf(a[l]);
    int mid=(l+r) >> 1;
    return NewParent(Build(l,mid),Build(mid+1,r));
}

int Update(int idx,int val,int oldRoot,int l,int r)
{
    if(l == r)return NewLeaf(value[oldRoot]+val);
    int mid=(l+r) >> 1;
    if(idx <= mid)return NewParent(Update(idx,val,lChild[oldRoot],l,mid),rChild[oldRoot]);
    return NewParent(lChild[oldRoot],Update(idx,val,rChild[oldRoot],mid+1,r));
}

int Query(int idx,int curL,int curR,int l,int r)
{
    if(r < curL  ||  l > curR)return 0;
    if(curL >= l  &&  curR <= r)return value[idx];
    int mid=(curL+curR) >> 1;
    if(r <= mid)return Query(lChild[idx],curL,mid,l,r);
    else if(l > mid)return Query(rChild[idx],mid+1,curR,l,r);
    return Query(lChild[idx],curL,mid,l,mid)+Query(rChild[idx],mid+1,curR,mid+1,r);
}

int main()
{
    vector<int>roots;
    int i,l,n,q,r,op,root,ver;
    cin >> n;
    for(i=1;i<=n;i++)cin >> a[i];
    root=Build(1,n);
    roots.emplace_back(root);
    cin >> q;
    while(q--)
    {
        cin >> op >> ver >> l >> r;
        if(op == 1)
        {
            root=Update(l,r,roots[ver],1,n);
            roots.emplace_back(root);
        }
        else cout << Query(roots[ver],1,n,l,r) << '\n';
    }
    return 0;
}


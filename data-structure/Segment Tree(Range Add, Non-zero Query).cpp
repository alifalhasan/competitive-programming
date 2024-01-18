#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int cnt[4*N],_tree[4*N],lazy[4*N];

void Update(int nodeNum,int start,int end,int l,int r,int value)
{
    if(start > r  ||  end < l)return;
    if(start >= l  &&  end <= r)
    {
        cnt[nodeNum]+=value;
        if(cnt[nodeNum])_tree[nodeNum]=end-start+1;
        else _tree[nodeNum]=lazy[nodeNum];
        return;
    }
    int mid=(start+end)/2;
    Update(2*nodeNum,start,mid,l,r,value);
    Update(2*nodeNum+1,mid+1,end,l,r,value);
    lazy[nodeNum]=_tree[2*nodeNum]+_tree[2*nodeNum+1];
    if(cnt[nodeNum])_tree[nodeNum]=end-start+1;
    else _tree[nodeNum]=lazy[nodeNum];
}

int Query(int nodeNum,int start,int end,int l,int r)
{
    if(start > end  ||  start > r  ||  end < l)return 0;
    if(start >= l  &&  end <= r)return _tree[nodeNum];

    int mid=(start+end)/2;
    int ans1=Query(nodeNum*2,start,mid,l,r);
    int ans2=Query(nodeNum*2 + 1,mid+1,end,l,r);

    return (ans1+ans2);
}

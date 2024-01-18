#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

long long tree[4*N],lazy[4*N];

void Update(int nodeNum,int start,int end,int l,int r,long long value)
{
    if(lazy[nodeNum] != 0)
    {
        tree[nodeNum]+=(end-start+1)*lazy[nodeNum];
        if(start != end)
        {
            lazy[nodeNum*2]+=lazy[nodeNum];
            lazy[nodeNum*2 + 1]+=lazy[nodeNum];
        }
        lazy[nodeNum]=0;
    }
    if(start > end  ||  start > r  ||  end < l)return;
    if(start >= l  &&  end <= r)
    {
        tree[nodeNum]+=(end-start+1)*value;
        if(start != end)
        {
            lazy[nodeNum*2]+=value;
            lazy[nodeNum*2 + 1]+=value;
        }
        return;
    }

    int mid=(start+end)/2;
    Update(nodeNum*2,start,mid,l,r,value);
    Update(nodeNum*2 + 1,mid+1,end,l,r,value);

    tree[nodeNum]=tree[nodeNum*2] + tree[nodeNum*2 + 1];
}

long long Query(int nodeNum,int start,int end,int l,int r)
{
    if(start > end  ||  start > r  ||  end < l)return 0;
    if(lazy[nodeNum] != 0)
    {
        tree[nodeNum]+=(end-start+1)*lazy[nodeNum];
        if(start != end)
        {
            lazy[nodeNum*2]+=lazy[nodeNum];
            lazy[nodeNum*2 + 1]+=lazy[nodeNum];
        }
        lazy[nodeNum]=0;
    }
    if(start >= l  &&  end <= r)return tree[nodeNum];

    int mid=(start+end)/2;
    long long ans1=Query(nodeNum*2,start,mid,l,r);
    long long ans2=Query(nodeNum*2 + 1,mid+1,end,l,r);

    return (ans1+ans2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    return 0;
}

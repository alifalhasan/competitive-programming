/*

    Build Complexity — O(n log^2 n)
    Query Complexity — O(log^3 n)
    Update Complexity — O(log^2 n)
    The code queries the k-th smallest element in a range with update.

*/
#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename temp>using ordered_set = tree<temp, null_type, less<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key(k)  : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).

const int N=1e5;

long long val[N+2];
ordered_set<pair<long long,int>>ostTree[4*N+8];

void Build(int nodeNum,int start,int end)
{
    if(start == end)
    {
        ostTree[nodeNum].insert({val[start],start});
        return;
    }
    int i,mid=(start+end) >> 1,lChild=mid << 1,rChild=lChild+1;
    for(i=start;i<=end;i++)ostTree[nodeNum].insert({val[i],i});
    Build(lChild,start,mid);Build(rChild,mid+1,end);
}

void Update(int nodeNum,int start,int end,int idx,long long oldVal,long long newVal)
{
    if(start == end)
    {
        ostTree[nodeNum].erase({oldVal,idx});
        ostTree[nodeNum].insert({newVal,idx});
        return;
    }
    int mid=(start+end) >> 1,lChild=mid << 1,rChild=lChild+1;
    if(idx <= mid)Update(lChild,start,mid,idx,oldVal,newVal);
    else Update(rChild,mid+1,end,idx,oldVal,newVal);
    ostTree[nodeNum].insert({newVal,idx});
    ostTree[nodeNum].erase(ostTree[nodeNum].find({oldVal,idx}));
}

int Query(int nodeNum,int start,int end,int l,int r,long long queryVal)
{
    if(start > r  ||  end < l)return 0;
    if(start >= l  &&  end <= r)return ostTree[nodeNum].order_of_key({queryVal,N+5});
    int mid=(start+end) >> 1,lChild=mid << 1,rChild=lChild+1;
    return Query(lChild,start,mid,l,r,queryVal)+Query(rChild,mid+1,end,l,r,queryVal);
}

int main()
{
    int i,k,l,n,q,r,op,temp;
    long long x,ans,high,low,mid;
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%lld",&val[i]);
    Build(1,1,n);
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&op);
        if(op)
        {
            scanf("%d %lld",&l,&x);
            Update(1,1,n,l,val[l],x);
            val[l]=x;
        }
        else
        {
            scanf("%d %d %d",&l,&r,&k);
            low=ostTree[1].find_by_order(0)->first;
            high=ostTree[1].find_by_order(n-1)->first;
            while(low <= high)
            {
                mid=(low+high) >> 1LL;
                temp=Query(1,1,n,l,r,mid);
                if(temp >= k)ans=mid,high=mid-1;
                else low=mid+1;
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}


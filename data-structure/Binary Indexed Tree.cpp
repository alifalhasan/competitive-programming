#include<bits/stdc++.h>

using namespace std;

const int N=1e5;
int a[N+2];
long long sum[N+2];

/********************Point Update********************/

void Update(int idx,int val)
{
    while(idx <= N)
    {
        sum[idx]+=val;
        idx+=idx & (-idx);
    }
}

/********************Point Update********************/



/********************Point Query********************/

long long Query(int idx)
{
    long long ans=0;
    while(idx > 0)
    {
        ans+=sum[idx];
        idx-=idx & (-idx);
    }
    return ans;
}

/********************Point Query********************/



/********************Range Update,Point Query********************/

void Update(int l,int r,int val)
{
    Update(l,val);
    Update(r+1,-val);
}

/********************Range Update,Point Query********************/



/********************Point Update,Range Query********************/

long long Query(int l,int r)
{
    return Query(r)-Query(l-1);
}

/********************Point Update,Range Query********************/



/********************Range Update,Range Query********************/

long long sum[2][N+2];

void Update(int num,int idx,long long val)
{
    while(idx <= N)
    {
        sum[num][idx]+=val;
        idx+=idx & (-idx);
    }
}

long long Query(int num,int idx)
{
    long long ans=0;
    while(idx > 0)
    {
        ans+=sum[num][idx];
        idx-=idx & (-idx);
    }
    return ans;
}

void RangeUpdate(int l,int r,long long val)
{
    Update(0,l,val);
    Update(0,r+1,-val);
    Update(1,l,val*(l-1));
    Update(1,r+1,-val*r);
}

long long PrefixSum(int idx)
{
    return Query(0,idx)*idx-Query(1,idx);
}

long long RangeQuery(int l,int r)
{
    return PrefixSum(r)-PrefixSum(l-1);
}

/********************Range Update,Range Query********************/

int main()
{
    return 0;
}

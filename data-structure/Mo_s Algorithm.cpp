/*
    This program will return number of distinct elements in a range.
*/
#include<bits/stdc++.h>

using namespace std;

const int N=3e4+2;
const int maxN=1e6+2;

struct query
{
    int l,r,id;
}q[200002];
int l,r,k,sum,a[N],ans[200002],cnt[maxN];

bool Compare(query &x,query &y)
{
    int a=x.l/k,b=y.l/k;
    if(a == b)return x.r < y.r;
    return a < b;
}

void Add(int x)
{
    x=a[x];
    ++cnt[x];
    if(cnt[x] == 1)++sum;
}

void Reduce(int x)
{
    x=a[x];
    --cnt[x];
    if(cnt[x] == 0)--sum;
}

int main()
{
    int i,m,n,x;
    cin >> n;
    for(i=0;i<n;i++)cin >> a[i];
    cin >> m;
    k=sqrt(m);
    for(i=0;i<m;i++)
    {
        cin >> x;
        q[i].l=x-1;
        cin >> x;
        q[i].r=x-1;
        q[i].id=i;
    }
    sort(q,q+m,Compare);
    l=0,r=-1,sum=0;
    for(i=0;i<m;i++)
    {
        while(l > q[i].l)Add(--l);
        while(r < q[i].r)Add(++r);
        while(l < q[i].l)Reduce(l++);
        while(r > q[i].r)Reduce(r--);
        ans[q[i].id]=sum;
    }
    for(i=0;i<m;i++)cout << ans[i] << '\n';
    return 0;
}

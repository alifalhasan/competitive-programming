/******************************************************************************

Number of distinct elements in a range without update.

*******************************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define PII pair<int,int>
#define FAST() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

pair<PII,int>queries[500002];
int n,a[500002],ans[500002],cnt[500002],lastIdx[500002];

bool Compare(pair<PII,int>&x,pair<PII,int>&y)
{
    return x.first.second < y.first.second;
}

void Update(int idx,int val)
{
    while(idx <= n)
    {
        cnt[idx]+=val;
        idx+=idx & (-idx);
    }
}

int Query(int idx)
{
    int ans=0;
    while(idx > 0)
    {
        ans+=cnt[idx];
        idx-=idx & (-idx);
    }
    return ans;
}

int main()
{
    FAST();
    int i,q,cur=1;
    cin >> n >> q;
    for(i=1;i<=n;i++)cin >> a[i];
    for(i=1;i<=q;i++)
    {
        cin >> queries[i].first.first >> queries[i].first.second;
        queries[i].second=i;
    }
    sort(queries+1,queries+q+1,Compare);
    for(i=1;i<=q;i++)
    {
        for( ;cur <= queries[i].first.second;cur++)
        {
            if(!lastIdx[a[cur]])
            {
                Update(cur,1);
                lastIdx[a[cur]]=cur;
            }
            else
            {
                Update(lastIdx[a[cur]],-1);
                Update(cur,1);
                lastIdx[a[cur]]=cur;
            }
        }
        ans[queries[i].second]=Query(queries[i].first.second)-Query(queries[i].first.first-1);
    }
    for(i=1;i<=q;i++)cout << ans[i] << '\n';
    return 0;
}



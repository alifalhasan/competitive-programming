///Necessary Condition : C(a,c) + C(b,d)  <=  C(a,d) + C(b,c) for all a <= b <= c <= d
///                      opt(grpNo,i) <= opt(grpNo,i+1)


#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int sz = 1e5+5;

int a[sz];
ll dp[sz][2];

ll Cost(int l,int r)
{
    ///Cost function should be defined as necessary
}

void Compute(int grpNo,int L,int R,int optL,int optR)
{
    if(L > R)return;
    int m=(L+R) >> 1,opt;
    ll &ans=dp[m][grpNo];
    ans=LLONG_MAX;
    for(int i=optL;i<=min(m,optR);i++)
    {
        ll tmp=dp[i-1][grpNo^1]+Cost(i,m);
        if(tmp < ans)ans=tmp, opt=i;
    }
    Compute(grpNo,L,m-1,optL,opt), Compute(grpNo,m+1,R,opt,optR);
}

int main()
{
    int k,n;cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)dp[i][0]=1e12;
    for(int i=1;i<=k;i++)Compute(i%2,1,n,1,n);
    cout << dp[n][k%2];
    return 0;
}

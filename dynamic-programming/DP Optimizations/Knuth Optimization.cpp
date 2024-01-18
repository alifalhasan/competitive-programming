///Necessary Condition : opt[grpNo-1][i] <= opt[grpNo][i] <= opt[grpNo][i+1]

#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int sz = 5e3+5;

int opt[sz][sz];
ll cost[sz][sz],dp[sz][sz];

ll Cost(int l,int r)
{
    ///Calculate the appropriate cost here
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k,n;cin >> n >> k;
    for(int i=1;i<=k;i++)opt[i][n+1]=n;
    for(int i=1;i<=n;i++)opt[0][i]=1;
    for(int grpNo=1;grpNo<=k;grpNo++)
    {
        for(int i=n;i;i--)
        {
            dp[grpNo][i]=LLONG_MAX;
            for(int j=opt[grpNo-1][i];j<=opt[grpNo][i+1];j++)
            {
                ll tmp=dp[grpNo-1][j-1]+Cost(j,i);
                if(tmp < dp[grpNo][i])dp[grpNo][i]=tmp, opt[grpNo][i]=j;
            }
        }
    }
    cout << dp[k][n];
    return 0;
}

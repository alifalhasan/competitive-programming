/*
    Sum of LCM(i,N) where 1 <= i <= N
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e6;
long long phi[N+5],sum[N+5];

void EulerPhi()
{
    int i,j;
    phi[1]=1;
    for(i=2;i<=N;i++)phi[i]=i-1;
    for(i=2;i<=N;i++)
    {
        for(j=2*i;j<=N;j+=i)phi[j]-=phi[i];
    }
}

void PreCal()
{
    int i,j;
    for(i=1;i<=N;i++)
    {
        for(j=i;j<=N;j+=i)sum[j]+=i*phi[i];
    }
}

int main()
{
    int n,t;
    long long ans;
    EulerPhi();
    PreCal();
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        ans=sum[n]+1;
        ans*=n;
        ans/=2;
        printf("%lld\n",ans);
    }
    return 0;
}

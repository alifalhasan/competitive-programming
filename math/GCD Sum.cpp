/*
    Sum of GCD of all pairs <= N.
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e5;
int phi[N+5];
long long sum[N+5];

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

void GCDSum()
{
    int i,j;
    EulerPhi();
    for(i=1;i<=N;i++)
    {
        for(j=2;i*j<=N;j++)sum[i*j]+=(long long)(i * phi[j]);
    }
    for(i=2;i<=N;i++)sum[i]+=sum[i-1];
}

int main()
{
    return 0;
}

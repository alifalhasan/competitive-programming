#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

long long phi[N],sum[N];

void EulerPhi()
{
    int i,j;
    phi[1]=1;
    for(i=2;i<N;i++)phi[i]=i-1;
    for(i=2;i<N;i++)
    {
        for(j=i+i;j<N;j+=i)phi[j]-=phi[i];
    }
}

void PreCal()
{
    int i,j;
    for(i=2;i<N;i++)
    {
        for(j=i;j<N;j+=i)sum[j]+=1ULL*phi[i]*i/2*j;
    }
    for(i=2;i<N;i++)sum[i]+=sum[i-1];
}

int main()
{
    return 0;
}

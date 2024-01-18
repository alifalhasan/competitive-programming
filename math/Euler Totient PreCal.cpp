#include<bits/stdc++.h>

using namespace std;

const int N=1e5;
int phi[N+5];

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

int main()
{
    EulerPhi();
    return 0;
}

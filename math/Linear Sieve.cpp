#include<bits/stdc++.h>

using namespace std;

const int N=1e7;

int lp[N+2];
vector<int>prime;

void Sieve()
{
    int i,j,l=0;
    for(i=2;i<=N;i++)
    {
        if(!lp[i])
        {
            lp[i]=i,++l;
            prime.emplace_back(i);
        }
        for(j=0;j<l  &&  prime[j] <= lp[i]  &&  i*prime[j]<=N;j++)lp[i*prime[j]]=prime[j];
    }
}

int main()
{
    Sieve();
    return 0;
}

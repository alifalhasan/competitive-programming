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

int SOD(long long n)
{
    int i,l=prime.size(),rt=sqrt(n);
    long long ans=1,cnt,pr;
    for(i=0;i<l  &&  prime[i] <= rt;i++)
    {
        if(n%prime[i] == 0)
        {
            cnt=pr=1;
            while(n%prime[i] == 0)
            {
                n/=prime[i];
                pr*=prime[i];
                cnt+=pr;
            }
        }
        rt=sqrt(n);
        ans*=cnt;
    }
    if(n > 1)ans*=(n+1);
    return ans;
}

int main()
{
    long long n;
    Sieve();
    cin >> n;
    cout << SOD(n);
}

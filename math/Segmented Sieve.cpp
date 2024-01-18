#include<bits/stdc++.h>

using namespace std;

const int N=1e7;

int range;
vector<long long>prime;
bool mark[N+2],segmentMark[N+2];

void Sieve()
{
    int i,j;
    range=sqrt(N);
    mark[0]=mark[1]=1;
    prime.emplace_back(2);
    for(i=4;i<=N;i+=2)mark[i]=1;
    for(i=3; i<=range; i+=2)
    {
        if(mark[i] == 0)
        {
            prime.emplace_back(i);
            for(j=i*i; j<=N; j+=2*i)mark[j]=1;
        }
    }
    j=range+(range%2)+1;
    for(i=j; i<N; i+=2)
    {
        if(!mark[i])prime.emplace_back(i);
    }
}

void SegmentSieve(long long a,long long b)
{
    long long i,j,base,araSize=b-a+1;
    memset(segmentMark,0,sizeof(segmentMark));
    for(i=0; prime[i]*prime[i]<=b; i++)
    {
        base=(a/prime[i])*prime[i];
        if(base<a)base+=prime[i];
        for(j=base; j<=b; j+=prime[i])segmentMark[j-a]=1;
        if(base<range)
        {
            if(!mark[base])segmentMark[base-a]=0;
        }
    }
    if(a == 1)segmentMark[0]=1;
    for(i=0; i<araSize; i++)
    {
        if(!segmentMark[i])printf("%lld\n",i+a);
    }
}

int main()
{
    Sieve();
    int t;
    long long a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld %lld",&a,&b);
        SegmentSieve(a,b);
    }
    return 0;
}

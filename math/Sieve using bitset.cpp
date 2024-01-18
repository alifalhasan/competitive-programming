#include<bits/stdc++.h>

using namespace std;

const int N=1e7+5;

void Sieve()
{
    bitset<N>sieve;
    sieve.flip();
    sieve.reset(1);
    int i,j,k,finalBit=sqrt(N)+1;
    for(j=4;j<N;j+=2)sieve.reset(j);
    for(i=3;i<finalBit;i+=2)
    {
        if(sieve.test(i))
        {
            for(j=i*i,k=2*i;j<N;j+=k)sieve.reset(j);
        }
    }
}

int main()
{
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int mod=1e9+7;
int inv[N];

void ModInverse()
{
    inv[1]=1;
    for(int i=2;i<N;i++)
    {
        inv[i]=(-(mod/i) * inv[mod%i])%mod;
        inv[i]+=mod;
    }
}

int main()
{
    return 0;
}

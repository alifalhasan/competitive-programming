#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

long long BigMod(long long val,long long pow)
{
    long long res = 1;
    val = val % mod;
    while(pow > 0)
    {
        if(pow & 1)res = (res*val) % mod;
        pow = pow >> 1;
        val = (val*val) % mod;
    }
    return res;
}

#define AND 1
#define OR 2
#define XOR 3

template<typename T>
struct FWHT
{
    void wht(T io[], const int& n, const int& flag)
    {
        for(int k=1; k<n; k<<=1)
        {
            for(int i=0, m=(k << 1); i<n; i+=m)
            {
                for(int j=0; j<k; j++)
                {
                    ///Apply modulo operation here if needed

                    T x=io[i+j], y=io[i+j+k];
                    if(flag == AND)io[i+j] = x+y;
                    else if(flag == OR)io[i+j+k] = x+y;
                    else io[i+j] = x+y, io[i+j+k] = x-y;
                }
            }
        }
    }

    void iwht(T io[], const int& n, const int& flag)
    {
        for(int k=1; k<n; k<<=1)
        {
            for(int i=0, m=(k << 1); i<n; i+=m)
            {
                for(int j=0; j<k; j++)
                {
                    ///Apply modulo operation here if needed

                    T x=io[i+j], y=io[i+j+k];
                    if(flag == AND)io[i+j] = x-y;
                    else if(flag == OR)io[i+j+k] = y-x;
                    else io[i+j] = (x+y) >> 1, io[i+j+k] = (x-y) >> 1; ///modular inverse if required
                }
            }
        }
    }

    /// a & b are two polynomials and size of them = n which is a power of 2
    void covolute(T a[], T b[], const int& n, const int& flag)
    {
        wht(a,n,flag);
        for(int i=0; i<n; i++)a[i]=(1ll*a[i]*b[i]); ///modulo if required
        iwht(a,n,flag);
    }
};
FWHT<int>T;

const int MX = (1 << 20);

int a[MX],b[MX];

int main()
{
    int n;cin >> n;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<n;i++)cin >> b[i];
    int flag;
    T.wht(a,n,flag), T.wht(b,n,flag); ///This operation is must, flag depends on the operation
    return 0;
}

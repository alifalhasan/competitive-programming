/*
    Find the position of P as a substring of S
*/
#include<bits/stdc++.h>

using namespace std;

const int N=3e5;

/********************Polynomial Hash********************/

const long long base1=191,base2=307;
const long long mod1=1000001011,mod2=1000009999;

long long pow1[N+2],pow2[N+2];

void PreCal()
{
    pow1[0]=pow2[0]=1;
    for(int i=1;i<N;i++)
    {
        pow1[i]=(pow1[i-1]*base1)%mod1;
        pow2[i]=(pow2[i-1]*base2)%mod2;
    }
}

struct PolyHash
{
    vector<pair<long long,long long> >Hash;

    //Polyhash(string &s): a constructor, makes the hash of string S
    PolyHash(string &s)
    {
        long long x = 0, y = 0;
        for(char ch : s)
        {
            x = (x * base1 + ch) % mod1;
            y = (y * base2 + ch) % mod2;
            Hash.emplace_back(x, y);
        }
    }

    // getHash(int l, int r): gives the hash value of the substring S[l, r]
    pair<long long,long long>GetHash(int l, int r)
    {
        long long x = Hash[ r ].first;
        long long y = Hash[ r ].second;
        if(l == 0)return {x, y};
        x = (x - (Hash[ l - 1 ].first * pow1[ r - l + 1 ]) % mod1 + mod1) % mod1;
        y = (y - (Hash[ l - 1 ].second * pow2[ r - l + 1 ]) % mod2 + mod2) % mod2;
        return {x, y};
    }
};

/********************Polynomial Hash********************/

int main()
{
    string s,p;
    int i,ls,lp;
    PreCal();
    cin >> s >> p;
    PolyHash sHash(s),pHash(p);
    ls=s.size(),lp=p.size();
    pair<long long,long long>need=pHash.GetHash(0,lp-1),temp;
    for(i=0 ; i+lp-1 < ls ; i++)
    {
        temp=sHash.GetHash(i,i+lp-1);
        if(temp == need)
        {
            cout << "Present";
            return 0;
        }
    }
    return 0;
}

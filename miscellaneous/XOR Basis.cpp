#include<bits/stdc++.h>

using namespace std;

struct Basis
{
    vector<long long> a;
    void insert(long long x)
    {
        for(auto &i: a) x = min(x, x ^ i);
        if(!x) return;
        for(auto &i: a) if((i ^ x) < i) i ^= x;
        a.emplace_back(x);
        sort(a.begin(), a.end());
    }
    bool can(long long x)
    {
        for(auto &i: a) x = min(x, x ^ i);
        return !x;
    }
    long long maxxor(long long x = 0)
    {
        for (auto &i: a) x = max(x, x ^ i);
        return x;
    }
    long long minxor(long long x = 0)
    {
        for (auto &i: a) x = min(x, x ^ i);
        return x;
    }
} XOR;

int main()
{
    return 0;
}

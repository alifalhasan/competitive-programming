/// Lower bound on BIT in O(logn)
/// https://codeforces.com/contest/992/problem/E

#pragma GCC optimize("Ofast")

#include <map>
#include <set>
#include <cmath>
#include <deque>
#include <stack>
#include <queue>
#include <bitset>
#include <chrono>
#include <random>
#include <vector>
#include <climits>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long

template<typename temp>using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key(k)  : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).//*(ost.find_by_order(k))

//int dx[]={-1,1,0,0};
//int dy[]={0,0,-1,1};
//int dx[]={-1,0,1,-1,1,-1,0,1};
//int dy[]={1,1,1,0,0,-1,-1,-1};

const int M=2e5+5;
const int N=2e6+5;
const int mod=1e9+7;

int a[M];
ll sum[M];

void Update(int i,const int& n,const int& v)
{
    while(i <= n)sum[i]+=v, i+=(i & -i);
}

ll Query(int i)
{
    ll ans=0;
    while(i)ans+=sum[i], i-=(i & -i);
    return ans;
}

int FindID(const int& n,const ll& v)
{
    int ans=0, l=log2(n);
    for(int i=l;i>=0;i--)
    {
        int tmp=ans+(1 << i);
        if(tmp <= n  &&  Query(tmp) < v)ans=tmp;
    }
    return ans+1;
}

int FindAns(const int& n)
{
    ll sum=0;
    while(true)
    {
        int i=FindID(n, sum+sum);
        if(i > n)return -1;
        sum=Query(i);
        if(sum == 2ll*a[i])return i;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i], Update(i,n,a[i]);
    while(q--)
    {
        int i,x;cin >> i >> x;
        Update(i,n,x-a[i]), a[i]=x;
        cout << FindAns(n) << '\n';
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;


void IndependentSet()
{
    int i,j,m,n;
    cin >> n;
    vector<int>v;
    vector<vector<int> >a(n);
    for(i = 0; i < n; i++)
    {
        cin >> m;
        a[i].resize(m);
        for(j = 0; j < m; j++)
        {
            cin >> a[i][j];
            v.emplace_back(a[i][j]);
        }
    }
    sort(v.begin(), v.end());
    map<int, int>mp;
    int ptr = 0;
    for(int x: v)
    {
        if(!mp[x])mp[x] = ++ptr;
    }
    vector<int> mask(ptr, 0), adj(n, 0);
    for(i = 0; i < n; i++)
    {
        for(int x: a[i])mask[mp[x] - 1] |= (1 << i);
    }

    for(i = 0; i < ptr; i++)
    {
        for(j = 0; j < n; j++)
        {
            if((mask[i] >> j) & 1)adj[j] |= mask[i] ^ (1 << j);
        }
    }
    bool flag;
    int ans = 0,sum;
    for(int i = 1; i < (1 << n); i++)
    {
        flag = 1, sum = 0;
        for(j = 0; j < n; j++)
        {
            if(((i >> j) & 1) && (i & adj[j]))flag = 0;
            if((i >> j) & 1)sum += (int)a[j].size();
        }
        if(flag)ans = max(ans, sum);
    }
    cout << ans << endl;
}

int main()
{
    int test;
    cin >> test;
    while(test--)IndependentSet();
}

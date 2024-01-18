#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

struct base
{
    double a, b;
    base(double a = 0, double b = 0) : a(a), b(b) {}
    const base operator + (const base &c) const
    {
        return base(a + c.a, b + c.b);
    }
    const base operator - (const base &c) const
    {
        return base(a - c.a, b - c.b);
    }
    const base operator * (const base &c) const
    {
        return base(a * c.a - b * c.b, a * c.b + b * c.a);
    }
};

void FFT(vector<base> &v, bool inv = 0)
{
    int n = (int)v.size(), i = 0, j, k, l, m;
    for(j = 1; j < n - 1; ++j)
    {
        for(k = n >> 1; k > (i ^= k); k >>= 1);
        if(j < i) swap(v[i], v[j]);
    }
    for(l = 1; (m = l << 1) <= n; l <<= 1)
    {
        double ang = 2 * PI / m;
        base wn = base(cos(ang), (inv ? 1 : -1) * sin(ang)), w;
        for(i = 0; i < n; i += m)
        {
            for(w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn)
            {
                base t = w * v[j + l];
                v[j + l] = v[j] - t, v[j] = v[j] + t;
            }
        }
    }
    if(inv) for(i = 0; i < n; ++i) v[i].a /= n, v[i].b /= n;
}
vector<long long> Multiply(vector<int> &a, vector<int> &b)
{
    int n = (int)a.size(), m = (int)b.size(), t = n + m - 1, sz = 1;
    while(sz < t) sz <<= 1;
    vector<base> x(sz), y(sz), z(sz);
    for(int i = 0 ; i < sz; ++i)
    {
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }
    FFT(x), FFT(y);
    for(int i = 0; i < sz; ++i) z[i] = x[i] * y[i];
    FFT(z, 1);
    vector<long long> ret(sz);
    for(int i = 0; i < sz; ++i) ret[i] = (long long) (z[i].a + 0.5);
    while((int)ret.size() > 1 && ret.back() == 0) ret.pop_back();
    return ret;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i,n,t,x;
    cin >> t;
    while(t--)
    {
        cin >> n;
        vector<int>A,B;
        for(i=0;i<=n;i++)cin >> x, A.emplace_back(x);
        for(i=0;i<=n;i++)cin >> x, B.emplace_back(x);
        vector<long long>ans = Multiply(A, B);
        for(i=0;i<=n+n;i++)cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}

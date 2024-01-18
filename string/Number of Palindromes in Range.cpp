#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

vector<int> d1, d2;
void manachers(string &s)
{
    int n = s.size();
    d1 = vector<int>(n); // maximum odd length palindrome centered at i
    // here d1[i]=the palindrome has d1[i]-1 right characters from i
    // e.g. for aba, d1[1]=2;
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])k++;
        d1[i] = k--;
        if (i + k > r)l = i - k, r = i + k;
    }
    d2 = vector<int>(n); // maximum even length palindrome centered at i
    // here d2[i]=the palindrome has d2[i]-1 right characters from i
    // e.g. for abba, d2[2]=2;
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])k++;
        d2[i] = k--;
        if (i + k > r)l = i - k - 1, r = i + k ;
    }
}

const int MAXV = 1e5+5;// maximum value of any element in array

// array values can be negative too, use appropriate minimum and maximum value
struct wavelet_tree
{
    int lo, hi;
    wavelet_tree *l, *r;
    int *b, bsz, csz;
    long long *c; //  c holds the prefix sum of elements

    wavelet_tree()
    {
        lo = 1;
        l = r = NULL;
        hi = bsz = csz = 0;
    }

    void init(long long *from, long long *to, int x, int y)
    {
        lo = x, hi = y;
        if(from >= to) return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int x)
        {
            return x <= mid;
        };
        b = (int*)malloc((to - from + 2) * sizeof(int));
        bsz = 0, b[bsz++] = 0;
        c = (long long*)malloc((to - from + 2) * sizeof(long long));
        csz = 0, c[csz++] = 0;
        for(auto it = from; it != to; it++)
        {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            bsz++, csz++;
        }
        if(hi == lo) return;
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree();
        l->init(from, pivot, lo, mid);
        r = new wavelet_tree();
        r->init(pivot, to, mid + 1, hi);
    }
    // count of numbers in [l, r] Less than or equal to k
    int LTE(int l, int r, int k)
    {
        if(l > r || k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    // sum of numbers in [l ,r] less than or equal to k
    long long sum(int l, int r, int k)
    {
        if(l > r or k < lo) return 0;
        if(hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wavelet_tree()
    {
        delete l;
        delete r;
    }
};

long long get(int l, int r)
{
    return (1ll * r * (r + 1)) / 2 - (1ll * (l - 1) * l) / 2;
}

wavelet_tree oddl, oddr;
long long odd(int l, int r)
{
    int m = (l + r) / 2;
    int c = 1 - l;
    int less_ = oddl.LTE(l, m, c);
    long long ansl = get(l, m) + oddl.sum(l, m, c) + 1ll * (m - l + 1 - less_) * c;
    c = 1 + r;
    less_ = oddr.LTE(m + 1, r, c);
    long long ansr = -get(m + 1, r) + oddr.sum(m + 1, r, c) + 1ll * (r - m - less_) * c;
    return ansl + ansr;
}

wavelet_tree evenl, evenr;
long long even(int l, int r)
{
    int m = (l + r) / 2;
    int c = -l;
    int less_ = evenl.LTE(l, m, c);
    long long ansl = get(l, m) + evenl.sum(l, m, c) + 1ll * (m - l + 1 - less_) * c;
    c = 1 + r;
    less_ = evenr.LTE(m + 1, r, c);
    long long ansr = -get(m + 1, r) + evenr.sum(m + 1, r, c) + 1ll * (r - m - less_) * c;
    return ansl + ansr;
}

long long a[N], b[N], c[N], d[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;
    int n = s.size();
    manachers(s);
    for(int i = 1; i <= n; i++) a[i] = d1[i - 1] - i;
    oddl.init(a + 1, a + n + 1, -MAXV, MAXV);
    for(int i = 1; i <= n; i++) b[i] = d1[i - 1] + i;
    oddr.init(b + 1, b + n + 1, -MAXV, MAXV);
    for(int i = 1; i <= n; i++) c[i] = d2[i - 1] - i;
    evenl.init(c + 1, c + n + 1, -MAXV, MAXV);
    for(int i = 1; i <= n; i++) d[i] = d2[i - 1] + i;
    evenr.init(d + 1, d + n + 1, -MAXV, MAXV);

    int q; cin >> q;
    while(q--)
    {
        int l,r;cin >> l >> r;
        cout << (odd(l, r) + even(l, r)) << '\n';
    }
    return 0;
}

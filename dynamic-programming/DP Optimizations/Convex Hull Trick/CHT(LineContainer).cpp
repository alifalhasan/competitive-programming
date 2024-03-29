//Set must be non-empty before query

#pragma once

struct Line
{
    mutable ll m, b, p;
    bool operator<(const Line& l) const { return m < l.m; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>>
{
    //for doubles use inf=1/.0, div(a,b)=a/b

    const long long inf=LLONG_MAX;

    long long div(long long a, long long b) { return a/b - ((a ^ b) < 0 && a % b); }

    bool isect(iterator x, iterator y)
    {
        if (y == end()) { x->p = inf; return false; }
        if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }

    void Insert(long long m, long long b)
    {
        //For min X=-X, Y=-Y

        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    long long Query(long long v)
    {
        assert(!empty());
        auto l=*lower_bound(v);
        return (l.m*v + l.b); //For min multiply with (-1)
    }
};

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// len -> largest string length of the corresponding endpos-equivalent class
// link -> longest suffix that is another endpos-equivalent class.
// firstpos -> 1 indexed end position of the first occurrence of the largest string of that node
// minlen(v) -> smallest string of node v = len(link(v)) + 1
// terminal nodes -> store the suffixes
struct SuffixAutomaton
{
    struct node
    {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> st;
    vector<int> terminal;
    vector<long long> dp;
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n)
    {
        g.resize(2 * n);
        st.resize(2 * n);
        dp.resize(2 * n, -1);
        terminal.resize(2 * n, 0);
        st[0].link = -1;
        sz = last = st[0].len = st[0].firstpos = 0;
    }
    void Extend(char c)
    {
        int p = last;
        if(st[p].nxt.count(c))
        {
            int q = st[p].nxt[c];
            if(st[q].len == st[p].len + 1)
            {
                last = q;
                return;
            }
            int clone = ++sz;
            st[clone] = st[q];
            st[clone].len = st[p].len + 1;
            st[q].link = clone;
            last = clone;
            while(p != -1  &&  st[p].nxt[c] == q)
            {
                st[p].nxt[c] = clone;
                p = st[p].link;
            }
            return;
        }
        int cur = ++sz;
        st[cur].len = st[last].len + 1;
        st[cur].firstpos = st[cur].len;
        p = last;
        while(p != -1 && !st[p].nxt.count(c))
        {
            st[p].nxt[c] = cur;
            p = st[p].link;
        }
        if(p == -1)st[cur].link = 0;
        else
        {
            int q = st[p].nxt[c];
            if(st[p].len + 1 == st[q].len)st[cur].link = q;
            else
            {
                int clone = ++sz;
                st[clone] = st[q];
                st[clone].len = st[p].len + 1;
                while(p != -1 && st[p].nxt[c] == q)
                {
                    st[p].nxt[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    void BuildTree()
    {
        for(int i = 1; i <= sz; i++) g[st[i].link].emplace_back(i);
    }
    void Build(string &s)
    {
        for(auto x: s)
        {
            Extend(x);
            terminal[last] = 1;
        }
        BuildTree();
    }
    long long Cnt(int i)   //number of times i-th node occurs in the string
    {
        if(dp[i] != -1) return dp[i];
        long long ret = terminal[i];
        for (auto &x: g[i]) ret += Cnt(x);
        return dp[i] = ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    SuffixAutomaton sa(n);
    sa.Build(s);
    long long ans = 0; //number of unique substrings
    for (int i = 1; i <= sa.sz; i++) ans += sa.st[i].len - sa.st[sa.st[i].link].len;
    cout << ans << '\n';
    return 0;
}

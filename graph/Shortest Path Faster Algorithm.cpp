///Shortest Path Faster Algorithm
///Complexity: O(mn)

#include<bits/stdc++.h>

using namespace std;

const int spfaSize = 2e5+5;

bool inQueue[spfaSize];
int cnt[spfaSize],dist[spfaSize];
vector<pair<int, int>>adj[spfaSize];

bool SPFA(const int& n, const int& source)
{
    queue<int> q;
    for(int i=1;i<=n;i++)cnt[i]=inQueue[i]=0, dist[i]=INT_MAX;

    dist[source] = 0, q.emplace(source), inQueue[source] = 1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop(), inQueue[v] = 0;

        for (auto [to,len] : adj[v])
        {
            if (dist[v] + len < dist[to])
            {
                dist[to] = dist[v] + len;
                if (!inQueue[to])
                {
                    cnt[to]++, inQueue[to] = 1, q.push(to);
                    if (cnt[to] > n) return false;  // negative cycle
                }
            }
        }
    }
    return true;
}

int main()
{
    return 0;
}

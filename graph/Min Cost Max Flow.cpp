#include <bits/stdc++.h>

using namespace std;

/// Min Cost Max Flow

struct Edge
{
    int from, to, capacity, cost;
};

const int mx = 2005;
const long long INF = 1e15;
bool inque[mx];
long long dist[mx];
vector<int>adj[mx];
int capacity[mx][mx],cost[mx][mx],par[mx];

void ShortestPaths(int n, int v0)
{
    for(int i=0; i<n; i++)dist[i]=INF, inque[i]=0, par[i]=-1;
    dist[v0] = 0;
    queue<int> q; q.emplace(v0);

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        inque[u] = false;
        for (int v : adj[u])
        {
            if (capacity[u][v] > 0 && dist[v] > dist[u] + cost[u][v])
            {
                dist[v] = dist[u] + cost[u][v], par[v] = u;
                if (!inque[v]) inque[v] = true, q.emplace(v);
            }
        }
    }
}

long long MinCostFlow(const int& N, const int& K, int s, int t)
{
    int flow = 0;
    long long cost = 0;
    while (flow < K)
    {
        ShortestPaths(N, s);
        if (dist[t] == INF) break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s)
        {
            f = min(f, capacity[par[cur]][cur]);
            cur = par[cur];
        }

        // apply flow
        flow += f;
        cost += 1ll * f * dist[t];
        cur = t;
        while (cur != s)
        {
            capacity[par[cur]][cur] -= f;
            capacity[cur][par[cur]] += f;
            cur = par[cur];
        }
    }

    if (flow < K) return -1;
    return cost;
}

void AddEdge(int i,int j,int cap,int cst)
{
    capacity[i][j] = cap;
    cost[i][j] = cst, cost[j][i] = -cst;
    adj[i].emplace_back(j), adj[j].emplace_back(i);
}

/// Min Cost Max Flow

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k,n;
    cin >> n >> k;
    /// Build the graph here
    cout << MinCostFlow(n+2,k,0,n+1); /// K-is the maximum flow we want to achieve
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

const ll INF = 1e18;

struct Dinic {

    struct edge {
        int v, to;
        ll f, c;

        edge(int a, int b, int C, int d) : v(a), to(b), f(C), c(d) {}

        edge() = default;
    };

    vector<vector<int>> g;
    vector<edge> e;
    vector<int> dist, pnt;
    ll low = 1;
    int s, t, n;

    Dinic() = default;

    Dinic(int n, int ss = -1, int tt = -1) :
            n(n + 2),
            s(ss == -1 ? n : ss),
            t(tt == -1 ? n + 1 : tt),
            dist(n + 2),
            pnt(n + 2, 0) {
        g.assign(n + 2, {});
    }

    void init(int nn, int ss, int tt) {
        n = nn + 2, s = (ss == -1 ? nn : ss), t = (tt == -1 ? nn + 1 : tt);
        dist.resize(n), pnt.assign(n, 0), g.assign(n, {});
    }

    void create(int v, int to, int c) {
        g[v].push_back(e.size());
        e.emplace_back(v, to, 0, c);
        g[to].push_back(e.size());
        e.emplace_back(to, v, 0, 0);
    }

    bool bfs() {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i: g[v])
                if (e[i].c - e[i].f >= low && dist[e[i].to] == INF) {
                    dist[e[i].to] = dist[v] + 1;
                    q.push(e[i].to);
                }
        }
        return dist[t] != INF;
    }

    int dfs(int v, ll minC = INF) {
        if (v == t) return minC;
        while (pnt[v] < g[v].size()) {
            int i = g[v][pnt[v]];
            if (dist[e[i].to] == dist[v] + 1 && e[i].c - e[i].f >= low) {
                int delta = dfs(e[i].to, min(minC, e[i].c - e[i].f));
                if (delta) {
                    e[i].f += delta;
                    e[i ^ 1].f -= delta;
                    return delta;
                }
            }
            ++pnt[v];
        }
        return 0;
    }

    ll flow(int S = -1, int Tt = -1) {
        low = 1;
        s = (S == -1 ? s : S), t = (S == -1 ? t : Tt);
        ll ans = 0;
        while (bfs()) {
            fill(pnt.begin(), pnt.end(), 0);
            while (ll y = dfs(s))
                ans += y;
        }
        return ans;
    }

    ll flow_fast(int S = -1, int Tt = -1) {
        s = (S == -1 ? s : S), t = (S == -1 ? t : Tt);
        ll ans = 0;
        for (low = INF; low; low >>= 1) {
            while (bfs()) {
                fill(pnt.begin(), pnt.end(), 0);
                while (ll y = dfs(s))
                    ans += y;
            }
        }
        return ans;
    }
};
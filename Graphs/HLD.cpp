#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 1;

int n;
vector<int> g[N];

struct HLD {
public:
    vector<int> s, tin, tout, head, p;
    int T;

    void size(int v = 0) {
        s[v] = 1;
        for (auto &u: g[v]) {
            if (s[u]) continue;
            p[u] = v, size(u), s[v] += s[u];
            if (s[g[v][0]] < s[u]) swap(g[v][0], u);
        }
    }

    void hld(int v = 0) {
        tin[v] = T++;
        for (int u: g[v]) {
            if (u == p[v])continue;
            if (u == g[v][0]) head[u] = head[v];
            else head[u] = u;
            hld(u);
        }
        tout[v] = T;
    }

    void build() {
        T = 0;
        p.resize(n), s.resize(n), tin.resize(n), tout.resize(n), head.resize(n);
        size(), hld();
    }

    int anc(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

    int lca(int u, int v) {
        for (;; v = p[head[v]]) {
            if (tin[v] < tin[u]) swap(u, v);
            if (tin[head[v]] <= tin[u]) return u;
        }
    }

    auto path(int u, int v) {
        vector<pii> ans;
        for (;; v = p[head[v]]) {
            if (tin[v] < tin[u]) swap(u, v);
            if (tin[head[v]] <= tin[u]) {
                ans.emplace_back(tin[u], tin[v]);
                return ans;
            }
            ans.emplace_back(tin[head[v]], tin[v]);
        }
    }
};
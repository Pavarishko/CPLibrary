#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 1, lg = 20;

int up[lg][N];
int tin[N], tout[N], T = 0;

vector<int> g[N];

void dfs(int v = 0, int p = -1) {
    tin[v] = T++;
    for (int l = 1; l < lg; l++) up[l][v] = up[l - 1][up[l - 1][v]];
    for (int u: g[v]) {
        if (p == u) continue;
        up[0][u] = v;
        dfs(u, v);
    }
    tout[v] = T;
}

int anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] >= tout[u];
}

int lca(int u, int v) {
    if (anc(u, v)) return u;
    if (anc(v, u)) return v;
    for (int l = lg - 1; l >= 0; l--)
        if (!anc(up[l][v], u))
            v = up[l][v];
    return up[0][v];
}
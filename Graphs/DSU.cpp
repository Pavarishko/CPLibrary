#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct DSU {
    vector<int> p;

    DSU(int n) {
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }
    
    int get(int v) {
        if (v == p[v]) return v;
        return p[v] = get(p[v]);
    }

    void un(int u, int v) {
        u = get(u), v = get(v);
        if (p[u] == p[v]) return;
        if (rnd() & 1) swap(u, v);
        p[v] = u;
    }
};
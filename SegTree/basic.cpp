#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll inf = 1e18;

struct SegmentTree {
    struct Node {
        ll sum = 0, mn = -inf, mx = inf;
    };

    Node merge(const Node &l, const Node &r) {
        return {l.sum + r.sum, min(l.mn, r.mn), max(l.mx, r.mx)};
    }

    vector<Node> t;
    vector<int> fl;
    int N;

    void build(const vector<int> &a) {
        int n = a.size();
        while (N <= n) N += N;
        t.clear(), fl.clear();
        t.resize(2 * N), fl.resize(2 * N);
        for (int i = 0; i < n; i++) t[i + N] = {a[i], a[i], a[i]};
        for (int i = N - 1; i; i--) t[i] = merge(t[i * 2], t[i * 2 + 1]);
    }

    void push(int v, int l, int r) {
        for (int u = v * 2; u <= v * 2 + 1; u++) {
            fl[u] += fl[v];
            t[u].mn += fl[v];
            t[u].mx += fl[v];
            t[u].sum += fl[v] * (r - l) / 2;
        }
        fl[v] = 0;
    }

    void upd(int lq, int rq, int x, int v, int l, int r) {
        if (rq <= l || r <= lq) return;
        if (lq <= l && r <= rq) {
            fl[v] += x;
            t[v].sum += x, t[v].mn += x, t[v].mx += x;
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        upd(lq, rq, x, v * 2, l, m);
        upd(lq, rq, x, v * 2 + 1, m, r);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    void upd(int l, int r, int x) { upd(l, r, x, 1, 0, N); }

    Node get(int lq, int rq, int v, int l, int r) {
        if (rq <= l || r <= lq) return {};
        if (lq <= l && r <= rq) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return merge(get(lq, rq, v * 2, l, m), get(lq, rq, v * 2 + 1, m, r));
    }

    Node get(int l, int r) { return get(l, r, 1, 0, N); }
};
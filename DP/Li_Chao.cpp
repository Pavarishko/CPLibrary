#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll inf = 1e18;

struct Line {
    ll k = 0, b = inf;

    Line() = default;

    Line(ll K, ll B) : k(K), b(B) {}

    ll operator()(ll x) { return k * x + b; }
};

int n;

struct LiChao {
    vector<Line> t;

    LiChao() {
        int N = 1;
        while (N <= n) N *= 2;
        t.resize(2 * N);
    }

    void upd(Line New, int v = 1, int l = 0, int r = n) {
        int m = (l + r) / 2;
        int okl = New(l) > t[v](l);
        int okm = New(m) > t[v](m);
        if (okm) swap(New, t[v]);
        if (r - l == 1)return;
        if (okl != okm) upd(New, v * 2, l, m);
        else upd(New, v * 2 + 1, m, r);
    }

    ll get(ll x, int v = 1, int l = 0, int r = n) {
        ll ans = t[v](x);
        if (r - l == 1)return ans;
        int m = (l + r) / 2;
        if (x < m) ans = max(ans, get(x, v * 2, l, m));
        else ans = max(ans, get(x, v * 2 + 1, m, r));
        return ans;
    }
};

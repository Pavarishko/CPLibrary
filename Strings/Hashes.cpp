#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll mod1 = 1e9 + 7, mod2 = 998244353;
const ll p1 = 31, p2 = 37;

struct Hash {
    vector<ll> h, p;
    ll mod;

    void build(const string &s, const ll &m, const ll &x) {
        int n = s.size();
        h.resize(n), p.resize(n);
        mod = m;
        h[0] = s[0] - 'a' + 1, p[0] = 1;
        for (int i = 1; i < n; i++) {
            h[i] = (h[i - 1] * x + (s[i] - 'a' + 1)) % m;
            p[i] = p[i - 1] * x % m;
        }
    }

    ll get(int l, int r) {
        if (!l) return h[r];
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }
};
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll N = 2e5 + 1;

ll f[N], n;

void upd(int i, int v) {
    for (int j = i; j < n; j = (j | (j + 1))) f[j] += v;
}

ll sum(int r) {
    ll ans = 0;
    for (int j = r; j >= 0; j = (j & (j + 1)) - 1) ans += f[j];
    return ans;
}

ll sum(int l, int r) {
    return sum(r) - sum(l - 1);
}
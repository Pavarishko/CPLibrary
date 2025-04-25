#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define sz(v) (int) v.size()
#define all(v) v.begin(), v.end()

using dl = double;

const dl eps = 1e-6;

struct P {
    dl x = 0, y = 0;

    P() = default;

    P(dl x, dl y) : x(x), y(y) {}

    dl len() const {
        return hypotl(x, y);
    }

};

dl vct(const P &a, const P &b) {
    return a.x * b.y - a.y * b.x;
}

dl sca(const P &a, const P &b) {
    return a.x * b.x + a.y * b.y;
}

P operator-(const P &a, const P &b) {
    return {a.x - b.x, a.y - b.y};
}

P operator+(const P &a, const P &b) {
    return {a.x + b.x, a.y + b.y};
}

bool operator==(const P &a, const P &b) {
    return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}

vector<P> convex_hull(vector<P> a) {
    int n = sz(a);
    P st = *min_element(all(a), [](const P &A, const P &B) {
        return A.y < B.y || (A.y == B.y && A.x < B.x);
    });
    sort(all(a), [&](const P &A, const P &B) {
        dl val = vct(A - st, B - st);
        if (fabs(val) < eps) return (A - st).len() < (B - st).len();
        return val > eps;
    });
    vector<P> b = {st};
    int m = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == st || (i && a[i] == a[i - 1])) continue;
        while (m > 1 && vct(b[m - 1] - b[m - 2], a[i] - b[m - 1]) <= 0) {
            b.pop_back();
            m--;
        }
        b.push_back(a[i]), m++;
    }
    return b;
}
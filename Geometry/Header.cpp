#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;
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

bool operator==(const P&a, const P &b){
    return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}

struct Line {
    dl a = 0, b = 0, c = 0;
    
    Line() = default;

    Line(dl a, dl b, dl c) : a(a), b(b), c(c) {}

    Line(const P &u, const P &v) {
        a = u.y - v.y;
        b = v.x - u.x;
        c = -(a * u.x + b * u.y);
    }

    dl dist_from_point(const P &p) {
        return fabsl(a * p.x + b * p.y + c) / hypotl(a, b);
    }

    int point_on_line(const P &p) {
        return fabsl(a * p.x + b * p.y + c) < eps;
    }

    P mirror(const P &p) {
        P q(a, b);
        dl boost = dist_from_point(p) / q.len();
        q.x *= boost, q.y *= boost;
        if (point_on_line(p + q)) return p + q + q;
        return p - q - q;
    }
};

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

//generate random double number on [l, r]

dl gen(dl l, dl r) {
    dl lol = (dl) rnd() / UINT32_MAX;
    return l + lol * (r - l);
}
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll inf = 1e18;

struct Node {
    ll x, y;
    Node *l, *r;

    Node(ll xi) : x(xi), y(rand()), l(nullptr), r(nullptr) {}
};

Node *root;

Node *merge(Node *L, Node *R) {
    if (!L)return R;
    if (!R)return L;
    if (L->y > R->y) {
        L->r = merge(L->r, R);
        return L;
    } else {
        R->l = merge(L, R->l);
        return R;
    }
}

pair<Node *, Node *> split(Node *V, ll x0) {
    if (!V)return {nullptr, nullptr};
    if (V->x <= x0) {
        auto [L, R] = split(V->r, x0);
        V->r = L;
        return {V, R};
    } else {
        auto [L, R] = split(V->l, x0);
        V->l = R;
        return {L, V};
    }
}

ll mn(Node *V) {
    if (!V)return inf;
    if (!(V->l)) return V->x;
    return mn(V->l);
}

ll mx(Node *V) {
    if (!V)return inf;
    if (!(V->r)) return V->x;
    return mx(V->r);
}

ll ex(ll x) {
    auto [L, R] = split(root, x);
    int ok = mx(L) == x;
    root = merge(L, R);
    return ok;
}

void insert(int x) {
    if (ex(x)) return;
    auto [L, R] = split(root, x);
    Node *V = new Node(x);
    root = merge(merge(L, V), R);
}

void erase(int x) {
    if (!ex(x)) return;
    auto [L, R] = split(root, x);
    auto [L1, R1] = split(L, x - 1);
    root = merge(L1, R);
}

ll next(ll x) {
    auto [L, R] = split(root, x);
    ll y = mn(R);
    root = merge(L, R);
    return y;
    // y = inf => x is the last element
}

ll prev(ll x) {
    auto [L, R] = split(root, x - 1);
    ll y = mx(L);
    root = merge(L, R);
    return y;
    // y = inf => x is the first element
}

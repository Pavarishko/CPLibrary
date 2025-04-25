#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Node {
    ll x, y, siz;
    Node *l, *r;

    Node(int xi) : x(xi), y(rand()), siz(1), l(nullptr), r(nullptr) {}
};

Node *root;

ll get_sz(Node *V) {
    if (!V)return 0;
    return V->siz;
}

void upd(Node *V) {
    if (!V)return;
    V->siz = 1 + get_sz(V->l) + get_sz(V->r);
}

Node *merge(Node *L, Node *R) {
    if (!L)return R;
    if (!R)return L;
    if (L->y > R->y) {
        L->r = merge(L->r, R);
        upd(L);
        return L;
    } else {
        R->l = merge(L, R->l);
        upd(R);
        return R;
    }
}

pair<Node *, Node *> split(Node *V, int k) {
    if (!V)return {nullptr, nullptr};
    if (k >= get_sz(V->l) + 1) {
        auto [L, R] = split(V->r, k - get_sz(V->l) - 1);
        V->r = L;
        upd(V);
        return {V, R};
    } else {
        auto [L, R] = split(V->l, k);
        V->l = R;
        upd(V);
        return {L, V};
    }
}
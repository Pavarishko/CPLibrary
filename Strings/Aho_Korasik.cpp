#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define sz(v) (int)v.size()
using ll = long long;

const ll H = 26;
int Q;

struct Node {
    int go[H];
    vector<int> term;
    int p, suflink, hyper;
    char pCh;

    Node() {
        fill(go, go + H, -1);
        p = 0, suflink = -1, hyper = -1;
    }
};

vector<Node> bor;
Node a;

void add(string &s) {
    int v = 0;
    for (char c: s) {
        int x = c - 'a';
        if (bor[v].go[x] == -1) {
            bor[v].go[x] = sz(bor);
            bor.push_back(a);
        }
        int u = bor[v].go[x];
        bor[u].p = v, bor[u].pCh = c;
        v = bor[v].go[x];
    }
    bor[v].term.push_back(Q);
}

int go(int v, char c);

int suflink(int v) {
    if (bor[v].suflink != -1) return bor[v].suflink;
    if (!v || !bor[v].p) {
        bor[v].suflink = 0;
        return 0;
    }
    bor[v].suflink = go(suflink(bor[v].p), bor[v].pCh);
    return bor[v].suflink;
}

int go(int v, char c) {
    int x = c - 'a';
    if (bor[v].go[x] != -1)return bor[v].go[x];
    if (!v) bor[v].go[x] = 0;
    else bor[v].go[x] = go(suflink(v), c);
    return bor[v].go[x];
}

int hypersuflink(int v) {
    if (bor[v].hyper != -1)return bor[v].hyper;
    int s = suflink(v);
    if (!bor[s].term.empty()) {
        bor[v].hyper = s;
        return s;
    }
    if (!s) {
        bor[v].hyper = 0;
        return 0;
    }
    bor[v].hyper = hypersuflink(s);
    return bor[v].hyper;
}
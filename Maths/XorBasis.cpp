#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int K = 20;

struct XorBasis {
    int t[K];

    XorBasis() {
        fill(t, t + K, -1);
    }

    void add(int x) {
        if (x == -1) return;
        for (int i = K - 1; i >= 0; --i) {
            if (!((x >> i) & 1)) continue;
            if (t[i] == -1) {
                t[i] = x;
                return;
            }
            x ^= t[i];
        }
    }

    int check(int x) {
        for (int i = K - 1; i >= 0; --i) {
            if ((x >> i) & 1) x ^= t[i];
        }
        return !x;
    }
};
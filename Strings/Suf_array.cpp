#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define sz(v) (int) v.size()
#define all(v) v.begin(), v.end()

struct SufArray {
    vector<int> s, p, c, lcp;
    const int m = 27;
    int n;

    SufArray(const string &S) {
        for (char sym: S) s.push_back(sym - 'a' + 1);
        s.push_back(0);
        n = sz(s);
        c.resize(n), p.resize(n);
        //sorting all suffixes by first letter
        int C = 0;
        vector<vector<int>> w(m);
        for (int i = 0; i < n; ++i) w[s[i]].push_back(i);
        int id = 0;
        for (int x = 0; x < m; ++x) {
            if (w[x].empty()) continue;
            for (int i: w[x]) c[i] = C, p[id++] = i;
            C++;
        }
        //sorting all suffixes by prefixes of 2^k length
        for (int k = 1; C < n; k *= 2) {
            vector<int> a(n), newc(n);
            vector<int> place(C);
            for (int i = 0; i < n; ++i) if (c[i] + 1 < C) place[c[i] + 1]++;
            for (int i = 0; i < C - 1; ++i) place[i + 1] += place[i];
            for (int i = 0; i < n; i++) {
                int pr = (p[i] - k + n) % n;
                a[place[c[pr]]++] = pr;
            }
            id = 0, C = 0;
            int pr = -1;
            for (int now: a) {
                if (pr != -1 && c[pr] != c[now]) pr = -1;
                if (pr == -1 || c[(now + k) % n] != c[(pr + k) % n]) C++;
                newc[now] = C - 1, p[id++] = now, pr = now;
            }
            c = newc;
        }
        //calculating lcp 
        n--;
        reverse(all(p)), p.pop_back(), reverse(all(p));
        for (int i = 0; i < n; ++i) c[i]--;
        lcp.resize(n);
        for (int i = 0; i < n; ++i) {
            if (c[i] + 1 == n) continue;
            int j = p[c[i] + 1];
            int k = 0;
            if (i) k = max(0, lcp[c[i - 1]] - 1);
            while (max(i, j) + k < n && s[i + k] == s[j + k]) k++;
            lcp[c[i]] = k;
        }
    }

};
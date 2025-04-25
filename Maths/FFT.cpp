#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1) return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<int> convertToDigits(const string &s, bool &negative) {
    vector<int> result;
    negative = false;
    int start = 0;
    if (s[0] == '-') {
        negative = true;
        start = 1;
    }
    for (int i = s.size() - 1; i >= start; i--)
        result.push_back(s[i] - '0');
    return result;
}

string multiplyNumbers(const string &num1, const string &num2) {
    bool negative1, negative2;
    vector<int> a = convertToDigits(num1, negative1);
    vector<int> b = convertToDigits(num2, negative2);
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0))
        return "0";
    bool resultNegative = negative1 ^ negative2;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    int carry = 0;
    for (int i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    while (carry > 0) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    string resultStr = resultNegative ? "-" : "";
    for (int i = result.size() - 1; i >= 0; i--)
        resultStr += to_string(result[i]);
    return resultStr;
}
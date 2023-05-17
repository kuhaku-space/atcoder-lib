#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A"
#include "math/prime_number.hpp"
#include "template/atcoder.hpp"

prime_number pn;

int main(void) {
    int n;
    cin >> n;
    auto v = pn.prime_factorization(n);
    cout << n << ':';
    for (auto p : v) {
        rep (i, p.second) cout << ' ' << p.first;
    }
    cout << '\n';

    return 0;
}

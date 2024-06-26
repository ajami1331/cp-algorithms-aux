// @brief Convolution mod $10^9+7$
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "cp-algo/math/poly.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace cp_algo::math;

const int mod = 1e9 + 7;
using base = modint<mod>;
using polyn = poly_t<base>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<base> a(n), b(m);
    copy_n(istream_iterator<base>(cin), n, begin(a));
    copy_n(istream_iterator<base>(cin), m, begin(b));
    (polyn(a) * polyn(b)).print(n + m - 1);
}

signed main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while(t--) {
        solve();
    }
}

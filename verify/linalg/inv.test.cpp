// @brief Inverse Matrix
#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("tune=native")
#include "cp-algo/linalg/matrix.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace cp_algo::linalg;
using namespace cp_algo::math;

const int mod = 998244353;

void solve() {
    int n;
    cin >> n;
    matrix<modint<mod>> a(n, n);
    a.read();
    auto ai = a.inv();
    if(!ai) {
        cout << -1 << "\n";
    } else {
        ai->print();
    }
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
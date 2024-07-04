// @brief Eertree
#define PROBLEM "https://judge.yosupo.jp/problem/eertree"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("tune=native")
#include "cp-algo/data_structures/eertree.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace cp_algo::data_structures;

int yosupo(int v) {
    if(v == 1) {
        return -1;
    } else if(v > 1) {
        return v - 1;
    } else {
        return 0;
    }
}

void solve() {
    string s;
    cin >> s;
    eertree me(size(s));
    vector<int> lasts;
    lasts.reserve(size(s));
    for(auto c: s) {
        me.add_letter(c);
        lasts.push_back(me.sufpal(yosupo));
    }
    me.print(yosupo);
    ranges::copy(lasts, ostream_iterator<int>(cout, " "));
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

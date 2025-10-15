#include <bits/stdc++.h>
using namespace std;

// 有序集合，时间复杂度 O(N logN)
int main() {
    int q, x;
    cin >> q >> x;
    vector<int> r_cnt(x);
    int ptr = 0;

    set<pair<int, int>> sset;
    for (int i=0; i<x; ++i) sset.emplace(r_cnt[i], i);

    for (int i=0; i<q; ++i) {
        int y;
        cin >> y;
        int r = y % x;
        r_cnt[r] += 1;
        sset.erase({r_cnt[r]-1, r});
        sset.emplace(r_cnt[r], r);

        cout << sset.begin()->first*x + sset.begin()->second << endl;
    }
}

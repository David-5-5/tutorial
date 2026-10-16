#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n, m; cin >> n >> m;
    vector a(n, vector<int>(m));
    for (int i=0; i<n; i++) for (int k=0; k<m; k++) cin >> a[i][k];

    int FULL = (1 << m)-1;
    vector pre(FULL+1, vector<int>());
    for (int x=1; x<=FULL; x++) {
        int base = (~x) & FULL;
        int s = x;
        do {
            pre[x].push_back(base | s);
            s = (s-1) & x;
        } while (s != x);
    }

    auto check = [&](int limit) -> pair<int, int> {
        // unordered_map<int, int> masks;
        vector<int> masks(FULL+1, -1);

        for (int i=0; i<n; i++) {
            int msk = 0;
            for (int k=0; k<m; k++) {
                if (a[i][k] >= limit) msk |= 1 << k;
            }
            if (msk == FULL) return {i, i};
            for (auto & y : pre[msk]) {
                if (masks[y] != -1) {
                    return {i, masks[y]};
                }
            }
            masks[msk] = i;
        }

        return {-1, -1};
    };

    int l = -1, r = 1e9 + 1;
    int i, j;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        auto [i0, j0] = check(mid);
        if (i0 < 0) {
            r = mid;
        } else {
            l = mid; i = i0, j = j0;
        }
    }

    cout << i+1 << " " << j+1 << endl;

    return 0;
}


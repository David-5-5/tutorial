#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, m;
    cin >> n >> m;
    vector<long long> balances(n);
    for (int i = 0; i < m; ++i) {
        int u, v; long long d;
        cin >> u >> v >> d;
        balances[u-1] -= d; balances[v-1] += d;
    }
    
    vector<pair<int, long long>> ap, ar;
    for (int i=0; i<n; i++) {
        if (balances[i] > 0) {
            ar.emplace_back(i, balances[i]);
        } else if (balances[i] < 0) {
            ap.emplace_back(i, -balances[i]);
        }
    }

    vector<array<long long, 3>> ans;
    size_t p1 = 0, p2 = 0;
    while (p1 < ap.size() && p2 < ar.size()) {
        auto &[debtor, pay] = ap[p1];
        auto &[creditor, recv] = ar[p2];
        long long trans = min(pay, recv);

        ans.push_back({debtor, creditor, trans});
        if (pay == recv) {
            p1 ++; p2++;
        } else if (pay > recv) {
            pay -= trans; p2++;
        } else {
            p1 ++; recv -= trans;
        }
    }

    cout << ans.size() << endl;
    for (auto & a: ans) {
        cout << a[0]+1 << " " << a[1]+1 << " " << a[2] << endl;
    }

    return 0;
}


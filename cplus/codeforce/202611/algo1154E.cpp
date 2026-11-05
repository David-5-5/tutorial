#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    priority_queue<pair<int, int>> pq;
    
    vector<pair<int, int>> links(n);
    for (int i=0; i<n; i++) {
        int val; cin >> val;
        pq.emplace(val, i);
        links[i] = {i-1, i+1};
    }

    int cur = 0;
    while (!pq.empty()) {
        while (!pq.empty() && a[pq.top().second]>0) pq.pop();
        if (pq.empty()) break;
        
        auto [_, idx] = pq.top(); pq.pop();
        a[idx] = 1 << cur;
        auto l = links[idx].first;  // prev
        int rem = k;
        while (l>-1 && rem) {
            a[l] = 1 << cur;
            l = links[l].first; rem--;
        }
        auto r = links[idx].second;
        rem = k;
        while (r < n && rem) {
            a[r] = 1 << cur;
            r = links[r].second; rem--;
        }
        if (l>-1) links[l].second = r;
        if (r<n) links[r].first = l;
        cur ^= 1;
    }
    
    for (auto& v: a) cout << v;
    cout << endl;
    return 0;
}


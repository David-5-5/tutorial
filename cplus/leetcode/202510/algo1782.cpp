// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
#include <bits/stdc++.h>
using namespace std;


// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        // 自行解答 难度分 2457
        // inx: index of vertex, value: degree of the vertex
        vector<int> degree(n);   
        // inx: u of vertex, map: key v of adjacent vertex， value: the degree between u, v
        vector<unordered_map<int, int>> endpoints(n);

        for (auto& e: edges){
            int u = e[0]-1, v = e[1]-1;
            degree[u] ++, degree[v] ++;
            endpoints[u][v] ++, endpoints[v][u] ++;
        }

        int idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            if (degree[i] == degree[j]) return i < j;
            return degree[i] < degree[j] ;
        });
        // for (int i=0; i<n; ++i) cout << "{" << idx[i] << ", " << degree[idx[i]] << "}" << endl;
        auto count = [&](int q) -> int {
            int l = 0, r = n-1, ans = 0;
            while (l < r) {
                int u = idx[l], v = idx[r];
                if (degree[u] + degree[v] > q){
                    ans += r - l;
                    for (auto& [t, cnt]: endpoints[v]) {
                        if (degree[t] < degree[u] ||
                            (degree[t] == degree[v] && t > v) ||
                            degree[t] > degree[v]) continue;
                        if (degree[t] + degree[v] - cnt <= q) ans --;
                    }
                    r--;
                } else l ++;
            }
            return ans;
        };

        vector<int> ans; 
        // for (auto q: queries) ans.push_back(count(q));
        // 优化重复的 q，避免重复计算 count(q)
        unordered_map<int, int> cache;
        for (auto q: queries) {
            if (!cache.count(q)) cache[q] = count(q);
            ans.push_back(cache[q]);
        }
        return ans;   
    }
};

int main() {
    vector<vector<int>> edges = {{1,2}, {2,4}, {1,3}, {2,3}, {2,1}};
    vector<int> queries = {2,3};
    cout << Solution().countPairs(4, edges, queries)[0] << endl;
}
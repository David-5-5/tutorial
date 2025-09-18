#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;
vector<int> prime_factors[N];

int init = [] {
    for (int i = 2; i < N; ++i) {
        if (prime_factors[i].empty()) { // 质数
            for (int j = i; j < N; j += i) {
                prime_factors[j].push_back(i);
            }
        }
    }
    return 0;
}();

// 数学算法 - 数论 - 1.3 质因数分解
class Solution {
public:
    int minJumps(vector<int>& nums) {
        // 参考题解; 无权重的路径的长度 bfs 即可. 不需要 dijkstra
        int n = nums.size();
        unordered_map<int, vector<int>> prime_idx;

        for (int i=1; i<n; ++i) {
            for (const auto& f: prime_factors[nums[i]]) {
                prime_idx[f].push_back(i);
            }
        }

        vector<int> que; que.push_back(0);
        vector<bool> vis(n); vis[0] = true;
        int ans = 0;

        while (!que.empty()) {
            vector<int> nxt;
            for (auto u: que) {
                if (u == n-1) return ans;
                if (u && !vis[u-1]) {
                    nxt.push_back(u-1); vis[u-1] = true;
                }
                if (u+1<n && !vis[u+1]) {
                    nxt.push_back(u+1); vis[u+1] = true;
                }
                if (prime_idx.count(nums[u])) {
                    for (auto v: prime_idx[nums[u]]) {
                        if (!vis[v]) {
                            vis[v] = true; nxt.push_back(v);
                        }
                    }
                    prime_idx.erase(nums[u]);   // 避免重复遍历，这又是一个坑
                }
            }
            que = move(nxt);
            ans ++;
        }
        // END TEMPLATE Dijkstra
        return ans; 
    }
};

int main() {
    vector<int> nums = {1,2,4,6};
    cout << Solution().minJumps(nums) << endl;
}
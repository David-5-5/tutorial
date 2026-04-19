#include <bits/stdc++.h>
using namespace std;

// 字符串 - 四、字符串哈希
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        // 标准 hash - 超时
        int n = target.length(); vector<int> dp(n+1, INT_MAX); dp[0] = 0;
        
        unordered_map<int, unordered_map<int, int>> hash_cost; set<int> w_len;
        // Rabin karp 变型 - 单hash
        int mod = 1e9 + 7, base = 401; 
        // vector<int> bm = {1};
        for (int i=0; i<words.size(); ++i) {
            auto m = words[i].length();
            w_len.insert(m);
            long long p = 0;
            for (int j=0; j<m; j++) {
                p = (p * base + words[i][j]) % mod;
                // if (bm.size()==i) bm.push_back(bm.back()*base%mod);
            }
            if (!hash_cost[m].count(p)) hash_cost[m][p] = costs[i];
            else hash_cost[m][p] = min(hash_cost[m][p], costs[i]);
        }
        
        unordered_map<int, long long> bm;
        for (auto it=w_len.begin(); it!=w_len.end(); it++) {
            auto m = *it; bm[m] = 1;
            for (int _=0; _<m-1; ++_) bm[m] = bm[m] * base % mod;
        }
        
        int mx = *prev(w_len.end());
        // cout << mx << endl;
        unordered_map<int, int> t_by_len;
        long long t = 0;
        for(int j=1; j<=mx; ++j) {
            t = (t * base + target[j-1]) % mod;
            if (w_len.count(j)) {
                t_by_len[j] =  t;
                if (hash_cost[j].count(t)) {
                    dp[j] = min(dp[j], dp[0] + hash_cost[j][t]);
                }
            }
        }

        for (int i=1; i<n; i++) {
            // if (dp[i] == INT_MAX) continue;
            for (auto it=w_len.begin(); it!=w_len.end(); it++) {
                auto m = *it;
                if (i+m-1 >= n) break;
                t_by_len[m] = ((t_by_len[m] + mod - (target[i-1] * bm[m])%mod) * base + target[i+m-1]) % mod;
                if (dp[i] < INT_MAX && hash_cost[m].count(t_by_len[m])) {
                    dp[i+m] = min(dp[i+m], dp[i] + hash_cost[m][t_by_len[m]]);
                }
            }
        }
        
        return dp[n]==INT_MAX?-1:dp[n];  
    }

    int minimumCost2(string target, vector<string>& words, vector<int>& costs) {
        // 使用前缀和计算字符串 hash，避免超时
        int n = target.length(); vector<int> dp(n+1, INT_MAX/2); dp[0] = 0;

        int mod = 1e9 + 7, base = 401; ; 

        vector<int> pow_base(n + 1); // pow_base[i] = base^i
        vector<int> pre_hash(n + 1); // 前缀哈希值 pre_hash[i] = hash(s[:i])
        pow_base[0] = 1;
        for (int i = 0; i < n; i++) {
            pow_base[i + 1] = (long long) pow_base[i] * base % mod;
            pre_hash[i + 1] = ((long long) pre_hash[i] * base + target[i]) % mod; // 秦九韶算法计算多项式哈希
        }

        // 计算 target[l] 到 target[r-1] 的哈希值
        auto sub_hash = [&](int l, int r) {
            return ((pre_hash[r] - (long long) pre_hash[l] * pow_base[r - l]) % mod + mod) % mod;
        };

        map<int, unordered_map<int, int>> hash_cost;
        for (int i=0; i<words.size(); ++i) {
            auto m = words[i].length();
            long long p = 0;
            for (int j=0; j<m; j++) {
                p = (p * base + words[i][j]) % mod;
            }
            if (!hash_cost[m].contains(p)) hash_cost[m][p] = costs[i];
            else hash_cost[m][p] = min(hash_cost[m][p], costs[i]);
        }

        
        for (int i=1; i<=n; i++) {
            for (auto &[len, mc]:hash_cost) {
                if (len > i) break;
                auto it = mc.find(sub_hash(i-len, i));
                if (it != mc.end()) dp[i] = min(dp[i], dp[i-len] + it->second);
            }
        }
        
        return dp[n]>=INT_MAX/2?-1:dp[n]; 
    }    
};


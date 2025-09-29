#include <bits/stdc++.h>
using namespace std;

const int N = 5 * 1e4 + 1;
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

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:

    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // 自行解答，超时
        int mx = ranges::max(nums), n = nums.size();
        map<int, int> num_cnt, gcd_cnt;
        
        for (auto v: nums) num_cnt[v]++;
        
        int prev = 0;
        for (auto [val, cnt]: num_cnt) {
            prev += cnt;
            auto left = n - prev;
            if (val == 1) {gcd_cnt[1] += cnt * (cnt-1 ) / 2 + cnt * left; continue;}

            gcd_cnt[val] += cnt * (cnt-1 ) / 2;
            set<int> vis;
            for (auto f: prime_factors[val]) {
                for (int i=(val/f+1)*f; i<=mx; i+=f) {
                    if (!vis.count(i) && num_cnt.count(i)) {
                        vis.insert(i);
                        gcd_cnt[gcd(val, i)] += cnt * num_cnt[i];
                        left -= num_cnt[i];
                    }
                }
            }
            if (left)gcd_cnt[1] += left * cnt;
        }
        
        set<pair<long long, int>> sort_gcd; long long pres = 0;
        for (auto[val, cnt]: gcd_cnt) {
            pres += cnt;
            sort_gcd.emplace(pres, val);
        }
        vector<int> ans;
        for (auto& q:queries) {
            ans.push_back(sort_gcd.upper_bound({q, INT_MAX})->second);
        }
        return ans;
    }

    vector<int> gcdValues2(vector<int>& nums, vector<long long>& queries) {
        // 参考题解
        // 对于 i 来说 cnt[i] = c*(c-1)/2 - cnt[2i] - cnt[3i] ...
        int mx = ranges::max(nums);
        vector<int> num_cnt(mx+1); 
        vector<long long> gcd_cnt(mx+1);
        
        for (auto v: nums) num_cnt[v]++;
        
        for (int i = mx; i>0; --i) {
            int cnt = 0;

            for (int j=i; j<=mx; j+=i) {
                cnt += num_cnt[j];
                gcd_cnt[i] -= gcd_cnt[j];
            }
            gcd_cnt[i] += 1L * cnt * (cnt-1) / 2;
        }
        
        // set<pair<long long, int>> sort_gcd; long long pres = 0;
        // for (int i=1; i<=mx; ++i) {
        //     pres += gcd_cnt[i];
        //     sort_gcd.emplace(pres, i);
        // }
        // vector<int> ans;
        // for (auto& q:queries) {
        //     ans.push_back(sort_gcd.upper_bound({q, INT_MAX})->second);
        // }
        
        // 另一种写法
        partial_sum(gcd_cnt.begin(), gcd_cnt.end(), gcd_cnt.begin());

        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            ans[i] = ranges::upper_bound(gcd_cnt, queries[i]) - gcd_cnt.begin();
        }
        return ans;
    } 

};

int main() {
    vector<int> nums = {2,3,4};
    vector<long long> queries = {0,2,2};
    Solution().gcdValues2(nums, queries);
}
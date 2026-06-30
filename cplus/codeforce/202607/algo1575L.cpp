#include <bits/stdc++.h>
using namespace std;


// 同力扣 3920
class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        auto longestPairChain = [&](vector<vector<int>>& pairArr) -> int {
            if (pairArr.size() == 0) return 0;
            sort(pairArr.begin(), pairArr.end(), [](const auto& e1, const auto& e2) {
                return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);  // 两个维度排序
            });

            vector<int> dp;

            for (auto& env : pairArr) {
                // auto it = ranges::upper_bound(dp, env[1]);
                auto it = upper_bound(dp.begin(), dp.end(), env[1]);
                if (it == dp.end()) dp.push_back(env[1]);
                else *it = env[1];

            }
            return dp.size();
        };

        vector<vector<int>> ans;
        int n = nums.size();
        for (int i=0; i<n; i++) {
            auto v = nums[i]; 
            if (v <= i + 1) {
                ans.push_back({v, i + 1 -v});
            }
        }

        return longestPairChain(ans);
    }
};

int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    cout << Solution().maxFixedPoints(nums) << endl;
    return 0;
}


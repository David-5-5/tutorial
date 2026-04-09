#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> numsGame(vector<int>& nums) {
        // 核心在变换，另 a_0 = x，则修改次数为
        // |a_0 - x| + |a_1 - (x+1)| + ... + |a_n-1 - (x+n-1)|
        // 另 b_i = a_i - i
        // |b_0 - x| + |b_i - x| + ... + |b_i - x| 将 b_i 统一变更为 x 的最小修改次数
        // 使用中位数贪心，建立对顶堆，记录中位数，并记录两个堆中元素的和
        
        // 大根堆的最大元素为中位数，大根堆的数量最多比小根堆多 1 个
        const int mod = 1e9 + 7;
        priority_queue< long long> left;                                    // 大根
        priority_queue< long long, vector< long long>, greater<>> right;    // 小根

        long long sum_l = 0, sum_r = 0; int n = nums.size(); 
        
        vector<int> ans;
        for (int i = 0; i<n; ++i) {
            auto b = nums[i] - i;
            left.emplace(b); sum_l += b;
            if (left.size() > right.size() + 1) {
                auto val = left.top(); left.pop();
                sum_l -= val; sum_r += val;
                right.emplace(val);
            } else if (right.size() && left.top() > right.top()) {
                auto l_val = left.top(); left.pop();
                auto r_val = right.top(); right.pop();
                sum_l += r_val - l_val; sum_r += l_val - r_val;
                left.emplace(r_val); right.emplace(l_val);
            }
            auto median = left.top();

            ans.push_back(((left.size()>right.size()?median:0) + sum_r - sum_l) % mod );

        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 最小字典序
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        // 自行解答 - 性能不好
        vector<int> ans; // 遍历 nums 过程中保持单调递增
        // 记录从 ans 出栈后ans的高度，后续需要插入到ans中
        stack<pair<int,int>> st;

        for (auto v : nums) {
            while (ans.size() && ans.back() > v) {
                int val = ans.back();
                ans.pop_back();
                st.push({ans.size(), val});
            }
            ans.push_back(v);
        }

        int sup = k - ans.size();
        for (int i=0; i<sup; ++i) {
            auto [inx, val] = st.top();
            st.pop();
            ans.insert(ans.begin()+inx, val);
        }

        ans.resize(k);

        return ans;
    }

    vector<int> mostCompetitive2(vector<int>& nums, int k) {
        // 参考题解
        vector<int> ans; // 遍历 nums 过程中保持单调递增
        int n = nums.size();

        for (int i=0; i<n; ++i) {
            // 仅需判断后续的元素个数 > k 就可以出栈了，即 ans.size() + n - i > k
            while (ans.size() && ans.back() > nums[i] && ans.size() + n - i > k) {
                ans.pop_back();
            }
            if (ans.size() < k) ans.push_back(nums[i]);
        }

        return ans;
    }
};
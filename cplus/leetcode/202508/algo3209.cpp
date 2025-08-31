#include <bits/stdc++.h>
using namespace std;

// 位运算 - AND/OR LogTrick
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        // 2025.8 复习
        vector<int> _and; long long ans = 0;
        for (auto & num: nums) {
            // 倒序 符号优先级
            for (int i=_and.size()-1; i>=0; --i)  {
                if (_and[i] == (_and[i] & num)) break;
                else _and[i] &= num;
            }
            _and.push_back(num);
            ans += ranges::upper_bound(_and, k) - ranges::lower_bound(_and, k);
        }
        return ans;

        // 另一种写法
        // int n = nums.size();
        // vector<int> _and(n); long long ans = 0;
        // for (int i = 0; i<n; ++i) {
        //     // 倒序 符号优先级
        //     for (int j=i-1; j>=0; --j)  {
        //         if (_and[j] == (_and[j] & nums[i])) break;
        //         else _and[j] &= nums[i];
        //     }
        //     _and[i]= nums[i];
        //     // 在区间内查找
        //     ans += ranges::upper_bound(_and.begin(), _and.begin()+i+1, k) - 
        //         ranges::lower_bound(_and.begin(), _and.begin()+i+1, k);
        // }
        // return ans;

    }
};

int main() {
    vector<int> nums = {1,9,9,7,4};
    cout << Solution().countSubarrays(nums, 1) << endl;
}
#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        // 参考题解, 排序后nums[0] 一定属于 lower[0]
        // [1..n]区间枚举 i，找到匹配 lower[0] 的 nums[i] == upper[0] 以确定 k, arr[0]
        // 通过双指针遍历后续的元素的最小未使用的元素 nums[left] + 2k == upper[right] 
        // 找到所用的 lower/upper 对，其数量为 nums.size() / 2

        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for (int i=1; i<n; i++) {
            if (nums[0] == nums[i] || (nums[i]-nums[0]) % 2) continue;

            int k = (nums[i] - nums[0]) / 2;

            vector<bool> used(n);
            vector<int> ans;
            used[0] = used[i] = true;
            ans.push_back(nums[0]+ k);

            int left = 0, right = 0;
            while (left< n && right < n) {
                while (left < n && used[left]) left++;
                while (right < n && (used[right] || nums[left]+2*k != nums[right])) right ++;

                if (left == n || right == n) break;
                
                used[left] = used[right] = true;
                ans.push_back(nums[left]+k);
            }
            
            if (ans.size() == n / 2 ) {
                for (auto v : ans) cout << v << "";
                cout << endl;
                return ans;
            }
        }
        return {};
        
    }
};


int main() {
    vector<int> nums = {5,435};
    vector<int> ans = Solution().recoverArray(nums);
    for (auto v : ans) cout << v << "";
    cout << endl;
    return 0;
}
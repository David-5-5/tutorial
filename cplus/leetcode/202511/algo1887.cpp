#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        // 自行解答，使用 map
        map<int, int> cnt;
        for (auto& v : nums) cnt[v] ++;
        int ans = 0, d = 0;
        for (auto& [_, freq]: cnt)  {
            ans += freq * d++;
        }
        return ans;
    }

    int reductionOperations2(vector<int>& nums) {
        // 自行解答，使用 分组循环模板
        map<int, int> cnt;
        sort(nums.begin(), nums.end());

        int ans = 0, i = 0, g = 0, n = nums.size();
        while (i < n) {
            int j = i;
            while (i<n && nums[j] == nums[i]) {
                ans += g;
                i++;
            }
            g++;
        }
        return ans;
    }

};
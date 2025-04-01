#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        // 自行解答 2000分
        int n = nums.size();
        
        // 前后缀分解前缀为长度为 f 的子数组的最大值，后缀为长度为 s 的子数组最大值
        auto cal = [&] (int f, int s) -> int {
            int i = 0;
            vector<int> suf(n-s+1);
            suf[n-s] = accumulate(nums.begin()+n-s, nums.end(), 0);
            int mx = suf[n-s];
            for (int i=n-s-1; i>=0; --i) {
                mx += nums[i] - nums[i+s];
                suf[i] = max(mx, suf[i+1]);
            }
            // for (auto& v:suf) cout << v << ",";
            cout << endl;
            mx = accumulate(nums.begin(), nums.begin()+f, 0);
            int pres = mx;
            int ans = mx + suf[f];
            for (int i=f; i<n-s; i++) {
                pres += nums[i] - nums[i-f];
                mx = max(mx, pres);
                ans = max(ans, mx + suf[i+1]);
            }
            
            return ans;
        };

        // 计算前后缀的最大和，前后缀的长度交替为 firstLen, secondLen
        return max(cal(firstLen, secondLen), cal(secondLen, firstLen));
    }
};
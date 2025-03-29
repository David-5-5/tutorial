#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        
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

        return max(cal(firstLen, secondLen), cal(secondLen, firstLen));
    }
};
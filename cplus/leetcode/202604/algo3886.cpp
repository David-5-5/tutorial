#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        // 自行解答
        int n = nums.size(), ans = 0;
        
        for (int k=1; k<=n; k++) {
            if (n % k) continue;
            auto seg = n / k;   // 分 seg 段
            bool satified = true;
            auto p_mx = 0;
            for (int i=0; i<seg; ++i) {
                auto mx = nums[i*k], mn = nums[i*k], cnt = 0;
                for (int j=0; j<k; j++) {
                    mx = max(mx, nums[i*k+j]), mn = min(mn, nums[i*k+j]);
                    if (nums[i*k+j] > nums[i*k+(j+1)% k]) cnt ++;   // 关键的坑，循环的位置
                    if (cnt > 1) {satified = false; break;}
                }

                if (mn < p_mx || !satified) {satified = false; break;}
                p_mx = mx;
            }
            if (satified) ans += k;
        }

        return ans;
    }
};
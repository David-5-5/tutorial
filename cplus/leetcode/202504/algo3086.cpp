#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.3 距离和
class Solution {
public:
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {

        int n = nums.size();
        vector<long> pres(n+1), predis(n+1);

        for (int i=0; i<n; i++) {
            pres[i+1] = pres[i] + nums[i];
            predis[i+1] = predis[i] + nums[i] * i;
        }

        // jb, je 区间的距离值
        auto distance = [&] (int i, int jb, int je) -> long {
            return predis[je+1] + predis[jb] - predis[i] - predis[i+1] + 
                i * (pres[i]+pres[i+1] - pres[jb] - pres[je+1]);
        };

        // 二分查找最小的半径，开区间写法
        auto radius = [&](int i, int target) -> int {
            int l = -1, r=max(n-i-1, i);
            while (l + 1 < r) {
                int  m = l + (r - l) / 2;
                if (pres[min(n, i+m+1)] - pres[max(0, i-m)] < target){
                    l = m;      // 扩大半径
                } else {
                    r = m;      // 减少半径
                }                
            }
            return r;
        };
        
        long ans = LONG_MAX;
        for (int i=0; i<n; i++) {
            // 枚举 aliceIndex
            long res = 0;
            int cnt1 = pres[min(n, i+2)] - pres[max(0, i-1)], rem = k;
            if (cnt1 < rem) {
                int t = min(maxChanges, k - cnt1);
                res += 2 * t, rem -= t;
            }
            int r = radius(i, rem);
            res += distance(i, max(0, i-r), min(n-1, i+r));
            // cout << i << ", rem=" << rem << ", r=" << r << ", res=" << res << endl;
            ans = min(ans, res);
        }

        return ans;      
        
    }
};
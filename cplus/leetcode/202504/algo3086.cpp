#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.3 距离和
class Solution {
public:
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
        // 自行思考
        // 思路，实质上就是距离和，枚举以每个索引为 aliceIndex, 
        // 在应 O(1) 时间计算出所需行动次数的最小值
        // 1. 区间的 1 数量应该为 k - maxChange <= x <= k
        // 2. 区间中 j nums[j] = 1, |j - aliceIndex|为操作次数
        // 3. 所有满足条件的 j 的最小的操作次数之和的最小值
        // 4. 使用 maxChange 的得到 1 的次数固定为 2, 对于|j - aliceIndex|>2的，
        //    可优先使用maxChange，越大于 2
        // 确定 边界的情况下 j_b <= aliceIndex <= j_e
        // 最短的距离为：
        // pred[je+1] + pred[jb] - (pred[aliceIndex] - pred[aliceIndex+1])
        // + i(pres[i]+pres[i+1]-pres[jb]-pres[je+1])
        // pres 为 nums[i] 的前缀和，统计区间内的 1 的数量
        // pred 为 nums[j] * j 的前缀和，统计区间内的距离和

        // 参考题解：
        // 1，如何确定 jb 及 je，二分查找最小的 d 满足 [aliceIndex-d, aliceIndex+d] 
        //    区间内的1的数量为 k - maxChanges
        // 2, 当 sum(nums[aliceIndex-1] .. nums[aliceIndex+1]) < k 时不使用 maxChanges
        //    否则优先使用 maxChanges，res += 2 * t
        //    其中 t = min(maxChanges, sum(nums[aliceIndex-1] .. nums[aliceIndex+1])-k)
        
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
            ans = min(ans, res);
        }

        return ans;      
        
    }

    long long minimumMoves2(vector<int>& nums, int k, int maxChanges) {
        // 参考题解 分类讨论
        // 1 - c + maxmaxChanges <= k
        // 2 - c + maxmaxChanges > k 滑动窗口 (k - maxChanges) 中位数的货舱选址问题

        vector<int> pos; int n = nums.size();
        int c = 0;
        for (int i=0; i<n; ++i) {
            if (nums[i] == 0) continue;
            pos.emplace_back(i);
            // 计算连续的 1，因此 nums[i] == 1
            if (c < 3) { // 不起眼的地方最大限度节省时间
                int res = nums[i];
                if (i-1>=0) res += nums[i-1];
                if (i+1<n) res += nums[i+1];
                c = max(c, res);
            }
        }

        if (c + maxChanges >= k) {
            return max(0, min(c, k)-1) + max(0, k-c) * 2;
        }

        int m = pos.size(); vector<long long> pres(m+1);
        for (int i=0; i<m; ++i) pres[i+1] = pres[i] + pos[i];

        long long ans = LLONG_MAX;
        // 中位数进行货舱选址，并通过前缀和计算距离和
        // 货舱选择算法，正好 aliceIndex = mid 时，距离为 0，即行动次数为 0
        for (int r=k-maxChanges; r<=m; ++r) {
            auto l = r - k + maxChanges; // [l, r)
            auto mid = (r + l) / 2;
            ans = min(ans, (1LL * pos[mid]*(mid-l+1)-(pres[mid+1]-pres[l])) + 
                pres[r] - pres[mid] - 1LL * pos[mid]*(r-mid));
        }

        return ans + 2 * maxChanges; 
    }
    
};
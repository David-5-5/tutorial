#include <bits/stdc++.h>
using namespace std;

// 位运算 - GCD LogTrick
class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        // 自行解答
        int n = nums.size(); 
        // first: gcd value, second:cnt of gcd
        vector<pair<int,int>> gcds;
        long long ans = 0;

        // 计算从 r 开始向左查找可以需要乘二的数量
        auto double_cnt = [&](int val, int r, int len) -> long {
            int pow2 = 1;
            while (val % 2 == 0) {
                pow2 *= 2; val /= 2;
            }
            pow2 *= 2;  // 乘以查看 nums[i] 是否包括 2
            long ret = 0, left = k;
            for (int i = r; i>r-len; --i) {
                if (nums[i] % pow2) {   // 不包含 2，需要使用一次
                    if (left) left --;
                    else break;
                }
                ret ++;
            }
            return ret;
        };

        for (int i=0; i<n; i++) {
            for (int j=gcds.size()-1; j>=0; --j) {
                gcds[j].first = gcd(gcds[j].first, nums[i]);
            }
            gcds.emplace_back(nums[i], 1);
            
            // 合并相同的 gcd val, 其频率 +
            vector<pair<int,int>> result;
            result.push_back(gcds[0]);
            for (int i=1; i<gcds.size(); ++i)  {
                if(gcds[i].first == result.back().first)
                    result.back().second += gcds[i].second;
                else result.push_back(gcds[i]);
            }
            gcds = move(result);

            long long cnt = 0;
            for (int j=gcds.size()-1; j>=0; --j) {
                cnt += gcds[j].second;                
                if (cnt <= k) ans = max(ans, 2 * cnt * gcds[j].first);
                else {
                    ans = max(ans, cnt * gcds[j].first);
                    if (2 * cnt * gcds[j].first > ans)
                        ans = max(ans, (long long) gcds[j].first * 2 *
                                    double_cnt(gcds[j].first, i, cnt) );
                }
            }
        }
        return ans;
    }
};;
#include <bits/stdc++.h>
using namespace std;

// compare to 1049
class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        // 参考题解 折半查找
        int n = nums.size() / 2;
        int ans = INT_MAX;
        vector<int> v1[16], v2[16];

        /**
         * 把 nums 的前 n 个数分成两个数组，数组中元素数量可以不同。记 s1 为第一个数组的和，
         * s2 为第二个数组的和，请算出一个列表 v1[i] 表示 nums 中前 n 个数有 i 个被划分到
         * 第一个数组的情况下，(s1−s2) 有哪些可能的值
         */
        auto f = [&](int begin, vector<int>* v) {
            // 组合技巧
            // (1<<n) i 中二进制第 j 位为 1 的数表示 nums[j] 属于第一组
            for (int i=0; i<(1<<n); i++) {
                // sm s1-s2 , cnt s1 中 数的数量
                int sm = 0, cnt = 0;
                for (int j=0; j<n; j++) {
                    if (i>>j & 1) {
                        sm += nums[begin+j]; cnt+=1;
                    } else sm -= nums[begin+j];
                }
                v[cnt].push_back(sm);
            }

            for (int i=0; i<=n; i++) 
                sort(v[i].begin(), v[i].end());
        };

        f(0, v1); f(n, v2);

        // for (int i=0; i<=n; i++) {
        //     for (int j=0; j<v1[i].size(); j++) 
        //         cout << v1[i][j] << ",";
        //     cout << endl;
        // }

        /**
         * 合并答案时，我们只需要枚举 v1[i] 中的每个数 x，然后检查 v2[n - i] 中哪个数 y 加上
         * 去最有可能最小化 ∣x+y∣。我们将 v1[i] 与 v2[n - i] 从小到大排序，利用 two pointers
         * 或二分的方法求出对于 v1[i] 中的每个数 v1[i][j]，满足 k 最小且 v1[i][j] + v2[n - i][k] >= 0
         * 的 k，那么只有 abs(v2[n - i][k - 1]) 和 abs(v2[n - i][k]) 才有可能成为答案。
         */
        // for (int i=0; i<=n; i++) {
        //     for (int j=0; j<v1[i].size(); j++) {
        //         // 二分实现
        //         int k = ranges::lower_bound(v2[n-i], -v1[i][j]) - v2[n-i].begin();
        //         if (k< v2[n-i].size()) ans = min(ans, abs(v1[i][j]+v2[n-i][k]));
        //         if (k > 0) ans = min(ans, abs(v1[i][j]+v2[n-i][k-1]));
        //     }
        // }

        for (int i=0; i<=n; i++) {
            for (int j=v1[i].size()-1, k=0; j>=0; j--) {
                // 双指针
                while (k<v2[n-i].size() && v1[i][j]+v2[n-i][k]<0) k++;
                if (k< v2[n-i].size()) ans = min(ans, abs(v1[i][j]+v2[n-i][k]));
                if (k > 0) ans = min(ans, abs(v1[i][j]+v2[n-i][k-1]));
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {1,2};
    cout << Solution().minimumDifference(nums);
}
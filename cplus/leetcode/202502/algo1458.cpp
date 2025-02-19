#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列  (LCS)
class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int m = nums1.size(), n = nums2.size();

        vector<vector<int>> memo(m, vector<int>(n, INT_MIN));

        function<int(int, int)> dfs = [&] (int i, int j) -> int {
        // auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i < 0 || j < 0) 
                return INT_MIN / 2;

            auto& res = memo[i][j];
            if (res > INT_MIN) return res;

            int v = nums1[i] * nums2[j];
            res = max({v, v+dfs(i-1,j-1), dfs(i, j-1), dfs(i-1, j)}); // 必须有一个写法
            return res;

        };

        return dfs(m-1, n-1);
    }
};

int main() {
    vector<int> nums1 = {-1,-1}, nums2 = {1, 1};
    cout << Solution().maxDotProduct(nums1, nums2) << endl;
}
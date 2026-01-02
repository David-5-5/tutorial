#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 杂项 - §7.1 回文数
class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        // 自行解答
        int h = intLength / 2, mid = intLength % 2;
        int base = h?lround(pow(10, h-1)):0; int cnt = h?base * 9 * (mid?10:1):9;

        int n = queries.size(); vector<long long> ans(n, -1);
        for (int i=0; i<n; ++i) {
            if (queries[i] > cnt) continue;
            int ord = queries[i], m = 0;

            // 个位数从 1 开始，其他从 10 开始 m 也是从 0 开始
            if (h) ord --;  
            if (mid) m = ord % 10, ord /= 10;   // m 奇数回文的中间数字，从 0 开始
            ord += base;
            if (mid) ans[i] = ord * 10 + m;
            else ans[i] = ord;
            while (ord) {
                ans[i] = ans[i] * 10 + ord % 10;
                ord /= 10;
            }
        }
        return ans;   
    }
};

int main() {
    vector<int> quereis = {1,2,3,4,5,90};
    vector<long long> ans = Solution().kthPalindrome(quereis, 3);
}
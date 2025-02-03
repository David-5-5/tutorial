#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最大子数组和
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        // 自行解答 参考 918
        int mod = 1e9 + 7;
        int n = arr.size();
        int tot = accumulate(arr.begin(), arr.end(), 0);

        int cur_max = 0, cur_min = 0;
        int ans_max = 0, ans_min = 0;


        for (int i=0; i < n; i++) {
            cur_max = max(cur_max, 0) + arr[i]; // 至少包含一个元素
            ans_max = max(ans_max, cur_max);
            
            cur_min = min(cur_min, 0) + arr[i];
            ans_min = min(cur_min, ans_min);
        }
        if (k == 1) return ans_max;
        return max((long long)tot*(k-1) + ans_max, (long long)max((long long)tot*k, (long long) max(ans_max,tot-ans_min))) % mod;
    }
};

int main() {
    // vector<int> arr = {-5,-2,0,0,3,9,-2,-5,4};
    vector<int> arr = {-1,-2};
    cout << Solution().kConcatenationMaxSum(arr, 7);

}
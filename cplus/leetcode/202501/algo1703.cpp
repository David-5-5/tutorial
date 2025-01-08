#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 中位数贪心
class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        // 参考题解
        // nums 中包含 m 个 1，pi 表示第 i 个 1 的位置
        // 假定 pi，pi+1，pi+k-1 共 k 个 1 移动到
        // 位置 q, q+1，q+2,..., q+k-1 k个位置上的最小值
        // sum |pj - (q+j-i) |  (i<=j<k) 的最大值
        // = sum |(pj-j) - (q-i)| 
        // q-i 取 pj-j 的中位数 能取得最小值
        vector<int> p_v;
        int count  = 0;
        for (int i=0; i <nums.size(); i++) 
            if (nums[i]) p_v.push_back(i-(count++));
        cout << p_v.size() << endl;
        // p_v 的前缀和
        int pres[p_v.size() + 1];
        pres[0] = 0;

        partial_sum(p_v.begin(), p_v.end(), pres + 1);

        int ans = INT_MAX;
        for (int i=0; i<p_v.size()-k+1; i++) {
            int mid = i + k / 2;
            // 化简 sum |(pj-j) - (q-i)| 遍历 i 通过前缀和找出移动的最小值
            ans = min(ans, p_v[mid]*(1-k%2)+pres[k+i]-pres[mid+1]-(pres[mid]-pres[i]));
        }
        return ans;
    }
};
#include <bits/stdc++.h>
using namespace std;

// 周赛 382
class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        // 参考题解，按从高位计算
        // 相邻项合并 -> 子数组 -> 每段是合并为 0 的长度 - 1
        // 计算低位时，需要同时带上高位进行计算，忽略掉无法消除的位
        int ans = 0, mask = 0; 
        for (int b=29; b>=0; b--){
            int cnt = 0, and_res = -1; // 各位全为 1
            for (auto x : nums) {
                mask |= 1 << b;
                and_res &= x & mask;
                if (and_res) 
                    cnt += 1; // 合并
                else and_res = -1; // and_res, 开始新的一段子数组
                // 由于 k < nums.size() 无需判断最后是否 and_res 不等于 0
                // 当nums所有项都无法AND为0时，cnt > k 必定成立
            }
            if (cnt > k) {
                ans |= 1 << b;    // 该位无法消除，加入ans
                mask ^= 1 << b;   // the bit of mask set to 0, ignore it
            }
        }
        return ans;

    }

    int minOrAfterOperations_org(vector<int>& nums, int k) {
        // int mx = ranges::max(nums);
        // 总结：遇到不好写的代码，一定是知识点没有掌握
        // 相邻项与运算并删除
        int bits = 5;

        // 按位合并项，并删除 --> 死胡同
        auto to_and = [&](int b) -> int {
            int n = nums.size();
            if (k == 0) return 0;
            int cnt = 0, first = -1;
            for (int i=0; i<n; i++) {
                if (nums[i] >> b & 1) cnt += 1;
                else if (first == -1) first = i;
            }
            if (cnt == 0 || cnt > k) return 0;

            vector<int> tmp;
            if (first > 0) {
                for (int i=0; i<first; i++) {
                    nums[first] &= nums[i];
                }
            }
            tmp.push_back(nums[first]);
            for (int i=first+1; i<n; i++) {
                if (nums[i] >> b & 1) 
                    if (i+1 >= n || nums[i+1]>>b & 1) tmp.back() &= nums[i];
                    else{
                        int a = (nums[i+1] & nums[i])|tmp.back();
                        int b = nums[i+1]|(nums[i]&tmp.back());
                        if (a < b)
                            nums[i+1] &= nums[i];
                        else tmp.back() &= nums[i];
                    }
                else tmp.push_back(nums[i]);
            }
            nums = tmp;
            return cnt;
        };

        for (int b=bits; b>=0; b--)  k -= to_and(b);

        int ans = 0;
        for (auto v : nums) ans |= v;
        return ans;
    }


};

int main() {
    Solution sol;
    // vector<int> nums = {37,6,46,32,23};
    vector<int> nums = {7,3,15,14,2,8};
    cout << sol.minOrAfterOperations(nums, 4);
}
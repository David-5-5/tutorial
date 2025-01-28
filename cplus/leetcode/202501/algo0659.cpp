#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // 参考题解 贪心：出现一个数字后x，进来加在x-1为结尾的子序列后面
        //               若无x-1为结尾的子序列，检查是否创建一个x+2为结尾的一个新子序列
        //                (这个贪心策略没看出来)
        // 由于 数据范围是 -1000 ~ 1000 创建数组代替哈希表
        vector<int> cnt(2004); // x 出现的数量 x + 1000, 
        vector<int> seq(2004); // x 为结尾的子序列数量

        for (auto x: nums) cnt[x+1000] += 1;
        for (auto x: nums) {
            x += 1000;
            if (cnt[x] == 0) continue; // 已经被使用了

            if (x>0 && seq[x-1]) {seq[x-1] --; seq[x] ++; cnt[x]--;}
            else {
                if (cnt[x+1] && cnt[x+2]){
                    seq[x+2] ++; cnt[x]--; cnt[x+1]--; cnt[x+2]--;}
                else return false;
            }
        }

        return true;
    }
};
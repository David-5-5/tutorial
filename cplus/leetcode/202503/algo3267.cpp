#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int countPairs(vector<int>& nums) {
        // 参考题解 实质上解题思路和 3265 一样，但是总觉得 n(logU)^4 会超时，没敢做下去
        // 本题在 3265 做一次变更，需要注意的是两次变换的情况下，会出现重复的数字因此
        // 每次元素的交换定义一个集合，将变化后的数据加入集合中，最后在根据集合中的值，统计次数
        unordered_map<int, int> cnt;
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (auto v:nums) {
            unordered_set<int> trans;                   // 定义结合，存储交换后的值
            trans.insert(v);
            string sv = to_string(v);                   // 排序后不需要补齐
            for (int i=1; i<sv.length(); i++) for (int j=0; j<i; j++) {         // 7 ** 2
                if (sv[i] != sv[j]) {
                    swap(sv[i], sv[j]);             // 使用内置函数完成交换
                    trans.insert(stoi(sv));           // 使用更安全的 stoi
                    for (int ii=1; ii<sv.length(); ii++) for (int jj=0; jj<ii; jj++) {
                        if (sv[ii] != sv[jj]) {
                            swap(sv[ii], sv[jj]);             // 使用内置函数完成交换
                            trans.insert(stoi(sv));           // 使用更安全的 stoi
                            swap(sv[ii], sv[jj]);             // 恢复现场
                        }
                    }
                    swap(sv[i], sv[j]);             // 恢复现场
                }
            }
            for (auto& t:trans) ans += cnt[t];      // 最后根据交换后的值统计相等的计数

            cnt[v] ++;
        }
        return ans; 
    }        
    
};
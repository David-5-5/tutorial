#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
// 3267 中等难度版本
class Solution {
public:
    int countPairs(vector<int>& nums) {
        // 自行解答，觉得代码写的特别烂
        unordered_map<int, int> cnt;
        int ans = 0;
        for (auto v:nums) {
            ans += cnt[v];
            string sv = "0000000" + to_string(v);
            for (int i=1; i<sv.length(); i++) {
                for (int j=0; j<i; j++) {
                    if (sv[i] != sv[j]) {
                        string nv = sv;
                        nv[i] = sv[j];
                        nv[j] = sv[i];
                        ans += cnt[atoi(nv.c_str())];
                    }
                }
            }

            cnt[v] ++;
        }
        return ans;    
    }


    int countPairs2(vector<int>& nums) {
        // 自行解答, 优化后的代码，觉得漂亮多了
        // 时间复杂度分析 O(n*m^2)  n 数组长度 m 为数组中值的数位长度
        unordered_map<int, int> cnt;
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (auto v:nums) {
            ans += cnt[v];
            // string sv = format("{:0>7}", to_string(v)); // 补齐到固定长度
            string sv = to_string(v);                   // 排序后不需要补齐
            for (int i=1; i<sv.length(); i++) {         // 7 ** 2
                for (int j=0; j<i; j++) {
                    if (sv[i] != sv[j]) {
                        swap(sv[i], sv[j]);             // 使用内置函数完成交换
                        ans += cnt[stoi(sv)];           // 使用更安全的 stoi
                        swap(sv[i], sv[j]);             // 恢复现场！！！
                    }
                }
            }

            cnt[v] ++;
        }
        return ans; 
    }
};
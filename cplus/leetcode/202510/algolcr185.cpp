#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 概率期望
class Solution {
private:
    // 计算n的阶乘（n!）
    long long factorial(int n) {
        long long res = 1;
        for (int i = 2; i <= n; ++i) {
            res *= i;
        }
        return res;
    }    
public:
    vector<double> statisticsProbability(int num) {
        // Translate from python by doubao
        if (num <= 0) return {};
        
        // 计算阶乘和分母（6^num）
        long long fact = factorial(num);
        long long deno = 1;
        for (int i = 0; i < num; ++i) deno *= 6;
        
        // 结果数组：索引对应 (总和 - num)，范围 [0, 5*num]
        int resSize = 5 * num + 1;
        vector<double> result(resSize, 0.0);
        
        // 生成所有允许重复的组合（非降序，模拟 combinations_with_replacement）
        vector<int> combo(num, 1);  // 初始组合：全为1
        while (true) {
            // 计算当前组合的总和及各数字出现次数
            int sum = 0;
            vector<int> cnt(7, 0);  // 索引1-6对应骰子点数
            for (int n : combo) {
                sum += n;
                cnt[n]++;
            }
            
            // 计算排列数：fact / (各点数出现次数的阶乘乘积)
            long long perm = fact;
            for (int i = 1; i <= 6; ++i) {
                if (cnt[i] > 0) {
                    perm /= factorial(cnt[i]);
                }
            }
            
            // 累加概率到对应位置
            result[sum - num] += (double)perm / deno;
            
            // 生成下一个组合（非降序，确保不重复）
            int pos = num - 1;
            while (pos >= 0 && combo[pos] == 6) {
                pos--;  // 找到可递增的位置
            }
            if (pos < 0) break;  // 所有组合生成完毕
            
            combo[pos]++;  // 当前位置递增
            // 后续位置设为当前位置的值（保持非降序）
            for (int i = pos + 1; i < num; ++i) {
                combo[i] = combo[pos];
            }
        }
        
        return result;        
    }
};
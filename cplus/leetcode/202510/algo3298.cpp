#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 不定长滑动窗口 2.3.2 越长越合法
class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        // translated from python bu doubao 
        unordered_map<char, int> cnt2;
        for (char ch : word2) {
            cnt2[ch]++;
        }
        
        // 统计当前窗口中word1字符的出现次数
        unordered_map<char, int> cnt1;
        int l = 0;
        long long ans = 0;
        
        // 判断当前窗口是否包含word2的所有字符（保持Python原逻辑）
        auto contain = [&]() -> bool {
            for (auto& [k, v] : cnt2) {
                if (cnt1[k] < v) {
                    return false;
                }
            }
            return true;
        };
        
        for (char ch : word1) {
            cnt1[ch]++;
            bool cur = true;
            // 保持原Python的循环条件和逻辑
            while (cur && contain()) {
                char left_ch = word1[l];
                cnt1[left_ch]--;
                // 判断当前左边界字符是否仍满足数量要求
                cur = (cnt1[left_ch] >= cnt2[left_ch]);
                l++;
            }
            ans += l;
        }
        
        return ans;
    }

    long long validSubstringCount2(string word1, string word2) {
        // translated from python bu doubao 
        unordered_map<char, int> cnt2;
        for (char ch : word2) {
            cnt2[ch]++;
        }
        
        unordered_map<char, int> cnt1;
        int l = 0;
        long long ans = 0;
        int match2 = 0;
        int len_word2 = word2.size();
        
        for (char ch : word1) {
            cnt1[ch]++;
            // 只有当当前计数仍小于等于目标计数时，才增加匹配数
            if (cnt1[ch] <= cnt2[ch]) {
                match2++;
            }
            
            // 当匹配数达到word2长度时，尝试收缩左边界
            while (match2 == len_word2) {
                char left_ch = word1[l];
                cnt1[left_ch]--;
                // 如果收缩后计数小于目标，减少匹配数
                if (cnt1[left_ch] < cnt2[left_ch]) {
                    match2--;
                }
                l++;
            }
            
            // 累加有效子字符串数量
            ans += l;
        }
        
        return ans;
    }

};
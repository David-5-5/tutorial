#include <bits/stdc++.h>
using namespace std;

// 双周赛 140
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        // 参考题解 字符串匹配 前后缀分解
        int n = word1.size(), m = word2.size();
        
        // 后缀匹配 suf[i] 表示 word1[i] 匹配 word2[suf[i]]
        // suf[i] = 0 word1 匹配 word2 中 所有 个字符
        // suf[i] = m word1 匹配 word2 中 0 个字符
        vector<int> suf(n+1, m); // 长度为 n+1, 初始值为 m
        int inx = m; // inx 指向当前比较的 word2 字符的下一个
        for (int i=n-1; i>=0; i--) {
            if (inx && word1[i] == word2[inx-1]) inx--;
            suf[i] = inx;
        }

        // 前缀字符匹配和修改字符的枚举同时进行
        // 要求最小的下标序列的字典序，因此贪心的策略
        // 如果字符相同不需要修改
        // 满足条件时，即前缀匹配数量 + 后缀匹配数量 + 1 = word2 长度，则修改
        bool modified = false;
        vector<int> ans; // 修改前，ans 的长度即前缀匹配数量
        inx = 0; // 指向 word2
        for (int i=0; i<n; i++) {
            if (ans.size() == m) break;
            if (word1[i] == word2[inx]) {
                ans.push_back(i);
                inx++;
            } else if (!modified && ans.size()+1 >= suf[i+1]) {
                // ans.size() 是无符号数，ans.size()+1-suf[i+1] >= 0 将转换为无符号整数
                // ans.size()+1-suf[i+1] >= 0 恒为 true
                ans.push_back(i);
                modified = true;
                inx++;
            }
        }

        // for(auto v : ans) cout << v;
        if (inx == m) return ans;
        else return vector<int>();
    }
};


int main() {
    Solution sol;
    sol.validSequence("bacdc", "abc");
}
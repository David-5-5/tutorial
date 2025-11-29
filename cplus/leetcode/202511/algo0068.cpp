#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
// 2025.11.22 复习
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        // 自行解答
        int i = 0, n = words.size(); vector<string> ans;
        while (i < n) {
            
            int st = i, charLen = words[i].length();
            i ++;
            while (i<n && charLen + words[i].length() < maxWidth)  // 不加等于，正好隐含把空格加上
                charLen += 1 + words[i++].length();
            int spaces = maxWidth - charLen + (i - st - 1);
            // 平均分配空格，左边比 space + (i - j - 1) / (i - j) 随着 j 增大， (i - j - 1)越来越小
            string line = words[st];
            for (int j=st+1; j<i; ++j) {
                int sp =  i==n?1:(spaces + i - j - 1) / (i-j);
                line += string(sp,' ') + words[j];
                spaces -= sp;
            }
            if (spaces) line += string(spaces, ' '); // 只有一个单词的情况
            ans.push_back(line);
        }

        return ans;
    }
};
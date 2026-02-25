#include <bits/stdc++.h>
using namespace std;

// 二、字符串 Z 函数（后缀的前缀）
// 三、字符串贪心 3.1 字典序最小/最大
class Solution {
public:
    string generateString(string str1, string str2) {
        // 自行解答 难度分 2605
        // z 函数 模板
        auto zFunc = [&](string& text) -> vector<int> {
            int t_len = (int)text.length();
            vector<int> ans(t_len);
            for (int i = 1, l = 0, r = 0; i < t_len; ++i) {
                if (i <= r && ans[i - l] < r - i + 1) {
                    ans[i] = ans[i - l];
                } else {
                    ans[i] = max(0, r - i + 1);
                    while (i + ans[i] < t_len && text[ans[i]] == text[i + ans[i]]) ++ans[i];
                }
                if (i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
            }
            return ans;
        };
        // z函数 模板
        
        int n = str1.length(), m = str2.length();
        string ans(n+m-1, 'a'); vector<bool> modi(n+m-1);

        int ptr = 0;

        for (int i=0; i<n; ++i) {
            if (str1[i] == 'F') continue;
            for (ptr = max(i, ptr); ptr<i+m; ++ptr) {
                ans[ptr] = str2[ptr-i]; modi[ptr] = true;
            }
        }
        string text = str2 + ans;
        auto zres = zFunc(text);

        int last = 0, revise = -1;
        for (int i=0; i<n; i++) {
            if (str1[i] == 'T') {
                if (zres[m+i] < m) return "";
                else last = i+m-1;       // last 之前不能修改了，减少后续修改区间
            }else if (zres[m+i] >= m && str1[i] == 'F' && revise < i) { // revise 不会大于 i+m-1 
                for (int j=i+m-1; j>=max(i, last); --j) {   // 从最后开始增加，这样保证最小字符
                    if (modi[j]) continue;
                    ans[j] ++; revise = j;
                    break;
                }
                if (revise < i)  return "";    // 未找到可修改字符
            }
        }

        return ans;
    }
};


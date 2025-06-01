#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    string decodeString(string s) {
        // 自行解答
        int begin = 0, n = s.length(), prev = 1;
        vector<int> cnt;
        vector<string> sub;
        sub.push_back("");      // 最外层输出

        for (int i=0; i<n; ++i) {
            if (s[i] == '[') {
                cnt.push_back(stoi(s.substr(begin, i-begin))), prev = 1;
                sub.push_back("");  // 每层新开一个子串
            } else if (s[i] == ']') {
                string res = ""    ;
                for (int _=0; _<cnt.back(); _++) res += sub.back();
                cnt.pop_back(), sub.pop_back();
                sub.back() += res; 
            } else if (s[i]>='a' && s[i] <='z') { // 小写字母
                sub.back() += s[i];
            } else {    // 数字
                if (prev == 1) begin = i, prev = 0;
            }
        }

        return sub[0];  
    }
};

#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    bool isValid(string code) {
        // 自行解答
        int n = code.length(), i = 0;
        stack<string> tags;

        while (i < n) {
            if (code[i] == '<') {
                if (i == n-1) return false;
                if (code[i+1] == '/') {     // 结束符号
                    int j = code.find('>', i);
                    if (j == string::npos || tags.empty()) return false;
                    string tag = code.substr(i+2, j-i-2);
                    if (tags.top() == tag) tags.pop();
                    else return false;
                    i = j + 1;
                    if (tags.empty() && i!=n) return false;
                } else if (code[i+1] == '!') {
                    if (tags.empty() || i+11>n || code.substr(i+2, 7) != "[CDATA[") return false;
                    int j = code.find("]]>", i+7);
                    if (j == string::npos) return false;
                    i = j+3;                    
                } else {
                    int j = code.find('>', i);
                    if (j == string::npos) return false;
                    string tag = code.substr(i+1, j-i-1);
                    if (tag.length()<1 || tag.length()>9) return false;
                    if (!all_of(tag.begin(), tag.end(), [](char c){return isupper(c);})) {
                        return false;
                    } else tags.push(tag);
                    i = j + 1;
                }
            } else {
                // tag content
                if (tags.empty()) return false;
                i++;
            }
        }

        return tags.empty();   

    }
};

int main() {
    cout << Solution().isValid("<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>") << endl;
}
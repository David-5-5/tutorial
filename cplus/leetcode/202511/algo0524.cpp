#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 双序列双指针 - 4.2 判断子序列
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        // 自行解答
        sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b){
            if (a.length() == b.length()) return a < b;
            return a.length() > b.length();
        });

        int n = s.length();
        for (auto & word: dictionary) {
            int inx1 = 0, inx2 = 0, m = word.length();
            while (inx1 < n && inx2 < m) {
                if (s[inx1] == word[inx2]) inx2 ++;
                inx1 ++;
            }
            if (inx2 == m) return word;
        }

        return "";       

    }
};
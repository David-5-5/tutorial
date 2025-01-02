#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 回文串贪心
class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        // 自行解答
        // 有序hash, key = 字符串长度， value : 数量
        // 按照字符串长度排序
        map<int, int> len_cnt;
        // hash 表 key：字母，value：数量
        unordered_map<char, int> char_cnt;

        for (auto& word :words) {
            len_cnt[word.size()] += 1;
            for (auto& ch : word)
                char_cnt[ch] += 1;
        }
        
        int pairs = 0, ans = 0;
        for (auto it = char_cnt.begin(); it != char_cnt.end(); ++it) {
            pairs += it->second / 2; // 两个相同字母，组成一个回文对
        }

        // cout << pairs << endl;
        for (auto it = len_cnt.begin(); it!=len_cnt.end(); ++it) {
            // cout << "first:" << it->first << ", second:" << it->second << endl;

            if ((it->first / 2) * it->second <= pairs) {
                ans += it->second;
                pairs -= (it->first / 2) * it->second;
            } else {
                ans += pairs / (it->first / 2);
                pairs = 0;
            }

            if (pairs == 0) break;
        }

        return ans;
    }
};
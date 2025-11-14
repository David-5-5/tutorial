#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.1 双指针
class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        // 自行解答，特别别扭
        auto freq = [](string word) -> vector<pair<char, int>> {
            vector<pair<char, int>> ret;
            word.push_back('&');
            int cnt = 1;
            for (int i=1; i<word.length(); ++i) {
                if (word[i-1] == word[i]) cnt++;
                else {
                    ret.emplace_back(word[i-1], cnt);
                    cnt = 1;
                }
            }
            return ret;
        };

        vector<pair<char, int>> s_cnt = freq(s);
        int n = s_cnt.size(), ans = 0;
        for (auto& word: words) {
            vector<pair<char, int>> word_cnt = freq(word);
            if (word_cnt.size() != n) continue;
            bool match = true;
            for (int i=0; i<n; i++) {
                if (!(word_cnt[i].first == s_cnt[i].first && 
                    (word_cnt[i].second==s_cnt[i].second ||
                        (word_cnt[i].second<s_cnt[i].second && s_cnt[i].second>2)))) {
                    match = false; break;
                }
            }
            if (match)  ans ++;
        } 

        return ans;     
    }
};
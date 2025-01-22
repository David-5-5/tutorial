#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 等价转换
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        // 自行解答，c++ 编程训练
        if (word1.size() != word2.size()) return false;
        
        vector<int> cnt1(26), cnt2(26);
        set<char> chset1, chset2;   // 不需要排序
        for (int i=0; i < word1.size(); i++) {
            char ch1 = word1[i], ch2 = word2[i];
            cnt1[ch1-'a'] ++, cnt2[ch2-'a'] ++;
            chset1.emplace(ch1), chset2.emplace(ch2);
        }
        sort(cnt1.begin(), cnt1.end()), sort(cnt2.begin(), cnt2.end());
        
        return cnt1 == cnt2 && chset1 == chset2;    
    }

    bool closeStrings(string word1, string word2) {
        // 参考题解，c++ 编程训练
        if (word1.size() != word2.size()) return false;
        
        vector<int> cnt1(26), cnt2(26);
        for (int i=0; i < word1.size(); i++) {
            char ch1 = word1[i], ch2 = word2[i];
            cnt1[ch1-'a'] ++, cnt2[ch2-'a'] ++;
        }
        sort(cnt1.begin(), cnt1.end()), sort(cnt2.begin(), cnt2.end());
        
        // 判断包含的字符是否相同，性能好
        for (int i = 0; i < 26; i++) {          
            if (cnt1[i] > 0 && cnt2[i] == 0 || cnt1[i] == 0 && cnt2[i] > 0) {
                return false;
            }
        }

        return cnt1 == cnt2;    
    }    
};
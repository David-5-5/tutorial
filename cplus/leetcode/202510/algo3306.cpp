#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.3.3 恰好型滑动窗口
class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        // 参考题解
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        int n = word.length();
        auto count = [&] (int limit) -> long long {
            unordered_map<char,int> v_cnt;
            long long ans = 0;
            int l = 0, cnt = 0; 
            for (int r=0; r<n; ++r) {
                if (!vowels.count(word[r])) cnt += 1;
                else v_cnt[word[r]] += 1;

                while (v_cnt.size()==5 && cnt >= limit) { // 直接套公式，就这一步没有建立起空间概念
                    if (!vowels.count(word[l])) cnt --;
                    else {
                        v_cnt[word[l]] --;
                        if (v_cnt[word[l]] == 0) v_cnt.erase(word[l]);
                    }
                    l+=1;
                }
                ans += l;
            }
            return ans;            
        };
        return count(k) - count(k+1);
    }
};
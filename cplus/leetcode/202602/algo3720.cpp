#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        // 参考题解 
        vector<int> all_s(26), pre_t(26);
        int n = s.length();
        
        for (int i=0; i<n; i++) {
            all_s[s[i]-'a'] ++; pre_t[target[i]-'a'] ++;
        }

        auto contain = [](vector<int> & arr1, vector<int>& arr2) {
            auto it2 = arr2.begin();
            return all_of(arr1.begin(), arr1.end(),[&](const int & val) {
                return val >= *it2++;
            });
        };
        
        for (int i=n-1; i>=0; --i) {
            pre_t[target[i]-'a'] --;
            if (contain(all_s, pre_t)) {
                vector<int> suf_s(26);
                for (int ch=0; ch<26; ch++) suf_s[ch] = all_s[ch] - pre_t[ch];
                bool found = false; // suf_s 中 找到比 target[i] 大的字符
                string ans = target.substr(0, i);
                for (int ch=target[i]-'a' + 1; ch<26; ch++) {
                    if (suf_s[ch]>0) {
                        found = true; suf_s[ch] --; ans.push_back('a' + ch); break;
                    }
                }
                if (found) {
                    for (int ch=0; ch<26; ch++) {
                        ans += string(suf_s[ch], ch+'a');
                    }
                    return ans;
                }
                // 前缀相等，但后缀小于等于 target，进行枚举下一个字符， s = "abb" b="abb" 
                // 枚举两个 b 都是前缀相同，但后缀相等，枚举到 a，前缀未空，找出大于 a 的字符最小字符 b，
                // 剩余字符从小到大排列，结果为 bab
            }
        }
        return "";     
    }
};
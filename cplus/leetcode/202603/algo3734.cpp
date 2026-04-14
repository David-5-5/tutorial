#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        // 自行解答 
        int n = s.length(), m = n / 2; string mid = "";
        if (n == 1 && s > target) return s;
        
        vector<int> all_s(26), pre_t(26);
        for (int i=0; i<n; i++) all_s[s[i]-'a'] ++; 
        for (int i=0; i<m; i++) pre_t[target[i]-'a'] ++;

        for (int ch=0; ch<26; ++ch) {
            if (all_s[ch] % 2) {
                if (mid == "") mid.push_back(ch + 'a');
                else return "";
            }
            all_s[ch] /= 2;
        }

        auto contain = [](vector<int> & arr1, vector<int>& arr2) {
            auto it2 = arr2.begin();
            return all_of(arr1.begin(), arr1.end(),[&](const int & val) {
                return val >= *it2++;
            });
        };

        // 仅需特判即可 -- 这一点没看出来
        if (contain(all_s, pre_t)) {
            string t_pref = target.substr(0, n/2); 
            auto t_suf = t_pref; reverse(t_suf.begin(), t_suf.end());
            if (mid + t_suf > target.substr(m)) {
                return t_pref + mid + t_suf;
            }
        }

        // 后续逻辑同 3720，从 m 往前就是不相等了，要么大于，要么小于
        // 找不到比当前 i 大的字符，则当前的字典序一定小于 target
        for (int i=m-1; i>=0; --i) {
            pre_t[target[i]-'a'] --;
            if (contain(all_s, pre_t)) {
                vector<int> suf_s(26);
                for (int ch=0; ch<26; ch++) suf_s[ch] = all_s[ch] - pre_t[ch];
                bool found = false; // suf_s 中 找到比 target[i] 大于等于的字符
                string ans = target.substr(0, i);
                for (int ch=target[i]-'a'+1; ch<26; ch++) {                    
                    if (suf_s[ch]>0) {
                        found = true; suf_s[ch] --; ans.push_back('a' + ch); break;
                    }
                }
                if (found) {
                    for (int ch=0; ch<26; ch++) {
                        ans += string(suf_s[ch], ch+'a');
                    }
                    auto suf = ans; reverse(suf.begin(), suf.end());
                    ans += mid + suf;
                    return ans;
                }
            }
        }
        return "";
    }
};
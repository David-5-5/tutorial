#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.5 排列型回溯
class Solution {
public:
    bool isSolvable(vector<string>& words, string result) {
        // 自行解答, 超时
        unordered_map<char, int> chars; unordered_set<char> initial;
        for (auto& w : words) for (auto& ch: w) if (!chars.count(ch)) chars[ch]=chars.size();
        for (auto & ch:result) if (!chars.count(ch)) chars[ch]=chars.size();
        initial.insert(result[0]); for (auto& w:words) initial.insert(w[0]);
        
        int n = chars.size();
        vector<char> v_chars(n); for (auto& [k,v]:chars) v_chars[v] = k;
        vector<int> mapto(n);

        auto check = [&] ()-> bool {
            int left = 0;
            for (auto& w: words) {
                int cur = 0;
                for (auto ch: w) {
                    cur = cur * 10 + mapto[chars[ch]];
                }
                left += cur;
            }
            int right = 0;
            for (auto ch: result) {
                right = right * 10 + mapto[chars[ch]];
            }
            return left == right;
        };

        auto dfs = [&] (this auto&& dfs, int i, int mask) -> bool {
            if (i == n) return check();

            for (int k=0; k<10; ++k) {
                if (initial.count(v_chars[i]) && k==0) continue; // 无前导 0
                if (((mask >> k)&1) == 0) {
                    mapto[i] = k;
                    if (dfs(i+1, mask|1<<k)) 
                        return true;
                    // mapto[i] = 0;   // 恢复现场
                }
            }

            return false;

        };

        return dfs(0, 0);
    }

    bool isSolvable(vector<string>& words, string result) {
        // 参考题解, 合并多项式, 优化 check 时间
        unordered_map<char, int> chars; unordered_set<char> initial;
        for (auto& w : words) {
            int pow10 = 1;
            for (int i=w.length()-1; i>=0; --i) {
                chars[w[i]] += -pow10 ; pow10 *= 10;
            }
        }
        
        int pow10 = 1;
        for (int i=result.length()-1; i>=0; --i) {
            chars[result[i]] += pow10; pow10 *= 10;
        }

        if (result.size()>1) 
            initial.insert(result[0]); 
        for (auto& w:words) if (w.length()>1) initial.insert(w[0]);
        
        int n = chars.size(), m = initial.size();
        // 虽然只有 10 个字符,但一定避免使用哈希表,!!!要用数组!!!
        vector<int> coeff;
        // 不能为 0 的字符放数组的前列，递归时检查不能为 0
        for (auto it = initial.begin(); it!=initial.end(); ++it) coeff.push_back(chars[*it]);
        for (auto [k, v]:chars) if (!initial.count(k)) coeff.push_back(v);
        vector<int> vals(n);

        // 合并多项式检查
        auto check = [&] ()-> bool {
            int result = 0;
            for (int i=0; i<n; ++i) {
                result += coeff[i] * vals[i];
            }
            return result == 0;
        };
        auto dfs = [&] (this auto&& dfs, int i, int mask) -> bool {
            if (i == n) return check();

            for (int k=0; k<10; ++k) {
                if (i<m && k==0) continue; // 无前导 0
                if (((mask >> k)&1) == 0) {
                    vals[i] = k;
                    if (dfs(i+1, mask|1<<k)) return true;
                }
            }
            return false;
        };

        return dfs(0, 0);
    }    
};
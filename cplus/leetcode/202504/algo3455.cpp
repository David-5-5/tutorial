#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.2 枚举中间
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        // 自行解答 KMP + 前后缀分解
        int pos1 = p.find('*'), pos2 = p.find('*', pos1+1);

        string pp = p.substr(0, pos1);          // 第一个 * 前面字符串
        string pm = p.substr(pos1+1, pos2-pos1-1);     // * * 中间字符串 
        string ps = p.substr(pos2+1);           // 第二个 * 后面字符串

        int ppl = pp.length(), pml = pm.length(), psl = ps.length();

        auto kmp = [](string str, string pat) -> vector<int> {
            int n = str.size(), m = pat.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && pat[j]!=pat[i])
                    j = p_pi[j-1];
                if (pat[j] == pat[i])
                    p_pi[i] = j + 1;
                else p_pi[i] = j;
            }
        
            vector<int> ans;
            int j = 0;
            for (int i=0; i<n; i++) {
                while (j > 0 && str[i] != pat[j])
                    j = p_pi[j-1];
                if (str[i] == pat[j]) j++;
                if (j == m) ans.push_back(i-j+1), j = p_pi[j-1];
            }
        
            return ans;
        };
        
        int ans = s.length()+1;
        vector<int> pre;
        if (ppl) {
            pre = kmp(s, pp);
            if (pre.size() == 0) return -1;
        }

        vector<int> mid;
        if (pml) {
            mid = kmp(s, pm);
            if (mid.size() == 0) return -1;
        }
        else for (int i=0; i<=s.length(); i++) mid.push_back(i);

        vector<int> suf;
        if (psl) {
            suf = kmp(s, ps);
            if (suf.size() == 0) return -1;
        }


        for (auto& m:mid) {
            int begin = -1;             
            if (ppl == 0) begin = m;        // 前缀长度为零, 匹配后缀
            else {
                int p_inx = m - ppl;        // pp 匹配的最大的开始字符
                // if (p_inx < 0) continue;    // 不满足条件，继续
                int i_pre = ranges::upper_bound(pre, p_inx) - pre.begin();
                if (i_pre) begin = pre[i_pre-1];
                else continue;
            }

            int end = s.length();
            if (psl == 0) end = m + pml;    // 后缀长度为零
            else {
                int p_inx = m + pml;
                int i_suf = ranges::lower_bound(suf, p_inx) - suf.begin();
                if (i_suf != suf.size()) end = suf[i_suf] + psl;
                else continue;
            }
            ans = min(ans, end-begin);
        }
        
        return ans < s.length()+1 ? ans : -1;    

    }
};

int main() {
    cout << Solution().shortestMatchingSubstring("cvtrmfmvuhzncqffl", "fl**") << endl;
}
#include <bits/stdc++.h>
using namespace std;

// 力扣周赛 384
class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        // 自行解答
        // kmp 模板，返回值由 索引数组 变更为 匹配数量
        auto kmp = [](string str, string pat) -> int {
            int n = str.size(), m = pat.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && pat[j]!=pat[i]) j = p_pi[j-1];
                if (pat[j] == pat[i]) p_pi[i] = ++j;
                // else p_pi[i] = j;
            }

            int ans = 0;
            int j = 0;
            for (int i=0; i<n; i++) {
                while (j > 0 && str[i] != pat[j])
                    j = p_pi[j-1];
                if (str[i] == pat[j]) j++;
                if (j == m) ans++, j = p_pi[j-1];
            }

            return ans;
        };

        string pat = "";
        string str = "";
        for (auto v : pattern)
            if (v == -1) pat += '2';
            else pat += to_string(v);

        for (int i=1; i<nums.size(); i++) {
            if (nums[i]>nums[i-1]) str += "1";
            else if (nums[i]==nums[i-1]) str += "0";
            else str += "2";
        }

        return kmp(str, pat);
    }
};

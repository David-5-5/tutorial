#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.4 其他（选做）
class Solution {
public:
    int maxRepOpt1(string text) {
        // 自行解答，写的太难受了，找机会优化一下
        vector<int> cnt(26);
        for (auto ch: text) cnt[ch-'a'] ++;
        int ans = 1, l = 0;
        unordered_map<char, int> win_cnt;
        auto check = [&] () -> bool {
            if (win_cnt.size() > 2) return true;
            int gt1_cnt = 0;
            for (auto [_, v]: win_cnt) if (v>1) gt1_cnt ++;

            return gt1_cnt == 2;
        };


        for (int r=0; r<text.length(); ++r) {
            
            win_cnt[text[r]] ++;
            while (check()) {
                win_cnt[text[l]] --;
                if (win_cnt[text[l]] == 0) win_cnt.erase(text[l]);
                l ++;
            }
            auto result = [&]() -> int {
                if (win_cnt.size() == 1) return r - l + 1;
                char k1 = ' ', k2 = ' ';
                for (auto [k, _]: win_cnt)  {
                    if (k1 == ' ') k1 = k;
                    else k2 = k;
                }
                if (win_cnt[k1] == win_cnt[k2]) return min(2, max(cnt[k1-'a'], cnt[k2-'a']));
                else if (win_cnt[k1] == 1) return min(cnt[k2-'a'], win_cnt[k2] + 1);
                else return min(cnt[k1-'a'], win_cnt[k1] + 1);
            };
            
            ans = max(ans, result());
        }
        return ans; 

    }
};

int main() {
    string text = "ababa";
    cout << Solution().maxRepOpt1(text) << endl; 
}
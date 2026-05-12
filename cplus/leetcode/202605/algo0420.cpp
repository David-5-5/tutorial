#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int strongPasswordChecker(string password) {
        // 自行解答
        bool has_lower = false, has_upper = false, has_digit = false;
        int len = password.length();
        vector<int> threshold;   // >= 3

        password.push_back(' ');

        char prev = ' '; int cnt = 1;
        for (auto & ch : password) {
            if (ch >= '1' && ch <= '9') has_digit = true;
            else if (ch >= 'a' && ch <= 'z') has_lower = true;
            else if (ch >= 'A' && ch <= 'Z') has_upper = true;

            if (prev == ch) cnt ++;
            else {
                if (cnt >= 3) threshold.push_back(cnt);
                cnt = 1;
            }
            prev = ch;
        }

        auto chg = [&] (int cnt) -> void {
            for (int _=0; _<cnt; _++) {
                if (!has_digit) has_digit = true;
                else if (!has_lower) has_lower  =  true;
                else if (!has_upper) has_upper =  true;
            }
        };

        // len > 20, 删除优先 长的还是短？ 短   
        // 即不长也不短，按照替换 > 3的长命令 替换次数 len / 3
        // （这也是在测试案例试错的基础上总结出来，不然也想不清楚）
        // 因此 len % 3 = 0, 1, 2 顺序进行删除
        // 当 len % 3 = 0, 删除 1， 则替换少 1
        //            = 1, 删除 2， 则替换少 1
        //            = 2, 删除 3， 则替换少 1
        int ans = 0;
        while (len > 20 && threshold.size()) {
            for (int i = 0; i < 3 && len > 20; ++i) {
                for (auto it = threshold.begin(); it != threshold.end(); ) {
                    if (len == 20) break;
                    if (*it % 3 != i) {
                        ++it;
                        continue;
                    }
                    
                    int l = min(i+1, len - 20);
                    *it -= l;
                    ans += l;
                    len -= l;
                    // 一边遍历，一边删除
                    if (*it < 3) it = threshold.erase(it);
                    else ++it;
                }
            }
        }

        if (len > 20) {ans += len - 20; len = 20;}

        while (len < 6 && threshold.size()) {
            int l;
            if (threshold.back() <= 4) l = 1;
            else if (threshold.back() <= 6) l = 2;

            l = min(l, 6 - len);
            if (threshold.back() - (l * 2) > 2) {
                threshold.back() -= l * 2;
            }else threshold.pop_back();

            ans += l; len += l;
            chg(l);
        }

        if (len < 6) {
            ans += 6 - len; chg(6 - len) ; len = 6; 
        }

        while (threshold.size()) {
            int l = threshold.back() / 3;
            ans += l; chg(l);
            threshold.pop_back();
        }

        if (!has_digit) ans ++;
        if (!has_lower) ans ++;
        if (!has_upper) ans ++;
        return ans;    
    }
};


int main() {
    cout << Solution().strongPasswordChecker("bbaaaaaaaaaaaaaaacccccc") << endl;
}
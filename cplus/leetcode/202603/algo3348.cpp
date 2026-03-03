#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    string smallestNumber(string num, long long t) {
        // prime 2, 3, 5, 7,
        // 初始 pre num中第一个零之前的数包含的质数数量
        //     suf 是 t 包含的质数数量减去 pre 的质数数量
        vector<vector<int>> pre;    // 记录前缀贡献给 t 的质数
        vector<int> suf(4);
        vector<int> primes = {2, 3, 5, 7};
        
        for (int p=0; p<4; ++p) {
            while (t % primes[p] == 0) {
                suf[p] ++; t /= primes[p];
            }
        }
        if (t>1) return "-1";

        auto add = [&](int i) -> void {
            for (int p=0; p<4; ++p) suf[p] += pre[i][p];
        };

        auto sub = [&](int i) -> void {
            auto val = num[i]; vector<int> cnt(4);
            if (val == '9') {cnt[1] = min(2, suf[1]); suf[1] -= cnt[1];}
            else if (val == '8') {cnt[0] = min(3, suf[0]); suf[0] -= cnt[0];}
            else if (val == '7') {cnt[3] = min(1, suf[3]); suf[3] -= cnt[3];}
            else if (val == '6') {
                cnt[0] = min(1, cnt[0]); cnt[1] = min(1, suf[1]);
                suf[0] -= cnt[0]; suf[1] -= cnt[1]; 
            }else if (val == '5') {cnt[3] = min(1, suf[3]); suf[3] -= cnt[3];}
            else if (val == '4') {cnt[0] = min(2, suf[0]); suf[0] -= cnt[0];}
            else if (val == '3') {cnt[1] = min(1, suf[1]); suf[1] -= cnt[1];}
            else if (val == '2') {cnt[0] = min(1, suf[0]); suf[0] -= cnt[0];}

            pre.emplace_back(cnt);
        };
        int pos0 = -1, n = num.length();
        for (int i=0; i<n; i++) {
            if (num[i] == '0') {
                pos0 = i; break;
            }
            sub(i);
        }

        string ans = "";
        for (int i=n-1; i>=0; --i) {

            if (i > pos0) add(i); int exp = 0;
            // cout << suf[0] << ", " << suf[1] << ", " << suf[2] << ", " << suf[3] << endl;
            if (suf[1]>=2) {suf[1] -= 2; exp = 9;}
            else if (suf[0] >= 3) {suf[0] -= 3; exp = 8;}
            else if (suf[3]>=1) {suf[3] -= 1; exp = 7;}
            else if (suf[0] >= 1 && suf[1]>=1 ) {suf[0] -= 1; suf[1] -= 1; exp = 6;}
            else if (suf[2] >= 1) {suf[2] -= 1; exp = 5;}
            else if (suf[0] >= 2) {suf[0] -= 2; exp = 4;}
            else if (suf[1] >= 1) {suf[1] -= 1; exp = 3;}
            else if (suf[0] >= 1) {suf[0] -= 1; exp = 2;}
            else exp = 1;

            if (suf[0] || suf[1] || suf[2] || suf[3]) ans.push_back(exp + '0');
            else ans.push_back(max(num[i]-'0', exp)+'0');
        }

        while (suf[0] || suf[1] || suf[2] || suf[3]) {
            if (suf[1]>=2) {suf[1] -= 2; ans.push_back('9');}
            else if (suf[0] >= 3) {suf[0] -= 3; ans.push_back('8');}
            else if (suf[3]>=1) {suf[3] -= 1; ans.push_back('7');}
            else if (suf[0] >= 1 && suf[1]>=1 ) {suf[0] -= 1; suf[1] -= 1; ans.push_back('6');}
            else if (suf[2] >= 1) {suf[2] -= 1; ans.push_back('5');}
            else if (suf[0] >= 2) {suf[0] -= 2; ans.push_back('4');}
            else if (suf[1] >= 1) {suf[1] -= 1; ans.push_back('3');}
            else if (suf[0] >= 1) {suf[0] -= 1; ans.push_back('2');}
            else ans.push_back('1');
        }

        reverse(ans.begin(), ans.end()); return ans;   
    }
};
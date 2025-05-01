#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int rotatedDigits(int n) {
        // 自行解答，用数位 DP，时间复杂度为 O(DlogN) D 为数的十进制数位
        // 暴力求解 从 1 遍历到 N，时间复杂度为 O(N)
        // 数位 DP 包括 上下限 排除前导 0
        string s = to_string(n);
        int m = s.length();
        const set<int> illegal = {3, 4, 7};
        const set<int> legal = {2, 5, 6, 9};

        unordered_map<int, int> memo;
        // included 至少需要包含 2， 5， 6， 9 中的一个
        auto f = [&] (this auto&& f, int i, bool included, bool is_num, bool limit) -> int {
            if (i == m) return included;
            
            int mask = i << 3 | included << 2 | is_num << 1 | limit;
            if (memo.count(mask)) return memo[mask];
            
            int res = 0;
            // 是否前导 0
            if (!is_num) res = f(i + 1, included, false, false); // limit = false

            int low = is_num?0 : 1;
            int up = limit? s[i] - '0': 9;
            for (int d=low; d<=up; ++d) {
                if (illegal.find(d)!= illegal.end()) continue;
                res += f(i+1, included|legal.find(d)!=legal.end(), true, limit&&d==up);
            }            
            return memo[mask] = res;
        };

        return f(0, false, false, true); // limit = true
    }

    int rotatedDigits2(int n) {
        // 无记忆化搜索 - 由于N比较小，无记忆化搜索也可以通过
        string s = to_string(n);
        int m = s.length();
        const set<int> illegal = {3, 4, 7};
        const set<int> legal = {2, 5, 6, 9};

        // included 至少需要包含 2， 5， 6， 9 中的一个
        auto f = [&] (this auto&& f, int i, bool included, bool is_num, bool limit) -> int {
            if (i == m) return included;
                        
            int res = 0;
            // 是否前导 0
            if (!is_num) res = f(i + 1, included, false, false); // limit = false

            int low = is_num?0 : 1;
            int up = limit? s[i] - '0': 9;
            for (int d=low; d<=up; ++d) {
                if (illegal.find(d)!= illegal.end()) continue;
                res += f(i+1, included|legal.find(d)!=legal.end(), true, limit&&d==up);
            }            
            return res;
        };

        return f(0, false, false, true); // limit = true
    }

    int rotatedDigits3(int n) {
        // 实际上不需要 is_num
        string s = to_string(n);
        int m = s.length();
        const set<int> illegal = {3,4,7};
        const set<int> legal = {2,5,6,9};

        unordered_map<int, int> memo;
        // included 至少需要包含 2， 5， 6， 9 中的一个
        auto f = [&] (this auto&& f, int i, bool included, bool limit) -> int {
            if (i == m) return included;
            
            int mask = i << 2 | included << 1 | limit;  // included < 1 写错了
            if (memo.count(mask)) return memo[mask];
            int res = 0;
            int up = limit?s[i]-'0':9;
            for (int d=0; d<=up; ++d) {
                if (illegal.find(d)!= illegal.end()) continue;
                res += f(i+1, included|legal.find(d)!=legal.end(), limit&&d==up);
            }            
            return memo[mask] = res;
            // return res;
        };

        return f(0, false, true);
    }    

};
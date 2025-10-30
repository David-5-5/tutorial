#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 组合数学 - 2.5 贡献法
class Solution {
public:
    long long countVowels(string word) {
        // 自行解答
        string vowels = "aeiou";
        int n = word.length();
        long long ans = 0;
        for (int i=0; i<n; i++) {
            if (vowels.find(word[i]) != string::npos)
                ans += 1LL * (i+1) * (n-i);
        }

        return ans;

    }
};
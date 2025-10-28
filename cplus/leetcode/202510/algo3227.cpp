#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 博弈论
class Solution {
public:
    bool doesAliceWin(string s) {
        // 自行解答 只要存在元音字母，Alice比胜
        string vowels = "aeiou";
        int cnt = 0;
        for (auto &ch : s) 
            if (vowels.find(ch)!=string::npos) cnt += 1;
        return cnt > 0;        
    }


};
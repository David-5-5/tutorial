#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 博弈论
class Solution {
public:
    bool winnerOfGame(string colors) {
        int alice = 0, bob = 0, a = 0, b = 0;
        for (auto c : colors) {
            if (c == 'A') {
                if (b > 0) {bob += max(0, b-2); b = 0;}
                a += 1;
            } else {
                if (a > 0) {alice += max(0, a-2); a = 0;}
                b += 1;
            }
        }
        // 最后一段
        if (a > 0) alice += max(0, a-2);
        else bob += max(0, b-2);
        return alice > bob;  
    }
};
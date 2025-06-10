#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.1 队列 - 基础
class Solution {
public:
    string predictPartyVictory(string senate) {
        // 参考题解 - 队列 - 贪心模拟投票过程
        int n = senate.size();
        queue<int> readiant, dire;
        for (int i=0; i<n; ++i) {
            if (senate[i] == 'R') readiant.push(i);
            else dire.push(i);
        }

        while (readiant.size() && dire.size()) {
            if (readiant.front() < dire.front()) {
                readiant.push(readiant.front() + n);
                readiant.pop();
                dire.pop();
            } else {
                dire.push(dire.front() + n);
                dire.pop();
                readiant.pop();
            }
        }

        if (readiant.empty()) return "Dire";
        else return "Radiant";
    }   
};
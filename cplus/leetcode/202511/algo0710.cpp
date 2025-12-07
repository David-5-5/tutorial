#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数

// 自行解答，分两种情况
// 当黑名单数量 / n > 1/2 使用白名单
//                < 1/2 使用黑名单
// n < 10 ^ 9
// blacklist.size() <= 10 ^ 5
// 因此需要存储的数据量 <= 10 ^ 5
class Solution {
    int n, whiteorblack = 0;
    vector<int> whitelist;
    set<int> blacklist;
public:
    Solution(int n, vector<int>& blacklist) {
        if (blacklist.size() * 2 > n) {
            // use whitelist
            set<int> all_value;
            for (int i=0; i<n; ++i) all_value.insert(i);
            for (auto & b: blacklist) all_value.erase(b);
            for (auto it = all_value.begin(); it != all_value.end(); ++it) 
                whitelist.emplace_back(*it);
        } else {
            // use blacklist
            whiteorblack = 1;
            this->n = n;
            for (auto & b: blacklist) this->blacklist.insert(b);
        }
    }
    
    int pick() {
        
        if (whiteorblack) {
            while (true) {
                int inx = rand() % n;
                if (!blacklist.count(inx)) return inx;
            }
        } else return whitelist[rand() % whitelist.size()];
    }
};


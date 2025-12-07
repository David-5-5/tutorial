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

// 参考题解 黑名单映射, [n-m, n) 为黑名单区域
// 若黑名单在[0, n-m) 则在[n-m, n) 映射一个白名单
class Solution {
    int bound;
    unordered_map<int, int> b2w;
public:
    Solution(int n, vector<int>& blacklist) {
        unordered_set<int> black_set(blacklist.begin(), blacklist.end());
        int m = blacklist.size();
        bound = n-m;
        int w = bound;
        for (auto b: blacklist) {
            if (b >= bound) continue; // 在黑名单区域
            while (black_set.count(w)) w++;
            b2w[b] = w++;
        }
    }
    
    int pick() {
        int x = rand() % bound;
        return b2w.count(x) ? b2w[x] : x;
    }
};

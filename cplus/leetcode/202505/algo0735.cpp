#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        // 自行解答
        vector<int> left, right;

        for (auto& v: asteroids) {
            if (v > 0) right.push_back(v);
            else {
                while (right.size() && right.back() < -v)
                    right.pop_back();
                
                if (right.empty()) 
                    left.push_back(v);
                else if (right.back() == -v) right.pop_back();
            }
        }

        left.insert(left.end(), right.begin(), right.end());

        return left;

    }
};
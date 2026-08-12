#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        unordered_set<int> ans;
        if (x == 1 && y == 1) return (bound >=2)?vector<int>{2}:vector<int>{};
        else if (x == 1 || y == 1) {
            x = max(x, y);
            int x1 = 1;
            while (x1 + 1 <= bound) {
                ans.insert(x1 + 1);
                x1 *= x;
            }
        } else {
            int x1 = 1;
            while (true) {
                int y1 = 1;
                while (x1 + y1 <= bound) {
                    ans.insert(x1 + y1);
                    y1 *= y;
                }
                x1 *= x;
                if (x1 >= bound) break;
            }
        }

        return vector<int>{ans.begin(), ans.end()};
    }
};
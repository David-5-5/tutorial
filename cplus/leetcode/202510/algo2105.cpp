#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        // 自行解答，按题意模拟
        int ans = 0, l = 0, r = plants.size()-1, ca = capacityA, cb = capacityB;
        while (l <= r) {
            if (l == r) {
                if (ca >= cb) {if (ca<plants[l]) ans += 1;}
                else {if (cb<plants[l]) ans += 1;}
            } else {
                if (ca<plants[l]) {
                    ans += 1; ca = capacityA - plants[l];
                } else ca -= plants[l];
                if (cb<plants[r]) {
                    ans += 1; cb = capacityB - plants[r];
                } else cb -= plants[r];
            }
            l ++, r --;
        }
        return ans;
    }
};
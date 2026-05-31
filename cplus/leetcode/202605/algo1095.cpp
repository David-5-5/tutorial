#include <bits/stdc++.h>
using namespace std;

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class MountainArray {
    public:
    int get(int index);
    int length();
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int l = 0, r = mountainArr.length() - 1;
        int i = 0;
        while (l <= r) {
            auto m = (l + r) / 2;
            if (m-1 < 0) {l ++ ; continue;}
            if (m+1 >= mountainArr.length()) {r --; continue;}
            auto v_m = mountainArr.get(m), v_m_l = mountainArr.get(m-1), v_m_r = mountainArr.get(m+1);
            if (v_m > v_m_l && v_m > v_m_r) {
                i = m; break;
            } else if (v_m > v_m_l && v_m < v_m_r) {
                l = m + 1;
            } else r = m - 1;
        }

        l = 0, r = i;
        while (l <= r) {
            auto m = (l + r) / 2;
            auto v_m = mountainArr.get(m);
            
            if (v_m == target) {
                return m; 
            } else if (v_m < target) {
                l = m + 1;
            } else r = m - 1;

        }

        l = i, r = mountainArr.length() - 1;
        while (l <= r) {
            auto m = (l + r) / 2;
            auto v_m = mountainArr.get(m);
            if (v_m == target) {
                return m; 
            } else if (v_m < target) {
                r = m - 1;
            } else l = m + 1;
        }

        return -1;  
    }
};


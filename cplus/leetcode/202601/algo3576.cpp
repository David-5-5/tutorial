#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    bool canMakeEqual(vector<int>& nums, int k) {
        // 自行解答
        int n = nums.size();
        auto check = [&](vector<int> arr, int t, int l) -> bool {
            for (int i=0; i<n-1; ++i) {
                if (arr[i] != t) {arr[i+1] *= -1, l--;}
                if (l < 0) return false;
            }
            return arr[n-1] == t;
        };


        return check(nums, -1, k) || check(nums, 1, k);    
    }
 
};
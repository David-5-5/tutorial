#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        // 自行解答，简单题，但需要升级难度，时间复杂度为 O(n) 
        int n = code.size();
        vector<int> ans(n);
        if (k == 0) return ans;
        auto abs_k = abs(k); int sum = 0;
        for (int i=0; i<abs_k-1; i++) sum += code[i];

        for (int i=abs_k-1; i<abs_k+n-1; ++i) {
            sum+=code[i%n];
            if (k < 0) ans[(i+1)%n] = sum;  
            else ans[(n+i-k)%n] = sum;      // 找规律
            sum-=code[(i-abs_k+1) % n];
        }
        return ans;        
    }
};
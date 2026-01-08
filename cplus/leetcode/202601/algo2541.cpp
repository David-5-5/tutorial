#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 其他
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        // 自行解答 
        long long gt = 0 , lt = 0; int n = nums1.size();
        for (int i=0; i<n; ++i) {
            int a = nums1[i], b = nums2[i];
            if (a == b) continue;
            if (a > b) {
                if (k == 0) return -1; 
                if ((a - b) % k == 0) gt += (a-b)/k; else return -1;
            }
            else {
                if (k == 0) return -1; 
                if ((b - a) % k == 0) lt += (b-a)/k; else return -1;
            }
        }

        return (gt == lt)? gt : -1;        
    }
};
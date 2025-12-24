#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        // 自行解答
        sort(arr.begin(), arr.end());
        int n = arr.size(); arr[0] = 1;
        for (int i=1; i<n; i++) {
            // if (arr[i-1]+1 < arr[i]) arr[i] = arr[i-1] + 1;
            arr[i] = min(arr[i-1]+1, arr[i]);   // 这个写法更好
        }

        return arr.back();        
    }


};
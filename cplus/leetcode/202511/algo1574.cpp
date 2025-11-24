#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.2 同向双指针
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        // 自行解答
        int p = 0, n = arr.size(), q = n-1;
        while (q>0 && arr[q-1] <= arr[q]) q--;
        if (q == 0) return 0;
        while (p<n-1 && arr[p] <= arr[p+1]) p++;

        int res = min(n-1-p, q);
        p = 0; // 从头开始
        while (q<n) {
            while ((p==0 || arr[p-1]<=arr[p]) && arr[p] <= arr[q]) p++;
            res = min(res, q-p);
            q ++;
        }
        return res;

    }
};

int main() {
    vector arr = {1,2,3,10,4,2,3,5};
    cout << Solution().findLengthOfShortestSubarray(arr) << endl;
}
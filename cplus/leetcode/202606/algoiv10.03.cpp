#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int target) {
        // 当大多数值相等时二分失效
        if (arr[0] <= arr.back()) {
            auto it = ranges::lower_bound(arr, target);
            if (it != arr.end() && *it == target) return it - arr.begin();
            else return -1;
        }

        int l = 0, r = arr.size() - 1;
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (arr[m] <= arr[r]) r = m; //arr[m] == arr[r] 时，两部分都需要继续查找
            else l = m;
        }
        
        if (target == arr[0]) return 0;
        else if (target > arr[0]) {
            auto it = lower_bound(arr.begin(), arr.begin() + l + 1, target);
            if (*it == target) return it - arr.begin();
            else return -1;
        } else {
            auto it = lower_bound(arr.begin()+r, arr.end(), target);
            if (it!=arr.end() && *it == target) return it - arr.begin();
            else return -1;
        }
    }


};
#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        // 自行解答
        int n = arr.size(), ans = 1;
        int cnt = 1;        // 边界条件 arr.size() = 1, 2情况
        if (arr.size() >= 2) {
            cnt = arr[0] == arr[1]?1:2;
            ans = max(ans, cnt);
        }
        for (int i=2; i<n; ++i) {
            if ((arr[i] > arr[i-1] && arr[i-1] < arr[i-2]) || 
                    (arr[i] < arr[i-1] && arr[i-1] > arr[i-2])) {
                ans = max(ans, ++cnt);
            }else if (arr[i] != arr[i-1]) {
                cnt = 2; ans = max(ans, cnt);
            } else cnt = 1;

        }
        return ans;        
    }
};
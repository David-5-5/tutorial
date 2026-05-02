#include <bits/stdc++.h>
using namespace std;

// 六、构造题
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // 脑筋急转弯
        int n = nums.size();
        if (n<=2) return n;

        return 1 << bit_width((unsigned) n);
    }
};
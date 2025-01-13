#include <bits/stdc++.h>
using namespace std;

// 周赛 382
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        // 自行解答 
        unordered_map<long long, int>  cnt;
        for (auto v : nums) cnt[v] ++;
   
        int ans = max(1, cnt[1] % 2 ? cnt[1] : max(0, cnt[1] - 1));
        cnt.erase(1);
        // 遍历 unordered_map cnt[x] 会自动添加元素，破坏遍历的完整性
        for (auto &[num, _] : cnt) { 
            int cur = 0;
            long long x = num;
            for (; cnt.contains(x) && cnt[x] > 1; x *= x) {
                cur += 2;
            }
            cur += cnt.contains(x) ?1:-1;
            ans = max(ans, cur);
        }  
        
        return ans;
    }
};



int main() {
    vector<int> nums = {48841,358801,28561,18974736,4356,221,358801,599,13,4356,66,48841,28561,815730721,13,815730721,18974736,66,169,599,169,221};
    cout << Solution().maximumLength(nums);
}

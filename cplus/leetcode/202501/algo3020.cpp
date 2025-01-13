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
            for (; cnt.count(x) && cnt[x] > 1; x *= x) { // use count replace of contains
                cur += 2;
            }
            cur += cnt.count(x) ?1:-1;
            ans = max(ans, cur);
        }  
        
        return ans;
    }
};



int main() {
    vector<int> nums = {1,3,2,4};
    cout << Solution().maximumLength(nums);
}

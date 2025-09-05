#include <bits/stdc++.h>
using namespace std;

// 位运算 - GCD LogTrick
class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        // 自行解答
        int n = nums.size();

        auto check = [&](int m) -> bool {
            int modi = 0;
            vector<pair<int, int>> gcds;
            for (auto num :nums) {
                int len = 0;
                if (m == 0 && num != 1) {
                    modi++; num = 1;
                    if (modi > maxC) return false;
                }
                // if (num != 1) len = 1;
                for (int i=gcds.size()-1; i>=0; --i) {
                    gcds[i].first = gcd(gcds[i].first, num);
                }
                gcds.emplace_back(num, 1);

                // 合并相同的 gcd val, 其频率 +
                auto it = gcds.begin(); auto nxt = it + 1;
                while (it !=gcds.end() && nxt != gcds.end()) {
                    
                    while (it !=gcds.end() && nxt != gcds.end() && it->first == nxt->first) {
                        nxt->second += it->second;
                        it = next(it); nxt = next(nxt);
                        gcds.erase(prev(it));
                    }
                    if (it !=gcds.end()) it = next(it);
                    if (nxt != gcds.end()) nxt = next(nxt);
                }
                int tot = 0;
                for (auto &[k, v]:gcds) {tot++; if (k!=1) len += v;}
                if (len > m) { // 超出最大长度 将当前值改为 1
                    if (++modi>maxC) return false;
                    gcds.clear(); gcds.emplace_back(1, tot);
                }
            }
            return true;
        };

        int l = -1, r = n+1;
        while (l+1<r) {
            auto mid = (l + r) / 2;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        return r;  
    }
};

int main() {
    vector<int> nums = {2,4,9,6};
    int maxC = 1;
    cout << Solution().minStable(nums, maxC) << endl;

}
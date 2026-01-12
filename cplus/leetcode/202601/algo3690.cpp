#include <bits/stdc++.h>
using namespace std;

// 位运算 - 一、基础题
class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        // 参考题解 暴力
        set<vector<int>> vis = {nums1};
        vector<vector<int>> q = {nums1};
        int n = nums1.size();
        for (int ans=0; ;ans ++) {
            vector<vector<int>> nxt;
            for (auto& a: q) {
               if (a == nums2) return ans;
                
               for (int l=0; l<n; l++) for (int r=l+1; r<=n; r++) {
                  auto b = a;
                  vector<int> sub(b.begin()+l, b.begin()+r);
                  b.erase(b.begin()+l, b.begin()+r);
                  for (int i=0; i<=b.size(); i++) { // i pos of insert
                     auto c = b;        // 需要插入多个位置，保留 b
                     c.insert(c.begin() + i, sub.begin(), sub.end());
                     if (vis.insert(c).second) nxt.emplace_back(c);
                  }
            
               }
            }
            q = move(nxt);
        }
    }

    int minSplitMerge2(vector<int>& nums1, vector<int>& nums2) {
        // 离散化后用整数标识数组
        auto a = nums1; int n = nums1.size();
        sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end());
        int mask1 = 0, mask2 = 0;
        for (int i=0; i<n; i++) {
            int idx = ranges::lower_bound(a, nums1[i]) - a.begin();
            mask1 |= idx << (3 * (n - i - 1));
            idx = ranges::lower_bound(a, nums2[i]) - a.begin();
            mask2 |= idx << (3 * (n - i - 1));
        }

        set<int> vis = {mask1};
        vector<int> q = {mask1};

        for (int ans=0; ; ans++) {
            vector<int> nxt;
            for (auto& a: q) {
                if (a == mask2) return ans;
                
                // 还有更好的位运算写法
                for (int l=0; l<n; l++) for (int r=l+1; r<=n; r++) {
                    auto sub = (a >> ((n-r)*3)) & ((1 << ((r-l)*3)) - 1);  
                    auto b = (a >> (r-l)*3 & ~((1 << (n-r)*3)-1)) | (a & ((1 << (n-r)*3)-1));
                    for (int i=0; i<=n-r+l; i++) { // i pos of insert
                        auto c = (b << (r-l)*3 & ~((1 << (n-i)*3)-1)) | (sub << (n-r+l-i)*3) | (b & (1 << (n-r+l-i)*3)-1);
                        if (vis.insert(c).second) nxt.emplace_back(c);
                    }
                }
            }
            q = move(nxt);
        }
    }    
};


int main() {
    vector<int> nums1={3,1,2}, nums2 = {1,2,3};
    cout << Solution().minSplitMerge2(nums1, nums2) << endl; 
}
#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        // 自行解答
        int n = grid.size();
        vector<int> cnt0(n);

        for (int i=0; i<n; ++i) {
            int cnt = 0;
            for (int j=n-1; j; --j) {
                if (grid[i][j] == 0) cnt ++;
                else break;
            }
            cnt0[i] = cnt;
        }

        int ans = 0;
        for (int i=0; i<n-1; i++) {
            int cnt = n - 1 - i;
            if (cnt0[i]>=cnt) continue;
            bool found = false;
            for (int j=i+1; j<n; ++j) {
                if (cnt0[j]>=cnt) {
                    ans += j - i; 
                    // 三种写法，讲元素 j 移到 i 之前
                    // 写法1：删除后，插入
                    // cnt0.erase(cnt0.begin()+j); cnt0.insert(cnt0.begin()+i, cnt);
                    // 写法2：rotate 写法简洁漂亮，将元素 j 插入到 i 之间 j >= i + 1
                    rotate(cnt0.begin()+i, cnt0.begin()+j, cnt0.begin() + j + 1);
                    // 写法3：从后循环移位
                    // for (int k=j; k>i; k--) swap(cnt0[k], cnt0[k-1]);
                    found = true; break;
                }
            }
            if (!found) return -1;
        }

        return ans;  

    }
};
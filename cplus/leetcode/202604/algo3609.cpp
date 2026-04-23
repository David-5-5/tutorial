#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.4 逆向思维
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        // 自行解答 
        auto find = [&](this auto&& find, int tx, int ty) -> int {
            int ans = 0;
            while (true) {
                // cout << format("tx = {}, ty = {}", tx, ty) << endl;
                if (sx > tx || sy > ty) break;
                if (sx == tx && sy == ty) return ans;
                if (tx == ty) {
                    return ans + 1 + max(find(0, ty), find(tx, 0));
                } else if (tx > ty) {
                    if (tx/2 >= ty) {
                        if (tx % 2) break;
                        tx /= 2;
                    }
                    else tx -= ty;
                } else {
                    if (ty/2 >= tx) {
                        if (ty % 2) break;
                        ty /= 2;
                    }
                    else ty -= tx;
                }
                ans ++;
            }
            return INT_MIN;
        };
        int ans = find(tx, ty);
        return ans<0?-1:ans;
    }
};
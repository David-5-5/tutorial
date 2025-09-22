#include <bits/stdc++.h>
using namespace std;

// 其他递归/分治
class Solution {
public:
    char findKthBit(int n, int k) {
        // 自行解答，reverse(invert(Si-1))
        auto dfs = [](this auto&& dfs, int len, int pos, int prev) {
            if (len == 1) return '0' + prev;

            if (len/2 == pos) return '0' + 1 ^ prev;
            else if (len/2 < pos) return dfs(len/2, len-pos-1,  prev^1);
            else return dfs(len/2, pos,  prev);
        };

        return dfs((1<<n)-1, k-1, 0);
    }
};

int main() {
    cout << Solution().findKthBit(3,1) << endl;
}
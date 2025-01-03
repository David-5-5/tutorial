#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 回文串贪心
class Solution {
public:
    int longestDecomposition(string text) {
        // 自行解答
        auto check = [&](int l, int r, int inx) -> bool {
            for (int i = 1; i<r-inx+1; i++) {
                if (text[l+i] != text[inx+i]) return false;
            }
            return true;
        };

        function<int(int, int)> count = [&](int l, int r) -> int {
            if (l > r) return 0; // 递归边界

            int end = r;
            while (true){
                int inx = text.rfind(text[l], end);
                if ((r-inx+1)*2 > r-l+1) return 1; // 超出边界
                if (check(l, r, inx)){
                    return 2 + count(l+r-inx+1, inx-1);
                } else {
                    end = inx-1;
                }
            }
        };

        return count(0, text.size()-1);   
    }
};

int main() {
    Solution solution;
    int result = solution.longestDecomposition("aaa");
    cout << "result = " << result << endl;
    return 0;
}
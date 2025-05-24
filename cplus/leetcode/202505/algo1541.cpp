#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    int minInsertions(string s) {
        // 自行解答， 
        int n = s.length(), ans = 0;
        
        int left = 0, right = 0;
        for (auto& ch: s) {
            if (ch == '(') {
                if (right != 0) { // 情况分析不透彻，WA了好多次，终于通过了
                    // right 为 1， 因此需要补一个 ')'， 并将right 设置为 0
                    ans += 1, right = 0;
                    // left == 0 ,需要补一个 '('
                    if (left == 0) ans += 1, left += 1;
                    // left > 0,抵销一个前面的 '('，再增加一个当前的 '('，left 的数量不变
                } else left +=1;
            } else {
                right += 1;
                if (right % 2 == 0) {
                    right = 0;
                    if (left) left -= 1;
                    else ans += 1;
                }
            }
        }

        if (left >= right) ans += 2 * left - right;
        else ans += (right+1)/2 -left + right % 2;
        return ans;
    }
};

int main() {
    cout << Solution().minInsertions("))))()))())") << endl;
}
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        // 自行解答，分类讨论
        // c 同 python 不同，不支持 a == b == c, a < b < c 这样的表达式
        if ((a == e && c != a) || (b == f && d != b) || // 车和皇后在同排或同列，象不在同列同排
              (a == e && e == c && !(min(b,f)<d && d<max(b,f))) || // 车,象 皇后在同排或同列，但 象不在中间
              (b == f && f == d && !(min(a,e)<c && c<max(a,e))))
            return 1;

        if (( c-e== d-f && (a-c != b-d || !(min(c,e)<a && a<max(c,e)))) ||
          (c-e== f-d && (a-c != d-b || !(min(c,e)<a && a<max(c,e)))))// 象和皇后在对角线，但车不在其中间
            return 1;

        return 2;
    }
};

int main() {
    Solution solution;
    int result = solution.minMovesToCaptureTheQueen(5, 8, 8, 8, 1, 8);
    cout << "result = " << result << endl;
    return 0;
}
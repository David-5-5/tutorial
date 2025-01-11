#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    string maximumBinaryString(string binary) {
        // 自行解答
        // 思路 00->10, 尽量大的转换，出现 011..0...0, 只要后面还有0, 可以通过 10 -> 01, 将 0 移到前面形成 00
        // 最终结果仅剩下一个 0 无法转换和移动 当后面都是 111011...11，就无法转换了
        // 最后零的位置就是出现 0 的起始位置 + 0 的数量就是 0 的最后位置
        int n = binary.size(), m = count(binary.begin(), binary.end(), '1');

        if (n <= m + 1) return binary; // 全是 1 或只有 1 个零

        int inx = binary.find('0');
        
        return string(inx+n-m-1, '1') + '0' + string(m-inx, '1');

    }
};
// 位运算 - 基础题
class Solution {
public:
    int hammingDistance(int x, int y) {
        // 自行解答 汉明距离
        int ans = 0;
        for (int i=0; i<32; ++i)    // 运算符优先级
            if ((x >> i & 1) != (y >> i & 1)) ans ++;
        return ans;    
    }
};
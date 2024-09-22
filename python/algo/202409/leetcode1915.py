# 常用数据结构-前缀异或和-题单
# 方法同 1542 仅数字变更为英文小写字母, 求 ”最大长度“ 变更为 ”计数“
from collections import defaultdict


class Solution:
    def wonderfulSubstrings(self, word: str) -> int:
        ans, pos = 0, defaultdict(int)
        pos[0] = 1
        xors = 0
        for ch in word:
            d = int(ord(ch)-ord('a'))
            xors ^= 1 << d

            ans += pos[xors]
            for b_p in range(10):
                # if xors >> b_p & 1 and pos[xors - (1 << b_p)]:
                #     ans += pos[xors - (1 << b_p)]
                # elif xors >> b_p & 1 == 0 and pos[xors + (1 << b_p)]:# 不包含则加上
                #     ans += pos[xors + (1 << b_p)]
                # 参考题解，优化如下
                pre_xor = xors ^ ( 1<< b_p)
                ans += pos[pre_xor]            
            pos[xors] += 1
            
        return ans

    
if __name__ == "__main__":
    sol = Solution()
    print(sol.wonderfulSubstrings("aabb"))
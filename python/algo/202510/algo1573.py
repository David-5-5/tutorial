# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def numWays(self, s: str) -> int:
        # 自行解答
        cnt = 0
        for ch in s:
            if ch == '1': cnt += 1

        #全部为 0 的情况，在 len(s)-1 个空隙中插入 2 两个隔板, 即 c(n-1,2), n = len(s)
        if cnt == 0: return (len(s) - 1) * (len(s)-2) // 2 % (10 ** 9 + 7)
        if cnt % 3 != 0: return 0

        s1_last, s2_first, s2_last, s3_first, unit  = 0, 0, 0, 0, cnt // 3
        cnt = 0
        for i, ch in enumerate(s):
            if ch == '1': 
                cnt += 1
                if cnt == unit: s1_last = i
                if cnt == unit + 1:s2_first = i
                if cnt == 2 * unit :s2_last = i
                if cnt == 2 * unit + 1:s3_first = i
            
        return (s2_first - s1_last) * (s3_first - s2_last) % (10 ** 9 + 7)  
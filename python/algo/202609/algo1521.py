
class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        # 参考题解，多维 DP 
        n = len(s)
        f = [[10 ** 5] * (k+1) for _ in range(n+1)]
        f[0][0] = 0

        # def cost(val: int) :
        #     if val == 0: return 0
        #     if val == 1: return 1
        #     elif 2 <= val <= 9: return 2
        #     elif 10 <= val <= 99: return 3
        #     else: return 4 # val == 100

        cost = lambda x: 1 if x == 1 else (2 if x < 10 else (3 if x < 100 else 4))

        for i in range(1, n+1):
            for j in range(min(i, k)+1):
                # 删除 s[i-1] 字符
                if j: f[i][j] = min(f[i][j], f[i-1][j-1])
                
                # 保留 s[i-1] 字符
                same = diff = 0
                for x in range(i, 0, -1):
                    # 关键找连续的 s[i-1] 作为 s[i-1] 字符串保留长度
                    if s[x-1] == s[i-1]:
                        same += 1
                        f[i][j] = min(f[i][j], f[x-1][j-diff] + cost(same))
                    else:
                        diff += 1
                        if diff > j: break
        return f[n][k]

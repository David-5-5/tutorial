# 周赛 300
class Solution:
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        # 自行解答
        # 列表中元素 第 i 天 [a,b]: 第 i 天 共有 a 人知道秘密，新增 b 人知道秘密，a 包含 b
        secret = [[0,0] for _ in range(n+1)] 
        secret[1] = [1,1] # 初始 第 1 天 1 人知道秘密，新增 1 人知道秘密
        for i in range(2, n+1):
            # 取前一天知道秘密的人数
            secret[i][0] = secret[i-1][0] 
            # 减去 forget 天前新增知道秘密的人数
            if i - forget > 0: secret[i][0] -= secret[i-forget][1] 
            # 加上 [i - forget + 1, i - delay] 区间新增秘密的人数
            for j in range(max(i-forget+1,0), max(i-delay,0)+1):
                secret[i][1] += secret[j][1]
            
            # 包含新增人数
            secret[i][0] += secret[i][1]
        return secret[-1][0]

if __name__ == "__main__":
    sol = Solution()
    print(sol.peopleAwareOfSecret(684,2,4))

from typing import List
from collections import defaultdict
# 使用埃氏算法计算最小质因子
MAXN = 10 ** 6
minprimefactor = [i for i in range((MAXN+1))]

for i in range(2, MAXN+1):
    if not minprimefactor[i] == i: continue
    minprimefactor[i] = i
    if i*i > MAXN: continue
    # 倍数从当前素数开始, 类如2 * 2, 后续元素 + 2
    # 3 从 3 * 3 开始,  后续元素 + 3,  不需要从 6 开始
    # 同理 5, 从 5 * 5开始,  后续元素 + 5 
    for j in range(i*i, MAXN+1, i):
        minprimefactor[j] = i


class Solution:
    def splitArray(self, nums: List[int]) -> int:
        f = defaultdict(lambda: float("INF"))
        
        prev = 0
        for num in nums:
            x, curmin = num, prev + 1
            # 从最小质因子计算出所有的质因子，例如30的最小的质因子为2，30/2=15,15的最小质因子为3,15/3=5为最后的质因子
            # minprimefactor[x] == x 表示 x 为质数
            # curmin的意义表示 num 的所有质因子和前序匹配后的最小值, prev = 0,
            # 例如初始时，[2, 3, 6] prev = 0
            # 处理 2 时    f[2] = 1 curmin = prev + 1 = 1
            # 处理 3 时    f[3] = 2 curmin = prev + 1 = 2
            # 处理 6 时    初始curmin = 3 首先 因子 2, curmin = min(f[2], 3) = 1
            #                           其次 因子 3, curmin = min(f[3], 1) = 1
            while minprimefactor[x] != x:
                f[minprimefactor[x]] = min(f[minprimefactor[x]], prev + 1)
                curmin = min(f[minprimefactor[x]], curmin)
                x //= minprimefactor[x]
            f[minprimefactor[x]] = min(f[minprimefactor[x]], prev + 1)
            prev = min(f[minprimefactor[x]], curmin)
        return prev

if __name__ == "__main__":
    sol = Solution()
    nums = [2,3,3,2,3,3]
    nums = [2,3,3,4,3,6]
    print(sol.splitArray(nums))
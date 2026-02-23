class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        
        # 复习推导 约瑟夫环
        # 思维过程举例 
        # n = 6 k = 3 举例
        # f(n) = [0, 1, 2, 3, 4, 5]     k=2 去除
        # f(n-1) = [3, 4, , 0, 1, 2]    剩余元素重新编号
        # 因此 f(n-1) 与 f(n) 的编号关系为 (除去 =2 之后， 从3开始重新编号)
        # f(n) = (f(n-1) + k) % n
        # 校验 f(n-1) = 3 -> 3 + 3 % n = 0 = f(n)
        # 校验 f(n-1) = 0 -> 0 + 3 % n = 3 = f(n)
        # 递归边界 n == 1, 返回 0 (从 0 开始编号 [0,...n-1])
        # 新的思路/方法，递归是观察 f(n) 元素编号 与 f(n-1) 重新编号后的关系
        def j(i: int) -> int:
            if i == 1: return 0
            return (j(i-1) + k) % i
        return j(n) + 1
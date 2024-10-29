from typing import List

N = 10 ** 5 + 1
g = [0] * N

# 预处理 omega ω 不同质因子个数 
# 注 Ω 所有质因子数量
for i in range(2, N):  
    if g[i] == 0:  # i 是质数
        for j in range(i, N, i):
            g[j] += 1  # i 是 j 的一个质因子

class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        # 参考题解
        n = len(nums)
        left = [-1] * n
        right = [n] * n
        st = []
        for i, v in enumerate(nums):
            while st and g[nums[st[-1]]] < g[v]:
                # j = st.pop()
                # right[j] = i
                right[st.pop()] = i
            if st: left[i] = st[-1]
            st.append(i)

        ans = 1
        for i, (num, l, r) in sorted(enumerate(zip(nums, left, right)), key=lambda p:p[1], reverse=True):
            if k == 0: break
            cnt = min(k, (i-l)*(r-i))
            # !!! IMPORTANT !!!
            # pow(num, cnt, 10 ** 9 + 7) 与
            # num ** cnt 性能差距巨大
            ans = (ans * pow(num, cnt, 10 ** 9 + 7)) % (10 ** 9 + 7)
            k -= cnt
        return ans % (10 ** 9 + 7)

if __name__ == "__main__":
    sol = Solution()
    nums, k = [19,12,14,6,10,18], 3
    print(sol.maximumScore(nums, k))
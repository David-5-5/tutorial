from collections import defaultdict
import heapq

class BIT:
    # 数组从零开始
    def __init__ (self, n:int) -> None:
        self.nums = [0] * n

    # 固定 +1
    def add(self, i:int):
        while i < len(self.nums):
            self.nums[i] += 1
            i += i & -i

    def query(self, i:int) ->int:
        res = 0
        while i > 0:
            res += self.nums[i]
            i -= i & -i
        return res

class Solution:
    def minInteger(self, num: str, k: int) -> str:
        # 自行解答 !!!OVERTIME!!!
        inv_c = [0] * 10

        n_list = [int(d) for d in num]

        h = [] # (d, i, inv)
        for i, d in enumerate(n_list):
            if inv_c[d]:
                heapq.heappush(h, (d, i, inv_c[d]))

            for v in range(d):
                inv_c[v] += 1

        switch = []
        mn_i = len(num)
        while h and k:
            _, i, inv = heapq.heappop(h)
            if inv > k or i > mn_i:
                if mn_i > i: mn_i = i
                continue
            switch.append((i, inv))
            k -= inv
        
        if k and mn_i < len(num):
            switch.append((mn_i,k))

        switch.sort() # 超时 执行时间是上述语句 20 倍
        for i, inv in switch: 
            n_list = n_list[0:i-inv] + n_list[i:i+1] + n_list[i-inv:i] + n_list[i+1:]

        return "".join([str(d) for d in n_list])
    
    def minInteger2(self, num: str, k: int) -> str:
        # 参考题解，遍历字符串从最高位，遍历后续的 0-9 进行替换
        # 引入树状数组，动态更新移位后，后续的更新位置
        n = len(num)

        bit = BIT(n+1)

        pos = defaultdict(list)
        for i in range(n-1,-1,-1):
            pos[int(num[i])].append(i+1)

        ans = ""
        for i in range(1, n+1):
            for j in range(10):
                if pos[j]:
                    behind = bit.query(n) - bit.query(pos[j][-1])
                    inv = pos[j][-1] + behind - i
                    if inv <= k:
                        ans += str(j)
                        inx = pos[j].pop()
                        bit.add(inx)
                        k -= inv
                        break
        return ans

if __name__ == "__main__":
    sol = Solution()
    num, k = "4321", 4
    print(sol.minInteger(num, k))
    print(sol.minInteger2(num, k))

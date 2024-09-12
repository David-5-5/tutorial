from typing import List

# 双周赛 120
class Solution:
    def placedCoins(self, edges: List[List[int]], cost: List[int]) -> List[int]:
        # 自行解答 
        n = len(cost)
        g = [[] for _ in range(n)]

        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        coin = [0] * n

        def dfs(u:int, fa:int) -> tuple[List[int], List[int]]:
            pos, neg = [], []
            
            if cost[u] > 0: pos.append(cost[u])
            else: neg.append(cost[u])

            for v in g[u]:
                if v == fa: continue
                _pos, _neg = dfs(v, u)
                pos.extend(_pos)
                neg.extend(_neg)
            
            #  以上的标准 dfs 代码，以下是按题目要求的计算输出
            pos.sort(reverse=True)
            neg.sort()
            mul = 1
            if len(pos) + len(neg) < 3: 
                coin[u] = 1
            elif len(pos) + len(neg) == 3:
                for v in pos + neg :mul *= v
                if mul > 0: coin[u] = coin[u] = mul
            else: # 4个以上的数
                if len(neg) >= 2: # 两个以上负数
                    mul *= neg[0] * neg[1] # 取两个负数
                    if pos:mul *= pos[0]   # 有正书情况下，优先乘以最大的正数，这是最大值的候选
                    else: mul *= neg[2]    # 没有正数的情况下，乘以第三个负数
                    if len(pos) >= 3:      # 正数超过三个的情况下，比较三个正数乘积和二负一正的乘积大小
                        mul = max(mul, pos[0]*pos[1]*pos[2])
                else:
                    mul = pos[0]*pos[1]*pos[2] # 仅一个负数时，返回三个正数的乘积
                if mul > 0: coin[u] = coin[u] = mul

            return pos[0:3], neg[0:2] # 最多保留3个最大的正数和两个最小的负数

        dfs(0,-1)
        return coin

if __name__ == "__main__":
    sol = Solution()
    edges, cost = [[0,1],[0,2],[0,3],[0,4],[0,5]], [1,2,3,4,5,6]
    edges, cost = [[0,1],[0,2]], [1,2,-2]
    print(sol.placedCoins(edges, cost))
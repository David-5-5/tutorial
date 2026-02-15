import sys
from collections import defaultdict, deque

# 对应C++的high常量
HIGH = 29
# 对应C++的MAX_TRIE_NODE（Python用动态结构，无需预分配）
trie = []
trie_idx = 0

# 并查集类（完全对齐你的UnionFind）
class UnionFind:
    def __init__(self, n):
        self.fa = list(range(n))  # iota的Python实现
    
    def find(self, x):
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])  # 路径压缩
        return self.fa[x]
    
    def merge(self, from_, to):
        x = self.find(from_)
        y = self.find(to)
        if x != y:
            self.fa[x] = y
    
    def is_same(self, x, y):
        return self.find(x) == self.find(y)

# Solution类（完全对齐你的C++代码）
class Solution:
    def resetRoot(self):
        global trie, trie_idx
        trie_idx = 0
        # 初始化根节点：[son0, son1, cnt, id]
        trie = [[-1, -1, 0, -1]]
    
    def insert(self, val, id_):
        global trie, trie_idx
        node = 0
        trie[node][2] += 1  # cnt++
        for i in range(HIGH, -1, -1):
            v = (val >> i) & 1
            if trie[node][v] == -1:
                trie_idx += 1
                trie.append([-1, -1, 0, -1])  # 新建节点
                trie[node][v] = trie_idx
            node = trie[node][v]
            trie[node][2] += 1
        trie[node][3] = id_  # 设置id
    
    def remove(self, val):
        global trie, trie_idx
        node = 0
        trie[node][2] -= 1  # cnt--
        for i in range(HIGH, -1, -1):
            v = (val >> i) & 1
            node = trie[node][v]
            trie[node][2] -= 1
    
    def min_xor(self, val):
        res = 0
        node = 0
        for i in range(HIGH, -1, -1):
            v = (val >> i) & 1
            # 检查son[v]是否存在且cnt>0
            if trie[node][v] != -1 and trie[trie[node][v]][2] > 0:
                node = trie[node][v]
            elif trie[node][v^1] != -1 and trie[trie[node][v^1]][2] > 0:
                res |= (1 << i)
                node = trie[node][v^1]
            else:
                return (-1, -1)
        return (res, trie[node][3])
    
    def xorMst(self, n, nums):
        uf = UnionFind(n)
        # 对应C++的unordered_map<int, list<int>> cc
        cc = defaultdict(deque)  # 用deque模拟list，支持高效拼接
        w2id = dict()  # 对应C++的unordered_map<int, int> w2id
        self.resetRoot()
        
        for i in range(n):
            if nums[i] in w2id:
                x = w2id[nums[i]]
                uf.merge(i, x)
            else:
                w2id[nums[i]] = i
                cc[i].append(i)
                self.insert(nums[i], i)
        
        ans = 0
        while len(cc) > 1:
            dis = dict()  # 对应C++的unordered_map<int, pair<int, int>>
            # 遍历每个连通块
            for x in list(cc.keys()):  # list(keys())避免遍历中修改字典
                vert = cc[x]
                # 删除当前连通块的所有节点
                for u in vert:
                    self.remove(nums[u])
                # 找最小异或边
                for u in vert:
                    weight = self.min_xor(nums[u])
                    if weight[0] == -1:
                        continue
                    if x not in dis or weight[0] < dis[x][0]:
                        dis[x] = weight
                # 插回当前连通块的所有节点
                for u in vert:
                    self.insert(nums[u], u)
            
            # 合并连通块
            to_erase = []
            for x in dis:
                if x not in cc:
                    continue
                weight = dis[x]
                y = uf.find(weight[1])
                if uf.is_same(x, y):
                    continue
                ans += weight[0]
                # 合并连通块（对应C++的splice）
                uf.merge(x, y)
                cc[y].extend(cc[x])  # 模拟splice
                to_erase.append(x)
            
            # 移除合并后的连通块
            for x in to_erase:
                del cc[x]
        
        return ans

# 主函数（对齐你的main）
def main():
    # 加速输入（对应C++的ios::sync_with_stdio(false)）
    input = sys.stdin.read().split()
    ptr = 0
    n = int(input[ptr])
    ptr += 1
    a = []
    for _ in range(n):
        a.append(int(input[ptr]))
        ptr += 1
    
    sol = Solution()
    print(sol.xorMst(n, a))

if __name__ == "__main__":
    main()
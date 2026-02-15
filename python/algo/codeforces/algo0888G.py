class Node:
    def __init__(self):
        self.son = [None, None]  # 0 和 1 两个子节点
        self.cnt = 0             # 经过该节点的数字数量
        self.ids = set()         # 存储连通块的 id

class UnionFind:
    """并查集类，用于维护连通分量"""
    def __init__(self, n):
        self.fa = list(range(n))  # 父节点数组
    
    def find(self, x):
        """查找x的根节点，并进行路径压缩"""
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]
    
    def merge(self, from_node, to_node):
        """合并两个节点所在的集合"""
        x = self.find(from_node)
        y = self.find(to_node)
        if x != y:
            self.fa[x] = y
    
    def is_same(self, x, y):
        """判断两个节点是否在同一集合"""
        return self.find(x) == self.find(y)

class Solution:
    def __init__(self):
        self.high = 30  # 数字的最高位（0~30 覆盖 int 范围）
        self.root = Node()
    
    def insert(self, val, id_):
        """将数字val（带id_）插入字典树"""
        node = self.root
        node.cnt += 1
        for i in range(self.high, -1, -1):
            v = (val >> i) & 1  # 获取第i位的二进制值
            if not node.son[v]:
                node.son[v] = Node()
            node = node.son[v]
            node.cnt += 1
        node.ids.add(id_)
    
    def remove(self, val, id_):
        """从字典树中移除数字val（带id_）"""
        node = self.root
        node.cnt -= 1
        for i in range(self.high, -1, -1):
            v = (val >> i) & 1
            node = node.son[v]
            node.cnt -= 1
        node.ids.discard(id_)  # discard避免key不存在报错
    
    def min_xor(self, val):
        """查找与val异或最小的数字，返回(异或值, 对应id)"""
        res = 0
        node = self.root
        for i in range(self.high, -1, -1):
            v = (val >> i) & 1
            # 优先走相同位的子节点（异或值更小）
            if node.son[v] and node.son[v].cnt > 0:
                node = node.son[v]
            elif node.son[v ^ 1] and node.son[v ^ 1].cnt > 0:
                res |= 1 << i  # 异或位为1，累计结果
                node = node.son[v ^ 1]
            else:
                return (-1, -1)  # 字典树为空
        # 返回异或值和第一个id（set转list取第一个）
        return (res, next(iter(node.ids)))
    
    def xorMst(self, n, nums):
        """计算XOR最小生成树的总权重"""
        uf = UnionFind(n)
        # 初始化连通分量：每个节点独立为一个连通块
        cc = {}
        for i in range(n):
            cc[i] = [i]
            self.insert(nums[i], i)
        
        ans = 0
        # 直到所有节点合并为一个连通块
        while len(cc) > 1:
            dis = {}  # 存储每个连通块的最小异或边 (key: 连通块根, value: (异或值, 目标id))
            # 遍历每个连通块
            for x in list(cc.keys()):  # 用list避免遍历中字典修改报错
                vert = cc[x]
                # 临时移除当前连通块的所有节点（避免和自身比较）
                for u in vert:
                    self.remove(nums[u], u)
                # 查找当前连通块到其他连通块的最小异或边
                for u in vert:
                    cost_v = self.min_xor(nums[u])
                    if cost_v[0] == -1:
                        continue
                    # 更新当前连通块的最小边
                    if x not in dis or cost_v[0] < dis[x][0]:
                        dis[x] = cost_v
                # 恢复当前连通块的节点到字典树
                for u in vert:
                    self.insert(nums[u], u)
            
            # 合并连通块
            merged = set()  # 记录已合并的连通块，避免重复处理
            for x in dis:
                if x in merged:
                    continue
                cost, v_id = dis[x]
                y = uf.find(v_id)
                if uf.is_same(x, y):
                    continue
                # 累加边权，合并连通块
                ans += cost
                uf.merge(x, y)
                # 合并连通块的节点列表
                cc[y].extend(cc[x])
                # 移除被合并的连通块
                del cc[x]
                merged.add(x)
        
        return ans

if __name__ == "__main__":
    import sys
    input = sys.stdin.read().split()
    n = int(input[0])
    a = list(map(int, input[1:n+1]))
    # 每次运行都新建Solution实例（避免字典树残留）
    print(Solution().xorMst(n, a))
from sortedcontainers import SortedDict
class Solution:
    def minMalwareSpread(self, graph, initial) -> int:
        '''
        自行解答，解题思路
        使用dfs深度遍历算法, 查找图的连通子图，每个子图存在病毒节点将会感染
        遍历每个子图为一个集合减去感染病毒的集合initial,得到diff:
        1、len(tree) == len(diff),集合数量不变, 忽略
        2、len(tree) == len(diff) + 1, 集合数量减少1, 则该子图仅一个病毒节点，
           移除该节点病毒, 能够减少感染len(tree)数量的节点
        3、len(tree) > len(diff) + 1, 集合数量减少大于1, 则该子图有多个病毒节点，
           移除该子图中任一节点病毒, 该子图仍旧感染病毒, 能够减少感染数量为0
        存储字典,key减少感染的数量, value为移除节点编号
        最后返回最大key值中的最小编号节点
        '''
        n = len(graph)
        left = [i for i in range(n)]
        forest = []
        tree = []

        def dfs(v:int):
            inx = left.index(v)
            left.pop(inx)
            tree.append(v)
            for i in range(n):
                if v != i and graph[v][i] == 1:
                    if i in left:
                        dfs(i)
        while left:
            dfs(left[0])
            forest.append(set(tree))
            tree = []
        
        iset = set(initial)
        intes = SortedDict()
        for tree in forest:
            sub = tree - iset
            if len(tree) - len(sub) > 0:
                vset = tree - sub
                if len(vset) == 1:
                    if len(tree) in intes.keys():
                        intes[len(tree)].extend(vset)
                    else:
                        intes[len(tree)] = list(vset)
                else:
                    if 0 in intes.keys():
                        intes[0].extend(vset)
                    else:
                       intes[0] = list(vset) 
        maxkey = max(intes.keys())
        return min(intes[maxkey])
   
if __name__ == "__main__":
    sol = Solution()
    graph, initial = [[1,1,0],[1,1,0],[0,0,1]], [0,1]
    graph, initial = [[1,0,0],[0,1,0],[0,0,1]], [0,2]
    graph, initial  = [[1,1,1],[1,1,1],[1,1,1]], [1,2]
    print(sol.minMalwareSpread(graph, initial))
class Solution:
    def sumOfDistancesInTree(self, n: int, edges) :
        graph = [[] for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])
        
        sum_dis = [0] * n
        # Each element is tuple, include: parent, level, chidrens, count_of_child_recursive
        # (-1, 0, 2, [1, 2])
        # The index of tree is vertex no. 
        # The root fixed to vertex 0.
        p_i = 0 # parent index in tuple
        l_i = 1 # level index in tuple
        cc_i = 2 # child count index in tuple
        chd_i = 3 # children index in tuple
        tree = [[-1, 0, 0, []] for _ in range(n)]
        todo = [(-1, 0)]
        while todo:
            parent, cur = todo.pop(0)
            tree[cur][p_i] = parent
            if parent != -1:
                tree[cur][l_i] = tree[parent][l_i] + 1
            for child in graph[cur]:
                if child != parent:
                    tree[cur][chd_i].append(child)
                    todo.append((cur, child))

        # post traver to calcuate the count_of_child_recursive for each node
        stack = []
        stack.append(0)
        inx = 0
        while inx < len(stack):
            stack.extend(tree[stack[inx]][chd_i])
            inx += 1
        
        # Get rid of root
        stack.pop(0)
        while stack:
            child = stack.pop(-1)
            parent = tree[child][p_i]
            tree[parent][cc_i] += tree[child][cc_i] + 1
            sum_dis[0] += tree[child][l_i]

        todo_c = []
        todo_c.extend(tree[0][chd_i])
        while todo_c:
            cur = todo_c.pop(0)
            parent = tree[cur][p_i]
            sum_dis[cur] = sum_dis[parent] - 2*tree[cur][cc_i] + n - 2
            todo_c.extend(tree[cur][chd_i])

        return sum_dis


if __name__ == "__main__":
    sol = Solution()
    n, edges = 6, [[0,1],[0,2],[2,3],[2,4],[2,5]]
    print(sol.sumOfDistancesInTree(n, edges))
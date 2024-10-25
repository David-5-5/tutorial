

from collections import defaultdict


n =  int(input().strip())
color = [int(i) for i in input().split()]
tree = [int(i) for i in input().split()]


treeNode = defaultdict(list)
root = -1
for i, v in enumerate(tree):
    
    if v == 0: root = i
    else:
        treeNode[v-1].append(i)

ans = [0, 0]
def dfs(node):
    if color[node] == 0:
        if len(treeNode[node]) == 0 or any(color[c]==1 for c in treeNode[node]):
            ans[0] += 1
    else:
        if len(treeNode[node]) == 0 or all(color[c]==0 for c in treeNode[node]):
            ans[1] += 1
    for c in treeNode[node]: dfs(c)

dfs(root)
print(" ".join(str(i) for i in ans))
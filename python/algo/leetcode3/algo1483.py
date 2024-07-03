from typing import List
class TreeAncestor:

    def __init__(self, n: int, parent: List[int]):
        # pa = [[p] + [-1] * m for p in parent]
        lg = n.bit_length()
        pa = [ [-1] * lg for _ in range(n)]
        for i in range(n):
            pa[i][0] = parent[i]
        for e in range(1, lg):
            for i in range(n):
                if pa[i][e-1] != -1:
                    pa[i][e] = pa[pa[i][e-1]][e-1]
        
        self.pa = pa

    def getKthAncestor(self, node: int, k: int) -> int:
        ancestor = node
        for i in range(k.bit_length()):
            if k >> i & 1:
                ancestor = self.pa[ancestor][i]
            if ancestor < 0: return ancestor
        return ancestor


if __name__ == "__main__":
    sol = TreeAncestor(6,[-1,2,3,4,5,0])
    print(sol.getKthAncestor(1,4))



        



# Your TreeAncestor object will be instantiated and called as such:
# obj = TreeAncestor(n, parent)
# param_1 = obj.getKthAncestor(node,k)
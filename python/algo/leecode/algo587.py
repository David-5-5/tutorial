class Solution:
    def outerTrees(self, trees) :
        n = len(trees)
        trees.sort()

        # s1 top of stack, p waitting for put
        def cross(s2, s1, p):
            return (s1[0]-s2[0])*(p[1]-s1[1]) - (s1[1]-s2[1])*(p[0]-s1[0])
        
        ans_down = []
        for i in range(n):
            while len(ans_down) > 1 and cross(ans_down[-2], ans_down[-1], trees[i]) < 0:
                ans_down.pop(-1)
            ans_down.append(trees[i])

        ans_up = []
        for i in range(n-1, -1, -1):
            while len(ans_up) > 1 and cross(ans_up[-2], ans_up[-1], trees[i]) < 0:
                ans_up.pop(-1)
            ans_up.append(trees[i])

        for point in ans_up:
            if point not in ans_down:
                ans_down.append(point)

        return ans_down

if __name__ == "__main__":
    sol = Solution()
    trees = [[1,2],[2,2],[4,2]]
    print(sol.outerTrees(trees))    
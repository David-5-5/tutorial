from typing import List

class Solution:
    def matrixSumQueries(self, n: int, queries: List[List[int]]) -> int:
        vis_r = set()
        vis_c = set()

        ans = 0
        for tp, index, val in reversed(queries):
            if tp == 0:
                if index not in vis_r:
                    ans += val * (n-len(vis_c))
                    vis_r.add(index)
            else:
                if index not in vis_c:
                    ans += val * (n-len(vis_r))
                    vis_c.add(index)
        return ans

    def matrixSumQueries2(self, n: int, queries: List[List[int]]) -> int:
        vis = [set(),set()]

        ans = 0
        for tp, index, val in reversed(queries):
            if index not in vis[tp]:
                ans += val * (n-len(vis[1-tp]))
                vis[tp].add(index)
        return ans


if __name__ == "__main__":
    sol = Solution()
    n, queries = 3, [[0,0,1],[1,2,2],[0,2,3],[1,0,4]]
    print(sol.matrixSumQueries2(n, queries))

from functools import lru_cache

class Solution:
    def minimumMoves(self, grid) -> int:
        n = len(grid)
        visited = []
        @lru_cache(maxsize = None)
        def move(head, tail):
            visited.append((head[0]*n+head[1], tail[0]*n+tail[1]))
            if head == (n-1,n-2) and tail == (n-1,n-1):
                visited.pop(-1)
                return 0
            ret = float("inf")
            # The snake is horizontal
            if head[0] == tail[0]:
                # to left
                if tail[1]+1 < n and grid[tail[0]][tail[1]+1] == 0:
                    ret = min(ret, 1 + move(tail, (tail[0], tail[1]+1)))
                # to down and to vertical
                if head[0]+1 < n and grid[head[0]+1][head[1]] == 0 and grid[tail[0]+1][tail[1]] == 0:
                    # to down
                    ret = min(ret, 1 + move((head[0]+1,head[1]), (tail[0]+1,tail[1])))
                    # change to vertical
                    if (head[0]*n+head[1], (head[0]+1)*n+head[1]) not in visited :
                        ret = min(ret, 1 + move(head, (head[0]+1,head[1])))
            else:
                # to left or to horizontal
                if head[1]+1 < n and grid[head[0]][head[1]+1] == 0 and grid[tail[0]][tail[1]+1] == 0:
                    ret = min(ret, 1 + move((head[0],head[1]+1), (tail[0], tail[1]+1)))
                    # change to horizontal
                    if (head[0]*n+head[1], head[0]*n+head[1]+1) not in visited :
                        ret = min(ret, 1 + move(head, (head[0],head[1]+1)))
                # to down
                if tail[0]+1 < n and grid[tail[0]+1][tail[1]] == 0:
                    # to down
                    ret = min(ret, 1 + move(tail, (tail[0]+1,tail[1])))
            visited.pop(-1)
            return ret                    

        ret = move((0,0), (0,1))
        return ret if ret != float("inf") else -1


if __name__ == "__main__":
    sol = Solution()
    grid = [[0,0,0,0,0,1],
               [1,1,0,0,1,0],
               [0,0,0,0,1,1],
               [0,0,1,0,1,0],
               [0,1,1,0,0,0],
               [0,1,1,0,0,0]]
    grid = [[0,0,1,1,1,1],
               [0,0,0,0,1,1],
               [1,1,0,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,0]]
    print(sol.minimumMoves(grid))
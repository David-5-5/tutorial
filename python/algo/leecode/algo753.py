class Solution:

    def crackSafe(self, n: int, k: int) -> str:

        def toKns(x: int, k: int) -> str:
            tok = []
            while x:
                tok.append(str(x % k))
                x //= k
            return "".join(tok[::-1])
        safe = []
        if n == 1:
            for i in range(k):
                safe.append(str(i))
            return "".join(safe)

        def dfs(begin: str):
            safe.append(begin[-1])
            while begin in graph.keys() and graph[begin]:
                prefix = "".join(safe[2-n:]) if n > 2 else ""
                for i in range(len(graph[begin])-1, -1, -1):
                    next = prefix + graph[begin][i]
                    if next in graph.keys() and len(graph[next]) > 0:
                        break
                if i < 0:
                    child = prefix + graph[begin].pop(0)
                else:
                    child = prefix + graph[begin].pop(i)
                dfs(child)

        graph = {}
        for i in range(k ** n):
            val = toKns(i, k).rjust(n, '0')
            if val[:-1] not in graph.keys():
                graph[val[:-1]] = [val[-1]]
            else:
                graph[val[:-1]].append(val[-1])
        for i in range(n-2):
            safe.append('0')
        dfs("".rjust(n-1, '0'))
        return "".join(safe)

if __name__ == "__main__":
    sol = Solution()
    print(sol.crackSafe(4, 8))
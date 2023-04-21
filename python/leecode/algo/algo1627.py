from functools import lru_cache


class Solution:
    def areConnected(self, n: int, threshold: int, queries) :
        @lru_cache
        def gcd(a: int, b: int) -> int:
            return gcd(b % a, a) if a else b

        qn = len(queries)
        ret = [False] * qn
        for i in range(qn):
            if queries[i][0] > queries[i][1]:
                queries[i][0], queries[i][1] = queries[i][1], queries[i][0]
        
        for qi, q in sorted(enumerate(queries)):
            if gcd(q[0], q[1]) > threshold:
                ret[qi] = True
        return ret
        

if __name__ == '__main__':
    sol = Solution()
    n = 10 ** 4
    import random
    queries = [[random.randint(1,n), random.randint(1,n)] for _ in range(10 ** 5)]
    sol.areConnected(n, 2, queries)
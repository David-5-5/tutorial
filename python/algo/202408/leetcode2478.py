from functools import cache


class Solution:
    
    def beautifulPartitions(self, s: str, k: int, minLength: int) -> int:
        n = len(s)
        primes = set([2, 3, 5, 7])
        non_p = set([0, 1, 4, 6, 8, 9])
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, b:int) -> int:
            if b == n:
                if i == k: return 1
                else :return 0
            
            if int(s[b]) not in primes or i == k:return 0
            res = 0
            for e in range(b, n):
                if e - b + 1 >= minLength and int(s[e]) in non_p:
                    res += dfs(i+1, e+1)

            return res % MOD
        return dfs(0,0)

    def beautifulPartitions_oom(self, s: str, k: int, minLength: int) -> int:
        n = len(s)

        @cache
        # 3-dimension out of memory
        def dfs(i:int, b:int, c:int) -> int:
            if c == n:
                if b == n and i == k: return 1
                return 0
            
            if int(s[b]) not in primes:return 0

            # 不选
            res =  dfs(i, b, c+1)

            # 选
            if int(s[b]) in primes and int(s[c]) in non_p and c-b+1>=minLength:
                res += dfs(i+1,c+1,c+1)

            return res % MOD
        return dfs(0,0,0)

if __name__ == "__main__":
    sol = Solution()
    s, k, minLength = "23542185131", 3, 2
    s, k, minLength = "783785773384176934289375227482689165849492976812467785683386278174726387323439126591215754338243182568593136425844311746579778183459442145731968426766928235653778836947994556929995999683642777387746469139589829866577575756998586128158414554339653174377596926549256623896289435891959798428534464597491418193896419889134377816487538518423698853875351767747243291188516143621623125158437539478752786823417568294359771526489365436412571178946317373359236134757545633377292182744958724233332485482973962411286389732353167715514534772645841751926663925911732117799911551693893763579495935894933682583245275696324932967212524858964894346853399284184357536",136,2
    print(sol.beautifulPartitions(s, k, minLength))

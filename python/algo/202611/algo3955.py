class Solution:
    def generateValidStrings(self, n: int, k: int) -> list[str]:
        ans = []
        for x in range(1 << n):
            s = f"{x:0{n}b}"
            cost, conti = 0, False
            for i in range(n):
                if s[i] == '1':
                    cost += i
                    if cost > k: break
                    if i and s[i-1] == '1':
                        conti = True
                        break
            if cost <= k and not conti:
                ans.append(s)
        return ans
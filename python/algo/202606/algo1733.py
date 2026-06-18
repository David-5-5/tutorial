from typing import List

# 贪心 八、其他
class Solution:
    def minimumTeachings(self, n: int, languages: List[List[int]], friendships: List[List[int]]) -> int:
        # 遍历语言
        lans = list(map(set, languages))

        m = len(friendships)
        comms = [False] * m
        for i, f in enumerate(friendships):
            m1, m2 = f[0] - 1, f[1] - 1
            if lans[m1] & lans[m2]: comms[i] = True
        
        ans = len(languages)
        for i in range(1, n+1):
            learn = set()
            for j, comm in enumerate(comms):
                if comm: continue
                m1, m2 = friendships[j][0] - 1, friendships[j][1] - 1
                if i not in lans[m1]: learn.add(m1)
                if i not in lans[m2]: learn.add(m2)
            if len(learn) < ans:
                ans = len(learn)
        return ans


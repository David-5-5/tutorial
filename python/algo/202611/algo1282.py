from collections import defaultdict

class Solution:
    def groupThePeople(self, groupSizes: list[int]) -> list[list[int]]:
        ans, grp = [], defaultdict(list)

        for i, g in enumerate(groupSizes):
            grp[g].append(i)
            if len(grp[g]) == g:
                ans.append(grp[g])
                del grp[g]
        return ans
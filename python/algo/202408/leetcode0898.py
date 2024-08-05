from typing import List

class Solution:
    def subarrayBitwiseORs(self, arr: List[int]) -> int:

        ans = set()
        ors = set()
        for x in arr:
            ors = { o | x for o in ors}
            ors.add(x)
            ans |= ors

        return len(ans)

if __name__ == "__main__":
    sol = Solution()
    print(sol.subarrayBitwiseORs([1,2,4]))
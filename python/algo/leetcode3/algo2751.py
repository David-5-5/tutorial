from typing import List


class Solution:
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        nocoll = []
        st = []

        for i, _ in sorted(enumerate(positions), key=lambda p:p[1]):
            if directions[i] == 'R':
                st.append(i)
                continue
            while st and healths[st[-1]] < healths[i]:
                st.pop()
                healths[i] -= 1
            if st and healths[st[-1]] == healths[i]:
                st.pop()
            elif st and healths[st[-1]] > healths[i]:
                healths[st[-1]] -= 1
            elif not st:
                nocoll.append(i)
        
        nocoll.extend(st)
        nocoll.sort()
        return [healths[i] for i in nocoll]

if __name__ == "__main__":
    sol = Solution()
    positions, healths, directions = [13,3], [17,2], "LR"
    print(sol.survivedRobotsHealths(positions, healths, directions))

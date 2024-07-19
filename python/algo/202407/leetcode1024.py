from typing import List

class Solution:
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        rightMost = [0] * (time + 1)
        for start, end in clips:
            if start > time: continue
            rightMost[start] = max(rightMost[start], end)

        ans = cur = next = 0
        for i in range(time):
            next = max(next, rightMost[i])
            if i == cur:
                if i == next: return -1
                ans += 1
                cur = next
        return ans

if __name__ == "__main__":
    sol = Solution()
    clips = [[0,1],[1,2]]
    print(sol.videoStitching(clips, 5))
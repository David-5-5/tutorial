from typing import Counter, List

class Solution:
    def maximizeWin(self, prizePositions: List[int], k: int) -> int:
        # 没有看懂视频讲解，先自行解答
        cnt = list(Counter(prizePositions).items())
        cnt.sort()
        print(cnt)
        n = len(cnt)
        l1 = r1 = 0
        fw = sw = 0
        while r1+1 < n and cnt[r1+1][0]-cnt[l1][0] <= k:
            fw += cnt[r1][1]
            r1 += 1
        fw += cnt[r1][1]

        l2 = r2 = r1 + 1
        while r2+1 < n and cnt[r2+1][0]-cnt[l2][0] <= k:
            sw += cnt[r2][1]
            r2 += 1
        if r2 < n: sw += cnt[r2][1]
        
        m_fw, ans = fw, fw + sw

        while r2 + 1 < n:
            r2 += 1
            sw += cnt[r2][1]
            while cnt[r2][0] - cnt[l2][0] > k:
                sw -= cnt[l2][1]
                l2 += 1
            
            while r1 + 1 < l2:
                r1 += 1
                fw += cnt[r1][1]
                while cnt[r1][0]-cnt[l1][0] > k:
                    fw -= cnt[l1][1]
                    l1 += 1
                m_fw = max(m_fw, fw)
            ans = max(ans, sw + m_fw)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    prizePositions, k = [1,1,2,2,3,3,5], 2
    print(sol.maximizeWin(prizePositions, k))
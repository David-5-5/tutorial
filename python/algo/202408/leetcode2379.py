class Solution:
    def minimumRecolors(self, blocks: str, k: int) -> int:
        cnt = blocks[0:k-1].count('W')
        ans = len(blocks)
        for i in range(k-1, len(blocks)):
            if blocks[i] == 'W':cnt += 1
            ans = min(ans, cnt)
            if blocks[i-k+1] == 'W':cnt -= 1
        return ans
    
if __name__ == '__main__':
    blocks, k = "WBBWWBBWBW", 7
    print(Solution().minimumRecolors(blocks, k))
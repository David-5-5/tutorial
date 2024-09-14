# 周赛 301 
class Solution:
    def canChange(self, start: str, target: str) -> bool:
        # 自行解答
        n = len(start)
        i = j = 0

        while i < n or j < n: # 从这到 break,消除末尾的 _
            while i < n and start[i] == '_':
                i += 1
            while j < n and target[j] == '_':
                j += 1
            
            if j == n or i == n: break

            if (start[i] == target[j] == 'L' and j <= i ) or start[i] == target[j] == 'R' and j >= i:
                i += 1
                j += 1
            else:
                return False

        return i == j


if __name__ == "__main__":
    sol = Solution()
    start, target = "_L__R__R_", "L______RR"
    # start, target = "R_L_", "__LR"
    print(sol.canChange(start, target))
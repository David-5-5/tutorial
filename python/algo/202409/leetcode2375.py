# 周赛 306
class Solution:
    def smallestNumber(self, pattern: str) -> str:
        # 自行解答
        # 默认为最小的序列
        perm = [str(i) for i in range(1, len(pattern)+2)]
        lasti = 0
        for i, p in enumerate(pattern):
            if p == 'I': # 若 pattern == 'I' 保持序列不变，更新 I 出现的最后位置
                lasti = i + 1
            else: # 若 pattern == 'I'
                c = perm.pop(i+1) # 将 i + 1 位置的字符弹出
                perm.insert(lasti, c) # 并插入到最后 I 所在的位置后面
        return ''.join(perm)


if __name__ == "__main__":
    sol = Solution()
    print(sol.smallestNumber("IIIDIDDD"))


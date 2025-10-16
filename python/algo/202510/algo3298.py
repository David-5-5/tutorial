from collections import Counter, defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.3.2 越长越合法
class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        # 自行解答
        cnt2 = Counter(word2)
        cnt1 = defaultdict(int)

        # 判断是否包含，性能较差
        def contain() -> bool:
            for k, v in cnt2.items():
                if cnt1[k] < v: return False
            return True

        l = ans = 0
        for ch in word1:
            cnt1[ch] += 1
            cur = True
            while cur and contain():
                cnt1[word1[l]] -= 1
                cur = cnt1[word1[l]] >= cnt2[word1[l]]
                l += 1
            ans += l
        return ans
    
    
    def validSubstringCount2(self, word1: str, word2: str) -> int:
        # 自行解答 - 优化
        cnt2 = Counter(word2)
        cnt1 = defaultdict(int)

        # 有 match2 的长度代替 contain 函数
        l = ans = match2 = 0
        for ch in word1:
            cnt1[ch] += 1
            if cnt1[ch] <= cnt2[ch]: match2 += 1
            while match2 == len(word2):
                cnt1[word1[l]] -= 1
                if cnt1[word1[l]] < cnt2[word1[l]]: match2 -= 1
                l += 1
            ans += l
        return ans
# 周赛 374 
from collections import Counter


class Solution:
    def countCompleteSubstrings(self, word: str, k: int) -> int:

        def f(seg:str) -> int:
            n = len(seg)
            '''
            最多包含26个长度为 k 的字母
            用滑动窗口分别求解包含 1, 2, ... 26 个时的子字符串数量
            其长度分别为 k, 2k, ... 26k
            '''
            res = 0
            for i in range(1, 27):
                # 字符串长度至为 k * i
                if n < k * i: break
                
                # 第一个窗口
                # cnt = Counter(seg[0:i*k])
                # if all(v==k for v in cnt.values()):
                #     res += 1
                cnt = Counter(seg[0:i*k-1])
                for out, in_ in zip(seg, seg[i*k-1:]):
                    cnt[in_] += 1
                    if all(v==0 or v==k for v in cnt.values()):
                        res += 1
                    cnt[out] -= 1

            return res

        # 相比较于 f 用数组代替Counter
        def f2(seg:str) -> int:
            n = len(seg)
            res = 0
            for i in range(1, 27):
                # 字符串长度至为 k * i
                if n < k * i: break
                
                # 第一个窗口
                cnt = [0] * 26
                for ch in seg[0:i*k-1]:
                    cnt[ord(ch)-ord('a')] += 1

                for out, in_ in zip(seg, seg[i*k-1:]):
                    cnt[ord(in_)-ord('a')] += 1
                    if all(v==0 or v==k for v in cnt):
                        res += 1

                    cnt[ord(out)-ord('a')] -= 1

            return res

        # 分组循环 模板
        ans = i = 0
        n = len(word)
        while i < n:
            start = i
            i += 1
            while i < n and abs(ord(word[i-1])-ord(word[i]))<=2:
                i += 1
            # now i is the next start, i-1 is end
            # ans += f(word[start:i])
            ans += f2(word[start:i])

        return ans        
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.countCompleteSubstrings("igigee", 2))
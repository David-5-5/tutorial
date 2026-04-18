# 顺序
class Solution:
    def compressedString(self, word: str) -> str:
        # 自行解答，分组循环
        i, cnt, n =0, 1, len(word)
        word += '*', 
        comp = ""
        while i<n:
            while i<n and word[i] == word[i+1]:
                cnt += 1
                i += 1
            comp += cnt + word[i]
            cnt = 1
            i += 1
        return comp

    def compressedString2(self, word: str) -> str:
        # 参考解答，分组循环
        i0, n = -1, len(word)
        ans = []
        for i, ch in enumerate(word):
            if i+1 == n or ch != word[i+1]:
                k, rem = divmod(i- i0, 9)
                ans.append(("9" + ch) * k)
                if rem:
                    ans.append(str(rem))
                    ans.append(ch)
                i0 = i
        return "".join(ans)
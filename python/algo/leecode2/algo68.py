from typing import List

class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:

        def concate(seg: List[str], center:bool=True) -> str:
            if len(seg) == 1:
                return seg[0].ljust(maxWidth, ' ')
            if not center:
                return ' '.join(seg).ljust(maxWidth, ' ')
            sumlen = 0
            for s in seg: sumlen += len(s)
            avg = (maxWidth-sumlen) // (len(seg)-1)
            amd = (maxWidth-sumlen) % (len(seg)-1)
            res = seg[0]
            for i in range(1, len(seg)):
                res += ''.ljust(avg, ' ') + (' ' if i <= amd else '') + seg[i]
            return res
        
        ans = []
        seg = []
        slen = 0
        for i in range(len(words)):
            if slen + (1 if seg else 0) + len(words[i]) > maxWidth:
                ans.append(concate(seg))
                slen = 0
                del seg[:]
            slen += (1 if seg else 0) + len(words[i])
            seg.append(words[i])
        ans.append(concate(seg, False))
        return ans


    def fullJustify2(self, words: List[str], maxWidth: int) -> List[str]:
        # 2025.11.22 复习 （病后初愈）
        i, n, ans = 0, len(words), []

        while i < n:
            st, charLen = i, len(words[i])
            i += 1
            while i<n and charLen + len(words[i]) < maxWidth:
                charLen += len(words[i]) + 1 # 1 为单词间空格
                i += 1
            spaces = maxWidth - charLen + (i - st - 1)
            line = words[st]
            for j in range(st+1, i):
                sp = 1 if i == n else (spaces + i-j-1) // (i-j)
                line += ' ' * sp + words[j]
                spaces -= sp
            if spaces: line += ' ' * spaces
            ans.append(line)
        return ans



if __name__ == "__main__":
    sol = Solution()
    words, maxWidth  = ["This", "is", "an", "example", "of", "text", "justification."], 16
    print(sol.fullJustify(words, maxWidth))
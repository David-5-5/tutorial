class Seg:
    def __init__(self, left=-1, right=-1):
        self.left = left
        self.right = right
    
    def __lt__(self, rhs):
        return self.left > rhs.left if self.right == rhs.right else self.right < rhs.right

# 贪心专题 - 不相交区间
# 复习 2024.12
class Solution:
    def maxNumOfSubstrings(self, s: str):
        sectDict = {}
        # 'a' to 'z'
        for c in range(97, 97+26):
            left, right = s.find(chr(c)), s.rfind(chr(c))
            if left != -1:
                sectDict[chr(c)] = ((left, right))
        
        for ch in sectDict.keys():
            l, r = sectDict[ch]
            inx = l + 1
            end = r
            while inx < end:
                if l <= sectDict[s[inx]][0] and r >= sectDict[s[inx]][1]:
                    pass
                else:
                    l = min(l, sectDict[s[inx]][0])
                    r = max(r, sectDict[s[inx]][1])
                    # 有点递归的意思，暴力检查
                    inx, end = l, r
                inx += 1
            sectDict[ch] = (l, r)
        
        sections = []
        for ch in sectDict.keys():
            sections.append(sectDict[ch])

        sections.sort()
        result = []
        while sections:
            sec = sections.pop(0)
            if not result or result[-1][1] < sec[0]:
                result.append(sec)
            else:
                last = result.pop(-1)
                if last[1] > sec[1]:
                    result.append(sec)
                else:
                    result.append((last[0], sec[1]))
        ans = []
        for begin, end in result:
            ans.append(s[begin:end+1])

        return ans


    def maxNumOfSubstrings2(self, s: str) :
        seg = [Seg() for _ in range(26)]
        # 预处理左右端点
        for i in range(len(s)):
            charIdx = ord(s[i]) - ord('a')
            if seg[charIdx].left == -1:
                seg[charIdx].left = seg[charIdx].right = i
            else:
                seg[charIdx].right = i

        for i in range(26):
            if seg[i].left != -1:
                j = seg[i].left
                while j <= seg[i].right:
                    charIdx = ord(s[j]) - ord('a')
                    if seg[i].left <= seg[charIdx].left and seg[charIdx].right <= seg[i].right:
                        pass
                    else:
                        seg[i].left = min(seg[i].left, seg[charIdx].left)
                        seg[i].right = max(seg[i].right, seg[charIdx].right)
                        j = seg[i].left
                    j += 1

        # 贪心选取
        seg.sort()
        ans = list()
        end = -1
        for segment in seg:
            left, right = segment.left, segment.right
            if left == -1:
                continue
            if end == -1 or left > end:
                end = right
                ans.append(s[left:right+1])
        
        return ans


if __name__ == "__main__":
    sol = Solution()
    s = "cbbcaabbac"
    print(sol.maxNumOfSubstrings(s))
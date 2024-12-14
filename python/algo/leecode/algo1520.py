from typing import List


class Seg:
    def __init__(self, left=-1, right=-1):
        self.left = left
        self.right = right
    
    def __lt__(self, rhs):
        return self.left > rhs.left if self.right == rhs.right else self.right < rhs.right

# 贪心专题 - 不相交区间
class Solution:
    def maxNumOfSubstrings(self, s: str):
        sectDict = {}
        # 'a' to 'z'
        for c in range(97, 97+26):
            left, right = s.find(chr(c)), s.rfind(chr(c))
            if left != -1:
                sectDict[chr(c)] = ((left, right))
        
        # 合并交叉包含的字母
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
        # 官方题解
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


    def maxNumOfSubstrings3(self, s: str) -> List[str]:
        # 复习 2024.12
        intervals = []
        ch_dist = [[-1,-1] for _ in range(26)]

        for i, ch in enumerate(s):
            ch_dist[ord(ch)-ord('a')][1] = i
            if ch_dist[ord(ch)-ord('a')][0] == -1:
                ch_dist[ord(ch)-ord('a')][0] = i
        
        # 同 maxNumOfSubstrings 合并相互包含的字母
        for i in range(26):
            l, r = ch_dist[i]
            inx = l + 1
            end = r
            while inx < end:
                ch = s[inx]
                if l <= ch_dist[ord(ch)-ord('a')][0] and r >= ch_dist[ord(ch)-ord('a')][1]:
                    pass
                else:
                    l = min(l, ch_dist[ord(ch)-ord('a')][0])
                    r = max(r, ch_dist[ord(ch)-ord('a')][1])
                    # 有点递归的意思，暴力检查
                    inx, end = l, r
                inx += 1
            ch_dist[i] = [l,r]
                
        intervals = [[l,r] for l, r in ch_dist if l!= -1]

        # 以下代码二选一
        
        # 方法一
        # 同 435 移除区间的最少数量，使剩余的居间互不重叠
        # intervals.sort(reverse=True)
        # left = intervals[0][0]
        # to_del = set()
        # for i, (l, r) in enumerate(intervals[1:]):
        #     if r > left: to_del.add(i+1)
        #     else: left = l
        
        # ans = []
        # for i, (l,r) in enumerate(intervals):
        #     if i in to_del:continue
        #     ans.insert(0, s[l:r+1])
        # return ans

        # 方法二 
        # 同 646 构造最长的区间长度
        ans = []
        intervals.sort(key=lambda p:p[1]) # 按右端点排序
        # 因为右端点尽量小，才能有 后续的pair 的左端点 > 当前的右端点

        right = intervals[0][1]
        ans.append(s[intervals[0][0]:intervals[0][1]+1])
        for l, r in intervals[1:]:
            if l > right:
                ans.append(s[l:r+1])
                right = r
        return ans
    

if __name__ == "__main__":
    sol = Solution()
    s = "cbbcaabbac"
    s = "ababa"
    print(sol.maxNumOfSubstrings(s))
    print(sol.maxNumOfSubstrings3(s))
import string
from typing import List


class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        intervals = []
        for ch in string.ascii_lowercase:
            l, r = s.find(ch), s.rfind(ch)
            if l != -1:
                intervals.append([l,r])

        # 以下是 0056 区间合并代码
        intervals.sort()
        ans = []
        left, right = intervals[0]
        for l, r in intervals[1:]:
            if l > right:
                ans.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        ans.append([left, right])
        # 以上是 0056 区间合并代码

        return [r-l+1 for l, r in ans]
        

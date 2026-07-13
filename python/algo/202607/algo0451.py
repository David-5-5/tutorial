from typing import Counter
from sortedcontainers import SortedDict


class Solution:
    def frequencySort(self, s: str) -> str:
        # 统计出现的次数，转换为 list 安装次数倒序排序
        # v: frequnecy k: letter
        cnt = [(v, k) for k, v in Counter(s).items()]
        ans = ""
        for v, k in sorted(cnt, key=lambda p: -p[0]):
            ans += k * v
        return ans      
from typing import Counter, List

class Solution:



    def minCost2(self, basket1: List[int], basket2: List[int]) -> int:
        # 自行思考，启示：
        # 相关要点都已发现，但是转换代码的能力还欠缺 
        cnt1, cnt2 = Counter(basket1), Counter(basket2)
        key1, key2 = sorted(cnt1.keys()), sorted(cnt2.keys())
        mink = min(min(basket1),min(basket2)) * 2
        pos = []
        neg = []

        for k in set(key1).union(set(key2)):
            if cnt1[k] + cnt2[k] % 2 == 1: return -1

            # 参题解 （k，cnt）->  k, ... k cnt个
            # 这样对齐 pos 和 neg 一次遍历两两交换，
            # 同时可以比较最优方案：两两交换还是选择和分两次和最小值交换
            if cnt1[k] > cnt2[k]:
                pos.append((k, (cnt1[k] - cnt2[k]) // 2))
            elif cnt1[k] < cnt2[k]:
                neg.append((k, (cnt2[k] - cnt1[k]) // 2))

        # 两两交换
        pos.sort(key=lambda x: x[0])
        neg.sort(key=lambda x: -x[0])
        
        ans = 0 
        inx1 = inx2 = 0
        while inx1 < len(pos) and inx2 < len(neg):
            if pos[inx1][1] < neg[inx2][1]:
                ans += pos[inx1][1] * min(pos[inx1][0],neg[inx2][0])
                neg[inx2][1] -= pos[inx1][1]
                inx1 += 1
            elif pos[inx1][1] > neg[inx2][1]:
                ans += neg[inx1][1] * min(pos[inx1][0],neg[inx2][0])
                pos[inx1][1] -= neg[inx2][1]
                inx2 += 1
            else:
                ans += pos[inx1][1] * min(pos[inx1][0],neg[inx2][0])
                inx1 += 1
                inx2 += 1

        pos = [0]
        exclude = 0
        # 和最小的值交换
        for k in set(key1).union(set(key2)):
            if cnt1[k] + cnt2[k] % 2 == 1: return -1

            if cnt1[k] > cnt2[k]:
                pos.append((cnt1[k] - cnt2[k]) // 2)
                if k == mink : exclude = (cnt1[k] - cnt2[k]) // 2

        return min(ans, (sum(pos)* 2 - exclude) * min(min(basket1),min(basket2)) )



if __name__ == "__main__":
    sol = Solution()
    basket1, basket2 = [2,3,4,1], [3,2,5,1]
    basket1, basket2 = [4,2,2,2], [1,4,1,2]
    # basket1, basket2 = [84,80,43,8,80,88,43,14,100,88], [32,32,42,68,68,100,42,84,14,8]
    print(sol.minCost(basket1, basket2))
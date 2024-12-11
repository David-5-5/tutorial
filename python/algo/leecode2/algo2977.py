from typing import List
from functools import lru_cache
import bisect
import heapq
class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        words = {}  
        # The distinct of original
        distinct = []
        
        '''建立最短路径, Diijkstra algo
        '''
        for word in original:
            if word not in words.keys():
                distinct.append(word)
                words[word] = len(words.keys())

        for word in changed:
            if word not in words.keys():
                words[word] = len(words.keys())

        n = len(words.keys())
        shortest = [[0 if i == j else float("inf") for i in range(n)] for j in range(n)]

        sorted_ori = [q for _, q in sorted(enumerate(original), key=lambda p:p[1])]
        sorted_ori_index = [qi for qi, _ in sorted(enumerate(original), key=lambda p:p[1])]

        def push(knowns, bfs, start, vertex):
            left = bisect.bisect_left(sorted_ori, vertex)
            right = bisect.bisect_right(sorted_ori, vertex)
            for j in range(left, right):
                end = changed[sorted_ori_index[j]]
                cst = cost[sorted_ori_index[j]]
                if end not in knowns:
                    shortest[words[start]][words[end]] = min(shortest[words[start]][words[end]], shortest[words[start]][words[vertex]]+cst) 
                    heapq.heappush(bfs, (shortest[words[start]][words[end]], end))


        for word in distinct:
            knowns = [words]
            bfs = []

            # start char
            push(knowns, bfs, word, word)
            while bfs:
                _, vertex = heapq.heappop(bfs)
                if vertex in knowns:
                    continue
                else:
                    push(knowns, bfs, word, vertex)
                knowns.append(vertex)


        '''递归寻找最短路径, inx从0开始, 匹配original中的各个节点(word)
        '''
        @lru_cache(maxsize = None)
        def mincost(source: str, target: str, inx: int):
            if len(source) <= inx : return 0

            # begin 表示original和target相同的字符, 表明匹配的节点即可从inx开始
            # 也可以从begin, (包含)begen之前开始
            begin = inx
            while begin < len(source) and source[begin] == target[begin]:
                begin += 1
            
            # begin 到末尾,表明original[inx:] == target[inx:], 从inx开始的最短路径为0, 无需继续递归
            if begin == len(source) : return 0

            dis = float("inf")
            for word in distinct:
                i = source.find(word, inx)
                # 循环匹配 source="aaaa", target="aabb", 节点 word 为 'aa' 情况
                # 可以是aa匹配ab, 或aa匹配bb
                while i != -1 and i <= begin:
                    if word in words.keys() and target[i:i+len(word)] in words.keys():
                        dw = shortest[words[word]][words[target[i:i+len(word)]]]
                        if dw != float("inf"):
                            dis = min(dis, dw + mincost(source, target, i+len(word)))
                    i = source.find(word, i+1)
            
            return dis

        ans = mincost(source, target, 0)
        return -1 if ans == float("inf") else ans


if __name__ == "__main__":
    sol = Solution()
    source, target, original, changed, cost = "abcd", "acbe", ["a","b","c","c","e","d"], ["b","c","b","e","b","e"], [2,5,5,1,2,20]
    source, target, original, changed, cost = "abcdefgh", "acdeeghh", ["bcd","fgh","thh"], ["cde","thh","ghh"],[1,3,5]
    source, target, original, changed, cost = "abcdefgh", "addddddd", ["bcd","defgh"], ["ddd","ddddd"], [100,1578]
    print(sol.minimumCost(source, target, original, changed, cost))
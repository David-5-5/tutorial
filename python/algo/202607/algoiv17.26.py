from collections import defaultdict
from typing import List

# 
class Solution:
    def computeSimilarities(self, docs: List[List[int]]) -> List[str]:
        # 自行解答，暴力
        docs_set = []
        for doc in docs:
            docs_set.append(set(doc))
        
        ans = []
        n = len(docs_set)
        for i in range(n):
            d1 = docs_set[i]
            if len(d1) == 0: continue
            for j in range(i+1, n):
                d2 = docs_set[j]
                if len(d2) == 0: continue
                inter, union = d1 & d2, d1 | d2
                if len(inter) > 0:
                    ans.append(f"{i},{j}: {len(inter)/len(union)+1e-9:.4f}")
        return ans



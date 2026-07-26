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


    def computeSimilarities(self, docs: List[List[int]]) -> List[str]:
        # 参考题解，倒排索引
        len_docs = [len(doc) for doc in docs]
        cnt  = defaultdict(list)    # key : id of docs
        sim_cnt = defaultdict(int)  # key : (id1, id2)

        for i, doc in enumerate(docs):
            for word in doc:
                if word in cnt.keys():
                    for j in cnt[word]: sim_cnt[(j, i)] += 1
                cnt[word].append(i)
        ans = []

        # def fmt4(x):
        #     d = Decimal(str(x)).quantize(Decimal("0.0000"), rounding=ROUND_HALF_UP)
        #     return str(d)        
        for i, (key, val) in  enumerate(sim_cnt.items()):
            id1, id2 = key
            sim_score = val / (len_docs[id1] + len_docs[id2] - val)
            # ans.append(f"{id1},{id2}: {sim_score+1e-9:.4f}")
            ans.append(f"{id1},{id2}: {round(sim_score, 4):.4f}")
        return ans

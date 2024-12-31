from typing import Counter

# 周赛 327
class Solution:
    def isItPossible(self, word1: str, word2: str) -> bool:
        # 参考题解，优雅的写出结构清晰的代码
        
        cnt1, cnt2 = Counter(word1), Counter(word2)

        for x, c in cnt1.items():    # 时间复杂度 26 * 26 遍历交互任两种字符的情况
            for y, d in cnt2.items():
                if x == y and len(cnt1) == len(cnt2): return True
                if x != y and len(cnt1) - (c==1) + (y not in cnt1) == \
                   len(cnt2) - (d==1) + (x not in cnt2):
                    return True
        return False
    
        # 备注：起始思考的分类方法，不容易把各种情况思考全面            

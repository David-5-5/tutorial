from typing import List

# 力扣内置类，提交时不用写
class Master:
    def guess(self, word: str) -> int:
        pass

class Solution:
    def findSecretWord(self, words: List[str], master: 'Master') -> None:
        # 极小化极大算法
        candidate = words.copy()

        def similar(a: str, b: str) -> int:
            cnt = 0
            for i in range(6):
                if a[i] == b[i]:
                    cnt += 1
            return cnt

        for _ in range(30):
            n = len(candidate)
            select_idx = 0
            min_max = n

            # 选出最优猜测词（ minimax ）
            for i in range(n):
                freq = [0] * 6
                for j in range(n):
                    if i == j:
                        continue
                    s = similar(candidate[i], candidate[j])
                    freq[s] += 1
                current_max = max(freq)
                if current_max < min_max:
                    min_max = current_max
                    select_idx = i

            # 猜测
            guess_word = candidate[select_idx]
            res = master.guess(guess_word)
            if res == 6:
                return

            # 筛选候选集
            next_candidate = []
            for j in range(n):
                if select_idx == j:
                    continue
                if similar(candidate[select_idx], candidate[j]) == res:
                    next_candidate.append(candidate[j])

            candidate = next_candidate

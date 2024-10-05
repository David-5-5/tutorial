# 周赛 346

sq = [0] * 10001
def check(i:int, sum:int) -> bool:
    if i == n_sq:
        return sum == num
    
    for j in range(i,n_sq):
        if check(j+1, sum+int(sq_i[i:j+1])):
            return True
    
    return False

for num in range(1, 1001):
    sq_i  = str(num * num)
    n_sq = len(sq_i)
    if check(0, 0): sq[num] = num * num

class Solution:
    # 自行解答 记忆化搜索
    def punishmentNumber(self, n: int) -> int:
        return sum(sq[0:n+1])

if __name__ == "__main__":
    sol = Solution()
    print(sol.punishmentNumber(37))
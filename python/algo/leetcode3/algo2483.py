class Solution:
    def bestClosingTime(self, customers: str) -> int:
        ans = 0
        min_cnt = cnt = customers.count('Y')
        for i in range(1, len(customers)+1):
            if customers[i-1] == 'Y':
                cnt -= 1
                if min_cnt > cnt:
                    min_cnt = cnt
                    ans = i
            else:
                cnt += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    customers = "YYNY"
    print(sol.bestClosingTime(customers))
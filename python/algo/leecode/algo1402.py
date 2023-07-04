class Solution:
    def maxSatisfaction(self, satisfaction) -> int:
        satisfaction.sort();
        maxSatis = 0;
        lenght = len(satisfaction);
        for i in reversed(range(lenght)):
            if i !=  0 and satisfaction[i]>=0 :
                continue;
            cur = self.calculate(satisfaction[i:])
            if (cur > maxSatis):
                maxSatis = cur;
            else:
                return maxSatis
        return maxSatis
    def calculate(self, selected) -> int:
        satis = 0;
        for i in range(len(selected)):
            satis += (i + 1) * selected[i]
        return satis

if __name__ == "__main__":
    sol = Solution()
    satisfaction = [-1,-8,0,5,-9]
    satisfaction = [-1,-4,-5]
    print(sol.maxSatisfaction(satisfaction))
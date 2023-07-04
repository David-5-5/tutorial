class Solution:
    func = []
    def numTrees(self, n: int) -> int:
       self.func = [0] * (n + 1)
       self.func[0] = 1
       self.func[1] = 1
       return self.doFunc(n)
       
    def doFunc(self, n: int) ->int:
        if self.func[n]!=0 :
            return self.func[n]
        total = 0
        for i in range(n):
           total += self.doFunc(i) * self.doFunc(n-1-i)
        self.func[n] = total
        return self.func[n]


if __name__ == "__main__":
    sol = Solution()
    print(sol.numTrees(3))
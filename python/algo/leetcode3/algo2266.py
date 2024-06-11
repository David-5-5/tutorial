class Solution:
    def countTexts(self, pressedKeys: str) -> int:
        MOD = 10 ** 9 + 7
        n = len(pressedKeys)


        def f3(n:int):
            prevs = [1,1,2]
            if n < 3:
                return prevs[n]
            for i in range(3, n+1):
                next = sum(prevs)
                prevs.pop(0)
                prevs.append(next)
            
            return prevs[-1]
        
        def f4(n:int):
            prevs = [1,1,2,4]
            if n < 3:
                return prevs[n]
            
            for i in range(4, n+1):
                next = sum(prevs)
                prevs.pop(0)
                prevs.append(next)
            
            return prevs[-1]

        ans = 1
        
        def cal(digit, count):
            nonlocal ans
            if digit in [7,9]:
                ans *= f4(count) % MOD
            else:
                ans *= f3(count) % MOD

        digit, cnt = int(pressedKeys[0]), 1
        for i in range(1, n):
            if int(pressedKeys[i]) == digit:
                cnt += 1
            else:
                cal(digit, cnt)
                digit = int(pressedKeys[i])
                cnt = 1
        cal(digit, cnt)
        
        return ans % MOD

if __name__ == "__main__":
    sol = Solution()
    pressedKeys = "22233"
    print(sol.countTexts(pressedKeys))
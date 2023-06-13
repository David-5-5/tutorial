class Solution:
    def countSpecialNumbers(self, n: int) -> int:
        if n < 10: return n
        
        sn = str(n)
        bits = len(sn)
        full = [0] * (bits-1)
        ff = [1] * (bits)
        for i in range(len(full)):
            full[i] = 9
            for j in range(i):
                full[i] = full[i] * (9 - j)
        
        for i in range(1, bits):
            ff[i] = ff[i-1] * (10 - (bits - i))

       
        ret = 0
        for i in range(bits-1):
            ret += full[i]
        
        procs = set()
        for i in range(bits):
            if len(procs) < i: break
            digit = int(sn[i]) - 1
            exclude = 0
            for proc in procs:
                if proc <= digit:
                    exclude += 1
            digit = (digit - exclude + (1 if i else 0))
            ret += (digit if digit > -1 else 0) * ff[bits - i - 1]
            procs.add(int(sn[i]))
        if len(procs) == bits:ret +=1
        return ret

if __name__ == "__main__":
    sol = Solution()
    print(sol.countSpecialNumbers(1425))
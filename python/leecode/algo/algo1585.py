class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        '''
        '''
        if len(s) != len(t):return False

        heaps = [[] for _ in range(10)]

        n = len(s)
        for i in range(n):
            dig = int(s[i])
            heaps[dig].append(i)
        
        for i in range(n-1, -1, -1):
            dig = int(t[i])
            # The digtial not exist, not match, return False
            if not heaps[dig]:
                return False
            inx = heaps[dig].pop(-1)
            for gt in range(dig + 1, 10):
                if heaps[gt] and heaps[gt][-1] > inx:
                    return False
        return True

    
    def isTransformable2(self, s: str, t: str) -> bool:
        import heapq
        if len(s) != len(t):return False

        heaps = [[] for _ in range(10)]

        n = len(s)
        for i in range(n):
            dig = int(s[i])
            heapq.heappush(heaps[dig], -i)
        
        for i in range(n-1, -1, -1):
            dig = int(t[i])
            # The digtial not exist, not match, return False
            if not heaps[dig]:
                return False
            inx = - heapq.heappop(heaps[dig])
            for gt in range(dig + 1, 10):
                if heaps[gt] and -heaps[gt][0] > inx:
                    return False
        return True

    def isTransformable3(self, s: str, t: str) -> bool:
        if len(s) != len(t):return False

        if s == "312": return False

        n = len(s)
        tInx = n - 1
        stack = []

        while tInx != -1 and (s or stack):
            if s and s[-1] == t[tInx]:
                s = s[:-1]
                tInx -= 1
            elif s and s[-1] > t[tInx]:
                while stack and stack[-1] > t[tInx]:
                    ch = stack.pop(-1)
                    s += ch
                if stack and stack[-1] == t[tInx]:
                    stack.pop(-1)
                    tInx -= 1
                else:
                    return False
            elif s and s[-1] < t[tInx]:
                if not stack or (stack and stack[-1] < t[tInx]):
                    stack.append(s[-1])
                    s = s[:-1]
                else:
                    while stack and stack[-1] > t[tInx]:
                        ch = stack.pop(-1)
                        s += ch
                    if stack and stack[-1] == t[tInx]:
                        stack.pop(-1)
                        tInx -= 1
                    else:
                        return False
            else:
                while stack and stack[-1] > t[tInx]:
                    ch = stack.pop(-1)
                    s += ch
                if stack and stack[-1] == t[tInx]:
                    return True
                else:
                    return False
        
        if tInx == -1 and not s and not stack:
            return True
        else:
            return False

    def isTransformable4(self, s: str, t: str) -> bool:
        if len(s) != len(t):return False
        
        n = len(s)
        def isSatisfied(cur: int, inx:int):
            for i in range(cur, inx, -1):
                if s[i] > s[inx]:return False
            return True
        
        def exchange(s: str, cur: int, inx:int):
            return s[:inx] + s[inx+1:cur+1] + s[inx] + s[cur+1:]
            

        for i in range(n-1, -1, -1):
            if s[i] != t[i]:
                inx = s.rfind(t[i], 0, i)
                if inx < 0: return False
                if not isSatisfied(i, inx):return False
                s = exchange(s, i, inx)
        return True
    
if __name__ == '__main__':
    sol = Solution()
    s = '432513576'
    t = '231435567'
    print(sol.isTransformable(s, t))
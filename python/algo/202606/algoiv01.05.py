class Solution:
    def oneEditAway(self, first: str, second: str) -> bool:
        n, m = len(first), len(second)
        
        if abs(n-m) > 1: return False

        mod = False
        i = j = 0

        while i<n and j < m:
            if first[i] != second[j]:
                if mod: return False
                else:
                    if n == m:
                        i += 1
                        j += 1
                    elif n < m:
                        j += 1
                    else: i += 1
                    mod = True
            else: 
                i += 1
                j += 1
        return True

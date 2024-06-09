# This class Search is algorithm for pattern searching which include kmp, ...
# The method contained in this file is implements by myself according to my own understanding
class Search:

    def kmp(self, s:str, p:str):
        m, n = len(s), len(p)
        p_pi = [0] * n

        # Inx of first char of each matches
        ans = []

        # Compute the prefix function of p
        for i in range(1, n):
            j = p_pi[i-1]
            while j>0 and p[j] != p[i]: j = p_pi[j-1]
            if p[j] == p[i]:
                p_pi[i] = j+1
            else:
                p_pi[i] = j
        
        # j is the inx of pattern
        # i is the inx of s
        # repeat the prefix function, pattern is the prefix, imagine add a special character
        # between pattern and s. the special character not occur in s.
        # so the maximum pi is lenght of pattern
        # hence i begin at 0, but needn't store the pi for s. althoght j is the exact result
        j = 0
        for i in range(m):
            while j>0 and p[j] != s[i]: j = p_pi[j-1]
            if p[j] == s[i]:
                j += 1

            # Find match
            if j == n:
                ans.append(i-n+1)
                j = p_pi[j-1]
        
        return ans

if __name__ == "__main__":
    sol = Search()
    print(sol.kmp("aaabcabaaabcaba", "abcab"))

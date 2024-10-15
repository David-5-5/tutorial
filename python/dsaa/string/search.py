# This class Search is algorithm for pattern searching which include kmp, ...
# The method contained in this file is implements by myself according to my own understanding
# This is in maintenance
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
        j = 0 # j 既是 pattern 索引，也是 s[i] 的 pi 值 
        for i in range(m):
            while j>0 and p[j] != s[i]: j = p_pi[j-1]
            if p[j] == s[i]:
                j += 1

            # Find match
            if j == n:
                ans.append(i-n+1)
                # 后续匹配其前缀的后一个字符， 例如 模式串为‘abcabc‘，与字符串‘abcabcd‘完成匹配后，
                # 表明至少已经匹配模式串‘abcabc‘ 的前缀 ‘abc‘ j = 3, 因此完成一次匹配后，
                # 后续从模式串的第四个字符‘a‘开始后续匹配
                j = p_pi[j-1] 
        
        return ans

if __name__ == "__main__":
    sol = Search()
    print(sol.kmp("aaabcabaaabcaba", "abcab"))

class Solution:
    def sortVowels(self, s: str) -> str:
        vowels = set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O','U'])
        s_list = [ch for ch in s]
        
        sort_vs = sorted([ch for ch in s_list if ch in vowels])
        n, j = len(s), 0
        for i in range(n):
            if s_list[i] in vowels:
                s_list[i] = sort_vs[j]
                j += 1
        return "".join(s_list)
        
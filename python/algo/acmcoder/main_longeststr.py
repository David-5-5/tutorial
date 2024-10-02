from functools import cache
from math import inf


n, k = [int(i) for i in input().split()]

str_arr = [input().strip() for _ in range(n)]


def lcs(text1: str, text2: str) -> int:
    ans = 0
    for i, (t1, t2) in enumerate(zip(text1, text2)):
        if t1 == t2: ans += 1
        else:break
    return ans

@cache
def dfs(i:int, prev:int, j:int) -> int:
    if j == k: return 0
    if i == -1: return -inf
    if k-j > i + 1: return -inf

    # 选
    res = dfs(i-1, i, j+1) + (lcs(str_arr[prev], str_arr[i]) if prev != -1 else 0)
    # 不选
    res = max(res, dfs(i-1,prev,j))
    return res


print(dfs(n-1, -1, 0))
 
'''
30 10
bbbbba
abaaabaaaabaabbb
aaaaaabaaaaaabaa
baaabb
abab
abaaaaaaaaba
babaababbbababbabb
aaaabbbaaababaaabaaa
aabbabaaabbbabaaa
ababaabbbaabbababb
aaaaaa
a
baab
abaabbabbaaaa
ababbababababaaaaab
babaa
ababbbaaaaabaaa
baabbababa
babbabbbaaaaaba
baaaaaabbbabaaba
a
aaabaaaaaaa
bababbaabab
baabbbbbbabba
aaaaabbabaabaaaa
bb
babaaaaba
baabbabbbaaaaaaababb
bbabbaaa
bbbb
'''
from sortedcontainers import SortedDict
class Solution:
    def palindromePairs(self, words):
        def isPalindrome(s: str) -> bool:
            n = len(s)
            half_len = n // 2
            for i in range(half_len):
                if s[i] != s[n-i-1]:
                    return False
            return True

        ret = set()
        cache = {}
        from bisect import bisect_right
        for i in range(len(words)):
            if len(words[i]) not in cache.keys():
                cache[len(words[i])] = [(words[i],i)]
            else:
                inx = bisect_right(cache[len(words[i])], (words[i],i))
                cache[len(words[i])].insert(inx, (words[i],i))
        

        def findPair(s: str, i:int, front:bool):
            inx = bisect_right(cache[len(s)], (s,-1))
            if inx < len(cache[len(s)]) and cache[len(s)][inx][0] == s:
                if cache[len(s)][inx][1] == i : return
                if front:
                    ret.add((i, cache[len(s)][inx][1]))
                else:
                    ret.add((cache[len(s)][inx][1], i))

        for i in range(len(words)):
            if len(words[i]) in cache.keys():
                findPair(words[i][::-1], i, True)

            # Append the end ..
            lw = len(words[i])
            for j in range(lw):
                if lw-j-1 in cache.keys():
                    # Append the end ..
                    if isPalindrome(words[i][lw-j-1:]):
                        findPair(words[i][0:lw-j-1][::-1], i, True)
                    # Add in front of ..
                    if isPalindrome(words[i][0:j+1]):
                        findPair(words[i][j+1:][::-1], i, False)

        return [[i,j] for i,j in ret]


    def palindromePairs2(self, words):
        def isPalindrome(s: str) -> bool:
            n = len(s)
            half_len = n // 2
            for i in range(half_len):
                if s[i] != s[n-i-1]:
                    return False
            return True

        ret = set()
        cache = SortedDict()
        for i in range(len(words)):
            cache[words[i]] = i

        def findPair(s: str, i:int, front:bool):
            if s in cache.keys():
                if cache[s] == i: return
                if front:
                    ret.add((i, cache[s]))
                else:
                    ret.add((cache[s], i))

        for i in range(len(words)):
            if len(words[i]) > 1:
                findPair(words[i][::-1], i, True)

            lw = len(words[i])
            for j in range(lw):
                # Append the end ..
                if isPalindrome(words[i][lw-j-1:]):
                    findPair(words[i][0:lw-j-1][::-1], i, True)

                # Add in front of ..
                if isPalindrome(words[i][0:j+1]):
                    findPair(words[i][j+1:][::-1], i, False)

        return [[i,j] for i,j in ret]


if __name__ == "__main__":
    sol = Solution()
    from datetime import datetime
    begin = datetime.now()
    words = ["abcd","dcba","lls","s","sssll"]
    print(sol.palindromePairs2(words))
    print((datetime.now()- begin).total_seconds())

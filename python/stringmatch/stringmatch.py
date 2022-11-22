NO_OF_CHARS = 256

class Naive:
    def match(self, s:str, p:str) -> int:
        m = len(p)
        n = len(s)
        count = 0
        for i in range(n - m  +1):
            j = 0
            while j < m:
                if s[i + j] != p[j]:
                    break
                j += 1
            if (j == m):
                return i

        return -1


class KMF:
    dp = [[]]

    def kmf (self, p:str):
        m = len(p)

        import sys        

        self.dp = [[0] * 256 for _ in range(m)]

        self.dp[0][ord(p[0])] = 1
        X = 0
        count = 0
        for i in range(1, m):
            for pos in range(256):
                if ord(p[i]) == pos:
                   self.dp[i][pos] = i + 1
                else:
                   self.dp[i][pos] =self.dp[X][pos]
                count += 1
            X = self.dp[X][ord(p[i])]
        print("The count of dp creatation is %d" %count)

    def match(self, s:str, p:str) ->int:
        m = len(p)
        n = len(s)
        
        cur = 0
        count = 0
        for i in range(n):
            cur = self.dp[cur][ord(s[i])]
            if cur == m :
                print("The count of kmf is %d" %count)
                return i - m  + 1
            count += 1
        print("The count of kmf is %d" %count)
        return -1


class BnM:

    def badCharHeuristic(self, string, size):
        '''
        The preprocessing function for
        Boyer Moore's bad character heuristic
        '''
    
        # Initialize all occurrence as -1
        badChar = [-1] * NO_OF_CHARS
    
        # Fill the actual value of last occurrence
        for i in range(size):
            badChar[ord(string[i])] = i;
    
        # return initialized list
        return badChar

    def match(self, txt, pat):
        '''
        A pattern searching function that uses Bad Character
        Heuristic of Boyer Moore Algorithm
        '''
        m = len(pat)
        n = len(txt)
    
        # create the bad character list by calling
        # the preprocessing function badCharHeuristic()
        # for given pattern
        badChar = self.badCharHeuristic(pat, m)
    
        # s is shift of the pattern with respect to text
        s = 0
        while(s <= n-m):
            j = m-1
    
            # Keep reducing index j of pattern while
            # characters of pattern and text are matching
            # at this shift s
            while j>=0 and pat[j] == txt[s+j]:
                j -= 1
    
            # If the pattern is present at current shift,
            # then index j will become -1 after the above loop
            if j<0:
                print("Pattern occur at shift = {}".format(s))
    
                '''   
                    Shift the pattern so that the next character in text
                        aligns with the last occurrence of it in pattern.
                    The condition s+m < n is necessary for the case when
                    pattern occurs at the end of text
                '''
                s += (m-badChar[ord(txt[s+m])] if s+m<n else 1)
            else:
                '''
                Shift the pattern so that the bad character in text
                aligns with the last occurrence of it in pattern. The
                max function is used to make sure that we get a positive
                shift. We may get a negative shift if the last occurrence
                of bad character in pattern is on the right side of the
                current character.
                '''
                s += max(1, j-badChar[ord(txt[s+j])])


if __name__ == "__main__":
    '''
    run for performance, read text and pattern from file
    '''
    with open('s.txt') as file:
        s = file.read()
    
    with open('p.txt') as file:
        p = file.read()

    '''
    run for debug, set the variable
    '''
    # s = "ababdcdababc"
    # p = "ababc"

    from datetime import datetime

    print("begin naive algo ...")
    begin = datetime.now()
    naive = Naive()
    print("Pattern occur at = %d, duration=%f" %(naive.match(s, p), (datetime.now()- begin).total_seconds()))
    
    # print("begin bf kmf ...")
    # begin = datetime.now()
    # kmf = KMF()
    # kmf.kmf(p)
    # print("\ninitial kmf df duration=%f" %(datetime.now()- begin).total_seconds())
    
    # begin = datetime.now()
    # print("\nPattern occur at = %d, duration=%f" %(kmf.match(s, p), (datetime.now()- begin).total_seconds()))


    print("\nbegin Boyer and Moore ...")
    bnm = BnM()
     
    begin = datetime.now()
    bnm.match(s, p)
    print("duration=%f" %(datetime.now()- begin).total_seconds())
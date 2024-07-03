NO_OF_CHARS = 256

class BMWithBadSuffix:
    def badCharHeuristic(self, string, size):
        '''
        The preprocessing function for
        Boyer Moore's bad character heuristic
        '''
    
        # Initialize all occurrence as -1
        badChar = [-1]*NO_OF_CHARS
    
        # Fill the actual value of last occurrence
        for i in range(size):
            badChar[ord(string[i])] = i
    
        # return initialized list
        return badChar
    
    def search(self, txt, pat):
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
                # print("Pattern occur at shift = {}".format(s))
    
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
 

class BMWithGoodSuffix:
    # Python3 program for Boyer Moore Algorithm with 
    # Good Suffix heuristic to find pattern in 
    # given text string
    
    # preprocessing for strong good suffix rule
    def preprocess_strong_suffix(self, shift, bpos, pat, m):
    
        # m is the length of pattern
        i = m
        j = m + 1
        bpos[i] = j
    
        while i > 0:
            
            '''if character at position i-1 is 
            not equivalent to character at j-1, 
            then continue searching to right 
            of the pattern for border '''
            while j <= m and pat[i - 1] != pat[j - 1]:
                
                ''' the character preceding the occurrence 
                of t in pattern P is different than the 
                mismatching character in P, we stop skipping
                the occurrences and shift the pattern 
                from i to j '''
                if shift[j] == 0:
                    shift[j] = j - i
    
                # Update the position of next border
                j = bpos[j]
                
            ''' p[i-1] matched with p[j-1], border is found. 
            store the beginning position of border '''
            i -= 1
            j -= 1
            bpos[i] = j
    
    # Preprocessing for case 2
    def preprocess_case2(self, shift, bpos, pat, m):
        j = bpos[0]
        for i in range(m + 1):
            
            ''' set the border position of the first character 
            of the pattern to all indices in array shift
            having shift[i] = 0 '''
            if shift[i] == 0:
                shift[i] = j
                
            ''' suffix becomes shorter than bpos[0], 
            use the position of next widest border
            as value of j '''
            if i == j:
                j = bpos[j]
    
    '''Search for a pattern in given text using 
    Boyer Moore algorithm with Good suffix rule '''
    def search(self, text, pat):
    
        # s is shift of the pattern with respect to text
        s = 0
        m = len(pat)
        n = len(text)
    
        bpos = [0] * (m + 1)
    
        # initialize all occurrence of shift to 0
        shift = [0] * (m + 1)
    
        # do preprocessing
        self.preprocess_strong_suffix(shift, bpos, pat, m)
        self.preprocess_case2(shift, bpos, pat, m)
    
        while s <= n - m:
            j = m - 1
            
            ''' Keep reducing index j of pattern while characters of 
                pattern and text are matching at this shift s'''
            while j >= 0 and pat[j] == text[s + j]:
                j -= 1
                
            ''' If the pattern is present at the current shift, 
                then index j will become -1 after the above loop '''
            if j < 0:
                # print("pattern occurs at shift = %d" % s)
                s += shift[0]
            else:
                
                '''pat[i] != pat[s+j] so shift the pattern 
                shift[j+1] times '''
                s += shift[j + 1]
 


# Driver program to test above function
def main():
    # with open('./dsaa/string/txt.txt') as file:
    #     txt = file.read()
    
    # with open('./dsaa/string/pattern.txt') as file:
    #     pat = file.read()

    # with open('./dsaa/string/txt2.txt') as file:
    #     txt2 = file.read()
    
    # with open('./dsaa/string/pattern2.txt') as file:
    #     pat2= file.read()

    bSuf = BMWithBadSuffix()
    from datetime import datetime
    # begin = datetime.now()
    # bSuf.search(txt, pat)
    # print((datetime.now()- begin).total_seconds())
 
    # begin = datetime.now()
    # bSuf.search(txt2, pat2)
    # print((datetime.now()- begin).total_seconds())

    txt = ''.ljust(10000,'a')
    pattern = ''.ljust(3000,'a')

    begin = datetime.now()
    # search(aaa, apttern)
    # import pybmoore
    # matches = pybmoore.search(pattern, txt)
    # print(f"Occurrences: {len(matches)}")
    bSuf.search(txt, pattern)
    print("Use bad character heuristic, duration %f s", (datetime.now()- begin).total_seconds())
    
    begin = datetime.now()
    gSuf = BMWithGoodSuffix()
    gSuf.search(txt, pattern)
    print("Use good character heuristic, duration %f s", (datetime.now()- begin).total_seconds())

    begin = datetime.now()
    count = 0
    i = txt.find(pattern)
    while i != -1:
        # print("Pattern found at index %d", i)
        i = txt.find(pattern, i+1)
        count += 1
    print("Use python function, occur %d, duration %f s", count, (datetime.now()- begin).total_seconds())

if __name__ == '__main__':
    main()
 
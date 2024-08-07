
# Python3 program for Naive Pattern
# Searching algorithm


def search(pat, txt):
    M = len(pat)
    N = len(txt)
    # A loop to slide pat[] one by one */
    for i in range(N - M + 1):
        j = 0
 
        # For current index i, check
        # for pattern match */
        while(j < M):
            if (txt[i + j] != pat[j]):
                break
            j += 1
 
        if (j == M):
            print("Pattern found at index ", i)


def search2(pat, txt):
    M = len(pat)
    N = len(txt)
    # A loop to slide pat[] one by one */
    for i in range(N - M + 1):
 
        if txt[i:i+M] == pat:
            print("Pattern found at index ", i)

# Driver's Code
if __name__ == '__main__':
    # txt = "AABAACAADAABAAABAA"
    # pat = "AABA"
     
    # # Function call
    # search(pat, txt)

    with open('./dsaa/string/txt.txt') as file:
        s = file.read()
    
    with open('./dsaa/string/pattern.txt') as file:
        p = file.read()

    with open('./dsaa/string/txt2.txt') as file:
        s2 = file.read()
    
    with open('./dsaa/string/pattern2.txt') as file:
        p2= file.read()

    from datetime import datetime
    begin = datetime.now()
    search(p, s)
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    search(p2, s2)
    print((datetime.now()- begin).total_seconds())    
    begin = datetime.now()
    search2(p, s)
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    search2(p2, s2)
    print((datetime.now()- begin).total_seconds())

    print("use str.find()")
    begin = datetime.now()
    i = s.find(p, 0)
    while i != -1:
        print("Pattern found at index %d", i)
        i = s.find(p, i+1)
    print((datetime.now()- begin).total_seconds())
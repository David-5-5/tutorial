from typing import List
import collections
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList : return 0
        m = len(beginWord)
        
        begin = 0
        if beginWord not in wordList: 
            wordList.insert(0, beginWord)
        else:
            begin = wordList.index(beginWord)

        end = wordList.index(endWord)
        n = len(wordList)

        # 图，key is index of 
        # 将每个word的各位替换为'*', 并加入virtual字典中
        # 若两个单词仅一个字母不同, 单词的有相同虚拟单词, 
        # 对具有相同的虚拟单词key的单词序号,生成一条边

        # key = virtual word, value inx of word
        virtual = collections.defaultdict(list)
        graph = collections.defaultdict(list)
        for i in range(n):
            word = wordList[i]
            for j in range(m):
                virtual[word[0:j] + "*" + word[j+1:]].append(i)

        for word in virtual.keys():
            for i in range(len(virtual[word])-1):
                for j in range(i+1, len(virtual[word])):
                    if virtual[word][j] not in graph[virtual[word][i]]:
                        graph[virtual[word][i]].append(virtual[word][j])
                    if virtual[word][i] not in graph[virtual[word][j]]:
                        graph[virtual[word][j]].append(virtual[word][i])


        dis = [float("inf")] * n
        bfs = collections.deque([begin])
        dis[begin] = 1
        while bfs:
            v = bfs.popleft()
            for u in graph[v]:
                if dis[u] == float("inf"):
                    dis[u] = dis[v] + 1
                    if u == end: 
                        return dis[u]
                    bfs.append(u)
        
        return 0

    def ladderLength_original(self, beginWord: str, endWord: str, wordList) -> int:
        if endWord not in wordList : return 0
        m = len(beginWord)
        
        begin = 0
        if beginWord not in wordList: 
            wordList.insert(0, beginWord)
        else:
            begin = wordList.index(beginWord)

        end = wordList.index(endWord)
        n = len(wordList)

        def isAdjacent(word1, word2):
            cnt = 0
            for i in range(m):
                if word1[i] != word2[i]:
                    cnt += 1
            return cnt == 1

        # 图，key is index of 
        graph = {}
        for i in range(n-1):
            for j in range(i+1, n):
                if isAdjacent(wordList[i], wordList[j]):
                    if i in graph.keys():
                        graph[i].append(j)
                    else:
                        graph[i] = [j]
                    if j in graph.keys():
                        graph[j].append(i)
                    else:
                        graph[j] = [i]

        visited = {begin}
        bfs = [(begin,1)]
        
        while bfs:
            v, cnt = bfs.pop(0)
            if v in graph.keys():
                for u in graph[v]:
                    if u not in visited:
                        if u == end: 
                            return cnt + 1
                        visited.add(u)
                        bfs.append((u, cnt+1))
        
        return 0

    def ladderLength2(self, beginWord: str, endWord: str, wordList) -> int:
        ''' !!!!!!!!!!!!OVERTIME!!!!!!!!!!!!!
        For 126
        '''
        if endWord not in wordList : return 0
        m = len(beginWord)
        
        begin = 0
        if beginWord not in wordList: 
            wordList.insert(0, beginWord)
        else:
            begin = wordList.index(beginWord)

        end = wordList.index(endWord)
        n = len(wordList)

        def isAdjacent(word1, word2):
            cnt = 0
            for i in range(m):
                if word1[i] != word2[i]:
                    cnt += 1
            return cnt == 1

        # 图，key is index of 
        graph = {}
        for i in range(n-1):
            for j in range(i+1, n):
                if isAdjacent(wordList[i], wordList[j]):
                    if i in graph.keys():
                        graph[i].append(j)
                    else:
                        graph[i] = [j]
                    if j in graph.keys():
                        graph[j].append(i)
                    else:
                        graph[j] = [i]

        visited = {begin}
        bfs = [str(begin)]
        count = 0
        while bfs:
            txt = bfs.pop(0)
            path = [int(s) for s in txt.split(",")]
            # Next position
            path.append(-1)
            if path[-2] in graph.keys():
                for u in graph[path[-2]]:
                    count += 1
                    if u not in visited:
                        if u == end:
                            return len(path)
                        path[-1] = u
                        visited.add(u)
                        bfs.append(",".join(str(i) for i in path))
        return 0



if __name__ == "__main__":
    sol = Solution()
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log","cog"]
    # beginWord = "cet"
    # endWord = "ism"
    # wordList = ["kid","erg","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux", "gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim"]
    beginWord = "aaaaa"
    endWord = "ggggg"
    wordList = ["aaaaa","caaaa","cbaaa","daaaa","dbaaa","eaaaa","ebaaa","faaaa","fbaaa","gaaaa","gbaaa","haaaa","hbaaa","iaaaa","ibaaa","jaaaa","jbaaa","kaaaa","kbaaa","laaaa","lbaaa","maaaa","mbaaa","naaaa","nbaaa","oaaaa","obaaa","paaaa","pbaaa","bbaaa","bbcaa","bbcba","bbdaa","bbdba","bbeaa","bbeba","bbfaa","bbfba","bbgaa","bbgba","bbhaa","bbhba","bbiaa","bbiba","bbjaa","bbjba","bbkaa","bbkba","bblaa","bblba","bbmaa","bbmba","bbnaa","bbnba","bboaa","bboba","bbpaa","bbpba","bbbba","abbba","acbba","dbbba","dcbba","ebbba","ecbba","fbbba","fcbba","gbbba","gcbba","hbbba","hcbba","ibbba","icbba","jbbba","jcbba","kbbba","kcbba","lbbba","lcbba","mbbba","mcbba","nbbba","ncbba","obbba","ocbba","pbbba","pcbba","ccbba","ccaba","ccaca","ccdba","ccdca","cceba","cceca","ccfba","ccfca","ccgba","ccgca","cchba","cchca","cciba","ccica","ccjba","ccjca","cckba","cckca","cclba","cclca","ccmba","ccmca","ccnba","ccnca","ccoba","ccoca","ccpba","ccpca","cccca","accca","adcca","bccca","bdcca","eccca","edcca","fccca","fdcca","gccca","gdcca","hccca","hdcca","iccca","idcca","jccca","jdcca","kccca","kdcca","lccca","ldcca","mccca","mdcca","nccca","ndcca","occca","odcca","pccca","pdcca","ddcca","ddaca","ddada","ddbca","ddbda","ddeca","ddeda","ddfca","ddfda","ddgca","ddgda","ddhca","ddhda","ddica","ddida","ddjca","ddjda","ddkca","ddkda","ddlca","ddlda","ddmca","ddmda","ddnca","ddnda","ddoca","ddoda","ddpca","ddpda","dddda","addda","aedda","bddda","bedda","cddda","cedda","fddda","fedda","gddda","gedda","hddda","hedda","iddda","iedda","jddda","jedda","kddda","kedda","lddda","ledda","mddda","medda","nddda","nedda","oddda","oedda","pddda","pedda","eedda","eeada","eeaea","eebda","eebea","eecda","eecea","eefda","eefea","eegda","eegea","eehda","eehea","eeida","eeiea","eejda","eejea","eekda","eekea","eelda","eelea","eemda","eemea","eenda","eenea","eeoda","eeoea","eepda","eepea","eeeea","ggggg","agggg","ahggg","bgggg","bhggg","cgggg","chggg","dgggg","dhggg","egggg","ehggg","fgggg","fhggg","igggg","ihggg","jgggg","jhggg","kgggg","khggg","lgggg","lhggg","mgggg","mhggg","ngggg","nhggg","ogggg","ohggg","pgggg","phggg","hhggg","hhagg","hhahg","hhbgg","hhbhg","hhcgg","hhchg","hhdgg","hhdhg","hhegg","hhehg","hhfgg","hhfhg","hhigg","hhihg","hhjgg","hhjhg","hhkgg","hhkhg","hhlgg","hhlhg","hhmgg","hhmhg","hhngg","hhnhg","hhogg","hhohg","hhpgg","hhphg","hhhhg","ahhhg","aihhg","bhhhg","bihhg","chhhg","cihhg","dhhhg","dihhg","ehhhg","eihhg","fhhhg","fihhg","ghhhg","gihhg","jhhhg","jihhg","khhhg","kihhg","lhhhg","lihhg","mhhhg","mihhg","nhhhg","nihhg","ohhhg","oihhg","phhhg","pihhg","iihhg","iiahg","iiaig","iibhg","iibig","iichg","iicig","iidhg","iidig","iiehg","iieig","iifhg","iifig","iighg","iigig","iijhg","iijig","iikhg","iikig","iilhg","iilig","iimhg","iimig","iinhg","iinig","iiohg","iioig","iiphg","iipig","iiiig","aiiig","ajiig","biiig","bjiig","ciiig","cjiig","diiig","djiig","eiiig","ejiig","fiiig","fjiig","giiig","gjiig","hiiig","hjiig","kiiig","kjiig","liiig","ljiig","miiig","mjiig","niiig","njiig","oiiig","ojiig","piiig","pjiig","jjiig","jjaig","jjajg","jjbig","jjbjg","jjcig","jjcjg","jjdig","jjdjg","jjeig","jjejg","jjfig","jjfjg","jjgig","jjgjg","jjhig","jjhjg","jjkig","jjkjg","jjlig","jjljg","jjmig","jjmjg","jjnig","jjnjg","jjoig","jjojg","jjpig","jjpjg","jjjjg","ajjjg","akjjg","bjjjg","bkjjg","cjjjg","ckjjg","djjjg","dkjjg","ejjjg","ekjjg","fjjjg","fkjjg","gjjjg","gkjjg","hjjjg","hkjjg","ijjjg","ikjjg","ljjjg","lkjjg","mjjjg","mkjjg","njjjg","nkjjg","ojjjg","okjjg","pjjjg","pkjjg","kkjjg","kkajg","kkakg","kkbjg","kkbkg","kkcjg","kkckg","kkdjg","kkdkg","kkejg","kkekg","kkfjg","kkfkg","kkgjg","kkgkg","kkhjg","kkhkg","kkijg","kkikg","kkljg","kklkg","kkmjg","kkmkg","kknjg","kknkg","kkojg","kkokg","kkpjg","kkpkg","kkkkg","ggggx","gggxx","ggxxx","gxxxx","xxxxx","xxxxy","xxxyy","xxyyy","xyyyy","yyyyy","yyyyw","yyyww","yywww","ywwww","wwwww","wwvww","wvvww","vvvww","vvvwz","avvwz","aavwz","aaawz","aaaaz"]

    print(sol.ladderLength(beginWord, endWord, wordList))
    # print(sol.ladderLength2(beginWord, endWord, wordList))
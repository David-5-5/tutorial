import copy
from typing import List, Any

class State:
    def __init__(self, i) -> None:
        self.i = i
        self.link: State = None
        self.next: dict([str], [State]) = {}

    def __len__(self):
        return self.i

class SAM:

    def __init__(self, seq: List[Any]):
        '''
        一开始SAM只包含一个状态t0, 编号为0(其它状态的编号为 1,2, )
        为了方便，对于状态 t0 我们指定 len=0、link=-None
        '''
        self.last = State(0)
        self.t0 = self.last

        for ch in seq:
            self.add(str(ch))

    def add(self, ch: str):
        '''
        last为添加字符ch之前, 整个字符串对应的状态, 
        创建一个新的状态cur, 并将len(cur) 赋值为len(last) + 1, 这时link(cur)的值未知
        '''
        p = self.last
        cur = State(len(self.last)+1)
        '''
        如果还没有到字符ch的转移, 我们就添加一个到状态cur的转移, 遍历后缀链接. 如果在某个点已经存在到字符ch的转移, 
        我们就停下来, 并将这个状态标记为p. 
        '''
        while p is not None and ch not in p.next.keys():
            p.next[ch] = cur
            p = p.link
        '''
        如果没有找到这样的状态p, p is None, 我们将cur.link指向初始状态节点t0
        '''
        if not p:
            cur.link = self.t0
        else:
            '''
            假设现在我们找到了一个状态p, 其可以通过字符ch转移. 我们将转移到的状态标记为q.
            现在我们分类讨论两种状态:
            1) len(p) + 1 = len(q)
            2) len(p) + 1 != len(q)
            '''
            q:State = p.next[ch]
            if len(p) + 1 == len(q):
                '''
                我们只要将cur.link赋值为q并退出
                '''
                cur.link = q
            else:
                '''
                需要复制状态q, 创建一个新的状态clone, 复制q的除了len值以外的所有信息(后缀链接和转移)
                我们将len(clone)赋值为len(p)+1. 
                复制之后, 我们将后缀链接从cur.link指向clone. 也从q的后缀链接指向clone.
                最终使用后缀链接从状态p往回走, 只要存在一条通过p到状态q的转移, 就将该转移重定向到状态clone
                '''
                clone = State(len(p)+1)
                clone.next = copy.deepcopy(q.next)
                clone.link = q.link
                q.link = clone
                cur.link = clone
                # If there is a path from p to q, change the link to clone
                while p.link and p.link != q:
                    p = p.link
                if p:
                    p.link = clone
        
        self.last = cur


    def lcp(self, t: List[Any]):
        '''
        Longest common perfix
        '''
        l, best, bestpos = 0, 0, 0
        p:State = self.t0
        for i in range(len(t)):
            while len(p) and str(t[i]) not in p.next.keys():
                p = p.link
                l = len(p)

            if str(t[i]) in p.next.keys():
                p = p.next[str(t[i])]
                l += 1
            if l > best:
                best = l
                bestpos = i
        return t[bestpos-best+1:bestpos+1]


    def endpos(self, t: List[Any]) -> List[int]:
        '''
        结束位置, 字符串s的任意非空子串t我们记endpos(t)为在字符串s中t的所有结束位置
        例如, 对于字符串"abcbc", 我们有endpos("bc")=[2, 4]
        '''
        pass

if __name__ == "__main__":
    sam = SAM("abcbc")
    print(sam.lcp("dcbcd"))
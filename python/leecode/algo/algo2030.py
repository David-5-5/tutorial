class Solution:
    def smallestSubsequence(self, s: str, k: int, letter: str, repetition: int) -> str:
        n = len(s)
        maxOut = n - k
        out, inx, letDel, stack  = 0, 0, 0, []
        couldBeDel = s.count(letter) - repetition

        def _push(inx:int, out:int, letDel:int):
            if len(stack) < k:
                stack.append(s[inx])
                inx =  inx + 1
            elif s[inx] == letter and letDel < couldBeDel:
                letDel = letDel + 1
                inx =  inx + 1
            elif s[inx] == letter:
                for i in range(len(stack)-1, -1, -1):
                    if stack[i] != letter:break
                stack.pop(i)
                out = out + 1
                stack.append(s[inx])
                inx =  inx + 1
            else:
                inx =  inx + 1
            return inx, out, letDel


        while out < maxOut and inx < n:
            if len(stack) == 0 or stack[-1] <= s[inx]:
                inx, out, letDel = _push(inx, out, letDel)
            else:
                while stack and stack[-1] > s[inx] and (stack[-1]!=letter or (stack[-1]==letter and letDel < couldBeDel)):
                    pops = stack.pop()
                    out += 1
                    if pops == letter:
                        letDel += 1
                    if out == maxOut : break
                inx, out, letDel = _push(inx, out, letDel)
        return ''.join(stack) + s[inx:]
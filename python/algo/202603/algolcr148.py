from typing import List

# LCR series 同 946
class Solution:
    def validateBookSequences(self, putIn: List[int], takeOut: List[int]) -> bool:
        ans = False

        st = []

        for i in putIn:
            while st and st[-1] == takeOut[0]:
                st.pop(-1)
                takeOut.pop(0)
            st.append(i)
            
        if len(st) == 0 and len(takeOut) == 0: ans = True
        elif len(st) != len(takeOut):
            ans = False
        elif st and takeOut and st == takeOut[::-1]:
            ans = True
        return ans
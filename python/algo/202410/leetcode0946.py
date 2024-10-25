from typing import List


class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        ans = False

        st = []

        for i in pushed:
            while st and st[-1] == popped[0]:
                st.pop(-1)
                popped.pop(0)
            st.append(i)
            
        if len(st) == 0 and len(popped) == 0: ans = True
        elif len(st) != len(popped):
            ans = False
        elif st and popped and st == popped[::-1]:
            ans = True
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    pushed, popped = [2,1,0], [1,2,0]
    print(sol.validateStackSequences(pushed, popped))
from typing import List
class Solution:
    def sandyLandManagement(self, size: int) -> List[List[int]]:
        
        def gen(looplevel: int, level: int) -> List[int]:
            part = []
            ''' 4层一循环, looplevel [0:3] 
            level为当前的层
            从最后一层开始, 其looplevel
            '''
            if level == 1:
                part.append([1, 1])
            elif looplevel == 0:
                part.append([level, 1])
            elif looplevel == 1:
                for i in range(2, level*2-1, 2):
                    part.append([level, i+1])
            elif looplevel == 2:
                part.append([level, 2]) 
            elif looplevel == 3:
                for i in range(0, level*2-1, 2):
                    part.append([level, i+1])
            return part

        ans = []
        offset = 3 - size % 4
        for i in range(size, 0, -1):
            ans.extend(gen((offset+i)%4, i))
        
        return ans


if __name__ == "__main__":
    sol = Solution()
    print(sol.sandyLandManagement(5))
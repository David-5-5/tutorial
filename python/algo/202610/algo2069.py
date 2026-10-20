from typing import List

DIRS = [[1, 0], [0, 1], [-1, 0], [0, -1]]
class Robot:
    
    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.d = 0
        self.x = 0
        self.y = 0

    def step(self, num: int) -> None:
        if self.d == 0: dis = self.width-1 - self.x
        elif self.d == 1: dis = self.height-1 - self.y
        elif self.d == 2: dis = self.x
        else: dis = self.y
        if num > dis:
            num = dis + (num - dis) % (2 * (self.width + self.height) - 4)

        while num:
            dx, dy = DIRS[self.d][0] * num, DIRS[self.d][1] * num
            if dx:
                if dx + self.x < 0:
                    num = -(dx + self.x)
                    self.x = 0
                elif dx + self.x > self.width-1:
                    num = dx + self.x - self.width + 1
                    self.x = self.width -1
                else:
                    self.x += dx
                    num = 0
            else:
                if dy + self.y < 0:
                    num = -(dy + self.y)
                    self.y = 0
                elif dy + self.y > self.height - 1:
                    num = dy + self.y - self.height + 1
                    self.y = self.height - 1
                else:
                    self.y += dy       
                    num = 0
            if num: self.d = (self.d + 1) % 4



    def getPos(self) -> List[int]:
        return [self.x, self.y]

    def getDir(self) -> str:
        return ["East", "North", "West", "South"][self.d]



# Your Robot object will be instantiated and called as such:
# obj = Robot(width, height)
# obj.step(num)
# param_2 = obj.getPos()
# param_3 = obj.getDir()
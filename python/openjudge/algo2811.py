class Solution:

    def turnOffLight(self, grid):
        ret = []

        def turnOff(enum, first):
            tryRet = []
            tryRet.append(first)
            for i in range(5):
                for j in range(6):
                    if tryRet[i][j]:
                        enum[i][j] = enum[i][j] ^ 1
                        if i : enum[i-1][j] = enum[i-1][j] ^ 1
                        if i + 1 < 5: enum[i+1][j] = enum[i+1][j] ^ 1
                        if j : enum[i][j-1] = enum[i][j-1] ^ 1
                        if j + 1 < 6: enum[i][j+1] = enum[i][j+1] ^ 1
                if i < 4: tryRet.append(enum[i].copy())
            return tryRet
            
        for com in range(64):
            enum = [i.copy() for i in grid]
            first = [int(i) for i in list(bin(com)[2:].rjust(6, '0'))]
            ret = turnOff(enum, first)
            # if found, All values in the fifth row are zero
            found = True
            for j in enum[4]:
                if j :
                    found = False
            if found:
                return ret


if __name__ == "__main__":
    sol = Solution()
    grid = [[0, 1, 1, 0, 1, 0],
        [1, 0, 0, 1, 1, 1],
        [0, 0, 1, 0, 0, 1],
        [1, 0, 0, 1, 0, 1],
        [0, 1, 1, 1, 0, 0]]
    print(sol.turnOffLight(grid))
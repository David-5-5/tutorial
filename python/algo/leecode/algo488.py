import re
from collections import deque
class Solution:
    def findMinStep(self, board: str, hand: str) -> int:
        visited = {(board,hand)}
        todo = [(board,hand)]
        
        def eliminate(content: str):
            x = re.search("R{3,}|Y{3,}|B{3,}|G{3,}|W{3,}", content)
            while len(content)>0 and x:
                content = content[0:x.span()[0]] + content[x.span()[1]:]
                x = re.search("R{3,}|Y{3,}|B{3,}|G{3,}|W{3,}", content)
            return content

        # bfs
        while todo:
            _board, _hand = todo.pop(0)
            for i in range(len(_hand)):
                # 手中的相同颜色的球，仅使用一次
                if i == _hand.index(_hand[i]):
                    for pos in range(len(_board)+1):
                        # 仅插相同颜色的球的左侧，
                        if pos > 0 and _board[pos-1] == _hand[i] : continue

                        choose = False
                        #  - 第 1 种情况 : 当前球颜色与后面的球的颜色相同
                        if pos < len(_board) and _board[pos] == _hand[i]: 
                            choose = True
                        if 0 < pos < len(_board) and _board[pos - 1] == _board[pos] and _board[pos - 1] != _hand[i]:
                            choose = True                                            
                        if choose:
                            inserted = eliminate(_board[0:pos]+_hand[i]+_board[pos:])
                            if inserted == "":
                                return len(hand) - len(_hand) + 1
                            if (inserted, _hand[0:i]+_hand[i+1:]) not in visited:
                                visited.add((inserted, _hand[0:i]+_hand[i+1:]))
                                todo.append((inserted, _hand[0:i]+_hand[i+1:]))
                                

        return -1

    def findMinStep2(self, board: str, hand: str) -> int:
        visited = {(board,hand)}
        todo = deque([(board,hand)])
        
        def eliminate(content: str):
            x = re.search("R{3,}|Y{3,}|B{3,}|G{3,}|W{3,}", content)
            while len(content)>0 and x:
                content = content[0:x.span()[0]] + content[x.span()[1]:]
                x = re.search("R{3,}|Y{3,}|B{3,}|G{3,}|W{3,}", content)
            return content

        # bfs
        while todo:
            _board, _hand = todo.popleft()
            for i in range(len(_hand)):
                # 手中的相同颜色的球，仅使用一次
                if i == _hand.index(_hand[i]):
                    for pos in range(len(_board)):
                        # 仅插相同颜色的球的左侧，
                        if pos > 0 and _board[pos-1] == _hand[i] : continue
                        # 左右两边球不同，不能得到更好解
                        if pos > 0 and pos < len(_board) and _board[pos] != _hand[i] and _board[pos-1] != _board[pos]: continue
                        if pos == 0 and _board[pos] != _hand[i]: continue
                        # 其他可以得到更优解的情况
                        inserted = eliminate(_board[0:pos]+_hand[i]+_board[pos:])
                        if inserted == "":
                            return len(hand) - len(_hand) + 1
                        if (inserted, _hand[0:i]+_hand[i+1:]) not in visited:
                            visited.add((inserted, _hand[0:i]+_hand[i+1:]))
                            todo.append((inserted, _hand[0:i]+_hand[i+1:]))
                            
        return -1


if __name__ == "__main__":
    sol = Solution()
    board, hand = "WRRBBW", "RB"
    board, hand = "WWRRBBWW", "WRBRW"
    board, hand = "RBYYBBRRB", "YRBGB"
    board, hand = "RRWWRRBBRR", "WB"
    board, hand = "RRGGBBYYWWRRGGBB", "RGBYW"
    from datetime import datetime
    begin = datetime.now()
    print(sol.findMinStep(board, hand))
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    print(sol.findMinStep2(board, hand))
    print((datetime.now()- begin).total_seconds())    
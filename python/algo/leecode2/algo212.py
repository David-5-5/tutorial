from bisect import bisect_right

class Solution:
    def findWords(self, board, words) :
        '''
        总体思路：
        从board中任一点出发, 遍历board中的节点
        '''
        
        '排序, 供后续bisect_right方法快速查找'
        words.sort()
        
        n, m = len(board), len(board[0])
        ans = set()

        def concate(visited):
            '''
            将遍历的节点, 根据坐标, 组合成word
            '''
            s = ""
            for p in visited:
                x, y = p // m, p % m
                s += board[x][y]
            return s

        def find(visited):
            word = concate(visited)
            inx = bisect_right(words, word)
            if inx > 0 and words[inx-1] == word:
                '一个word仅加入一次, 匹配后即删除, 避免重复和冗余查找'
                del words[inx-1]
                if word not in ans : ans.add(word)
            elif len(word) == 10 or inx == len(words) or words[inx].find(word) != 0:
                return

            nextInx = len(visited)
            '下一个填充位，遍历'
            visited.append(-1)
            x, y = visited[nextInx-1] // m, visited[nextInx-1] % m
            for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                if 0 <= x+_x < n and 0 <= y+_y < m and (x+_x)*m+y+_y not in visited:
                    visited[-1] = (x+_x)*m+y+_y
                    find(visited)
            '删除剪枝，供后续回溯查找'
            del visited[nextInx:]


        for i in range(n):
            for j in range(m):
                find([i*m+j])
        
        return list(ans)

    def findWords2(self, board, words) :
        '''
        复兴，性能优化
        '''
        
        '排序, 供后续bisect_right方法快速查找'
        words.sort()
        
        n, m = len(board), len(board[0])
        ans = set()
        

        def find(word:str, i:int, j:int, visited):
            visited[i][j] = True
            word += board[i][j]
            
            inx = bisect_right(words, word)
            if inx > 0 and words[inx-1] == word:
                '一个word仅加入一次, 匹配后即删除, 避免重复和冗余查找'
                del words[inx-1]
                inx -= 1    # 删除后 inx 会发生变化，影响后续判断
                if word not in ans : ans.add(word)
            if not (len(word) == 10 or inx == len(words) or words[inx].find(word) != 0):    # 剪枝
                for x, y in [(0,1),(0,-1),(-1,0),(1,0)]:
                    if 0 <= i+x < n and 0 <= j+y < m and not visited[i+x][j+y]:
                        find(word, i+x, j+y, visited)
            '删除剪枝，供后续回溯查找'
            visited[i][j] = False           # 恢复现场
            word = word[:-1]                # 恢复现场


        for i in range(n):
            for j in range(m):
                visited = [[False] * m for _ in range(n)]
                find("", i, j, visited)
        
        return list(ans)       

if __name__ == "__main__":
    sol = Solution()
    words = ["oath","pea","eat","rain"]
    board = [["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
    print(sol.findWords2(board, words))
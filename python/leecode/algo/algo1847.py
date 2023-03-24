class Solution:
    def closestRoom(self, rooms, queries) :
        rooms.sort(key = lambda p: p[1])
        count = len(queries)
        ret = [-1] * count
        roomids = []
        
        from bisect import bisect_right
        def put(roomid):
            inx = bisect_right(roomids, roomid)
            roomids.insert(inx, roomid)
            
        for ri, query in sorted(enumerate(queries), key = lambda p:p[1][1], reverse = True):
            while rooms and rooms[-1][1] >= query[1]:
                roomid, _ = rooms.pop(-1)
                put(roomid)
            if roomids:
                inx = bisect_right(roomids, query[0])
                if inx == 0:
                    ret[ri] = roomids[0]
                elif inx == len(roomids):
                    ret[ri] = roomids[inx - 1]
                else:
                    ret[ri] = roomids[inx - 1] if (roomids[inx-1] + roomids[inx]) // 2 >= query[0] else roomids[inx]
        return ret

if __name__ == "__main__":
    sol = Solution()
    # rooms = [[2,2],[1,2],[3,2]]
    # queries = [[3,1],[3,3],[5,2]]
    # rooms = [[1,4],[2,3],[3,5],[4,1],[5,2]]
    # queries = [[2,3],[2,4],[2,5]]
    rooms = [[23,22],[6,20],[15,6],[22,19],[2,10],[21,4],[10,18],[16,1],[12,7],[5,22]]
    queries = [[12,5],[15,15],[21,6],[15,1],[23,4],[15,11],[1,24],[3,19],[25,8],[18,6]]
    print(sol.closestRoom(rooms, queries))        
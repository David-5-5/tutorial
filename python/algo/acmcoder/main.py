from collections import defaultdict
import heapq
from bisect import bisect_left

n, m = [int(i) for i in input().split()]

occupied = []
pq = []
c_2_chair = {}
chair_2_c = defaultdict(lambda :-1)

heapq.heappush(pq, (n*2, 1, n, -1, -1))

for _ in range(m):
    f, x = [int(i) for i in input().split()]
    if f == 1:
        while pq[0][-1] != -1 and pq[0][-1] not in c_2_chair.keys() or pq[0][-2] != -1 and pq[0][-2] not in c_2_chair.keys():
            heapq.heappop(pq)
        _, l, r, _, _ = heapq.heappop(pq)
        if chair_2_c[l] == -1:
            c_2_chair[x] = l
            chair_2_c[l] = x
            if r in chair_2_c.keys():
                if r-l-1 :heapq.heappush(pq, (1+l-r, l, r, chair_2_c[l], chair_2_c[r]))
            else:
                heapq.heappush(pq, ((1+l-r) * 2, l, r, chair_2_c[l], chair_2_c[r]))
        elif chair_2_c[r] == -1:
            c_2_chair[x] = r
            chair_2_c[r] = x
            if r-l-1:heapq.heappush(pq, (1+l-r, l, r, chair_2_c[l], chair_2_c[r]))
        else:
            mid = (l+r) // 2
            c_2_chair[x] = mid
            chair_2_c[mid] = x
            if mid-l-1: heapq.heappush(pq, (l+1-mid, l, mid, chair_2_c[l], chair_2_c[mid]))
            if r-mid-1: heapq.heappush(pq, (mid+1-r, mid, r, chair_2_c[mid], chair_2_c[r]))

        inx = bisect_left(occupied, c_2_chair[x])
        occupied.insert(inx, c_2_chair[x])
        print(c_2_chair[x])
    else:
        chair = c_2_chair[x]
        del c_2_chair[x]
        del chair_2_c[chair]
        inx = bisect_left(occupied, chair)
        if len(occupied) == 1:
            pq = []
            occupied = []
            heapq.heappush(pq, (-n * 2, 1, n, -1))
        else:
            if inx == 0:
                l = 1
                r = occupied[inx+1]
                heapq.heappush(pq, ((l+1-r) * 2, l, r, chair_2_c[l], chair_2_c[r]))
            elif inx == len(occupied) - 1:
                l = occupied[inx-1]
                r = n
                heapq.heappush(pq, ((l+1-r) * 2, l, r, chair_2_c[l], chair_2_c[r]))
            else:
                l = occupied[inx-1]
                r = occupied[inx+1]
                heapq.heappush(pq, ((l+1-r), l, r, chair_2_c[l], chair_2_c[r]))
            occupied.pop(inx)

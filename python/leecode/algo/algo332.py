class Solution:
    def findItinerary(self, tickets):
        left_edges = len(tickets)
        graph = {}
        
        from bisect import bisect_right
        
        for fromi, toi in tickets:
            if fromi not in graph.keys():
                graph[fromi] = [toi]
            else:
                inx = bisect_right(graph[fromi], toi)
                graph[fromi].insert(inx, toi)
        ret = ['JFK']
        while left_edges:
            cur = 0
            while (graph[ret[-1]][cur] not in graph.keys() or len(graph[graph[ret[-1]][cur]])==0) \
                and cur < len(graph[graph[ret[-1]][cur]])==0 and left_edges>1:
                cur += 1
            next = graph[ret[-1]].pop(cur)
            ret.append(next)
            
            left_edges -= 1
        return ret

if __name__ == "__main__":
    sol = Solution()
    # tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
    tickets = [["EZE","TIA"],["EZE","HBA"],["AXA","TIA"],["JFK","AXA"],["ANU","JFK"],["ADL","ANU"],["TIA","AUA"],["ANU","AUA"],["ADL","EZE"],["ADL","EZE"],["EZE","ADL"],["AXA","EZE"],["AUA","AXA"],["JFK","AXA"],["AXA","AUA"],["AUA","ADL"],["ANU","EZE"],["TIA","ADL"],["EZE","ANU"],["AUA","ANU"]]
    print(sol.findItinerary(tickets))
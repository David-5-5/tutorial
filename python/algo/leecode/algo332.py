class Solution:
    def findItinerary(self, tickets):
        '''
        Hierholzer 算法
        '''
        '''
        Hierholzer 算法
        '''
        graph = {}

        from bisect import bisect_right
        
        for fromi, toi in tickets:
            if fromi not in graph.keys():
                graph[fromi] = [toi]
            else:
                inx = bisect_right(graph[fromi], toi)
                graph[fromi].insert(inx, toi)
        
        def dfs(vertex):
            while vertex in graph.keys() and graph[vertex]:
                child = graph[vertex].pop(0)
                dfs(child)
            ret.append(vertex)

        ret = []
        dfs('JFK')
        return ret[::-1]

if __name__ == "__main__":
    sol = Solution()
    tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    # tickets = [["EZE","TIA"],["EZE","HBA"],["AXA","TIA"],["JFK","AXA"],["ANU","JFK"],["ADL","ANU"],["TIA","AUA"],["ANU","AUA"],["ADL","EZE"],["ADL","EZE"],["EZE","ADL"],["AXA","EZE"],["AUA","AXA"],["JFK","AXA"],["AXA","AUA"],["AUA","ADL"],["ANU","EZE"],["TIA","ADL"],["EZE","ANU"],["AUA","ANU"]]
    print(sol.findItinerary(tickets))
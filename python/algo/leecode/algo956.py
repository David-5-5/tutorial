class Solution:
    def tallestBillboard2(self, rods) -> int:
        '''
        官方题解，方法一动态规划
        '''
        
        

    def tallestBillboard2(self, rods) -> int:
        '''
        官方题解，方法二暴力优化，折半法
        '''
        def combi(part):
            # part元素组合，特别巧妙
            # 每个元素由三种情况，X（集合1， a）， -X（集合2， b）， 不出现
            state = {(0,0)}
            for x in part:
                state |= {(a+x, b) for a, b in state} | \
                {(a, b+x) for a, b in state}
            
            delta = {}
            for a, b in state:
                delta[a-b] = max(a, delta.get(a-b, 0))
            return delta

        ans = 0
        left = combi(rods[0:len(rods)//2])
        right = combi(rods[len(rods)//2:])
        for d in left.keys():
            if -d in right.keys():
                ans = max(ans, left[d] + right[-d])
        return ans


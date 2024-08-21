from typing import List


class Solution:
    def mostPopularCreator(self, creators: List[str], ids: List[str], views: List[int]) -> List[List[str]]:
        mx = 0
        mxcreate = set()
        mxid = {}

        for c, id, v in zip(creators, ids, views):
            if c in mxid.keys():
                mxid[c][0] += v
                if v > mxid[c][2]:
                    mxid[c][1] = id
                    mxid[c][2] = v
                elif v == mxid[c][2]:
                    mxid[c][1] = min(mxid[c][1], id)

            else:
                mxid[c] = [v, id, v]


            if mxid[c][0] > mx:
                mx = mxid[c][0]
                mxcreate.clear()
                mxcreate.add(c)
            elif mxid[c][0] == mx:
                mxcreate.add(c)
        
        ans = []
        for c in mxcreate: ans.append([c,mxid[c][1]])
        return ans

if __name__ == "__main__":
    sol = Solution()
    creators, ids, views = ["alice","bob","alice","chris"], ["one","two","three","four"], [5,10,5,4]
    print(sol.mostPopularCreator(creators, ids, views))

                
        


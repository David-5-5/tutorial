from audioop import add
from site import addpackage
from urllib import request


class Solution:
    def smallestSufficientTeam(self, req_skills, people) :
        hashSkill = {}
        n = len(req_skills)
        m = len(people)

        for i in range(n):
            for j in range(m):
                if req_skills[i] in people[j]:
                    if req_skills[i] in hashSkill.keys():
                        hashSkill[req_skills[i]].add(j)
                    else:
                        hashSkill[req_skills[i]] = set([j])
        candidate = [([i], set(req_skills) - set(people[i])) for i in range(m)]
        
        def addPeople(candidate) :
            newCan = []
            for result, skill in candidate:
                can_p = None
                lskill = list(skill)
                for el in lskill:
                    if not can_p:
                        can_p = hashSkill[el]
                    else:
                        can_p = can_p.union(hashSkill[el])
                l_can_p = list(can_p)
                for p in l_can_p:
                    newresult = result.copy()
                    newresult.append(p)
                    newCan.append((newresult, skill - set(people[p])))

            return newCan

        while True:
            for result, skill in candidate:
                if len(skill) == 0:
                    return result
            candidate = addPeople(candidate)


    def smallestSufficientTeam2(self, req_skills, people) :
        n = len(req_skills)

        dp = [None] * (1 << n)
        dp[0] = []
        for i, q in enumerate(people):
            cur_skill = 0
            for skill in q:
                cur_skill |= 1 << req_skills.index(skill)
            
            for prev in range(1 << n):
                if dp[prev] is None:
                    continue
                comb = prev | cur_skill
                if dp[comb] is None or len(dp[comb]) > len(dp[prev]) + 1:
                    dp[comb] = [i] + dp[prev]

        return dp[(1 << n) -1]

    def smallestSufficientTeam3(self, req_skills, people) :
        n = len(req_skills)

        # 参考官方题解，将1<<n长度list改为dict
        dp = {}
        dp[0] = []
        for i, q in enumerate(people):
            cur_skill = 0
            for skill in q:
                cur_skill |= 1 << req_skills.index(skill)
            
            prevs = list(dp.keys())
            # 避免在稀疏的1<<n长度的list表中遍历
            for prev in prevs:
                comb = prev | cur_skill
                if not (comb in dp.keys()) or len(dp[comb]) > len(dp[prev]) + 1:
                    dp[comb] = [i] + dp[prev]

        return dp[(1 << n) -1]


if __name__ == "__main__":
    sol = Solution()
    req_skills = ["java","nodejs","reactjs"]
    people = [["java"],["nodejs"],["nodejs","reactjs"]]
    req_skills = ["gkgtfxpvxnxlbhxu","baayobms","yomqrposuurmvisx","vsftojpcp","pjovtkytubbouq","hlmvucyi","chpzrslbtd","uighcqpiteg"]
    people = [["pjovtkytubbouq"],["baayobms"],["baayobms","pjovtkytubbouq"],["chpzrslbtd"],[],["yomqrposuurmvisx"],["uighcqpiteg"],[],["gkgtfxpvxnxlbhxu","yomqrposuurmvisx","uighcqpiteg"],[],["pjovtkytubbouq","uighcqpiteg"],["yomqrposuurmvisx"],[],[],[],["pjovtkytubbouq"],["gkgtfxpvxnxlbhxu","yomqrposuurmvisx","pjovtkytubbouq","uighcqpiteg"],["yomqrposuurmvisx","pjovtkytubbouq"],["chpzrslbtd"],["pjovtkytubbouq"],[],[],["baayobms"],["yomqrposuurmvisx","chpzrslbtd"],["yomqrposuurmvisx","pjovtkytubbouq"],["pjovtkytubbouq"],[],["yomqrposuurmvisx"],[],["yomqrposuurmvisx","pjovtkytubbouq"],[],[],[],["yomqrposuurmvisx"],[],["pjovtkytubbouq"],[],[],[],["vsftojpcp"],[],["yomqrposuurmvisx","pjovtkytubbouq"],[],[],["gkgtfxpvxnxlbhxu"],["yomqrposuurmvisx"],["pjovtkytubbouq","chpzrslbtd"],["uighcqpiteg"],["pjovtkytubbouq"],["yomqrposuurmvisx","pjovtkytubbouq","uighcqpiteg"],[],["pjovtkytubbouq"],[],["chpzrslbtd"],["hlmvucyi"],["yomqrposuurmvisx","pjovtkytubbouq"],["pjovtkytubbouq"],[],["yomqrposuurmvisx"],[]]
    print(sol.smallestSufficientTeam3(req_skills, people))
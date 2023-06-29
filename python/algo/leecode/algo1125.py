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


if __name__ == "__main__":
    sol = Solution()
    req_skills = ["java","nodejs","reactjs"]
    people = [["java"],["nodejs"],["nodejs","reactjs"]]
    req_skills = ["gkgtfxpvxnxlbhxu","baayobms","yomqrposuurmvisx","vsftojpcp","pjovtkytubbouq","hlmvucyi","chpzrslbtd","uighcqpiteg"]
    people = [["pjovtkytubbouq"],["baayobms"],["baayobms","pjovtkytubbouq"],["chpzrslbtd"],[],["yomqrposuurmvisx"],["uighcqpiteg"],[],["gkgtfxpvxnxlbhxu","yomqrposuurmvisx","uighcqpiteg"],[],["pjovtkytubbouq","uighcqpiteg"],["yomqrposuurmvisx"],[],[],[],["pjovtkytubbouq"],["gkgtfxpvxnxlbhxu","yomqrposuurmvisx","pjovtkytubbouq","uighcqpiteg"],["yomqrposuurmvisx","pjovtkytubbouq"],["chpzrslbtd"],["pjovtkytubbouq"],[],[],["baayobms"],["yomqrposuurmvisx","chpzrslbtd"],["yomqrposuurmvisx","pjovtkytubbouq"],["pjovtkytubbouq"],[],["yomqrposuurmvisx"],[],["yomqrposuurmvisx","pjovtkytubbouq"],[],[],[],["yomqrposuurmvisx"],[],["pjovtkytubbouq"],[],[],[],["vsftojpcp"],[],["yomqrposuurmvisx","pjovtkytubbouq"],[],[],["gkgtfxpvxnxlbhxu"],["yomqrposuurmvisx"],["pjovtkytubbouq","chpzrslbtd"],["uighcqpiteg"],["pjovtkytubbouq"],["yomqrposuurmvisx","pjovtkytubbouq","uighcqpiteg"],[],["pjovtkytubbouq"],[],["chpzrslbtd"],["hlmvucyi"],["yomqrposuurmvisx","pjovtkytubbouq"],["pjovtkytubbouq"],[],["yomqrposuurmvisx"],[]]
    print(sol.smallestSufficientTeam(req_skills, people))
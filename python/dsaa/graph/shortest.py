from collections import defaultdict
from math import inf
from typing import List
import heapq
# graph is a dict ,which key is the vertex(from 0,..,n-1) and 
# value is list of ajacent vertex and it weigth
class shortest:
    def dijkstra(self, n:int, start :int, graph :List[List[int]])->List[int]:
        dist = [inf] * n
        visited = [False] * n

        dist[start] = 0
        # The element in pr is truple (weight, vertex)
        pr = []
        heapq.heappush(pr, (0,start)) 
        while pr:
            _, u = heapq.heappop(pr)
            if visited[u]:
                continue
            visited[u] = True
            for v, w in graph[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    heapq.heappush(pr, (dist[v], v))

        return dist
        

if __name__ == "__main__":
    # graph = {}
    # graph[0] = [[1,1],[2,12]]
    # graph[1] = [[0,1],[2,9],[3,3]]
    # graph[2] = [[0,12],[1,9],[3,4],[4,5]]
    # graph[3] = [[1,3],[2,4],[4,13],[5,15]]
    # graph[4] = [[2,5],[3,13],[5,4]]
    # graph[5] = [[3,15],[4,4]]
    # short = shortest()
    # print(short.dijkstra(graph))

    edges = [[1,30,439],[24,4,950],[5,20,730],[38,7,455],[8,14,532],[11,38,450],[14,29,382],[20,41,430],[21,22,974],[21,23,457],[29,21,611],[25,24,256],[17,26,182],[17,25,485],[29,39,249],[30,31,807],[34,15,645],[15,41,917],[13,36,644],[13,12,225],[9,37,839],[9,38,276],[10,39,730],[31,10,234],[31,27,624],[28,27,574],[32,28,197],[12,32,574],[16,12,769],[40,18,670],[35,18,699],[0,41,575],[0,33,156],[33,16,686],[6,16,874],[6,25,484],[25,35,647],[35,9,309],[19,9,125],[3,19,138],[2,3,875],[42,2,253],[32,31,858],[30,2,255],[7,39,388],[9,16,121],[28,0,408],[16,29,870],[30,27,771],[18,17,883],[31,25,552],[35,12,871],[33,37,581],[9,17,312],[29,11,833],[38,12,642],[14,30,402],[32,8,840],[29,38,878],[35,27,361],[17,31,682],[25,38,483],[42,11,377],[30,12,264],[42,20,750],[42,1,712],[14,42,482],[35,6,119],[39,18,940],[35,7,629],[24,15,310],[15,3,807],[5,11,576],[12,40,762],[32,40,181],[34,30,224],[0,42,662],[25,19,307],[38,36,635],[5,32,108],[14,38,578],[35,0,347],[31,14,762],[0,17,887],[25,13,790],[17,38,126],[20,6,550],[10,5,695],[27,22,785],[37,11,196],[28,18,489],[3,23,543],[32,35,591],[21,31,515],[32,42,495],[22,39,164],[23,13,408],[38,1,753],[10,23,707],[29,0,293],[15,9,178],[16,23,977],[35,5,703],[40,21,814],[24,19,363],[9,31,948],[5,18,438],[8,21,195],[13,0,946],[31,7,581],[23,7,765],[24,9,810],[14,3,130],[19,23,502],[17,11,578],[32,21,660],[35,34,146],[16,11,486],[22,42,951],[13,21,107],[19,4,168],[9,5,153],[12,7,273],[40,22,213],[13,37,767],[2,40,975],[15,5,986],[28,39,307],[33,38,377],[23,39,429],[10,37,217],[24,38,654],[5,25,354],[2,41,965],[17,13,375],[15,28,741],[3,34,386],[2,25,340],[40,34,959],[16,30,855],[20,23,702],[37,1,889],[14,32,312],[33,6,977],[2,8,189],[12,20,112],[31,37,978],[17,21,733],[26,20,319],[36,27,406],[39,20,473],[3,39,726],[40,1,855],[28,17,800],[29,18,963],[35,8,723],[26,35,728],[21,20,475],[22,30,642],[24,26,735],[28,3,691],[42,39,525],[14,33,773],[34,25,678],[36,39,729],[6,30,145],[4,34,307],[32,13,230],[0,16,382],[13,30,313],[9,18,518],[31,19,610],[10,25,962],[0,20,1],[42,40,178],[28,38,336],[17,27,819],[37,27,421],[24,5,565],[30,26,538],[33,22,297],[39,12,259],[7,6,619],[34,41,564],[35,19,973],[22,29,648],[32,0,745],[4,12,238],[10,16,738],[0,14,572],[28,35,538],[2,36,953],[29,30,949],[24,8,899],[41,42,215],[38,34,277],[11,0,848],[8,36,154],[20,9,790],[7,25,937],[28,21,259],[19,34,290],[35,22,482],[12,22,344],[3,8,736],[28,33,985],[33,5,613],[22,8,181],[21,16,760],[40,15,704],[13,34,971],[1,22,543],[28,24,512],[1,25,736],[18,2,235],[40,26,334],[18,24,818],[31,40,419],[28,34,396],[23,11,606],[3,10,324],[10,28,597],[14,41,213],[17,2,476],[8,38,378],[30,19,336],[4,13,600],[30,11,157],[6,0,713],[3,16,640],[6,22,669],[33,17,476],[34,0,404],[5,8,201],[37,8,731],[15,39,533],[12,0,628],[27,20,444],[18,33,450],[12,28,411],[19,1,885],[15,29,731],[42,37,514],[0,23,640],[5,3,284],[17,1,579],[16,22,336],[41,12,960],[8,0,583],[16,7,483],[13,15,218],[34,11,438],[34,12,372],[18,26,146],[41,32,238],[3,7,461],[31,8,889],[7,27,459],[24,39,543],[11,24,705],[41,5,364],[27,39,704],[21,15,679],[8,12,869],[12,1,835],[28,5,830],[35,31,434],[31,13,826],[30,32,838],[37,32,943],[11,13,480],[35,13,515],[39,9,323],[7,37,262],[23,2,483],[7,36,633],[27,15,771],[5,14,604],[24,35,321],[32,9,118],[17,29,519],[38,39,707],[39,14,437],[32,1,377],[24,42,748],[38,41,275],[16,19,906],[40,27,949],[20,34,730],[8,42,321],[31,16,851],[24,40,749],[29,34,207],[11,41,844],[8,33,548],[36,35,258],[40,38,357],[36,31,905],[41,1,153],[34,17,189],[40,35,342],[16,28,411],[30,36,679],[35,38,247],[14,19,163],[40,3,876],[35,39,635],[12,9,101],[8,20,1],[19,2,850],[33,30,153],[13,27,869],[22,26,191],[22,0,614],[29,42,958],[33,26,909],[37,23,996],[41,16,238],[12,42,694],[7,15,929],[7,4,850],[39,16,301],[10,18,883],[32,27,942],[37,14,618],[36,37,918],[17,5,468],[13,3,337],[29,25,986],[8,34,851],[40,23,572],[3,29,637],[2,28,380],[4,10,255],[26,1,697],[20,15,280],[20,36,814],[32,20,689],[5,6,223],[41,39,562],[16,38,967],[6,13,379],[16,13,864],[21,42,538],[15,8,711],[12,33,388],[10,29,665],[8,25,256],[9,11,570],[30,18,795],[30,8,472],[7,20,722],[11,4,191],[36,14,753],[18,8,639],[26,7,457],[27,25,999],[1,28,695],[35,33,831],[37,41,911],[33,21,939],[28,42,418],[27,12,643],[2,27,606],[36,4,720],[7,42,843],[1,6,122],[7,0,292],[37,29,446],[18,1,811],[12,10,813],[29,5,869],[19,33,929],[23,1,320],[33,2,663],[5,34,768],[10,32,392],[19,21,845],[25,30,849],[30,35,776],[14,27,526],[2,16,251],[26,36,241],[33,11,750],[3,4,888],[25,20,201],[42,6,826],[4,25,264],[37,35,850],[13,26,446],[34,16,952],[9,36,192],[37,25,387],[13,19,664],[16,15,340],[19,37,707],[4,8,608],[8,27,356],[15,37,511],[21,4,864],[1,10,743],[24,3,155],[40,17,176],[40,39,652],[25,41,834],[31,29,339],[37,30,229],[1,33,791],[22,32,912],[13,41,103],[32,38,910],[8,28,714],[29,35,252],[15,35,178],[6,34,582],[17,8,743],[19,10,294],[10,14,129],[26,39,516],[9,6,229],[35,10,838],[15,33,136],[13,5,568],[2,24,178],[1,8,1],[17,10,562],[4,17,741],[4,31,705],[30,41,692],[10,26,663],[36,10,393],[1,5,672],[42,3,975],[16,20,726],[32,11,739],[29,36,845],[29,41,229],[2,39,311],[38,5,373],[12,14,826],[11,15,554],[3,25,740],[40,8,987],[5,36,391],[6,15,235],[14,22,953],[14,24,521],[21,6,333],[16,1,740],[20,40,438],[34,31,658],[4,18,663],[13,9,106],[35,16,642],[19,32,984],[4,2,899],[28,20,820],[10,42,123],[19,42,262],[7,9,158],[13,22,677],[38,18,488],[4,27,698],[40,10,365],[39,6,151],[9,2,324],[40,14,259],[33,27,231],[22,38,233],[17,6,996],[25,0,906],[15,10,640],[26,37,442],[19,15,424],[18,12,363],[18,0,393],[38,15,784],[3,9,720],[20,17,375],[24,0,669],[31,41,903],[18,22,434],[26,29,471],[26,23,909],[25,28,279],[36,19,240],[40,28,949],[37,22,164],[13,33,208],[36,41,746],[4,15,569],[36,12,630],[3,6,675],[29,8,528],[3,36,352],[11,21,831],[1,14,820],[2,32,422],[39,19,342],[40,6,486],[34,26,767],[19,6,417],[0,26,497],[33,7,639],[24,16,672],[22,28,112],[10,7,929],[35,1,984],[16,18,875],[30,5,526],[7,8,680],[33,25,410],[37,38,295],[13,39,522]]
    graph = defaultdict(list)

    for u, v, w in edges:
        graph[u].append((v, w))
        graph[v].append((u, w))

    short = shortest()
    from datetime import datetime
    begin = datetime.now()
    print("begin ..  edges count is %d " % (len(edges)))
    print(short.dijkstra(43, 0, graph))
    print((datetime.now()- begin).total_seconds())
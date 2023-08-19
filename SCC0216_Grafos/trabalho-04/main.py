def main():

    ## Load Grpah Info ##

    v, a = input().split()

    ## Populate the Graph with Data ##

    graph = Graph(v = int(v))

    for i in range(int(a)):
        u, v, w = input().split()
        graph.addEdge(int(u), int(v), int(w))

    ## Goal Input ##

    goal = input()

    ## Problem Solving ##

    mst_cost = generateMST(graph = graph)
    vip_cost = dijkstraDist(graph = graph, goal = int(goal))

    if mst_cost < vip_cost:
        print('PADRAO')
        print(mst_cost)
    elif mst_cost > vip_cost:
        print('VIP')
        print(vip_cost)
    elif mst_cost == vip_cost:
    	print('NDA')
    	print(mst_cost)



## Graph ##

from queue import PriorityQueue
import heapq

class Graph:
    def __init__(self, v):
        self.size = v
        self.edges = [[] for _ in range(v)] # graph of lists
        self.visited = [] # used for djikstra algorithm
        
    def addEdge(self, u, v, w):
        if v not in map(lambda x: x[0] ,self.edges[u]):
            self.edges[u].append((v, w))
        
        if u not in map(lambda x: x[0] ,self.edges[v]):
            self.edges[v].append((u, w))
        
    def printGraph(self): # for test pourposes
        printString = ""
        
        for i, u in enumerate(self.edges):
            printString += f"V[{i}]: "
            for v, w in u:
                printString += f"({v}, {w}); "
            printString += "\n"
        
        print('Graph (List):')
        print(printString)


def generateMST(graph: Graph):

    parents = [(-1,-1) for _ in range(graph.size)]
    priority_queue = PriorityQueue()
    in_tree = [False] * graph.size

    priority_queue.put((0,0,-1))

    while not priority_queue.empty():
        
        weight, current, parent = priority_queue.get()
        
        if in_tree[current]:
            continue

        in_tree[current] = True
        parents[current] = (parent, weight)

        for child, weight in graph.edges[current]:
            
            if not in_tree[child]:
                priority_queue.put((weight, child, current))
            

    # Create a Graph to represent the generated tree
    # new_graph = Graph(graph.size)
    # for i in range(graph.size):
    #     if parents[i][0] != -1:
    #         new_graph.addEdge(i, parents[i][0], parents[i][1])

    # print(parents)

    cost = sum(map(lambda x: x[1], parents))

    return cost


def dijkstra(graph: Graph, start: int):
    distances = {vertex: float('inf') for vertex in range(graph.size)}
    previous = {vertex: None for vertex in range(graph.size)}

    distances[start] = 0
    pq = [(0, start)]

    while len(pq) > 0:
        current_dist, current_vertex = heapq.heappop(pq)

        if current_dist > distances[current_vertex]:
            continue

        for neighbor, weight in graph.edges[current_vertex]:
            distance = current_dist + weight
            
            if previous[neighbor] == None:
                previous[neighbor] = current_vertex

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))

    return [distances, previous]


def dijkstraDist(graph: Graph, goal: int):
    [distances, previous] = dijkstra(graph = graph, start = 0) # find the cost and the previous node

    count = 1
    current = goal
    while current != 0: # count how many nodes our path passes though
        count += 1
        current = previous[current]

    remaining = graph.size - count
    vip_cost = remaining * distances[goal] # vip cost = remaining cities * cost to vip delivery
    
    return vip_cost

if __name__ == "__main__":
    main()

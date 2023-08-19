import os

class Graph:
    def __init__(self, v):
        self.size = v
        self.graph = [[] for _ in range(v)] # graph of lists
        self.graph_header = [0 for _ in range(v)]

    def addEdge(self, v1, v2):
        self.graph[v1].append(v2)
        self.graph_header[v1] += 1
        self.graph[v2].append(v1)
        self.graph_header[v2] += 1

    def removeEdge(self, v1, v2):
        self.graph[v1].remove(v2)
        self.graph_header[v1] -= 1
        self.graph[v2].remove(v1)
        self.graph_header[v2] -= 1

    def printGraph(self): # for test pourposes
        print('Graph (List Representation):')
        for i, v in enumerate(self.graph):
            count = self.graph_header[i]
            print(f'V[{i}] = {count} --> {v}')

    # ===============================================

    def isEuler(self):
        # Theorem: If every vertex has an *even* number of connections, it has an Euler Path 
        for v_count in self.graph_header:
            if (v_count % 2) != 0:
                return False
            
        return True
    
    # ===============================================

    def DFSCount(self, v, visited): # Deep Field Search to check bridges
        count = 1
        visited[v] = True
		
        for i in self.graph[v]:
            if visited[i] == False:
                count = count + self.DFSCount(i, visited)		
        
        return count
    
    def isNextEdgeValid(self, v0, v1):
        # Case 01: v1 is the adjacent vertex of v0
        if len(self.graph[v0]) == 1:
            return True
        else:
            # Case 02: v0-v1 is not a bridge (it doesn't cut the graph)
            visited = [False] * (self.size)
            count1 = self.DFSCount(v0, visited)

            self.removeEdge(v0, v1)

            visited = [False] * (self.size)
            count2 = self.DFSCount(v0, visited)

            self.addEdge(v0, v1)
            self.graph[v0].sort()
            self.graph[v1].sort()

            comp = count1 > count2 # If count1 is greater, then edge v0-v1 is a bridge

            return (not comp)
    
    def findEulerPath(self, v0, path = []):
        for v1 in self.graph[v0]:
            if self.isNextEdgeValid(v0, v1):
                path += [v0]
                self.removeEdge(v0, v1)

                path = self.findEulerPath(v1, path)
                
        return path

# ================================================================= #

## Read the file and Grpah Info ##

here = os.path.dirname(os.path.abspath(__file__))

filename = input()
# filename = 'ex1.in'
# filename = 'ex2.in'
file = open(os.path.join(here, filename), 'r')
v, a = file.readline().split(' ')

## Populate the Graph with data ##

graph = Graph(int(v))

for i in range(int(a)):
    line = file.readline().replace('\n', '')
    v0, v1 = line.split(' ')

    graph.addEdge(int(v0), int(v1))

file.close()

# graph.printGraph()

## Find the Euler Path if it exists ##

if graph.isEuler():
    startPos = 0
    path = graph.findEulerPath(startPos)
    path += [0] # end node

    print('Sim')
    [print(n, end = ' ') for n in path]
    # print('\n0 1 2 3 1 4 3 0 << res') # ex1.in
    # print('\n0 1 2 0 5 2 3 4 5 6 0 << res') # ex2.in
else:
    print('Não')

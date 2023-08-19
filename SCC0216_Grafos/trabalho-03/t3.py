import os

class Graph:
    def __init__(self, v, isDirectional):
        self.size = v
        self.isDirectional = isDirectional        # directional graph flag
        self.graph = [[] for _ in range(v)]       # graph of lists
        self.graph_header = [0 for _ in range(v)]
        # Problem help variables
        self.step = 0                             # time
        self.sccStack = []                        # strongly connected component stack (result) 

    def addEdge(self, v1, v2):
        self.graph[v1].append(v2)
        self.graph_header[v1] += 1
        if not self.isDirectional:
          self.graph[v2].append(v1)
          self.graph_header[v2] += 1

    def removeEdge(self, v1, v2):
        self.graph[v1].remove(v2)
        self.graph_header[v1] -= 1
        if not self.isDirectional:
          self.graph[v2].remove(v1)
          self.graph_header[v2] -= 1

    def printGraph(self): # for test pourposes
        print('Graph (List Representation):')
        for i, v in enumerate(self.graph):
            count = self.graph_header[i]
            print(f'V[{i}] = {count} --> {v}')

    def SCCDFS(self, u, low, disc, stackItem, sccStack):
        disc[u] = self.step   # discovery time
        low[u] = self.step    # low value
        self.step += 1
        stackItem[u] = True
        sccStack.append(u)
 
        for v in self.graph[u]:
            if disc[v] == -1:
                self.SCCDFS(v, low, disc, stackItem, sccStack)
                low[u] = min(low[u], low[v])
 
            elif stackItem[v] == True:
                low[u] = min(low[u], disc[v])
 
        w = -1  # To store stack extracted vertices
        if low[u] == disc[u]:
            hold = []

            while w != u:
                w = sccStack.pop()
                hold.append(w)
                stackItem[w] = False

            hold.sort()
            self.sccStack.append(hold[0:])
 
    def SCC(self):
        disc = [-1] * (self.size)
        low = [-1] * (self.size)
        stackItem = [False] * (self.size)
        sccStack = []

        for i in range(self.size):
            if disc[i] == -1:
                self.SCCDFS(i, low, disc, stackItem, sccStack)

# ================================================================= #

## Read the file and Grpah Info ##

runcodes = True
testName = '1.in'

if runcodes:
    v, a = input().split()
else : 
  here = os.path.dirname(os.path.abspath(__file__))
  filename = os.path.join('test', testName)
  file = open(os.path.join(here, filename), 'r')
  
  v, a = file.readline().split(' ')

## Populate the Graph with data ##

graph = Graph(v = int(v), isDirectional = True)

for i in range(int(a)):
    if runcodes:
      v0, v1 = input().split()
    else:
      line = file.readline().replace('\n', '')
      v0, v1 = line.split(' ')

    graph.addEdge(int(v0), int(v1))

if not runcodes:
  file.close()

# graph.printGraph()

## Check for sub-graphs and print results ##

graph.SCC()

graph.sccStack.sort()

print(len(graph.sccStack))
for line in graph.sccStack:
    print(' '.join(str(item) for item in line))

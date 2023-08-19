#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <memory>
#include <utility>
#include <iostream>
#include <algorithm>

using adjacency_list_type = std::list<int>;

class Graph
{
private:
    
public:

    std::unordered_map<int, adjacency_list_type> adjacency_lists;

    Graph();

    //Add a vertex to the graph
    void addVertex(int vertex_value);
    //Connect two vertices if they are already in the graph
    void connectVertex(int first_vertex_value, int second_vertex_value);

    std::list<int> searchPath(int fromID, int toID);
};

#endif

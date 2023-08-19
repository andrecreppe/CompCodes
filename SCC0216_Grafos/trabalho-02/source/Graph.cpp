#include "../header/Graph.h"

Graph::Graph() { }

void Graph::addVertex(int vertex_value){
    adjacency_lists.insert({vertex_value, {}});
}

void Graph::connectVertex(int first_vertex_value, int second_vertex_value)
{
    //Access pair instances of vertices and edges maps
    auto& first_vertex = adjacency_lists.at(first_vertex_value);
    auto& second_vertex =  adjacency_lists.at(second_vertex_value);

    //Return if the vertex is already inside the adjacent list
    if(std::find(first_vertex.begin(), first_vertex.end(), second_vertex_value) != first_vertex.end())
        return;

    first_vertex.push_back({second_vertex_value});
    second_vertex.push_back({first_vertex_value});
}

std::list<int> Graph::searchPath(int start, int finish) {
    // Vertices as not visited
    std::unordered_set<int> visited;

    bool hasFound = false;

    // Queue for BFS
    std::deque<int> queue;
    std::unordered_map<int, int> parents; // to keep track of parent vertices

    visited.insert(start);
    queue.push_back(start);

    while (!queue.empty()) {
        // Dequeue a vertex from queue
        int current = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued element
        // If a adjacent has not been visited, mark it visited and enqueue it
        const auto& adjacentList = adjacency_lists.at(current);
        for (const auto& adjacent : adjacentList) {
            if (visited.find(adjacent) == visited.end()) {
                visited.insert(adjacent);
                queue.push_back(adjacent);
                parents[adjacent] = current; // set the parent of the adjacent vertex to the current vertex
                if(adjacent == finish){
                    hasFound = true;
                    break;
                }
            }
        }

        if(hasFound)
            break;
    }

    // build path from finish to start
    std::list<int> path{};

    // If start is equal to finish, then return a list with only the start element
    if(start == finish){
        path.push_front(start);
        return path;
    }

    // If finish vertex was not found, then return an empty list
    if(!hasFound){
        return path;
    }

    int current = finish;
    while (current != start) {
        path.push_front(current);
        current = parents.at(current);
    }
    path.push_front(start);

    return path;
}
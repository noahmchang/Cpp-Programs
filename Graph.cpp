#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"
#include "GraphNode.hpp"
#include <queue>

// template <typename T>
// Graph<T>::Graph(){
// }

/// @brief construct a graph from a list of edges
/// @param edges a vector of pairs of vertices representing the edges
///        each pair is two veritces <from, to>
template <typename T>
Graph<T>::Graph(const std::vector<std::pair<T, T>> &edges){
    for(const std::pair<T, T> &edge : edges){
        addVertex(edge.first);
        addVertex(edge.second);
        addEdge(edge.first, edge.second);
    }
}

/// @brief construct a graph from an adjacency list
/// @param adjList a map from vertex to a set of its neighbors
template <typename T>
Graph<T>::Graph(const std::map<T, std::set<T>> &adjList){
    for(const auto &adj_pair : adjList){
        addVertex(adj_pair.first);
        for(const T &neighbor_vertex : adj_pair.second){
            addVertex(neighbor_vertex);
            addEdge(adj_pair.first, neighbor_vertex);
        }
    }
}

// template <typename T>
// Graph<T>::~Graph(){
//     _adjList.clear();
//     _vertices.clear();
// }

/// @brief get the number of vertices in the graph
/// @return the number of vertices in the graph
template <typename T>
int Graph<T>::size() const{
    return _vertices.size();
}

/// @brief add a vertex to the graph with no edges
/// @param vertex the value of the vertex to add
template <typename T>
void Graph<T>::addVertex(T vertex){
    if(_adjList.find(vertex) == _adjList.end()){
        _adjList[vertex] = std::set<T>();
        _vertices[vertex] = GraphNode<T>(vertex);
    }
}

/// @brief add an edge to the graph
/// @param from the value of the vertex to add the edge from
/// @param to the value of the vertex to add the edge to
template <typename T>
void Graph<T>::addEdge(T from, T to){
    addVertex(from);
    addVertex(to);
    (_adjList[from]).insert(to);
    //edge goes both ways?!
    //(_adjList[to]).insert(from);
}

/// @brief check if an edge exists in the graph
/// @param from the value of the vertex to check the edge from
/// @param to the value of the vertex to check the edge to
template <typename T>
bool Graph<T>::hasEdge(T from, T to) const{
    auto iterator = _adjList.find(from);
    //makes sure "from" exists in adjlist, then finds if "to" is in the set
    return (iterator != _adjList.end() && iterator->second.find(to) != iterator->second.end());
}

/// @brief get the neighbors of a vertex
/// @param vertex the value of the vertex to get the neighbors of
/// @return a set of the neighbors of the vertex if vertex is in the graph, otherwise std::nullopt
template <typename T>
std::optional<std::set<T>> Graph<T>::getNeighbors(T vertex) const{
    auto iterator = _adjList.find(vertex);
    if(iterator != _adjList.end()){
        return iterator->second;
    }
    return std::nullopt;
}

// ----------------- BFS -----------------

/// @brief BFS traversal of the graph
/// @param start the value of the vertex to start the traversal from
/// @return a vector of vertices in the order of BFS traversal
template <typename T>
std::vector<T> Graph<T>::BFS(T start){
    // std::vector<T> new_vector;
    // std::unordered_set<T> visited_nodes;
    // std::queue<T> new_queue;
    // new_queue.push(start);
    // visited_nodes.insert(start);
    // while(!new_queue.empty()){
    //     T current_node = new_queue.front();
    //     new_queue.pop();
    //     new_vector.push_back(current_node);
    //     for(const T &neighbor_vertex : _adjList[current_node]){
    //         if(visited_nodes.find(neighbor_vertex) == visited_nodes.end()){
    //             new_queue.push(neighbor_vertex);
    //             visited_nodes.insert(neighbor_vertex);
    //         }
    //     }
    // }
    // return new_vector;

    //edge case
    if(_vertices.empty()){
        return {};
    }

    for(auto &vertex : _vertices){
        vertex.second.color = White;
        vertex.second.distance = std::numeric_limits<int>::max(); //infinity!
        vertex.second.predecessor = std::nullopt;
    }
    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    _vertices[start].predecessor = std::nullopt;
    std::queue<T> Q;
    std::vector<T> new_vector;
    Q.push(start);
    while(!Q.empty()){
        T u = Q.front();
        Q.pop();
        new_vector.push_back(u);
        for(const auto &v : _adjList[u]){
            if(_vertices[v].color == White){
                _vertices[v].color = Gray;
                _vertices[v].distance = _vertices[u].distance + 1;
                _vertices[v].predecessor = u;
                Q.push(v);
            }
        }
        _vertices[u].color = Black;
    }
    // std::vector<T> new_vector;
    // for(const auto &vertex : _vertices){
    //     new_vector.push_back(vertex.first);
    //     // T visited_vertex = Q.front();
    //     // Q.pop();
    //     // new_vector.push_back(visited_vertex);
    // }
    return new_vector;
}

/// @brief find the length of the shortest path between two vertices
/// @param start the starting vertex of the shortest path
/// @param end the ending vertex of the shortest path
/// @return the length of the shortest path between the two vertices
template <typename T>
int Graph<T>::shortestPath(T start, T end){
    //ONLY FOR UNWEIGHTED

    //edge case
    if(start == end){
        return 0;
    }

    for(auto &vertex : _vertices){
        vertex.second.color = White;
        vertex.second.distance = std::numeric_limits<int>::max(); //infinity!
        vertex.second.predecessor = std::nullopt;
    }
    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    _vertices[start].predecessor = std::nullopt;
    std::queue<T> Q;
    Q.push(start);
    while(!Q.empty()){
        T u = Q.front();
        Q.pop();
        for(const auto &v : _adjList[u]){
            if(_vertices[v].color == White){
                _vertices[v].color = Gray;
                _vertices[v].distance = _vertices[u].distance + 1;
                _vertices[v].predecessor = u;
                Q.push(v);
                if(v == end){
                    //edge case for if there's a direct edge that didn't get caught due to cycle
                    if(_adjList[start].find(end) != _adjList[start].end()){
                        return 1;
                    } else{
                        return _vertices[v].distance;
                    }
                }
            }
        }
        _vertices[u].color = Black;
    }
    return -1;
}

// ----------------- DFS -----------------

/// @brief helper function for DFS
/// @param u the vertex to visit
/// @param time the current time count
/// @param record a list of vertices in the order of topological sort
template <typename T>
void Graph<T>::DFS_visit(const T &u, int &time, std::list<T> &record){
    time += 1;
    _vertices[u].discovery_time = time;
    _vertices[u].color = Gray;
    for(const T &v : _adjList[u]){
        if(_vertices[v].color == White){
            _vertices[v].predecessor = u;
            DFS_visit(v, time, record);
        }
    }
    time += 1;
    _vertices[u].finish_time = time;
    _vertices[u].color = Black;
    record.push_front(u);
}

/// @brief DFS traversal of the graph
/// @return a list of vertices in the order of topological sort
template <typename T>
std::list<T> Graph<T>::DFS(){
    for (auto& vertex : _vertices){
        vertex.second.color = White;
        vertex.second.predecessor = std::nullopt;
    }
    int time = 0;
    std::list<T> record;
    for(auto &vertex : _vertices){
        if(vertex.second.color == White){
            DFS_visit(vertex.first, time, record);
        }
    }
    //sort?
    return record;
}

#endif // GRAPH_CPP
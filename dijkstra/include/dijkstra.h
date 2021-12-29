#pragma once

# include "../../graph/include/graph_header.h"
# include "../../parsing/include/parser_header.h"
# include "../../traversals/include/BFS.h"

# include <vector>
# include <string>
# include <algorithm>
# include <map>
# include <limits>

class Dijkstra {
    public:

        Dijkstra(); 

        Dijkstra(Graph _graph);

        std::vector<Edge> shortestPath(Airport * _source, Airport * _destination);

        Graph getGraph();

    private:
        Graph graph;
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, float> dist;
        std::unordered_map<int, int> prev;
}; 
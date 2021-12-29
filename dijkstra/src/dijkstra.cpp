# include "dijkstra.h"
# include <algorithm>
# include <queue>
# include <utility>

/**
 * The empty constructor
 */
Dijkstra::Dijkstra() {

}

/**
 * Initializes a Dijkstra object on a given graph
 * @param _graph The graph that Dijkstras will work on
 */

Dijkstra::Dijkstra(Graph _graph) { //source and destination are airport ids
    const int infinity = 0x3f3f3f3f;
    graph = _graph; //graph should be initialized with airports and routes (verticies and edges)
    unordered_map<int, Airport> allAirports = graph.getAirports(); //initialize airport map
    for (unsigned x = 0; x < allAirports.size(); x++) { //initialize distance map
        dist[allAirports[x].getID()] = infinity;
    }
    for (unsigned x = 0; x < allAirports.size(); x++) { //initialize visited map
        visited[allAirports[x].getID()] = false;
    }
    std::unordered_map<int, int> prev; // initialize previous map
}

/**
 * Runs the shortest path algorithm on a graph between two airports
 * @param source The starting airport pointer
 * @param destination The ending airport pointer
 */

std::vector<Edge> Dijkstra::shortestPath(Airport * source, Airport * destination) {
    if (source == NULL || destination == NULL) { // Makes sure valid airports are passed in
        throw std::invalid_argument("invalid source or destination");
    }
   if (graph.getAdjacent(*source).empty()) { // If no adjacent airports to source, return empty vector
       return std::vector<Edge>();
   }
    dist[source->getID()] = 0; // starting airport has a distance of 0
    std::priority_queue<std::pair<int, float>, std::vector<std::pair<int, float>>, std::greater<std::pair<int, float>>> priorityqueue; // initialize min heap priority queue
    priorityqueue.push(make_pair(source->getID(), 0)); // push a pair of ID and Distances to queue
    while (priorityqueue.top().first != destination->getID() && !(priorityqueue.empty())) {
        int currentAirID = priorityqueue.top().first;
        Airport currentAirport = graph.getAirports().at(currentAirID); //convert id to airport
        priorityqueue.pop();
        
        std::vector<int> adjacentAirports = graph.getAdjacent(currentAirport); //get adjacent airports from current airport
        for (unsigned i = 0; i < adjacentAirports.size(); i++) {
            if (visited[adjacentAirports[i]] == false) { // if airport hasnt already been visited
                int adjacent_Airport = adjacentAirports[i];
                Airport full_adj_air = graph.getAirport(adjacent_Airport); //convert id to airport
                int edge_Weight = graph.incidentEdges(currentAirport).at(adjacent_Airport).getWeight(); //get edge weight between two airports
                //compare distance values to determine if an adjacent airport gets you closer to the destination airport
                if (dist[adjacent_Airport] > dist[currentAirport.getID()] + edge_Weight) {
                    dist[adjacent_Airport] = dist[currentAirport.getID()] + edge_Weight;
                    prev[adjacent_Airport] = currentAirport.getID(); //add the current airport to the previous airport map
                    priorityqueue.push(make_pair(adjacent_Airport, dist[adjacent_Airport]));
                }
            }
        }
        visited[currentAirport.getID()] = true; //mark that airport as visited
    }
    std::vector<Edge> solution_path;
    if (prev.find(destination->getID()) == prev.end()) { //if no destination exists in previous map, return an empty vector
        return std::vector<Edge>();
    } 
    
    int weight = 0;
    for (int x = destination->getID(); x != source->getID(); x = prev[x]) { //construct solution path from previous map
        Airport full_prev_air = graph.getAirport(prev[x]);
        weight = graph.incidentEdges(full_prev_air).at(x).getWeight();
        std::vector<Edge>::iterator iter = solution_path.begin();
        iter = solution_path.insert(iter, Edge(prev[x], x, weight, std::to_string(prev[x]) + " to " + std::to_string(x)));
    }
    prev.clear(); //empty previous map for next shortest path call
    return solution_path; //returns solution vector of edges
}

/**
 * Gets the graph that Dijkstra is operating on
 */

Graph Dijkstra::getGraph() {
    return graph;
}
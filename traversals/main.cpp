#include <iostream>
#include "../include/BFS.h"
#include "../include/parser_header.h"
#include "../include/graph_header.h"

int main() {

    CSVReader reader("data/airports.dat", "data/routes.dat");
    reader.parse();
    
    // Building Graph:
    std::vector<Airport*> airports = reader.GetAirportList();
    std::vector<Route*> routes = reader.GetRoutes();
    Graph g = Graph(airports, routes);

    // BFS Traversal:
    BFS bfs = BFS(g, 1);

    // Write Traversal to file
    std::cout << "Writing BFS Traversal to file: bfs_output_main.txt" << std::endl;
    Traversal::BFSTraversalToFile("bfs_output_main.txt", g, 1);

    return 0;
}
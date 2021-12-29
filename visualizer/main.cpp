#include <iostream>
#include "../include/visualizer_header.h"

int main() {
    // Parsing data:
    CSVReader reader("data/airports.dat", "data/routes.dat");
    reader.parse();
    
    // Building Graph:
    std::vector<Airport*> airports = reader.GetAirportList();
    std::vector<Route*> routes = reader.GetRoutes();
    Graph g = Graph(airports, routes);

    Visualizer v(g);
    v.drawShortestPath(airports[4], airports[627], "main");
        
    std::cout << "Attempting to write output image to visualmain.png" <<  std::endl;

    return 0;
}
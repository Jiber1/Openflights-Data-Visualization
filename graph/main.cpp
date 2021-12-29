#include "graph_header.h"
#include "../parsing/include/parser_header.h"

#include <string>
#include <vector>
#include <iostream>
#include "../include/graph_header.h"
#include "include/parser_header.h"


int main() {
  
    std::string airports_file = "../data/airports.dat";
    std::string routes_file = "../data/routes.dat";
    
    CSVReader reader(airports_file, routes_file);
    reader.parse();

    std::vector<Airport*> airportlist = reader.GetAirportList();
    std::vector<Route*> routeslist = reader.GetRoutes();

    Graph g(airportlist, routeslist);

    Airport airport = g.getAirport(3830);
    const unordered_map<int, Edge>& map = g.incidentEdges(airport);
    
    Edge route = map.at(4042);

    std::cout << "Source of the route: " << g.origin(route).getName() << std::endl;
    std::cout << "Destination of the route: " << g.destination(route).getName() << std::endl;

    return 0;
}

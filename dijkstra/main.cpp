#include "include/dijkstra.h"

#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string airports_file = "../data/airports.dat";
    std::string routes_file = "../data/routes.dat";

    CSVReader reader(airports_file, routes_file);
    reader.parse();

    std::vector<Airport*> airportlist = reader.GetAirportList();
    std::vector<Route*> routeslist = reader.GetRoutes();

    Graph g(airportlist, routeslist);

    Airport airport = g.getAirport(3830);

    Dijkstra d(g);
    std::vector<Edge> shortestPath = d.shortestPath(airportlist[2], airportlist[32]);

    std::cout << "Distance of short path from airpotr 2 to 32: " << shortestPath.size() << std::endl;
}
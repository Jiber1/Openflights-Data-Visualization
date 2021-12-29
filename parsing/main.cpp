#include "include/parser_header.h"

#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string airports_file = "../data/airports.csv";
    std::string routes_file = "../data/routes.csv";

    CSVReader reader(airports_file, routes_file);
    reader.parse();

    std::vector<Airport*> airportlist = reader.GetAirportList();
    std::vector<Route*> routeslist = reader.GetRoutes();

    std::cout << airportlist.size() << " airports parsed" << std::endl;
    std::cout << routeslist.size() << " routes parsed" << std::endl; 

    return 0;
}
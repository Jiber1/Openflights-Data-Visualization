#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "airport.h"
#include "route.h"

class CSVReader {
    public:
        CSVReader();
        CSVReader(const std::string& _airports_file, const std::string& _routes_file);

        //rule of three
        CSVReader(const CSVReader& other);
        CSVReader& operator=(const CSVReader& other);
        ~CSVReader();

        void parse(); //call both private helps here
        int getSize();
        std::vector<Airport*> GetAirportList();
        std::vector<Route*> GetRoutes();
        // Airport find(std::string code);

    private:
        std::string airports_file;
        std::string routes_file;
        std::vector<Airport*> airportList;
        int size;
        std::vector<Route*> routeList;

        std::vector<Airport*> parseAirports(const std::string& _airport_file);
        std::vector<Route*> parseRoutes(const std::string& _route_file);
        
};
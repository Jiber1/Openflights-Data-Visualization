#include "../include/parser.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

/**
 * Defualt CSVReader constructor
 */
CSVReader::CSVReader() {
    size = 0;
}

/**
 * CSVReader constructor
 * @param _airports_file Path to airport data file
 * @param _routes_file Path to routes data file
 */
CSVReader::CSVReader(const std::string& _airports_file, const std::string& _routes_file) {
    airports_file = _airports_file;
    routes_file = _routes_file;
}

/**
 * CSVReader copy constructor
 * @param other The CSVReader to copy from
 */
CSVReader::CSVReader(const CSVReader& other) {
    *this = other;
}

/**
 * CSVReader assignment operator
 * @param other The CSVReader to copy from
 */
CSVReader& CSVReader::operator=(const CSVReader& other) {
    if (this != &other) {
        delete this;
        // Build airportList from other
        for (Airport * airport : other.airportList) {
            airportList.push_back(new Airport(*airport));
        }
        // Build routeList from other
        for (Route * route : other.routeList) {
            routeList.push_back(new Route(*route));
        }
        airports_file = other.airports_file;
        routes_file = other.routes_file;
    }
    return *this;
}

/**
 * CSVReader destructor
 */
CSVReader::~CSVReader() {
    for (Airport * airport : airportList) {
        delete airport;
    }
    airportList.clear();
    for (Route * route : routeList) {
        delete route;
    }
    routeList.clear();
}

/**
 * Parse both the Airport and Route files into airportList and routeList
 */
void CSVReader::parse() {
    airportList = parseAirports(airports_file);
    routeList = parseRoutes(routes_file);
}

int CSVReader::getSize() {
    return size;
}
std::vector<Airport*> CSVReader::GetAirportList() {
    return airportList;
}

std::vector<Route*> CSVReader::GetRoutes() {
    return routeList;
}

/**
 * Parse each line of the specified path into Airport objects, then return the list of these Airports.
 * @param _airport_file The path to the airport data file.
 */
std::vector<Airport*> CSVReader::parseAirports(const std::string& _airport_file) {
    std::fstream file;
    std::string delimiter = ",";
    std::vector<Airport*> elements;
    bool line1 = true;
    
    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

    
    if (_airport_file.empty()) {
        std::cout << "no file detected (airports)" << std::endl;
        return std::vector<Airport*>();
    } 

    file.open(_airport_file, std::ios::in);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // Skip over first line
            if (line1 == true) {
                line1 = false;
                continue;
            }

            // Remove all quote characters from the line before parsing. 
            // https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());

            std::vector<std::string> data;
            std::string token;
            int position = 0;
            while ((position = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, position);
                data.push_back(token);
                line.erase(0, position + delimiter.length());
            }
            data.push_back(line);

            if (line.empty() == false) {
                Airport* airport = new Airport(data[1],std::stoi(data[0],nullptr,10),data[4],data[5],std::stof(data[6]),std::stof(data[7]),std::stof(data[8]));
                elements.push_back(airport);
            } else {
                /* Do Nothing. Line is empty. */
            }
        }
    } else {
        std::cout << "Cant open file" << std::endl;
        return std::vector<Airport*>();
    }
    return elements;
}

/**
 * Parse each line of the specified path into Route objects, then return the list of these Routes.
 * @param _route_file The path to the route data file.
 */
std::vector<Route*> CSVReader::parseRoutes(const std::string& _route_file) {
    std::fstream file;
    std::string delimiter = ",";
    std::vector<Route*> elements;
    bool line1 = true;
    
    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    
    if (_route_file.empty()) {
        std::cout << "no file detected (routes)" << std::endl;
        return std::vector<Route*>();
    } 

    file.open(_route_file, std::ios::in);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // Skip over first line
            if (line1 == true) {
                line1 = false;
                continue;
            }

            // Remove all quote characters from the line before parsing. 
            // https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());

            std::vector<std::string> data;
            std::string token;
            int position = 0;
            while ((position = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, position);
                data.push_back(token);
                line.erase(0, position + delimiter.length());
            }
            data.push_back(line);

            if (line.empty() == false) {
                Route* route = new Route(data[0],data[1],data[2],std::stof(data[3]),data[4],std::stof(data[5]),std::stof(data[7]));
                
                elements.push_back(route);
            } else {
                /* Do Nothing. Line is empty. */
            }
        }
    } else {
        std::cout << "Cant open file" << std::endl;
        return std::vector<Route*>();
    }
    return elements;
}
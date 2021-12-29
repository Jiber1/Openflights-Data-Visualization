#include "catch2/catch.hpp"
#include "../include/graph_header.h"
#include "../../parsing/include/parser_header.h"

#include <algorithm>

TEST_CASE("Testing graph") {
    SECTION("Test getAirport function") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        Airport airport = graph.getAirport(3830);

        REQUIRE(airport.getID() == 3830);
    }
    
    SECTION("Test incident edges count") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        Airport ohare = graph.getAirport(3830);
        Airport fw = graph.getAirport(4041);
        unordered_map<int, Edge> ohare_outbounds = graph.incidentEdges(ohare);
        unordered_map<int, Edge> fw_outbounds = graph.incidentEdges(fw);

        REQUIRE(ohare_outbounds.size() == 8);
        REQUIRE(fw_outbounds.size() == 1);
    }

    SECTION("Test getAdjacent") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);
        
        vector<int> adjacent = graph.getAdjacent(graph.getAirport(3830));

        bool exists1 = std::find(adjacent.begin(), adjacent.end(), 4041) != adjacent.end();
        bool exists2 = std::find(adjacent.begin(), adjacent.end(), 4009) != adjacent.end();
        bool exists3 = std::find(adjacent.begin(), adjacent.end(), 3653) != adjacent.end();
        bool exists4 = std::find(adjacent.begin(), adjacent.end(), 3685) != adjacent.end();

        REQUIRE(adjacent.size() == 8);
        REQUIRE((exists1 && exists2 && exists3 && exists4));
    }

    SECTION("Test origin function") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        Airport source = graph.getAirport(3830);
        unordered_map<int, Edge> source_outbounds = graph.incidentEdges(source);

        REQUIRE(graph.origin(source_outbounds[2170]).getID() == source.getID());
    }

    SECTION("Test destination function") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        Airport source = graph.getAirport(3830);
        Airport destination = graph.getAirport(2170);
        unordered_map<int, Edge> source_outbounds = graph.incidentEdges(source);

        REQUIRE(graph.destination(source_outbounds[2170]).getID() == destination.getID());
    }

    SECTION("Test airport count") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        REQUIRE(graph.getAirports().size() == 9);
    }

    SECTION("Test route count") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
        reader.parse();
        
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();

        Graph graph(airports, routes);

        int routeCounts = 0;

        for (auto iter = graph.getEdges().begin(); iter != graph.getEdges().end(); ++iter) {
            routeCounts += iter->second.size();
        }

        REQUIRE(routeCounts == 16);
    }
}

#include "catch2/catch.hpp"
#include "../include/dijkstra.h"
#include "../include/parser_header.h"
#include "../include/graph_header.h"
#include "../include/BFS.h"
#include "../include/visualizer_header.h"
#include <vector>


TEST_CASE("Visualizer Test") {
    SECTION("Sanity Check") {
        REQUIRE(true);
    }
}

TEST_CASE("Visualizer is constructed properly") {
    CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_route.dat");
    reader.parse();
    std::vector<Airport*> resultairport = reader.GetAirportList();
    std::vector<Route*> resultroute = reader.GetRoutes();

    Graph g(resultairport, resultroute);

    SECTION("Visualizer constructor sets airports at proper pixels") {
        Visualizer v(g);

        std::unordered_map<std::string, std::pair<int, int>> loc_map = v.getLocationMap();
        
        //960 x 960
        REQUIRE(loc_map["Goroka Airport"].first == 1337);
        REQUIRE(loc_map["Goroka Airport"].second == 765);
    }

    SECTION("Visualizer constructor draws airports") {
        Visualizer v(g);

        cs225::PNG out;
        out.readFromFile("images/Webp.net-resizeimage_6.png");
        v.drawAirports(out);
        out.writeToFile("airport_1.png");
        std::cout << "Attempting to write output image to tests/airport_1.png" <<  std::endl;
    }

}

TEST_CASE("Drawing Visualization") {
    CSVReader reader("tests/test_data/test_airport_c_dc.dat", "tests/test_data/test_routes_connected.dat");
    reader.parse();
    std::vector<Airport*> resultairport = reader.GetAirportList();
    std::vector<Route*> resultroute = reader.GetRoutes();

    Graph g(resultairport, resultroute);

    SECTION("Visualizer draws routes correctly") {
        Visualizer v(g);

        cs225::PNG out;
        out.readFromFile("images/Webp.net-resizeimage_6.png");
        v.drawRoute("Wewak International Airport", "Narsarsuaq Airport", out);
        out.writeToFile("route_1.png");
        std::cout << "Attempting to write output image to tests/route_1.png" <<  std::endl;
    }

    SECTION("Visualizer draws shortest path") {
        Visualizer v(g);
        v.drawShortestPath(resultairport[0], resultairport[8], "smallset");
        
        std::cout << "Attempting to write output image to tests/visualsmallset.png" <<  std::endl;
    }


}

TEST_CASE("Drawing Visualization on whole dataset") {
    CSVReader reader("../data/airports.dat", "../data/routes.dat");
    reader.parse();
    std::vector<Airport*> airports = reader.GetAirportList();
    std::vector<Route*> routes = reader.GetRoutes();
    Graph g = Graph(airports, routes);

    Visualizer v(g);
    v.drawShortestPath(airports[4], airports[627], "fullset");
        
    std::cout << "Attempting to write output image to tests/visualfullset.png" <<  std::endl;

}

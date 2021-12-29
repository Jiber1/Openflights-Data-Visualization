#include "catch2/catch.hpp"
#include "../include/dijkstra.h"
#include "../include/parser_header.h"
#include "../include/graph_header.h"
#include "../include/BFS.h"
#include <vector>


TEST_CASE("Dijkstra works on a small dataset (3 airports, 2 routes)") {
        CSVReader reader("tests/test_data/test_larger_airport.dat", "tests/test_data/test_larger_route.dat");
        reader.parse();
        std::vector<Airport*> resultairport = reader.GetAirportList();
        std::vector<Route*> resultroute = reader.GetRoutes();

        Graph g(resultairport, resultroute);

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(resultairport[0], resultairport[2]);

        REQUIRE(edgeList.size() == 1);
        REQUIRE(edgeList[0].getDestinationID() == resultairport[2]->getID());
    
}


/**
 *      Connected Graph:
 * 
 * [(1)]-(2)--(3)  (4)--(5)
 *   |\    \       /     |
 *   |  \    \   /       |
 *  (6)  (7)  (8)--(9)--(10) <- Destination
 */


TEST_CASE("Dijkstra works on connected dataset (cycle) (10 airports, 10 routes)") {
    CSVReader reader("tests/test_data/test_airport_c_dc.dat", "tests/test_data/test_routes_connected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        // std::cout << g.getAirport(airports[0]->getID()).getID() << endl;
        // std::cout << g.getAirport(airports[8]->getID()).getID() << endl;

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(airports[0], airports[9]);      

        REQUIRE(edgeList.size() == 4);  
}


/**
 *      Disconnected Graph:
 *                 Start
 *  (1)--(2)--(3)  [(4)]--(5)
 *   |\            /       |
 *   |  \        /         |
 *  (6)  (7)   (8)--(9)--(10)<-Destination
 */


TEST_CASE("Dijkstra works on disconnected dataset (10 airports, 9 routes)") {
    CSVReader reader("tests/test_data/test_airport_c_dc.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        // std::cout << g.getAirport(airports[3]->getID()).getID() << endl;
        // std::cout << g.getAirport(airports[9]->getID()).getID() << endl;

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(airports[3], airports[9]);      

        REQUIRE(edgeList.size() == 2);  
        REQUIRE(edgeList[1].getDestinationID() == airports[9]->getID());  
}


/**
 *      Acyclic Graph:
 *               Start
 *  (1)-(2)--(3) [(4)]--(5)
 *   |\    \             |
 *   |  \    \           |
 *  (6)  (7)  (8)--(9)--(10)
 *        ^
 *   Destination
 */      


TEST_CASE("Dijkstra works on a tree-like acyclic graph (10 airports, 9 routes)") {
    CSVReader reader("tests/test_data/test_airport_c_dc.dat", "tests/test_data/test_routes_tree.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        //std::cout << g.getAirport(airports[0]->getID()).getID() << endl;
        //std::cout << g.getAirport(airports[8]->getID()).getID() << endl;

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(airports[3], airports[6]);      

        REQUIRE(edgeList.size() == 7);  
}



TEST_CASE("Dijkstra works on a non-existant path (3 airports, 1 route)") {
    CSVReader reader("tests/test_data/test_larger_airport.dat", "tests/test_data/test_non_route.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        //std::cout << g.getAirport(airports[3]->getID()).getID() << endl;
        //std::cout << g.getAirport(airports[9]->getID()).getID() << endl;

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(airports[0], airports[2]);      

        REQUIRE(edgeList.size() == 0);  
}

TEST_CASE("Dijkstra works on entire dataset") {
    CSVReader reader("../data/airports.dat", "../data/routes.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        //std::cout << g.getAirport(airports[0]->getID()).getID() << endl;
        //std::cout << g.getAirport(airports[626]->getID()).getID() << endl;

        Dijkstra d(g);
        std::vector<Edge> edgeList = d.shortestPath(airports[0], airports[4292]);    
        //std::cout << edgeList[1].getSourceID() << endl;  

        REQUIRE(edgeList.size() == 9);  
        REQUIRE(edgeList[1].getSourceID() == airports[4]->getID());
        REQUIRE(edgeList[8].getSourceID() == airports[626]->getID()); 
}
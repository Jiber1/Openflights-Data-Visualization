#include "catch2/catch.hpp"
#include "../include/parser_header.h"
#include "graph_header.h"
#include "BFS.h"


/**
 *      Connected Graph:
 * 
 * [(1)]-(2)--(3)  (4)--(5)
 *   |\    \       /     |
 *   |  \    \   /       |
 *  (6)  (7)  (8)--(9)--(10)
 */


TEST_CASE("BFS Connected Traversal Test") {
    SECTION("BFS first element is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_connected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        REQUIRE(bfs.pop() == 1);
    }
    SECTION("BFS has right number of elements") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_connected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        Traversal::Iterator it = bfs.begin();

        int count = 0;
        while (it != bfs.end()) {
            ++it;
            count++;
        }
        REQUIRE(count == 10);
    }
    SECTION("BFS order is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_connected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        Traversal::Iterator it = bfs.begin();
        std::vector<int> expected = {1, 2, 6, 7, 3, 8, 4, 9, 5, 10};

        int count = 0;
        while (it != bfs.end()) {
            int curr = *it;
            REQUIRE(curr == expected[count]);
            ++it;
            count++;
        }
    }

    SECTION("Output to file") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_connected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        Traversal::BFSTraversalToFile("bfsOutput.txt", g, 1);
    }
}

/**
 *      Test 1 Graph:
 * 
 * [(1)]-(2)--(3)  (4)--(5)
 *   |\            /     |
 *   |  \        /       |
 *  (6)  (7)  (8)--(9)--(10)
 */

TEST_CASE("BFS Disconnected Traversal Test 1") {
    SECTION("BFS first element is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        REQUIRE(bfs.pop() == 1);
    }
    SECTION("BFS has right number of elements") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        Traversal::Iterator it = bfs.begin();

        int count = 0;
        while (it != bfs.end()) {
            ++it;
            count++;
        }
        REQUIRE(count == 5);
    }
    SECTION("BFS order is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 1);
        Traversal::Iterator it = bfs.begin();
        std::vector<int> expected = {1, 2, 6, 7, 3};

        int count = 0;
        while (it != bfs.end()) {
            int curr = *it;
            REQUIRE(curr == expected[count]);
            ++it;
            count++;
        }
    }
}

/**
 *      Test 2 Graph:
 * 
 *  (1)--(2)--(3)  (4)--(5)
 *   |\            /     |
 *   |  \        /       |
 *  (6)  (7) [(8)]-(9)--(10)
 */

TEST_CASE("BFS Disconnected Traversal Test 2") {
    SECTION("BFS first element is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 8);
        REQUIRE(bfs.pop() == 8);
    }
    SECTION("BFS has right number of elements") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 8);
        Traversal::Iterator it = bfs.begin();

        int count = 0;
        while (it != bfs.end()) {
            ++it;
            count++;
        }
        REQUIRE(count == 5);
    }
    SECTION("BFS order is correct") {
        CSVReader reader("tests/test_data/test_airport.dat", "tests/test_data/test_routes_disconnected.dat");
        reader.parse();
        std::vector<Airport*> airports = reader.GetAirportList();
        std::vector<Route*> routes = reader.GetRoutes();
        Graph g = Graph(airports, routes);

        BFS bfs = BFS(g, 8);
        Traversal::Iterator it = bfs.begin();
        std::vector<int> expected = {8, 4, 9, 5, 10};

        int count = 0;
        while (it != bfs.end()) {
            int curr = *it;
            REQUIRE(curr == expected[count]);
            ++it;
            count++;
        }
    }
}
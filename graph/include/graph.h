#pragma once

#include "../../parsing/include/airport.h"
#include "../../parsing/include/route.h"
#include "utilities.h"
#include "edge.h"

#include <vector>
#include <unordered_map>

using namespace std;


class Graph {
    public:
        /**
         * Default constructor
         */
        Graph();

        /**
         * Creates a graph from two files, one with airport data, one with route data
         */
        Graph(const vector<Airport*>& airports, const vector<Route*>& routes);

        /**
         * Create a vertex for the graph given an airport pointer
         */
        void insertVertex(Airport* airport);

        /**
         * Creates an edge between two airports
         */
        void insertEdge(Airport* airport1, Airport* airport2, const Edge& edge);

        /**
         * Remove a vertex from the graph, hangles edges
         */
        void removeVertex(Airport* airport);

        /**
         * Removes an edge between two airports
         */
        void removeEdge(Airport* airport1, Airport* airport2);

        /**
         * Returns a map containing all edges incident on an airport
         */
        const unordered_map<int, Edge>& incidentEdges(const Airport & airport) const;

        /**
         * Tests if two airports are adjacent
         */
        bool areAdjacent(Airport* airport1, Airport* airport2) const;

        /**
         * Returns the starting point of the edge
         */
        const Airport& origin(const Edge& edge) const;

        /**
         * Returns the ending point of the edge
         */
        const Airport& destination(const Edge& edge) const;

        /**
         * Returns a list of airport IDs adjacent to the parameter airport
         */
        vector<int> getAdjacent(const Airport& source) const;

        /**
         * Returns an aiport given an ID
         */
        const Airport& getAirport(int id) const;

        /**
         * Getter for airport data
         */
        const unordered_map<int, Airport>& getAirports() const;

        /**
         * Getter for edge data
         */
        const unordered_map<int, unordered_map<int, Edge>>& getEdges() const;

    private:
        /**
         * Maps airport ID to airport object
         */
        unordered_map<int, Airport> airports_;

        /**
         * Maps airport ID to a mapping of a destinationID to edge
         */
        unordered_map<int, unordered_map<int, Edge>> edges_;

};
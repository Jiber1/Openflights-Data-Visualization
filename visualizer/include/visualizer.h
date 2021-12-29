#pragma once

# include "../../graph/include/graph_header.h"
# include "../../parsing/include/parser_header.h"
# include "../../traversals/include/BFS.h"
# include "../../dijkstra/include/dijkstra.h"
# include "../include/PNG.h"
# include "../include/HSLAPixel.h"

# include <vector>
# include <string>
# include <algorithm>
# include <map>
# include <limits>

class Visualizer {

    public:

        Visualizer(Graph g);

        void drawShortestPath(Airport * source, Airport * dest, std::string outfile);

        void drawAirports(cs225::PNG& image);

        void drawRoute(std::string source, std::string dest, cs225::PNG& image);

        void airportMapper(std::unordered_map<int, std::unordered_map<int, Edge>> routes);

        void addAirport(std::string airport, std::pair<float,float> location);

        std::unordered_map<std::string, std::pair<int, int>> getLocationMap();

        private:

        const cs225::HSLAPixel ROUTE_COLOR = cs225::HSLAPixel(12, 1, 0.5, 1);
        const cs225::HSLAPixel AIRPORT_COLOR = cs225::HSLAPixel(12, 1, 0, 1);
        const cs225::HSLAPixel AIRPORT_BORDER_COLOR = cs225::HSLAPixel(12, 1, 0, 1);

        Graph graph;

        cs225::PNG backgroundImage;

        std::unordered_map<std::string, std::pair<int, int>> location_map = std::unordered_map<std::string, std::pair<int, int>>();
};
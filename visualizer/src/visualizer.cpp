#include "../include/visualizer.h"
#include "../include/PNG.h"
#include "../include/extras.h"

/**
 * Visualizer constructor from a provided Graph
 * @param g The graph to visualize
 */
Visualizer::Visualizer(Graph g) {
    graph = g;

    backgroundImage.readFromFile("images/Webp.net-resizeimage_6.png");

    location_map.clear();

    airportMapper(graph.getEdges());
}

/**
 * Create a PNG visualization of the shortest path between the provided airports
 * @param source The starting Airport object
 * @param dest The destination Airport object
 * @param outfile The path to store the output PNG.
 */
void Visualizer::drawShortestPath(Airport * source, Airport * dest, std::string outfile) {

    // Start with a PNG of the Mercator projection of the Earth
    cs225::PNG out(backgroundImage);

    // Run Dijkstra's Algorithm to find the shortest path from source to destination
    Dijkstra d(graph);
    std::vector<Edge> solution = d.shortestPath(source, dest);

    //Draw all airports and the routes within the shortest path.
    drawAirports(out);
    for (int x = 0; x < solution.size(); x++) {
        Airport sourceport = graph.getAirport(solution[x].getSourceID());
        Airport destinationport = graph.getAirport(solution[x].getDestinationID());
        drawRoute(sourceport.getName(), destinationport.getName(), out);
    }
    out.writeToFile("visual" + outfile + ".png");
}

/**
 * Helper function to draw all airports on the specified PNG.
 * @param image The PNG image to modify
 */
void Visualizer::drawAirports(cs225::PNG& image) {
    for (auto it = location_map.begin(); it != location_map.end(); it++) {
        std::pair<int, int> coordinates = it->second;

        if (coordinates.first < 0 || coordinates.first > image.width() || coordinates.second < 0 || coordinates.second > image.height()) { // OOB
            //std::cout << "Out of Bounds: (" << coordinates.first << ", " << coordinates.second << "), [" << image.width() << " x " << image.height() << "]" << std::endl;
            continue;
        }

        image.getPixel(coordinates.first, coordinates.second) = AIRPORT_COLOR;
        //plus symbol for airports
        if (coordinates.first > 0) { 
            image.getPixel(coordinates.first - 1, coordinates.second) = AIRPORT_BORDER_COLOR;
        }
        if (coordinates.second > 0) { 
            image.getPixel(coordinates.first, coordinates.second - 1) = AIRPORT_BORDER_COLOR;
        }
        if (coordinates.first < ((int) image.width() - 1)) { 
            image.getPixel(coordinates.first + 1, coordinates.second) = AIRPORT_BORDER_COLOR;
        }
        if (coordinates.second < ((int) image.height() - 1)) { 
            image.getPixel(coordinates.first, coordinates.second + 1) = AIRPORT_BORDER_COLOR;
        }
    }
}

/**
 * Helper function to draw the specified route on the specified PNG.
 * @param source The name of the source Airport object
 * @param dest The name of the destination Airport object
 * @param image The PNG image to modify
 */
void Visualizer::drawRoute(std::string source, std::string dest, cs225::PNG& image) {
    std::pair<int, int> source_point = location_map[source];
    std::pair<int, int> dest_point = location_map[dest];

    // # of steps is the max between delta_x and delta_y
    int d_x = dest_point.first - source_point.first;
    int d_y = dest_point.second - source_point.second;
    int steps = max(abs(d_x), abs(d_y));

    if (steps == 0) {
        return;
    }

    double x_increment = d_x / steps;
    double y_increment = (double)d_y / (double)steps;

    std::pair<double, double> curr = source_point;

    // Offset of +0.5 makes float -> int casts round to the nearest whole number
    curr.first += 0.5;
    curr.second += 0.5;
    
    for (size_t i = 0; i < steps; i++) {
        // Get nearest pixels
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (curr.first + i < 0 || curr.first + i > image.width() || curr.second + j < 0 || curr.second + j > image.height()) { // OOB
                    std::cout << "Out of Bounds: (" << curr.first + i << ", " << curr.second + j << "), [" << image.width() << " x " << image.height() << "]" << std::endl;
                    continue;
                }
                cs225::HSLAPixel & p = image.getPixel((int)curr.first + i, (int)curr.second + j);
                
                // Update pixel
                p = ROUTE_COLOR;
            }
        }

        // Update current position on line
        curr.first += x_increment;
        curr.second += y_increment;

    }
}

/**
 * Helper function to add an airport and its relevant data to the location map.
 * @param airport The Airport object to store in the map
 * @param location The latitude and longitude coordinates of the Airport as a pair of floats.
 */
void Visualizer::addAirport(std::string airport, std::pair<float,float> location) {
    if (location_map.find(airport) != location_map.end()) {
        return;
    }
    location_map[airport] = airportgrapher(location, backgroundImage.width(), backgroundImage.height());
}

/**
 * Gets source and destination Airports from all edges in the provided edge list and maps unique Airports with addAirport.
 * @param edgeList List of edges in the graph.
 */
void Visualizer::airportMapper(std::unordered_map<int, std::unordered_map<int, Edge>> edgelist) {

    for (const auto& outer_map : edgelist) {
        for (const auto& e : outer_map.second) {
            Edge edge = e.second;

            Airport sourceport = graph.getAirport(e.second.getSourceID());
            std::pair<float, float> source = std::make_pair(sourceport.getLatitude(), sourceport.getLongitude());
            Airport destinationport = graph.getAirport(e.second.getDestinationID());
            std::pair<float, float> destination = std::make_pair(destinationport.getLatitude(), destinationport.getLongitude());

            addAirport(sourceport.getName(), source);
            addAirport(destinationport.getName(), destination);
        }
    }
}

std::unordered_map<std::string, std::pair<int, int>> Visualizer::getLocationMap() {
    return location_map;
}


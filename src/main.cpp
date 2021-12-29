
# include "../graph/include/graph_header.h"
# include "../parsing/include/parser_header.h"
# include "../traversals/include/BFS.h"
# include "../dijkstra/include/dijkstra.h"
# include "../visualizer/include/visualizer_header.h"

# include <vector>
# include <string>
# include <algorithm>
# include <map>
# include <limits>
# include <fstream>
# include <stdlib.h>

// Input: 	./main.sh [airport file] [route file] [source ID] [destination ID]

int main(int argc, const char * argv[]) {
    
    if (argc != 5) {
		std::cout << "Invalid arguments: check that you're passing in:" << std::endl;
		std::cout << "Argument 1: airport dataset file location" << std::endl;
		std::cout << "Argument 2: routes dataset file location" << std::endl;
		std::cout << "Argument 3: airport source ID (start ID for BFS)" << std::endl;
		std::cout << "Argument 4: airport destination ID" << std::endl;
        std::cout << "\nExample: ./main.sh ../data/airports.dat ../data/routes.dat 636 1948" << std::endl;
		return -1;
	}

	std::cout << "\nYou have entered: airport file: " << argv[1] << ", route file: " << argv[2] 
    << ", airport source ID: " << argv[3] << ", and airport destination ID: " << argv[4] << std::endl;

	/* Creating the graph */
	std::cout << "Now creating graph" << std::endl;
	CSVReader reader(argv[1], argv[2]);
    reader.parse();

    std::vector<Airport*> resultairport = reader.GetAirportList();
    std::vector<Route*> resultroute = reader.GetRoutes();
    
    Graph g(resultairport, resultroute); 


	/* Running BFS */
	std::cout << "Running BFS" << std::endl;

	int airport_source_id = strtol(argv[3], NULL, 10);
	int airport_destination_id = strtol(argv[4], NULL, 10);
	
	Airport * airport_source;
	Airport * airport_destination;

	for (Airport * airport : resultairport) {
		if (airport->getID() == airport_source_id) {
			airport_source = airport;
		} 
		if (airport->getID() == airport_destination_id) {
			airport_destination = airport;
		}
	}

	if (std::find(resultairport.begin(), resultairport.end(), airport_source) == resultairport.end()) {
		std::cout << "invalid source airport id detected" << std::endl;
		return -1;
	}

	if (std::find(resultairport.begin(), resultairport.end(), airport_destination) == resultairport.end()) {
		std::cout << "invalid destination airport id detected" << std::endl;
		return -1;
	}

	BFS bfs = BFS(g, airport_source->getID());
    bfs.BFSTraversalToFile("BFS.txt", g, airport_source->getID());

    std::cout << "BFS complete!" << std::endl;

	/* Running Dijkstras */
	std::cout << "Running dijkstra's algorithm" << std::endl;
	Dijkstra d(g);

    std::vector<Edge> edgeList = d.shortestPath(airport_source, airport_destination);

	std::ofstream output("dijkstra.txt");
    for (auto edge : edgeList) {
        output << edge.getLabel() << endl;
    }

    std::cout << "Dijkstra's algorithm complete!" << std::endl;
	
    /* Creating Visualization */
	std::cout << "Creating Visualization" << std::endl;

	Visualizer v(g);

	v.drawShortestPath(airport_source, airport_destination, "");

	std::cout << "Visualization Complete! \n" << std::endl;

	/* Show result paths */
	std::cout << "\nSuccess!" << std::endl;
    std::cout << "\nYou can see the results of BFS at : /src/BFS.txt" << std::endl;
    std::cout << "\nYou can see the results of Dijkstra's algorithm at : /src/dijkstra.txt" << std::endl;    
    std::cout << "\nYou can see the results of the Visualization at : /src/visual.png\n" << std::endl;   

	return 0;

}
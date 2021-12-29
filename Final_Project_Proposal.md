Leading Question:

We want to project the flight paths of all flights across a world map, and determine which airport is most important using betweenness centrality, in which the airport with the most flights passing through it in their shortest path is the most important. You can input two destinations to see the shortest route by highlighting the route on the map. We could calculate exact distances between two airports (nodes) using geo coordinates. From this information, we could obtain other interesting data such as minimum distance around the world in flights, flights within a certain distance range, etc.
 
Dataset Acquisition and Processing:

We want to use the OpenFlight dataset (https://openflights.org/data.html), which maps flights up to 2014. We will download the file onto our repo to store and process. Since it is a csv file, we will split it by commas to get the data. We will handle empty spots in entries by ignoring them, considering them invalid, unless the data column is deemed unimportant to what we are trying to do. We will have a method/class that parses the data in.
 
Graph Algorithms:

We will implement a BFS traversal, Dijkstra’s Algorithm for the shortest path, and the betweenness centrality algorithm. Our nodes will be airports, our edges will be routes, and the weight will be determined by distance a route travels between nodes. Dijkstra’s algorithm will be implemented with a priority queue, requiring a BFS traversal, and it will use the distance between nodes (airports) as the weight. It will output the shortest path between two airports. Our betweenness centrality algorithm will take in the results from dijkstra’s algorithm between all routes and find the most important airports based on how many shortest paths go through that airport. We will aim for runtime of O(E + V log(V)), which lines up with the run time of a minimum priority queue implementation of dijkstra’s algorithm, since that algorithm will do the most work.
 
Timeline:

Data Acquisition: Nov 14th

Data Processing: Nov 14th

BFS Traversal: Nov 21th

Dijkstra’s Algorithm: Nov 29th

Betweenness Centrality: Dec 6th

(FINAL) Visualization with world map: Dec 13th

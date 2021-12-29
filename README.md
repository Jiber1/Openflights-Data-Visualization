# OpenFlights Data Visualization

##### Project Members: 

-Jimmy Berg\
-Gabriel Grais\
-Milosz Dabrowski

##### Project Description

Our project uses the OpenFlight dataset (https://openflights.org/data.html) to perform a BFS traversal and Dijkstra's shortest path algorithm. The user can enter two airports and custom data snippets to create a visualization of the different airports and the shortest path between them on a world map.



# Project Structure
We structured our project to make the most out of CMake; Each folder contains a include folder for header files, a src folder for cpp files, a test folder, main, and CMake files. below is a visualization of our structure:
```
project/
> parsing/
    > include/
        - ..header files
    > src/
        - ..src files
    - CMakeLists.txt
    - main.cpp
> graph/
    > ...
```


# Set up
The home project directory will be referred to as `project/`
To run the project, first run the following commands:

`$ cd project/`

`project$ chmod +x run.sh`

`project$ chmod +x bake.sh`

`project$ chmod +x test.sh`

`project$ chmod +x main.sh`

`project$ ./run.sh`

`./run.sh` is a combination of bake, which compiles the project, and tests, which will run the test suite and make sure everything is working properly.


# Useful Commands:

We wanted to use CMake in this project due to how helpful it is in Makefile generation; Makefiles can be created through the use of macros.

`project$ ./bake.sh` will bake (build & make) the project.

`project$ ./test.sh` will run the test suites for the project. All of the tests should pass.

`project$ ./main.sh [Airport Data File Location] [Route Data File Location] [Source Airport] [Destination Airport]` will run main and will generate 2 txt files that contain BFS and Dijkstra results in the src folder, and output an image PNG that contains the shortest path visualized on a world map.

`[Airport Data File Location]` The file location of the OpenFlights Airport dataset. Our airport data can be found at `../data/airports.dat`.
`[Route Data File Location]` The file location of the OpenFlights Route dataset. Our route data can be found at `../data/routes.dat`.
`[Source Airport]` The OpenFlights Airport ID for the source airport.
`[Destination Airport]` The OpenFlights Airport ID for the destination airport. 

For example: `./main.sh ../data/airports.dat ../data/routes.dat 636 1948`

##### Test Suite

To test **parsing**, we tested 3 classes: `CSVReader`, `Airport`, and `Route` class. For `CSVReader` we ensured that the size of the nodes vector was accurate after parsing a snippet of our data. We also tested each `Airport` in the results to make sure that they were parsed correctly and had all the necessary data. We then tested the parsed `Route`. We passed in a large dataset to make sure it got the correct number of routes, then we tested a random route and made sure it had the correct data. 

To test the **Dijkstra** algorithm, we tested the Dijkstra constructor and its shortestPath method, which runs priority queue solving algorithm. We checked that the algorithm gets the proper results for all kinds of graphs: connected, disconnnected, trees, etc, and made sure it returned an empty vector when there wasn't a valid path from the passed in data.

To test the **BFS** algorithm, we created a sample data set which could be split into two separate graphs, acyclic and cyclic. We checked that the BFS traversal starts at the specified airport, then we verified that the total number of Airports traversed matched the test set in each case. Finally, we tested that the order of traversal was correct for the entire sample set, as well as each of the connected components in the split data set. We also ensured that only Airports within the connected component were traversed. To deal with tie breaking, the BFS traversal object sorts the vector of adjacent nodes by ID to ensure that neighbors are traversed in the same order every time.

To test the **graph** constructor, we would create multiple graph objects from custom datasets, where each individual relevent function would be tested. The graph itself would be tested to make sure the right amount of airports and routes/edges exist, then the `incidentEdges()` and `getAdjacent()` were tested to make sure that the proper amount of neighboring airports and routes existed. Finally, the getters were tested to make sure all the data was correctly recieved.

To test the **visualizer** constructor, our testing was divided into two parts. The first part was making sure the airports were properly converted from latitude and longitude to x and y on a png file. We would verify where a certain airport would be using the mercator equation, and then made sure that the function airportgrapher put it at the proper pixel position on the image. The second part was making sure everything was drawn properly on the image. We first tested airport plotting, making sure the graph had the proper amount of ports at the right positions. Then, we tested the draw route method to make sure it drew in routes properly. Lastly, we ran the shortest path algorithm to make sure it works on the whole dataset. the results would be outputted to pngs inside of the visualizer folder.

# Acknowledgements

This is our final project for UIUC CS 225\
Our data is taken from OpenFlights\
Our world map is attributed to wikipedia: https://en.wikipedia.org/wiki/Mercator_projection , By Strebe - Own work, CC BY-SA 3.0, https://commons.wikimedia.org/w/index.php?curid=17700069

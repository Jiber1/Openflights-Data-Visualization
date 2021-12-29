#include "../include/graph.h"

// Needed for traversal default constructor
Graph::Graph() {
    airports_ = unordered_map<int, Airport>();
    edges_ = unordered_map<int, unordered_map<int, Edge>>();
}

Graph::Graph(const vector<Airport*>& airports, const vector<Route*>& routes) {
    for (size_t i = 0; i < airports.size(); i++) {
        airports_[airports[i]->getID()] = *airports[i];
    }

    // for every route, look at origin, then add that route to the origin list or edges
    for (Route* route : routes) {
        std::pair<float, float> airport1_coords(airports_[route->getSource()].getLatitude(),
                                                airports_[route->getSource()].getLongitude());
        std::pair<float, float> airport2_coords(airports_[route->getDestination()].getLatitude(),
                                                airports_[route->getDestination()].getLongitude());

        float weight = distance(airport1_coords, airport2_coords);

        Edge edge(route->getSource(), route->getDestination(), weight);

        edges_[route->getSource()][route->getDestination()] = edge;
        edges_[route->getDestination()][route->getSource()] = edge;
    }
}

void Graph::insertVertex(Airport* airport) {
    airports_[airport->getID()] = *airport;
}

void Graph::insertEdge(Airport* airport1, Airport* airport2, const Edge& edge) {
    int firstID = airport1->getID();
    int secondID = airport2->getID();

    edges_[firstID][secondID] = edge;
    edges_[secondID][firstID] = edge;
}

void Graph::removeVertex(Airport* airport) {
    int removedID = airport->getID();

    // iterate over edges of airport being removed to go to that destinationID and remove removedID
    for (auto iter = edges_[removedID].begin(); iter != edges_[removedID].end(); ++iter) {
        edges_[iter->first].erase(removedID);
    }

    airports_.erase(removedID);
    edges_.erase(removedID);
}

void Graph::removeEdge(Airport* airport1, Airport* airport2) {
    int firstID = airport1->getID();
    int secondID = airport2->getID();

    edges_[firstID].erase(secondID);
    edges_[secondID].erase(firstID);
}

const unordered_map<int, Edge>& Graph::incidentEdges(const Airport & airport) const {
    return edges_.at(airport.getID());
}

bool Graph::areAdjacent(Airport* airport1, Airport* airport2) const {
    int firstID = airport1->getID();
    int secondID = airport2->getID();

    if (edges_.at(firstID).find(secondID) != edges_.at(firstID).end()) {
        return true;
    }

    return false;
}

const Airport& Graph::origin(const Edge& edge) const {
    return airports_.at(edge.getSourceID());
}

const Airport& Graph::destination(const Edge& edge) const {
    return airports_.at(edge.getDestinationID());
}

vector<int> Graph::getAdjacent(const Airport& source) const
{
    auto to_find = edges_.find(source.getID());
    if (to_find == edges_.end()) {
        return vector<int>();
    } else {
        vector<int> adj_air_list;
        const unordered_map<int, Edge> & map = edges_.at(source.getID());
        for (auto iter = map.begin(); iter != map.end(); iter++)
        {
            adj_air_list.push_back(iter->first);
        }
        return adj_air_list;
    }
}

const Airport& Graph::getAirport(int id) const {
    return airports_.at(id);
}

const unordered_map<int, Airport>& Graph::getAirports() const {
    return airports_;
}

const unordered_map<int, unordered_map<int, Edge>>& Graph::getEdges() const {
    return edges_;
}
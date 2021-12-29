#include "../include/edge.h"

#include <string>

Edge::Edge(int _source, int _destination) { 
        source = _source;
        destination = _destination;
        discovery = false;
        cross = false;
        weight = -1;
        label = "";
    }

Edge::Edge(int _source, int _destination, float _weight) {
    source = _source;
    destination = _destination;
    weight = _weight;
    discovery = false;
    cross = false;
    label = "";
}

Edge::Edge(int _source, int _destination, bool _discovery, bool _cross) { 
    source = _source;
    destination = _destination;
    discovery = _discovery;
    cross = _cross;
    weight = -1;
    label = "";
}

Edge::Edge(int _source, int _destination, float _weight, bool _discovery, bool _cross) { 
        source = _source;
        destination = _destination;
        discovery = _discovery;
        cross = _cross;
        weight = _weight;
        label = "";
    }

Edge::Edge(int _source, int _destination, float _weight, std::string _label) { 
        source = _source;
        destination = _destination;
        weight = _weight;
        label = _label;
    }

    
Edge::Edge() {
    source = 0;
    destination = 0;
    discovery = false;
    cross = false;
    weight = -1;
    label = "";
}

    
bool Edge::operator>(const Edge& other) const {
    return weight > other.weight;
}

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}
    
bool Edge::operator==(Edge& other) const {
    if (this->source != other.source) {
        return false;
    }
    if (this->destination != other.destination) {
        return false;
    }
    return true;
}

int Edge::getSourceID() const {
    return source;
}

int Edge::getDestinationID() const {
    return destination;
}

bool Edge::getDiscovery() const {
    return this->discovery;
}

bool Edge::getCross() const {
    return this->cross;
}

    
float Edge::getWeight() const {
    return this->weight;
}

std::string Edge::getLabel() const {
    return this->label;
}
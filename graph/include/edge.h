#pragma once

#include <string>

class Edge
{
  public:

    /**
     * Multiple ways to construct an Edge object
     */
    Edge(int _source, int _destination);
    Edge(int _source, int _destination, float _weight);
    Edge(int _source, int _destination, bool _discovery, bool _cross);
    Edge(int _source, int _destination, float _weight, bool _discovery, bool _cross);
    Edge(int _source, int _destination, float _weight, std::string _label);
    Edge();

    /**
     * Comparison operators
     */
    bool operator>(const Edge& other) const;
    bool operator<(const Edge& other) const;  
    bool operator==(Edge& other) const;

    /**
     * Getters
     */
    int getSourceID() const;
    int getDestinationID() const;
    bool getDiscovery() const;
    bool getCross() const;
    float getWeight() const;
    std::string getLabel() const;
    
private:
    int source; 
    int destination; 
    bool discovery; 
    bool cross;
    float weight; 
    std::string label;
};
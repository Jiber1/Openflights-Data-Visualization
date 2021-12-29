#include "traversal.h"
#include "BFS.h"
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * Default iterator constructor
 */
Traversal::Iterator::Iterator() {
    position_ = -1;
    traversal_ = NULL;
    start_ = -1;
    graph_ = Graph();
    finished_ = true;
}

Traversal::Iterator::Iterator(Graph g, Traversal * traversal, int startID) :
    position_(startID), traversal_(traversal), start_(startID), graph_(g), finished_(false) {
        visited_[startID] = true;
}

/**
 * Iterator increment operator
 */
Traversal::Iterator & Traversal::Iterator::operator++() {
      vector<int> adjacent = graph_.getAdjacent(graph_.getAirport(position_));
      std::sort(adjacent.begin(), adjacent.end());

      // Add all adjacent airport IDs to traversal
      for (int id : adjacent) {
        traversal_->add(id);
      }

      // Keep popping IDs off the top until we get one that hasn't been visited
      int nextID = traversal_->peek();
      while (visited_[nextID]) {
        traversal_->pop();
        if (traversal_->empty()) {
          finished_ = true;
          position_ = -1;
          return *this;
        }
        nextID = traversal_->peek();
      }

      position_ = traversal_->pop();
      if (traversal_->empty()) {
        finished_ = true;
        position_ = -1;
        return *this;
      }
      visited_[position_] = true;

      return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current ID in the traversal.
 */
int Traversal::Iterator::operator*() {
  return position_;
}

/**
 * Iterator inequality operator.
 * Determines if two iterators are not equal.
 */
bool Traversal::Iterator::operator!=(const Traversal::Iterator &other) {
  return !(position_ == other.position_);
}


void Traversal::BFSTraversalToFile(std::string path, Graph g, int startID) {

  BFS bfs = BFS(g, startID);
  Traversal::Iterator it = bfs.begin();

  ofstream file;
  file.open(path);

  while (it != bfs.end()) {
    file << *it << "\n";
    ++it;
  }
  file.close();
}
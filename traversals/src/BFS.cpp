#include "BFS.h"

/**
 * Initializes a breadth-first traversal on a given graph, starting at
 * the airport ID `startID`
 * @param g The graph this BFS is going to traverse
 * @param start The starting ID of this BFS 
 */
BFS::BFS(const Graph & g, const int & startID) {
    graph_ = g;
    start_ = startID;
    queue_.push(startID);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
Traversal::Iterator BFS::begin() {
    return Traversal::Iterator(graph_,  this, start_);
}


/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
Traversal::Iterator BFS::end() {
    return Traversal::Iterator();
}

/**
 * Adds an ID for the traversal to visit at some point in the future.
 */
void BFS::add(const int & id) {
    queue_.push(id);
}

/**
 * Removes and returns the current ID in the traversal.
 */
int BFS::pop() {
    int result = queue_.front();
    queue_.pop();
    return result;
}

/**
 * Returns the current ID in the traversal.
 */
int BFS::peek() const {
    return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
    return queue_.empty();
}
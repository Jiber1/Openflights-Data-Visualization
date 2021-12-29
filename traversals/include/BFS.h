#pragma once

#include <iterator>
#include <queue>
#include "../../graph/include/graph_header.h"
#include "traversal.h"

class BFS : public Traversal {
    public:
        BFS(const Graph & g, const int & startID);

        Traversal::Iterator begin();
        Traversal::Iterator end();

        void add(const int & id);
        int pop();
        int peek() const;
        bool empty() const;

    private:
        int start_;
        Graph graph_;
        std::queue<int> queue_;
};
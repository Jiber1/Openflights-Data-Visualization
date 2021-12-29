#pragma once

#include <iterator>
#include <unordered_map>
//#include <bits/stdc++.h>
#include "../../graph/include/graph_header.h"

class Traversal {
    public:
        class Iterator : std::iterator<std::forward_iterator_tag, int> {
            public:
                Iterator();

                Iterator(Graph g, Traversal * traversal, int start);

                Iterator & operator++();

                int operator*();

                bool operator!=(const Iterator & other);

            private:
                int position_;
                Traversal * traversal_;
                int start_;
                Graph graph_;
                std::unordered_map<int, bool> visited_;
                bool finished_;
        };

        virtual Iterator begin() = 0;

        virtual Iterator end() = 0;

        virtual void add(const int & id) = 0;

        virtual int pop() = 0;

        virtual int peek() const = 0;

        virtual bool empty() const = 0;

        static void BFSTraversalToFile(std::string path, Graph g, int startID);

};
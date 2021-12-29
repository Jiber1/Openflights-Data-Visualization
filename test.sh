#!/bin/bash

# This is a shell script to run all tests sequentially.

TEST_PARSING="test-parsing"
TEST_GRAPH="test-graph"
TEST_TRAVERSALS="test-traversals"
TEST_DIJKSTRA="test-dijkstra"
TEST_VISUALIZER="test-visualizer"

echo "Testing Parsing"
cd parsing/
./$TEST_PARSING
cd ..

echo "Testing Graph"
cd graph/
./$TEST_GRAPH
cd ..

echo "Testing Traversals"
cd traversals/
./$TEST_TRAVERSALS
cd ..

echo "Testing Dijkstra"
cd dijkstra/
./$TEST_DIJKSTRA
cd ..

echo "Testing Visualizer"
cd visualizer/
./$TEST_VISUALIZER
cd ..
#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include <iostream>

using namespace std;

struct GraphNode //GraphNode structure to hold each adjacent vertex and path weight to this vertex.
{
	int vertex;
	float weight;

	GraphNode( int v, float w ) : vertex( v ), weight( w ) { };
};

#endif
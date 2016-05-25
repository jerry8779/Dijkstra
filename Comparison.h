#ifndef COMPARISON_H
#define COMPARISON_H
#include <iostream>
#include "GraphNode.h"

using namespace std;

class Comparison //Comparison classed used for the priority queue to return the smaller weight of each graphNode//
{
public:
	bool const operator( )(GraphNode & nodeA, GraphNode & nodeB)
	{
		return( nodeA.weight > nodeB.weight );
	}
};

#endif


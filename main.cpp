/*************************************************************************************************
*                                    Przemyslaw Renkowski										 *
*                                    Programming Project 3 										 *
*     								 12/22/2015													 *
*  Program to compute Shortest paths from Source Vertex to all other vertices, and from source to*
*  target Vertex 																				 *
**************************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
#include <list>
#include <map>
#include "DijkstrasGraph.h"
#include "GraphNode.h"
#include "Comparison.h"

using namespace std;

int main( int argc, char *argv[] )
{
	DijkstrasGraph graph;
	int vertices;

	string inputFile = argv[1];
	int startVertex = stoi( argv[2] );

	vertices = graph.readInput( inputFile );
	vector< list<GraphNode> > adjList( vertices );

	if( startVertex >= graph.numberOfVertices )
	{
		cout << "Invalid Source Vertex! " << endl;
		return 0;
	}
	graph.createAdjList( adjList );
	graph.dijkstrasAlgorithm( startVertex, adjList );
	graph.printTotalPaths( startVertex );
	graph.sourceToTarget( startVertex, adjList );
}

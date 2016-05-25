#ifndef DIJKSTRASGRAPH_H
#define DIJKSTRASGRAPH_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
#include <list>
#include <map>
#include "GraphNode.h"
#include "Comparison.h"


using namespace std;

class DijkstrasGraph
{
public:
	vector<float> inputVector; //Vector used to parse the input file// 
	vector<float> pathWeight; //Vector used to store shortest path from vertex to target ie pathweight[target]// 
	priority_queue< GraphNode, vector< GraphNode >, Comparison > PQ; //Priority Queue that inserts a graph node and uses the weight of each node as comparison//
	int target;
	int numberOfVertices;

	int readInput( string & file ) //Function to read the input text files and store the input in a vector//
	{
		ifstream in( file );
		string line;

		in >> numberOfVertices;

		while( getline( in, line ) )
		{
			stringstream is( line );
			float x;

			while( is >> x )
			{
				inputVector.push_back( x );
			}
		}

		return numberOfVertices;
	}

	void createAdjList( vector< list<GraphNode> > & adjList ) //Function to parse the inputVector and create an Adjacency List//
	{
		float skip = -1;
		int j = 0;
		int v;
		float w;

		for( int i = 1; i < inputVector.size( ); i++ )
		{
			if( inputVector[i] == skip )
			{
				j = inputVector[i+1];
				i++;
			}
			else
			{	
				v = inputVector[i];
				i++;
				w = inputVector[i];
				adjList[j].push_back(GraphNode( v, w )); //Create an Adjacency List with GraphNodes 
			}
		}
	}

	void dijkstrasAlgorithm( int & v, vector< list<GraphNode> > & adjList )
	{
		GraphNode startNode( v, 0 ); //GraphNode that specifies the starting vertex//
		GraphNode currentNode( 0, 0 ); 

		for( int i = 0; i < numberOfVertices; i++ )
		{
			pathWeight.push_back( INT_MAX ); //Loop to maximize all vertex weights to INT_MAX ie INFINITY//
		}

		pathWeight[startNode.vertex] = 0; //Source vertex to source vertex is always 0//
		PQ.push( startNode );

		while( !PQ.empty( ) )
		{
			currentNode = PQ.top( ); //Priority queue uses greedy algorithm to bring the nodes with the smallest weight to the top.
			PQ.pop( );
			if( currentNode.weight <= pathWeight[currentNode.vertex] ) //If current nodes weight <= pathWeight of that same node//
			{
				for( list<GraphNode>::iterator it = adjList[currentNode.vertex].begin( ); it != adjList[currentNode.vertex].end( ); it++ )
				{ 
					if( pathWeight[(*it).vertex] > pathWeight[currentNode.vertex] + (*it).weight ) //If pathweight of adjacent vertex > pathweight of current vertex plus 
					{																			  //the edge to the adjacent vertex than you store this as the new min weight of
						pathWeight[(*it).vertex] = pathWeight[currentNode.vertex] + (*it).weight; //of the adjacent vertex and push adjacent vertex with new pathweight into 
																								  // priority queue.
						PQ.push( GraphNode( (*it).vertex, pathWeight[(*it).vertex]));
					}
				}
			}
		}
	}

	void printTotalPaths( int & startVertex ) //Function that prints the paths from the starting vertex to all other vertices//
	{
		for( int i = 0; i < numberOfVertices; i++ )
		{
			if( pathWeight[i] != INT_MAX )
			{
				cout << "Shortest path from " << startVertex << " to " << i << " : " << pathWeight[i] << endl;
			}
		}
	}

	void printPath( int & t, int & v, vector< list<GraphNode> > & adjList ) //Modified function dijkstrasAlgorithm to print the path from source to target//
	{

		map<int, int> parent; //added a map and list to keep track of the parent vertices to determine the path//
		list<int> shortestPath;
		GraphNode startNode( v, 0 );
		GraphNode currentNode( 0, 0 );
		int target = t;

		pathWeight.clear( );

		for( int i = 0; i < numberOfVertices; i++ )
		{
			pathWeight.push_back( INT_MAX );
		}

		pathWeight[startNode.vertex] = 0;
		PQ.push( startNode );

		cout << "--Path from " << v << " to " << t << "--" << endl;

		while( !PQ.empty( ) )
		{
			currentNode = PQ.top( );
			PQ.pop( );

			if( currentNode.weight <= pathWeight[currentNode.vertex] )
			{
				for( list<GraphNode>::iterator it = adjList[currentNode.vertex].begin( ); it != adjList[currentNode.vertex].end( ); it++ )
				{
					if( pathWeight[(*it).vertex] > pathWeight[currentNode.vertex] + (*it).weight )
					{
						pathWeight[(*it).vertex] = pathWeight[currentNode.vertex] + (*it).weight;
						PQ.push( GraphNode( (*it).vertex, pathWeight[(*it).vertex]));
						parent[(*it).vertex] = currentNode.vertex; //Store the current vertex number in parent[adjacent vertex number/next]
					}
				}
			}
		}

		map<int, int>::iterator it;
		shortestPath.push_front( target );
		while( ( it = parent.find( target ) ) != parent.end( ) ) //Push each node visited on the path from source to target backtracking from target going to source.
		{
			target = (*it).second;
			shortestPath.push_front( target );
		} 
		for( list<int>::iterator it = shortestPath.begin( ); it != shortestPath.end( ); it++ ) //Iterate through shorestPath list and print put path of nodes from target to source.
		{
			cout << (*it) << "  ";
		}
		cout << endl << "Path Weight: " << pathWeight[t] << endl;
		cout << endl;
	}

	void sourceToTarget( int & startVertex, vector< list<GraphNode> > & adjList )//Function that continously asks for target and prints out path to target from source.
	{
		cout << endl << "Enter target (-1 to exit): ";
		cin >> target;
		cout << endl;

		while( target != -1)
		{
			printPath( target, startVertex, adjList );
			cout << "Enter target (-1 to exit): ";
			cin >> target;
			cout << endl;
		}
	}
	
};

#endif
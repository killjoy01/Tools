#pragma once
#include "templatedArray.h"

struct Vert;
struct COORD
{
	int x,y;
};
struct Edge
{
	//a pointer to the Vert that the Edge goes to
	Vert* connentsTo;
	//how much it costs to get across the edge
	int cost;

	//unparam'd cotr. 
	Edge();

	//fills out the attributes with the passed parameters
	Edge(Vert*,int);
};

struct Vert
{
	//array of edges adjacent to this vertex
	tArray<Edge> adjacency;
	//COORDINATE
	COORD pos;
	//PATHFINDING: tells the user if this vert has been checked
	bool visitStatus;
	//PATHFINDING: total cost to this vertex
	int distanceCount;
	//PATHFINDING: a stored counter to the previously visited vert
	int backID;
	//PATHFINDING: after the path is calculated, 
	int nextID;
	


	/*adds an edge to the adjacency array. 
	accepts a pointer to the array it connects to
	and the cost for that edge*/
	void addEdge(Vert*, int);

	//unparam'd cotr
	Vert();

	//places the vertex on the coordinate plane
	Vert(int,int);
	//places the vertex on the coordinate plane
	Vert(COORD);
};

class Graph
{
private:
	//holds all the verticies in the graph for future reference
	tArray<Vert*> MASTERVERTLIST;

public:
	//unparam'd cotr
	Graph();












};
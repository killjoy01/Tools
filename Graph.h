#pragma once
#include "templatedArray.h"

struct Vert;
struct Position
{
	int x,y;

	Position(int x, int y):x(x),y(y){}

};
struct Edge
{
	//a pointer to the Vert that the Edge goes to
	Vert* connectsTo;
	//how much it costs to get across the edge
	float cost;

	//unparam'd cotr. 
	Edge()
		:connectsTo(NULL),cost(0.0)
	{}

	//fills out the attributes with the passed parameters
	Edge(Vert* ct,float c)
		:connectsTo(ct), cost(c)
	{}

	//tests equality of edges
	bool operator==(const Edge& other) const{return other.cost == cost && other.connectsTo == connectsTo;}
	
	//an edge is less than another if it's cost is less
	bool operator<(const Edge& other) const{return other.cost < cost;}

	//an edge is greater than another if it's cost is greater
	bool operator>(const Edge& other) const{return other.cost > cost;}

	//less than or equal test
	bool operator<=(const Edge& other) const{return other.cost <= cost;}

	//greater than or equal
	bool operator>=(const Edge& other ) const{return other.cost >= cost;}
};

struct Vert
{
	//array of edges adjacent to this vertex
	tArray<Edge> adjacency;
	//COORDINATE
	Position pos;
	//PATHFINDING: tells the user if this vert has been checked
	bool visitStatus;
	//PATHFINDING: total cost to this vertex
	int distanceCount;
	//PATHFINDING: a stored counter to the previously visited vert
	int backID;
	//PATHFINDING: after the path is calculated, 
	int nextID;

	//unparam'd cotr
	Vert()
		:pos(0,0),visitStatus(false), distanceCount(0), backID(-1),nextID(-1),adjacency(4)
	{}

	//places the vertex on the coordinate plane
	Vert(int row, int col):pos(row,col){}

	//places the vertex on the coordinate plane
	Vert(Position p):pos(p.x,p.y){}

	//copy cotr
	Vert(const Vert& other)
	{
		adjacency.copy(other.adjacency);
		backID = other.backID;
		visitStatus= other.visitStatus;
		distanceCount = other.distanceCount;
		pos = other.pos;
		nextID = other.nextID;
	}

	/*adds an edge to the adjacency array. 
	accepts a pointer to the array it connects to
	and the cost for that edge*/
	void addEdge(Vert* to, float cost)
	{
		Edge e(to,cost);
		adjacency.insert(e);
	}
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
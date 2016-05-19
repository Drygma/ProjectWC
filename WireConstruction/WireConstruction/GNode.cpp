#include "GNode.h"
#include <iostream>
#include <vector>


GNode::GNode() : x(0), y(0), z(0), edge('D')
{
}

GNode::GNode(const GNode &N)
{
	x = N.x;
	y = N.y;
	z = N.z;
	edge = N.edge;
	weight = N.weight;
	/*std::vector<GNode *>::const_iterator it = N.neighbours.begin();
	neighbours.clear();
	for (; it != N.neighbours.end(); it++)
	{
		neighbours.push_back(*it);
	}*/
}

GNode::GNode(float X, float Y, float Z): x(X), y(Y), z(Z), edge('D')
{
}

GNode::GNode(float X, float Y, float Z, char Edge): x(X), y(Y), z(Z), edge(Edge)
{
}

GNode::~GNode()
{
	neighbours.clear();
}

GNode GNode::operator=(const GNode& N)
{
	this->x = N.x;
	this->y = N.y;
	this->z = N.z;
	this->edge = N.edge;
	this->weight = N.weight;
	/*std::vector<GNode *> new_neighbours;
	std::vector<GNode *>::const_iterator it = N.neighbours.begin();
	for (; it != N.neighbours.end(); it++)
	{
		new_neighbours.push_back(*it);
	}
	this->neighbours.swap(new_neighbours);*/
	return *this;
}

bool GNode::operator==(const GNode& N)
{
	return ((this->x == N.x) && (this->y == N.y) && (this->z == N.z));
}
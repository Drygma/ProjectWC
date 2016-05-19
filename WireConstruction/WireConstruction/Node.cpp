#include "Node.h"

CNode::CNode()
{
	edge = 'D';
}

CNode::CNode(char edge, float x, float y) : edge(edge), x(x), y(y)
{
}


CNode::~CNode()
{
}

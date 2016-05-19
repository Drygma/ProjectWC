#pragma once
#include <vector>

class GNode
{
public:
	float x, y, z;
	char edge; //грани N,W,B,E,S,T + ребра X(по X), Y(по Y), Z(по Z)
				// D - default (для конструктора без параметра edge)
	std::vector<GNode*> neighbours;
	float weight; // вес нейрона: 0 - обычный нейрон, 1 - входной нейрон, 1 - "двойной" нейрон, -1 - неактивный нейрон
public:
	GNode();
	GNode(const GNode &N);
	GNode(float X, float Y, float Z);
	GNode(float X, float Y, float Z, char Edge);
	~GNode();

	GNode operator=(const GNode& point);
	bool operator==(const GNode& N);
};


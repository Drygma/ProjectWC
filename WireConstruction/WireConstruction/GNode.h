#pragma once
#include <vector>

class GNode
{
public:
	float x, y, z;
	char edge; //����� N,W,B,E,S,T + ����� X(�� X), Y(�� Y), Z(�� Z)
				// D - default (��� ������������ ��� ��������� edge)
	std::vector<GNode*> neighbours;
	float weight; // ��� �������: 0 - ������� ������, 1 - ������� ������, 1 - "�������" ������, -1 - ���������� ������
public:
	GNode();
	GNode(const GNode &N);
	GNode(float X, float Y, float Z);
	GNode(float X, float Y, float Z, char Edge);
	~GNode();

	GNode operator=(const GNode& point);
	bool operator==(const GNode& N);
};


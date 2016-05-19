#pragma once

#include "Node.h"
#include "GNode.h"
#include <vector>

class CRoom
{
public:
	float width;
	float length;
	float height;

	// ������, ���������� ������� n ������, ����� 8 ����� �������,
	// � ����� ��������������� ����, ��������������� �������� GenerateGrid
	std::vector<GNode> Network;
	// ���������� ������
	int n;

	float **wMatrix;

public:
	CRoom();
	CRoom(float w, float l, float h);
	~CRoom();
public:
	// �������� �����
	int AddNode(GNode X);
	//�������� �����-������
	int AddInput(GNode T);
	// ���������� �� ����� �� �����
	float SLength(CNode X1, CNode X2);
	// ������� ��������� �����
	// ��������� �������������� ����� �� ������ �����-��������
	void GenerateGrid();
	// ������������� ������� ���������� ����� ������ ����
	void GenerateMatrix();
	// �������� ������� ����������
	void ShowMatrix();

	// ������� ��������� ����� ����� ����� ������
	void LinkNeighbours(GNode *T1, GNode *T2);
	// ������� ���� ����
	void RemoveNode(std::vector<GNode>::iterator &it);
	// Network Check
	void NetworkCheck();

	void n_train();

private:
	// ������� ��� ����������� GNode � CNode
	CNode GNodeToCNode(GNode T);
};

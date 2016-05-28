#pragma once

#include "Node.h"
#include "GNode.h"
#include <fstream>
#include <string>
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

	std::string f_path_out;

public:
	CRoom();
	CRoom(float w, float l, float h, std::string path_out);
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
	void RemoveNode(GNode *it);
	// Network Check
	void NetworkCheck();

	void n_train();
	void findPath(float I = 1);

private:
	// ������� ��� ����������� GNode � CNode
	CNode GNodeToCNode(GNode T);
	//
	bool isInput(GNode *node);
	// ������� ��� �������� ���������� �� ����� �� ���� ������
	float IDistSum(GNode *node);
	// ���������� ����� ��������
	float SrcToTarget(int src, int target, float **graph, int V, int* visit_cnt, std::fstream &out, bool write);
	//
	int minKey(float key[], bool mstSet[], int V, int target);
};

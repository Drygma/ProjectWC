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

	// Вектор, содержащий сначала n входов, потом 8 углов комнаты,
	// а потом вспомогательные узлы, сгенерированные функцией GenerateGrid
	std::vector<GNode> Network;
	// Количество входов
	int n;

	float **wMatrix;

	std::string f_path_out;

public:
	CRoom();
	CRoom(float w, float l, float h, std::string path_out);
	~CRoom();
public:
	// Добавить точку
	int AddNode(GNode X);
	//Добавить точку-прибор
	int AddInput(GNode T);
	// Расстояние от точки до точки
	float SLength(CNode X1, CNode X2);
	// Функция генерации сетки
	// Генерация дополнительных узлов на основе узлов-приборов
	void GenerateGrid();
	// Сгенерировать матрицу расстояний между узлами сети
	void GenerateMatrix();
	// Показать матрицу расстояний
	void ShowMatrix();

	// Создать соседскую связь между двумя узлами
	void LinkNeighbours(GNode *T1, GNode *T2);
	// Удалить узел сети
	void RemoveNode(GNode *it);
	// Network Check
	void NetworkCheck();

	void n_train();
	void findPath(float I = 1);

private:
	// Функция для превращения GNode в CNode
	CNode GNodeToCNode(GNode T);
	//
	bool isInput(GNode *node);
	// Функция для подсчета расстояния от точки до всех входов
	float IDistSum(GNode *node);
	// Возвращает длину маршрута
	float SrcToTarget(int src, int target, float **graph, int V, int* visit_cnt, std::fstream &out, bool write);
	//
	int minKey(float key[], bool mstSet[], int V, int target);
};

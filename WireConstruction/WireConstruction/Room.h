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

	// Вектор, содержащий сначала n входов, потом 8 углов комнаты,
	// а потом вспомогательные узлы, сгенерированные функцией GenerateGrid
	std::vector<GNode> Network;
	// Количество входов
	int n;

	float **wMatrix;

public:
	CRoom();
	CRoom(float w, float l, float h);
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
	void RemoveNode(std::vector<GNode>::iterator &it);
	// Network Check
	void NetworkCheck();

	void n_train();

private:
	// Функция для превращения GNode в CNode
	CNode GNodeToCNode(GNode T);
};

#include <iostream>
#include <fstream>
#include <conio.h>

#include "GNode.h"
#include "Room.h"

using namespace std;

void ExportFile(CRoom *room, string filename);

int main(int argc, char **argv)
{
	cout << "Room Wire Construction v.0.05" << endl << endl;

	CRoom room(3, 2, 2);
	
	room.AddInput(GNode(0, 0, 0));
	//room.AddInput(GNode(0, 0, 2));
	//room.AddInput(GNode(0, 1, 1));
	//room.AddInput(GNode(2, 1, 1));
	room.AddInput(GNode(1, 3, 1));
	room.n_train();

	// !!! 1 � 4 �� �������� ������ (����� ����������
	/// ������ ���������� ������ �����, ��� �����. ��� ���������� ��-�� ����, 
	/// ��� ����������� ��������� ���������.

	// ���������� ���� ��� �������� � Matlab, ����� ��� �� ���������� :)
	ExportFile(&room, "nodes.txt");
	_getch();
	return 0;
}

void ExportFile(CRoom *room, string filename)
{
	fstream file;
	file.open(filename);
	file << "X Y Z" << endl;
	file << room->length << " " << room->width << " " << room->height << endl;

	std::vector<GNode>::const_iterator it = room->Network.begin();
	for (; it != room->Network.end(); it++)
	{
		file << it->x << " " << it->y << " " << it->z << endl;
	}
	file.close();
	cout << "File saved." << endl;
}
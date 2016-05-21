#include "Room.h"
#include "Node.h"
#include "GNode.h"
#include <iostream>
#include <limits>
#include <conio.h>

#include <math.h>

using namespace std;

CRoom::CRoom(): n(0)
{
}

CRoom::CRoom(float w, float l, float h) : width(w), length(l), height(h), n(0)
{
}

CRoom::~CRoom()
{
}

int CRoom::AddNode(GNode T)
{
	// ���������, ��������� �� ����� � ������� ���������
	if (T.x > length || T.x < 0 || T.y > width || T.y < 0 || T.z > height || T.z < 0)
	{
		std::cout << "Node hasn't been added. It's out of room. (" << T.x << " ; " << T.y << " ; " << T.z << ")" << " [" << T.edge << "]" << endl;
		return -1;
	}

	// ��������� ������� ��������, ��������� �� D, � ���� edge.
	// ���� ��� ����� D, �� ���������� ���������� ��������.
	if (T.edge == 'D')
	{
		if ((T.x == 0 && T.y == 0) || (T.x == length && T.y == 0)
			|| (T.x == 0 && T.y == width) || (T.x == length && T.y == width))
			T.edge = 'Z';
		else if ((T.x == 0 && T.z == 0) || (T.x == length && T.z == 0)
			|| (T.x == length && T.z == height) || (T.x == 0 && T.z == height))
			T.edge = 'Y';
		else if ((T.y == 0 && T.z == 0) || (T.y == width && T.z == 0)
			|| (T.y == width && T.z == height) || (T.y == 0 && T.z == height))
			T.edge = 'X';
		else if (T.x == 0)
			T.edge = 'N';
		else if (T.x == length)
			T.edge = 'S';
		else if (T.y == 0)
			T.edge = 'W';
		else if (T.y == width)
			T.edge = 'E';
		else if (T.z == 0)
			T.edge = 'B';
		else if (T.z == height)
			T.edge = 'T';
	}

	// ���������, ���� �� ����� �� ����� � Network
	int exists = 0;
	for (std::vector<GNode>::iterator net_iterator = Network.begin(); net_iterator != Network.end(); net_iterator++)
	{
		if ((*(net_iterator)).x == T.x && (*(net_iterator)).y == T.y && (*(net_iterator)).z == T.z)
		{
			exists = 1;
			break;
		}
	}

	// ���� ��� ����������, �� ��������� ���� � Network
	if (!exists)
	{
		Network.push_back(T);

		GNode &inserted = Network.back();
		inserted.weight = 0; // ���������� ��� = 0 ��� �������� �������

		std::cout << "Added node (" << inserted.x << " ; " << inserted.y << " ; " << inserted.z << ")" << " [" << inserted.edge << "]" << endl;
		return 0;
	}
	else
	{
		std::cout << "There is similar node in network. Node hasn't been added. (" << T.x << " ; " << T.y << " ; " << T.z << ")" << " [" << T.edge << "]" << endl;
		return 1;
	}
}

int CRoom::AddInput(GNode T)
{
	int ret = 0;
	ret = AddNode(T);
	if (ret == 0)
	{
		GNode &added = Network.back();
		added.weight = 1; // ���������� ��� = 1 ��� �������� �������
		n++;
	}
	return ret;
}

CNode CRoom::GNodeToCNode(GNode T)
{
	CNode ret;
	if (T.edge == 'S')
	{
		ret.edge = 'S';
		ret.x = width - T.y;
		ret.y = T.z;
	}
	else if (T.edge == 'N')
	{
		ret.edge = 'N';
		ret.x = T.y;
		ret.y = T.z;
	}
	else if (T.edge == 'E')
	{
		ret.edge = 'E';
		ret.x = T.x;
		ret.y = T.z;
	}
	else if (T.edge == 'W')
	{
		ret.edge = 'W';
		ret.x = length - T.x;
		ret.y = T.z;
	}
	else if (T.edge == 'T')
	{
		ret.edge = 'T';
		ret.x = T.y;
		ret.y = length - T.x;
	}
	else if (T.edge == 'B')
	{
		ret.edge = 'B';
		ret.x = T.y;
		ret.y = length - T.x;
	}
	else if (T.x == 0 && T.y == 0)
	{
		ret.edge = 'N';
		ret.x = 0;
		ret.y = T.z;
	}
	else if (T.x == 0 && T.y == width)
	{
		ret.edge = 'N';
		ret.x = width;
		ret.y = T.z;
	}
	else if (T.x == length && T.y == width)
	{
		ret.edge = 'S';
		ret.x = 0;
		ret.y = T.z;
	}
	else if (T.x == length && T.y == 0)
	{
		ret.edge = 'S';
		ret.x = width;
		ret.y = T.z;
	}
	else if (T.x == 0 && T.z == 0)
	{
		ret.edge = 'B';
		ret.x = T.y;
		ret.y = length;
	}
	else if (T.x == length && T.z == 0)
	{
		ret.edge = 'B';
		ret.x = T.y;
		ret.y = 0;
	}
	else if (T.x == length && T.z == height)
	{
		ret.edge = 'T';
		ret.x = T.y;
		ret.y = 0;
	}
	else if (T.x == 0 && T.z == height)
	{
		ret.edge = 'T';
		ret.x = T.y;
		ret.y = length;
	}
	return ret;
}

float CRoom::SLength(CNode X1, CNode X2)
{
	// ��� ��������� �������� ������������ ���� �����
	// ������������ ���� �����

	// ��������� �������
	//     N
	//  W  B  E
	//     S
	//     T
	
	if (X1.edge == X2.edge)
	{
		return fabsf(X1.x - X2.x) + fabsf(X1.y - X2.y);
	}
	else if((X1.edge == 'E' && X2.edge == 'N') || (X1.edge == 'N' && X2.edge == 'E'))
	{ 
		if (X1.edge == 'E' && X2.edge == 'N')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		return X1.x + width - X2.x + fabsf(X1.y - X2.y);
	}
	else if ((X1.edge == 'N' && X2.edge == 'W') || (X1.edge == 'W' && X2.edge == 'N'))
	{
		if (X1.edge == 'W' && X2.edge == 'N')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		return X1.x + length - X2.x + fabsf(X1.y - X2.y);
	}
	else if ((X1.edge == 'W' && X2.edge == 'S') || (X1.edge == 'S' && X2.edge == 'W'))
	{
		if (X1.edge == 'S' && X2.edge == 'W')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		return X1.x + width - X2.x + fabsf(X1.y - X2.y);
	}
	else if ((X1.edge == 'S' && X2.edge == 'E') || (X1.edge == 'E' && X2.edge == 'S'))
	{
		if (X1.edge == 'E' && X2.edge == 'S')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		return X1.x + length - X2.x + fabsf(X1.y - X2.y);
	}
	else if ((X1.edge == 'E' && X2.edge == 'W') || (X1.edge == 'W' && X2.edge == 'E'))
	{
		if (X1.edge == 'W' && X2.edge == 'E')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}

		// ����� �������
		float S1 = height - X1.y + height - X2.y + fabsf(X1.x - (length - X2.x)) + width;
		// ����� ���
		float S2 = X1.y + X2.y + fabsf(X1.x - (length - X2.x)) + width;
		// ����� N
		float S3 = X1.x + length - X2.x + fabsf(X1.y - X2.y) + width;
		// ����� S
		float S4 = length - X1.x + X2.x + fabsf(X1.y - X2.y) + width;

		return fminf(fminf(S1, S2), fminf(S3, S4));
	}
	else if ((X1.edge == 'S' && X2.edge == 'N') || (X1.edge == 'N' && X2.edge == 'S'))
	{
		if (X1.edge == 'N' && X2.edge == 'S')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}

		// ����� �������
		float S1 = height - X1.y + height - X2.y + fabsf(X1.x - (width - X2.x)) + length;
		// ����� ���
		float S2 = X1.y + X2.y + fabsf(X1.x - (width - X2.x)) + length;
		// ����� E
		float S3 = X1.x + width - X2.x + fabsf(X1.y - X2.y) + length;
		// ����� W
		float S4 = width - X1.x + X2.x + fabsf(X1.y - X2.y) + length;

		return fminf(fminf(S1, S2), fminf(S3, S4));
	}
	else if ((X1.edge == 'E' && (X2.edge == 'T' || X2.edge == 'B')) || ((X1.edge == 'T' || X1.edge == 'B') && X2.edge == 'E'))
	{
		if (X1.edge == 'T' || X1.edge == 'B')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		if(X2.edge == 'T')
			return height - X1.y + width - X2.x + fabsf(length - X1.x - X2.y);
		else if (X2.edge == 'B')
			return X1.y + width - X2.x + fabsf(length - X1.x - X2.y);
	}
	else if ((X1.edge == 'W' && (X2.edge == 'T' || X2.edge == 'B')) || ((X1.edge == 'T' || X1.edge == 'B') && X2.edge == 'W'))
	{
		if (X1.edge == 'T' || X1.edge == 'B')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		if (X2.edge == 'T')
			return height - X1.y + X2.x + fabsf(X1.x - X2.y);
		else if (X2.edge == 'B')
			return X1.y + X2.x + fabsf(X1.x - X2.y);
	}
	else if ((X1.edge == 'N' && (X2.edge == 'T' || X2.edge == 'B')) || ((X1.edge == 'T' || X1.edge == 'B') && X2.edge == 'N'))
	{
		if (X1.edge == 'T' || X1.edge == 'B')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		if (X2.edge == 'T')
			return height - X1.y + length - X2.y + fabsf(X1.x - X2.x);
		else if (X2.edge == 'B')
			return X1.y + length - X2.y + fabsf(X1.x - X2.x);
	}
	else if ((X1.edge == 'S' && (X2.edge == 'T' || X2.edge == 'B')) || ((X1.edge == 'T' || X1.edge == 'B') && X2.edge == 'S'))
	{
		if (X1.edge == 'T' || X1.edge == 'B')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}
		if (X2.edge == 'T')
			return height - X1.y + X2.y + fabsf(width - X1.x - X2.x);
		else if (X2.edge == 'B')
			return X1.y + X2.y + fabsf(width - X1.x - X2.x);
	}
	else if ((X1.edge == 'B' && X2.edge == 'T') || (X1.edge == 'T' && X2.edge == 'B'))
	{
		if (X1.edge == 'T' && X2.edge == 'B')
		{
			CNode tmp = X1;
			X1 = X2;
			X2 = tmp;
		}

		// ����� N
		float S1 = length - X1.y + height + length - X2.y;
		// ����� S
		float S2 = X1.y + height + X2.y;
		// ����� E
		float S3 = width - X1.x + height + width - X2.x;
		// ����� W
		float S4 = X1.x + height + X2.x;

		return fminf(fminf(S1, S2), fminf(S3, S4));
	}
		
	return -1;
}

void CRoom::GenerateGrid()
{
	std::cout << std::endl << "Grid generation has started." << std::endl;

	// ������ ��� ������
	int f = 0;

	// �������� Network, ���������� ������ �����, �� ��������� ������
	std::vector<GNode> tmp = Network;

	// ���������� ���� �������
	AddNode(GNode(0, 0, 0, 'Z'));
	AddNode(GNode(0, 0, height, 'Z'));
	AddNode(GNode(length, 0, 0, 'Z'));
	AddNode(GNode(length, 0, height, 'Z'));
	AddNode(GNode(0, width, 0, 'Z'));
	AddNode(GNode(0, width, height, 'Z'));
	AddNode(GNode(length, width, 0, 'Z'));
	AddNode(GNode(length, width, height, 'Z'));

	std::vector<GNode>::iterator iterator = tmp.begin();
	for (int i = 0; i < n; i++)
	{
		GNode cur_node = *iterator;
		if (cur_node.edge == 'S' || cur_node.edge == 'N')
		{
			AddNode(GNode(length, cur_node.y, cur_node.z, 'S'));
			AddNode(GNode(length, cur_node.y, 0, 'Y'));
			AddNode(GNode(length, cur_node.y, height, 'Y'));
			AddNode(GNode(length, 0, cur_node.z, 'Z'));
			AddNode(GNode(length, width, cur_node.z, 'Z'));

			AddNode(GNode(0, cur_node.y, cur_node.z, 'N'));
			AddNode(GNode(0, cur_node.y, 0, 'Y'));
			AddNode(GNode(0, cur_node.y, height, 'Y'));
			AddNode(GNode(0, 0, cur_node.z, 'Z'));
			AddNode(GNode(0, width, cur_node.z, 'Z'));
		}
		else if (cur_node.edge == 'E' || cur_node.edge == 'W')
		{
			AddNode(GNode(cur_node.x, width, cur_node.z, 'E'));
			AddNode(GNode(cur_node.x, width, 0, 'X'));
			AddNode(GNode(cur_node.x, width, height, 'X'));
			AddNode(GNode(0, width, cur_node.z, 'Z'));
			AddNode(GNode(length, width, cur_node.z, 'Z'));

			AddNode(GNode(cur_node.x, 0, cur_node.z, 'W'));
			AddNode(GNode(cur_node.x, 0, 0, 'X'));
			AddNode(GNode(cur_node.x, 0, height, 'X'));
			AddNode(GNode(0, 0, cur_node.z, 'Z'));
			AddNode(GNode(length, 0, cur_node.z, 'Z'));
		}
		else if (cur_node.edge == 'B' || cur_node.edge == 'T')
		{
			AddNode(GNode(cur_node.x, cur_node.y, height, 'T'));
			AddNode(GNode(cur_node.x, 0, height, 'X'));
			AddNode(GNode(cur_node.x, width, height, 'X'));
			AddNode(GNode(0, cur_node.y, height, 'Y'));
			AddNode(GNode(length, cur_node.y, height, 'Y'));

			AddNode(GNode(cur_node.x, cur_node.y, height, 'B'));
			AddNode(GNode(cur_node.x, 0, height, 'X'));
			AddNode(GNode(cur_node.x, width, height, 'X'));
			AddNode(GNode(0, cur_node.y, height, 'Y'));
			AddNode(GNode(length, cur_node.y, height, 'Y'));
		}
		else if (cur_node.edge == 'X')
		{
			AddNode(GNode(cur_node.x, 0, height, 'X'));
			AddNode(GNode(cur_node.x, width, height, 'X'));
			AddNode(GNode(cur_node.x, width, 0, 'X'));
			AddNode(GNode(cur_node.x, 0, height, 'X'));
		}
		else if (cur_node.edge == 'Y')
		{
			AddNode(GNode(0, cur_node.y, height, 'Y'));
			AddNode(GNode(length, cur_node.y, height, 'Y'));
			AddNode(GNode(length, cur_node.y, 0, 'Y'));
			AddNode(GNode(0, cur_node.y, height, 'Y'));
		}
		else if (cur_node.edge == 'Z')
		{
			AddNode(GNode(0, 0, cur_node.z, 'Z'));
			AddNode(GNode(0, width, cur_node.z, 'Z'));
			AddNode(GNode(length, width, cur_node.z, 'Z'));
			AddNode(GNode(length, 0, cur_node.z, 'Z'));
		}
		iterator++;
	}

	// ������, ����� �� ������� �������� �����, ������� ��������������
	// ����-"�����������" ������� ���� � ������ ������
	tmp = Network;
	for (iterator = tmp.begin(); iterator != tmp.end(); iterator++)
	{
		GNode cur_node = *iterator;
		for (std::vector<GNode>::iterator iterator2 = iterator + 1; iterator2 != tmp.end(); iterator2++)
		{
			if (iterator2 == tmp.end())
				break;

			GNode cur_node2 = *(iterator2);
			if (cur_node.edge != 'X' && cur_node.edge != 'Y' && cur_node.edge != 'Z')
			{
				if (cur_node.edge == cur_node2.edge)
				{
					if (cur_node.edge == 'N' || cur_node.edge == 'S')
					{
						AddNode(GNode(0, cur_node.y, cur_node.z, 'N'));
						AddNode(GNode(0, cur_node.y, cur_node2.z, 'N'));
						AddNode(GNode(0, cur_node2.y, cur_node.z, 'N'));
						AddNode(GNode(0, cur_node2.y, cur_node2.z, 'N'));
						AddNode(GNode(length, cur_node.y, cur_node.z, 'S'));
						AddNode(GNode(length, cur_node.y, cur_node2.z, 'S'));
						AddNode(GNode(length, cur_node2.y, cur_node.z, 'S'));
						AddNode(GNode(length, cur_node2.y, cur_node2.z, 'S'));
					}
					else if (cur_node.edge == 'W' || cur_node.edge == 'E')
					{
						AddNode(GNode(cur_node.x, 0, cur_node.z, 'W'));
						AddNode(GNode(cur_node.x, 0, cur_node2.z, 'W'));
						AddNode(GNode(cur_node2.x, 0, cur_node.z, 'W'));
						AddNode(GNode(cur_node2.x, 0, cur_node2.z, 'W'));
						AddNode(GNode(cur_node.x, width, cur_node.z, 'E'));
						AddNode(GNode(cur_node.x, width, cur_node2.z, 'E'));
						AddNode(GNode(cur_node2.x, width, cur_node.z, 'E'));
						AddNode(GNode(cur_node2.x, width, cur_node2.z, 'E'));
					}
					else if (cur_node.edge == 'B' || cur_node.edge == 'T')
					{
						AddNode(GNode(cur_node.x, cur_node.y, 0, 'B'));
						AddNode(GNode(cur_node.x, cur_node2.y, 0, 'B'));
						AddNode(GNode(cur_node2.x, cur_node.y, 0, 'B'));
						AddNode(GNode(cur_node2.x, cur_node2.y, 0, 'B'));
						AddNode(GNode(cur_node.x, cur_node.y, height, 'T'));
						AddNode(GNode(cur_node.x, cur_node2.y, height, 'T'));
						AddNode(GNode(cur_node2.x, cur_node.y, height, 'T'));
						AddNode(GNode(cur_node2.x, cur_node2.y, height, 'T'));
					}
				}
				else
				{
					if ((cur_node.edge == 'N' || cur_node.edge == 'S') && (cur_node2.edge == 'E' || cur_node2.edge == 'W'))
					{
						AddNode(GNode(cur_node2.x, cur_node.y, 0));
						AddNode(GNode(cur_node2.x, cur_node.y, height));
					}
					else if ((cur_node2.edge == 'N' || cur_node2.edge == 'S') && (cur_node.edge == 'E' || cur_node.edge == 'W'))
					{
						AddNode(GNode(cur_node.x, cur_node2.y, 0));
						AddNode(GNode(cur_node.x, cur_node2.y, height));
					}
				}
			}
		}
	}

	std::cout << std::endl << "Grid has been generated." << std::endl;
}

void CRoom::GenerateMatrix()
{
	// �������������� ������� ����������
	wMatrix = new float*[Network.size()];
	for (int k = 0; k < Network.size(); k++)
		wMatrix[k] = new float[Network.size()];

	for (int k = 0; k < Network.size(); k++)
		for (int l = 0; l < Network.size(); l++)
			wMatrix[k][l] = 0;


	int k = 0;
	for (std::vector<GNode>::iterator iterator = Network.begin(); iterator != Network.end(); iterator++)
	{
		
		// ������� ����������� ���������� � ������ ������� �� �����
		float min_x_low = std::numeric_limits<float>::infinity(), min_x_high = std::numeric_limits<float>::infinity();
		float min_y_low = std::numeric_limits<float>::infinity(), min_y_high = std::numeric_limits<float>::infinity();
		float min_z_low = std::numeric_limits<float>::infinity(), min_z_high = std::numeric_limits<float>::infinity();

		GNode i = *iterator;

		int l = 0;
		for (std::vector<GNode>::iterator iterator2 = Network.begin(); iterator2 != Network.end(); iterator2++)
		{
			GNode j = *iterator2;

			// � ����� ������ �������� ������� �� �����������������. ����� ��� ��� ��� � �����������.
			if (i.edge == 'B' && j.edge == 'T' || i.edge == 'T' && j.edge == 'B'
				|| i.edge == 'N' && j.edge == 'S' || i.edge == 'S' && j.edge == 'N'
				|| i.edge == 'W' && j.edge == 'E' || i.edge == 'E' && j.edge == 'W')
			{
				wMatrix[k][l] = 0;
			}
			else if (i.x == j.x) // �.�. ��� ����� �� ������ N ��� S (� ����� ����������� � ��� ������)
			{
				if (i.z == j.z)
				{
					if (i.y - j.y < 0 && j.y - i.y < min_y_high)
						min_y_high = j.y - i.y;
					else if (i.y - j.y > 0 && i.y - j.y < min_y_low)
						min_y_low = i.y - j.y;
				}
				else if (i.y == j.y)
				{
					if (i.z - j.z < 0 && j.z - i.z < min_z_high)
						min_z_high = j.z - i.z;
					else if (i.z - j.z > 0 && i.z - j.z < min_z_low)
						min_z_low = i.z - j.z;
				}				
			}
			else if (i.y == j.y) // �.�. ��� ����� �� ������ W ��� E (� ����� ����������� � ��� ������)
			{
				if (i.x == j.x)
				{
					if (i.z - j.z < 0 && j.z - i.z < min_z_high)
						min_z_high = j.z - i.z;
					else if (i.z - j.z > 0 && i.z - j.z < min_z_low)
						min_z_low = i.z - j.z;
				}
				else if (i.z == j.z)
				{
					if (i.x - j.x < 0 && j.x - i.x < min_x_high)
						min_x_high = j.x - i.x;
					else if (i.x - j.x > 0 && i.x - j.x < min_x_low)
						min_x_low = i.x - j.x;
				}
			}
			else if (i.z == j.z) // �.�. ��� ����� �� ������ B ��� T (� ����� ����������� � ��� ������)
			{
				if (i.x == j.x)
				{
					if (i.y - j.y < 0 && j.y - i.y < min_y_high)
						min_y_high = j.y - i.y;
					else if (i.y - j.y > 0 && i.y - j.y < min_y_low)
						min_y_low = i.y - j.y;
				}
				else if (i.y == j.y)
				{
					if (i.x - j.x < 0 && j.x - i.x < min_x_high)
						min_x_high = j.x - i.x;
					else if (i.x - j.x > 0 && i.x - j.x < min_x_low)
						min_x_low = i.x - j.x;
				}			
			}
			else
				wMatrix[k][l] = 0;
			l++;
		}
		
		
		// ���������� �������� � �������, � ����� �������������� ������� ������ �����
		l = 0;
		for (std::vector<GNode>::iterator iterator2 = Network.begin(); iterator2 != Network.end(); iterator2++)
		{
			GNode j = *iterator2;

			if (i.x == j.x) // �.�. ��� ����� �� ������ N ��� S (� ����� ����������� � ��� ������)
			{
				if (i.z == j.z)
				{
					if (i.y - j.y < 0 && min_y_high == j.y - i.y)
					{
						wMatrix[k][l] = min_y_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.y - j.y > 0 && min_y_low == i.y - j.y)
					{
						wMatrix[k][l] = min_y_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
				else if (i.y == j.y)
				{
					if (i.z - j.z < 0 && min_z_high == j.z - i.z)
					{
						wMatrix[k][l] = min_z_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.z - j.z > 0 && min_z_low == i.z - j.z)
					{
						wMatrix[k][l] = min_z_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
			}
			else if (i.y == j.y) // �.�. ��� ����� �� ������ W ��� E (� ����� ����������� � ��� ������)
			{
				if (i.x == j.x)
				{
					if (i.z - j.z < 0 && min_z_high == j.z - i.z)
					{
						wMatrix[k][l] = min_z_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.z - j.z > 0 && min_z_low == i.z - j.z)
					{
						wMatrix[k][l] = min_z_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
				else if (i.z == j.z)
				{
					if (i.x - j.x < 0 && min_x_high == j.x - i.x)
					{
						wMatrix[k][l] = min_x_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.x - j.x > 0 && min_x_low == i.x - j.x)
					{
						wMatrix[k][l] = min_x_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
			}
			else if (i.z == j.z) // �.�. ��� ����� �� ������ B ��� T (� ����� ����������� � ��� ������)
			{
				if (i.x == j.x)
				{
					if (i.y - j.y < 0 && min_y_high == j.y - i.y)
					{
						wMatrix[k][l] = min_y_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.y - j.y > 0 && min_y_low == i.y - j.y)
					{
						wMatrix[k][l] = min_y_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
				else if (i.y == j.y)
				{
					if (i.x - j.x < 0 && min_x_high == j.x - i.x)
					{
						wMatrix[k][l] = min_x_high;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
					else if (i.x - j.x > 0 && min_x_low == i.x - j.x)
					{
						wMatrix[k][l] = min_x_low;
						LinkNeighbours(&(*iterator), &(*iterator2));
					}
				}
			}
			else
				wMatrix[k][l] = 0;

			l++;
		}
		k++;
	}
}

void CRoom::ShowMatrix()
{
	std::cout << "Matrix: " << endl;
	for (int i = 0; i < Network.size(); i++)
	{
		for (int j = 0; j < Network.size(); j++)
		{
			std::cout << wMatrix[i][j] << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void CRoom::LinkNeighbours(GNode *T1, GNode *T2)
{
	// ���������, ���� �� � T1 ����� ����� ��, ��� T2
	int exists = 0;
	std::vector<GNode *>::iterator it = (*T1).neighbours.begin();
	for (; it != (*T1).neighbours.end(); it++)
	{
		if ((*it)->x == (*T2).x && (*it)->y == (*T2).y && (*it)->z == (*T2).z)
		{
			exists = 1;
			break;
		}
	}

	// ���� ������ ������ ��, ��� �2, �� �������, �� ������� �����
	if (!exists)
	{
		(*T1).neighbours.push_back(T2);
		(*T2).neighbours.push_back(T1);
		std::cout << "(" << (*T1).x << " ; " << (*T1).y << " ; " << (*T1).z << ") [" << (*T1).edge << "] and (";
		std::cout << (*T2).x << " ; " << (*T2).y << " ; " << (*T2).z << ") [" << (*T2).edge << "]";
		std::cout << " are neighbours NOW." << std::endl;
	}
	else
	{
		std::cout << "(" << (*T1).x << " ; " << (*T1).y << " ; " << (*T1).z << ") [" << (*T1).edge << "] and (";
		std::cout << (*T2).x << " ; " << (*T2).y << " ; " << (*T2).z << ") [" << (*T2).edge << "]";
		std::cout << " are neighbours ALREADY." << std::endl;
	}
}

void CRoom::RemoveNode(std::vector<GNode>::iterator &it)
{
	std::cout << "> Removing node..." << endl;

	it->neighbours.clear();

	std::vector<GNode>::iterator net_iterator = Network.begin();
	for (; net_iterator != Network.end(); net_iterator++)
	{
		GNode &cur_node = *net_iterator;
		std::vector<GNode *>::iterator neighbour_iterator = cur_node.neighbours.begin();
		std::vector<GNode *> new_neighbours;
		for (; neighbour_iterator != cur_node.neighbours.end(); neighbour_iterator++)
		{
			if ((*neighbour_iterator)->x != it->x || (*neighbour_iterator)->y != it->y || (*neighbour_iterator)->z != it->z)
			{
				if((*neighbour_iterator)->weight >= 0)
					new_neighbours.push_back(*neighbour_iterator);
			}				
		}
		cur_node.neighbours.swap(new_neighbours);
	}

	std::cout << "> Neighbours cleared." << endl;

	it->weight = -1;

	std::cout << "> Node removed." << endl;
}

void CRoom::NetworkCheck()
{
	std::vector<GNode>::iterator net_iterator = Network.begin();
	std::vector<GNode> newNet;
	for (; net_iterator != Network.end(); net_iterator++)
	{
		// �������� �������� ������� �� ��������� ������ newNet
		if ((*net_iterator).weight >= 0)
			newNet.push_back(*net_iterator);
	}


	std::vector<GNode>::iterator newNet_iterator = newNet.begin();
	net_iterator = Network.begin();
	for (; newNet_iterator != newNet.end(); newNet_iterator++)
	{
		std::vector<GNode *>::iterator net_neighbour = net_iterator->neighbours.begin();
		for (; net_neighbour != net_iterator->neighbours.end(); net_neighbour++)
		{
			std::vector<GNode>::iterator newNet_iterator2 = newNet.begin();
			for (; newNet_iterator2 != newNet.end(); newNet_iterator2++)
			{
				if ((*net_neighbour)->x == newNet_iterator2->x && (*net_neighbour)->y == newNet_iterator2->y
					&& (*net_neighbour)->z == newNet_iterator2->z)
					LinkNeighbours(&(*newNet_iterator2), &(*newNet_iterator));
			}
		}
		net_iterator++;
	}
	Network.swap(newNet);
}

void CRoom::n_train()
{
	// ���������� ����� � ������� ����� �������
	GenerateGrid();
	// ���������� ������� ����������
	GenerateMatrix();
	ShowMatrix();
	
	// �������� ���������� ��������
	
	// --- �������� ��������� ------------------------------------------------------------------------------------------------/
	// ������ �������� ���������� ����������� ������� ����� ����� ���������-������� �� ������� �������� Network.
	// �������� �������� �� ������� �� ��������, ������� �� ��� �������. ��� ������� �������� ������� �����������
	// ��������� ������-����, ������������ ��� BMI (Best Matching Input). ����� ����� �������� �������� �� ���� ��������
	// �������� �������� �������� �������, ����� ��������� �� ������� "�������������" �� ������ ������.
	// ������� "�������������":
	// <��� �������> (0 - ������� ������, 1 - ������� ������, 1 - "�������/�������/..." ������)
	// + 0.5 �� �������� � BMI
	// + 1 �� ������� ������-�����
	// = 0, ���� ���������� �� BMI ������, ��� � �������� �������
	// ������-����� �������� ������� ����������� ��������-�����������, ���� ����� ���������� "�������������", � ������������
	// ��� BMU (Best Matching Unit). ������� ������ "���������" ��������-�����������, ���������� ��� ��� �� 1. ����� �������
	// ������-���������� ���������� ������ �������-����� � �������� ������ �������� ��������.
	// ���� BMU �������� �� ������� (���������� ��������� �������� � ���������� "��������������"), �� ������� ������ ��������
	// �� �����. ���������� ������� � ����������.
	// ����� ������� ������� ����������� ������ �����. ������ ����� ���������� ����������� ������� �� ������������ �����.
	// �������� ���������������, ����� �� ���� ������ ����� �� ��������� � ���� �������� �������.
	// -----------------------------------------------------------------------------------------------------------------------/

	int epoch = 1; // ����� ������� �����
	int N_epochs = 30; // ������������ ���������� ����
	int cng = 1; // ������� ��������� � ���� (���� ��������� ��������)

	std::cout << "Training starts." << endl;

	//AddNode(GNode(1, 1, 0));

	// �������� �������� ���� �� ����� ��������� ������������ ���-�� ���� � ���� ���������� ���������
	while (epoch <= N_epochs || cng != 0)
	{
		if (cng == 0)
			break;
		std::cout << "EPOCH #" << epoch << endl;
		cng = 0;

		std::vector<GNode>::iterator net_iterator = Network.begin() + n; // �������� � ������� ��������, ��������� �������		
		for (; net_iterator != Network.end(); )
		{
			GNode &cur_node = *net_iterator;

			if (cur_node.x == 2 && cur_node.y == 1 && cur_node.z == 0)
			{
				cout << endl;
			}

			if (cur_node.weight < 0)
			{
				net_iterator++;
				continue;
			}
			if (cur_node.neighbours.size() == 0)
			{
				cur_node.weight = -1;
				cng++;
				net_iterator++;
				continue;
			}
			if (cur_node.neighbours.size() == 1)
			{
				std::cout << "> Moving towards BMU..." << endl;
				cur_node.neighbours[0]->weight = 1;
				RemoveNode(net_iterator);
				net_iterator = Network.begin() + n;
				cng += 1;
				continue;
			}

			// �������� BMI
			GNode *BMI = nullptr;
			float min_len = std::numeric_limits<float>::infinity();
			int cnt = 0; // ������� ���������� ��������
			std::vector<GNode>::iterator input_iterator = Network.begin();
			for (int i = 0; i < n; i++) // �������� ������ �� ������� �������� � ������� ����������� ����������
			{
				std::cout << "> Evaluating distance to BMI..." << endl;
				GNode &cur_input = *input_iterator;

				// �������� GNode'� � CNode'�� ��� ������������� SLength
				// ������� ���������� ����� ������� �������� � ������
				float len = SLength(GNodeToCNode(cur_node), GNodeToCNode(cur_input));
				
				// ���� ������� ������ � ���� �� ����� "�����", �� ������ �� ���������� ����� ��������.
				// ��� �����, ����� ����������� ������ ����������������� ��� ������ BMI, �.�. ������ ���������, ���
				// ���� ����� ����������� BMI, �� �������� ������� ���������, �.�. ���������� �� ��� ���������.
				if (cur_node.edge == cur_input.edge)
					len -= 0.1f;
				
				if (len < min_len)
					min_len = len;

				input_iterator++;
			}
			input_iterator = Network.begin();
			// ������ �������� �� ������� �������� � �������� ���, �� �������� ���������� ����� min_len
			for (int i = 0; i < n; i++) // �������� ������ �� ������� �������� � ������� ����������� ����������
			{
				std::cout << "> Choosing BMI..." << endl;
				GNode &cur_input = *input_iterator;

				// �������� GNode'� � CNode'�� ��� ������������� SLength
				// ������� ���������� ����� ������� �������� � ������
				float len = SLength(GNodeToCNode(cur_node), GNodeToCNode(cur_input));
				// ���� ������� ������ � ���� �� ����� "�����", �� ������ �� ���������� ����� ��������.
				if (cur_node.edge == cur_input.edge)
					len -= 0.1f;
				if (len == min_len)
				{
					cnt++;
					BMI = &(*input_iterator);
				}

				input_iterator++;
			}
			// ���� ���������� ������ �� ���� (cnt != 1)
			if (cnt != 1)
			{
				// ���� � ������� ���� �����-����, �� ��� �� ����� �������, ����� - ���������
				int f = 0; // ���� �������-������
				std::vector<GNode *>::const_iterator n_it = cur_node.neighbours.begin();
				for (; n_it != cur_node.neighbours.end(); n_it++)
				{
					std::vector<GNode>::const_iterator nn_it = Network.begin();
					for (; nn_it != Network.begin() + n; nn_it++)
					{
						if ((*n_it)->x == nn_it->x && (*n_it)->y == nn_it->y && (*n_it)->z == nn_it->z)
						{
							f = 1;
							break;
						}
					}

					if (f)
						break;
				}

				if (f)
				{
					std::cout << "> There are more than one BMI!" << endl;
					BMI = nullptr;
					net_iterator++;
					continue;
				}
				
			}

			// �� ������ ������ ���������, �� ����� �� BMI "����"
			if (BMI != nullptr)
			{
				// ���� ����� ����� ����, �� ��������� � ����
				if (cur_node.neighbours.size() == 1)
				{
					cur_node.neighbours[0]->weight = 1;
					RemoveNode(net_iterator);
					net_iterator = Network.begin() + n;
					cng += 1;
				}
				else
				{
					// �������� �� ������� � ������� ������������ �������� ������� "�������������"
					float max_influence = 0;
					cnt = 0;
					GNode *BMU = nullptr;
					std::vector<GNode *>::iterator neighbour_iterator = cur_node.neighbours.begin();
					for (; neighbour_iterator != cur_node.neighbours.end(); neighbour_iterator++)
					{
						std::cout << "> Evaluating influence function..." << endl;
						GNode &cur_neighbour = **neighbour_iterator;
						if (cur_neighbour.weight < 0)
							continue;

						float influence = 0;
						if (min_len > SLength(GNodeToCNode(cur_neighbour), GNodeToCNode(*BMI)))
							influence += 0.5; // + 0.5 �� �������� � BMI
						std::vector<GNode *>::iterator n2_iterator = cur_neighbour.neighbours.begin();
						for (; n2_iterator != cur_neighbour.neighbours.end(); n2_iterator++)
						{
							GNode &cur_n2 = **n2_iterator;
							// �� ������� ������, ������� ����� ��� 1, �� ���������� +1 � �������������.
							if (cur_n2.weight == 1)
								influence += 1;
						}

						if (influence > max_influence)
							max_influence = influence;
					}
					// ������ ��� ��� �������� � �������� BMU
					neighbour_iterator = cur_node.neighbours.begin();
					for (; neighbour_iterator != cur_node.neighbours.end(); neighbour_iterator++)
					{
						std::cout << "> Choosing BMU..." << endl;
						GNode &cur_neighbour = **neighbour_iterator;
						if (cur_neighbour.weight < 0)
							continue;
						float influence = 0;
						if (min_len > SLength(GNodeToCNode(cur_neighbour), GNodeToCNode(*BMI)))
							influence += 0.5; // + 0.5 �� �������� � BMI

						std::vector<GNode *>::iterator n2_iterator = cur_neighbour.neighbours.begin();
						for (; n2_iterator != cur_neighbour.neighbours.end(); n2_iterator++)
						{
							GNode &cur_n2 = **n2_iterator;
							// �� ������� ������, ������� ����� ��� 1, �� ���������� +1 � �������������.
							if (cur_n2.weight == 1)
								influence += 1;
						}

						if (influence == max_influence)
						{
							BMU = *neighbour_iterator;
							cnt++;
						}
					}


					// ������� ����� ���������� �� BMU � �� ������� ����� �� ���� ������
					float distSumNode = 0;
					float distSumBMU = 0;
					std::vector<GNode>::const_iterator nn_it = Network.begin();
					for (; nn_it != Network.begin() + n; nn_it++)
					{
						distSumNode += SLength(GNodeToCNode(cur_node), GNodeToCNode(*nn_it));
						distSumBMU += SLength(GNodeToCNode(*BMU), GNodeToCNode(*nn_it));
					}
					// ���� ����� ���������� �� BMU ������ ��� ����� ����� ���������� �� ������� �����,
					// �� ���� ����� �� �������, �.�. ��� ��� �� ������������ ����� �� ���� ������.
					if (distSumBMU >= distSumNode)
					{
						BMU = nullptr;
						net_iterator++;
						continue;
					}

					// ����� ���, ��� �������, ��������� �� �������-������ �, ���� ��� ����, ���������,
					// ������� � ��� �������� �������. ���� ����, �� �� ���������.
					int f = 0;
					neighbour_iterator = cur_node.neighbours.begin();
					for (; neighbour_iterator != cur_node.neighbours.end(); neighbour_iterator++)
					{
						std::vector<GNode>::iterator nn_it = Network.begin();
						for (; nn_it != Network.begin() + n; nn_it++)
						{
							if (*nn_it == **neighbour_iterator)
							{
								if (nn_it->neighbours.size() == 1)
								{
									f = 1;
									break;
								}
							}
						}
						if (f)
							break;
					}
					
					if (f)
					{
						BMU = nullptr;
						net_iterator++;
						continue;
					}

					// ������ ������������ ������-����������, "���������" � ����, ������ ������� ������
					std::cout << "> Moving towards BMU..." << endl;
					BMU->weight = 1;
					RemoveNode(net_iterator);
					net_iterator = Network.begin() + n;
					cng += 1;
				}			
			}
		}

		std::cout << "EPOCH #" << epoch << " ended. Number of changes: " << cng << endl;

		epoch++;
	}

	// ������� ���������� �������
	NetworkCheck();

	std::cout << endl << "Training's ended." << endl;
}
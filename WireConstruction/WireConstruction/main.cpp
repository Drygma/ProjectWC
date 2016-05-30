#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

#include "GNode.h"
#include "Room.h"

using namespace std;

int ImportFile(CRoom *room, string filename);
void ExportFile(CRoom *room, string filename);

int main(int argc, char* argv[])
{
	// Считывание параметров запуска
	std::string optFile;
	bool mute = false;

	if (argc < 3) { // Если параметров меньше, чем надо, то информируем пользователя
					// 3 параметра:
					//		1. Путь к исполняемому файлу
					//		2. и 3. сами параметры: -options "..."
		std::cout << "Usage: -options \"path to options file\" (--mute)\n";
		exit(0);
	}
	else { // Если предоставлено нужное кол-во параметров
		for (int i = 1; i < argc; i += 2) {
			if (i + 1 != argc) {
				if (!strcmp(argv[i], "-options")) {
					optFile = argv[i + 1];
				}
				else if (!strcmp(argv[i], "--mute"))
				{
					mute = true;
				}
				else {
					std::cout << "Not enough or invalid arguments, please try again.\n";
					std::cout << argv[i] << std::endl;
					exit(0);
				}
			}
		}
	}

	// Считываем настройки из файла
	std::string f_input;
	std::string f_output_nodes;
	std::string f_output_path;
	float I = 1;

	CRoom *rooms;
	int N = 0;

	std::fstream fs;
	fs.open(optFile, fstream::in);
	if (fs.is_open())
	{
		std::string line;
		
		// Считываем основные настройки
		getline(fs, line);
		if (!line.compare("[GENERAL]"))
		{
			while (line.compare("[/GENERAL]"))
			{
				if (!line.compare("[/GENERAL]"))
					break;

				getline(fs, line);
				if (line.size())
				{
					if (!line.substr(0, line.find_first_of("=", 0)).compare("input"))
					{
						f_input = line.substr(line.find_first_of("=", 0) + 1);
						std::cout << "Input file: " << f_input << std::endl;
					}
					else if (!line.substr(0, line.find_first_of("=", 0)).compare("output_nodes"))
					{
						f_output_nodes = line.substr(line.find_first_of("=", 0) + 1);
						std::cout << "Output 'nodes' file: " << f_output_nodes << std::endl;
					}
					else if (!line.substr(0, line.find_first_of("=", 0)).compare("output_path"))
					{
						f_output_path = line.substr(line.find_first_of("=", 0) + 1);
						std::cout << "Input 'path' file: " << f_output_path << std::endl;
					}
					else if (!line.substr(0, line.find_first_of("=", 0)).compare("i"))
					{
						I = atof(line.substr(line.find_first_of("=", 0) + 1).c_str());
						std::cout << "'I' parameter: " << I << std::endl;
					}
				}
			}
			if (!f_input.size() || !f_output_nodes.size() || !f_output_path.size())
			{
				std::cout << "Incomplete options file!\n";
				std::cout << optFile << std::endl;
				exit(0);
			}
		}
		else
		{
			std::cout << "Invalid options file!\n";
			std::cout << optFile << std::endl;
			exit(0);
		}

		// Считываем информацию о комнатах
		// Ищем входную точку
		while (line.compare("[ROOMS]"))
		{
			if (!line.compare("[ROOMS]"))
				break;
			getline(fs, line);
		}
		// Нашли входную точку
		// Считываем количество комнат
		getline(fs, line);
		if (!line.substr(0, line.find_first_of("=", 0)).compare("number_of_rooms"))
		{
			N = atoi(line.substr(line.find_first_of("=", 0) + 1).c_str());
			std::cout << "Number of rooms: " << N << std::endl;
		}
		else
		{
			std::cout << "Invalid options file! (check number of rooms)\n";
			std::cout << optFile << std::endl;
			exit(0);
		}

		// Инициализируем массив комнат
		rooms = new CRoom[N];

		// Считываем сами комнаты
		int n = 0;
		getline(fs, line);
		std::cout << "- Rooms" << std::endl;
		while (line.compare("[/ROOMS]"))
		{
			if (!line.compare("[/ROOMS]"))
				break;

			if (!line.compare("[ROOM]"))
			{
				std::cout << "--- Room #" << n + 1 << std::endl;
				float width = 0, length = 0, height = 0;
				while (line.compare("[/ROOM]"))
				{
					if (!line.compare("[/ROOM]"))
						break;

					getline(fs, line);
					if (line.size())
					{
						if (!line.substr(0, line.find_first_of("=", 0)).compare("width"))
						{
							width = atof(line.substr(line.find_first_of("=", 0) + 1).c_str());
							std::cout << "Width: " << width << std::endl;
						}
						else if (!line.substr(0, line.find_first_of("=", 0)).compare("length"))
						{
							length = atof(line.substr(line.find_first_of("=", 0) + 1).c_str());
							std::cout << "Length: " << length << std::endl;
						}
						else if (!line.substr(0, line.find_first_of("=", 0)).compare("height"))
						{
							height = atof(line.substr(line.find_first_of("=", 0) + 1).c_str());
							std::cout << "Height: " << height << std::endl;
						}
					}
				}
				if (width == 0 || length == 0 || height == 0)
				{
					std::cout << "Invalid options file! (check rooms information)\n";
					std::cout << optFile << std::endl;
					exit(0);
				}
				rooms[n] = CRoom(width, length, height, f_output_path);
				n++;
			}
			getline(fs, line);
		}

		if (n != N)
		{
			std::cout << "Invalid options file! (check 'number_of_rooms' and real number of rooms)\n";
			std::cout << optFile << std::endl;
			exit(0);
		}
	}
	else
	{
		std::cout << "Failed to open options file\n";
		std::cout << optFile << std::endl;
		exit(0);
	}
	fs.close();

	cout << endl << "Room Wire Construction v.0.7" << endl << endl;
	
	cout << ">> START" << endl;

	for (int i = 0; i < N; i++)
	{
		CRoom &room = rooms[i];
		if (&room != NULL)
		{
			if (ImportFile(&room, f_input))
			{
				std::cout << "Invalid input file\n";
				std::cout << f_input << std::endl;
				exit(0);
			}
			room.n_train();
			ExportFile(&room, f_output_nodes);
			room.findPath(I);
		}
		else
		{
			std::cout << "ERROR! One of rooms is NULL o_O\n";
			exit(0);
		}
	}

	cout << ">> FINISH" << endl;
	return 0;
}

int ImportFile(CRoom *room, string filename)
{
	int n = 0;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		float x = 0, y = 0, z = 0;
		while (file >> x >> y >> z)
		{
			n++;
			room->AddInput(GNode(x, y, z));
		}
		file.close();
	}
	else
		return -1;

	if (n == 0)
		return -1;
	else
		return 0;
}

void ExportFile(CRoom *room, string filename)
{
	fstream file;
	file.open(filename, fstream::out);
	file << "X Y Z" << endl;
	file << room->length << " " << room->width << " " << room->height << endl;
	file << room->n << " " << room->Network.size() << " " << 0 << endl;

	std::vector<GNode>::const_iterator it = room->Network.begin();
	for (; it != room->Network.end(); it++)
	{
		file << it->x << " " << it->y << " " << it->z << endl;
	}
	file.close();
	cout << "File saved." << endl;
}
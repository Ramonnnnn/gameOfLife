#include "input.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h>
#include <stdio_ext.h>

using namespace advcpp;

enum Shapes
{
	CROSS = 0,
	LINE
};

struct InputTask : public IRunnable
{
	InputTask(Input& _input)
		: m_input(_input) { }

	void Run()
	{
		int fdSender;
		size_t n;
		const size_t TEMP_BUFF_SIZE = 128;
		char *fifoSender = "../fifoSender";
		
		char readBuffSender[TEMP_BUFF_SIZE];
		/*fd_set active_fd_set;*/
		char commandSender[TEMP_BUFF_SIZE];
		snprintf(commandSender, TEMP_BUFF_SIZE, "gnome-terminal --geometry=40x20+100+200 --title MENU:, -t MENU: --command=\"./a.out\"");

		system(commandSender);

		mkfifo(fifoSender, 0666);
		fdSender = open(fifoSender, O_RDONLY);
		
		while(1)
		{
			__fpurge(stdin);
            __fpurge(stdout);
			n = read(fdSender, readBuffSender, TEMP_BUFF_SIZE);
			if(n < 0)
			{
				/* zlog */
			}
			enum Shapes kind;
			memcpy(&kind, readBuffSender, 4);
			
            //fsync(fdSender);
			n = read(fdSender, readBuffSender, TEMP_BUFF_SIZE);
			if(n < 0)
			{
				/* zlog */
			}
			int x;
			memcpy(&x, readBuffSender, 4);
			
            //fsync(fdSender);
			n = read(fdSender, readBuffSender, TEMP_BUFF_SIZE);
			if(n < 0)
			{
				/* zlog */
			}
			int y;
			memcpy(&y, readBuffSender, 4);

			std::list<std::tr1::shared_ptr<Coordinate> > coordinates;
			
			if(kind == CROSS)
			{
				std::tr1::shared_ptr<Coordinate> spCoord(new Coordinate(x, y, true));
				coordinates.push_back(spCoord);
				std::tr1::shared_ptr<Coordinate> spCoord1(new Coordinate(x, y + 1, true));
				coordinates.push_back(spCoord1);
				std::tr1::shared_ptr<Coordinate> spCoord2(new Coordinate(x, y + 2, true));
				coordinates.push_back(spCoord2);
				std::tr1::shared_ptr<Coordinate> spCoord3(new Coordinate(x - 1, y + 1, true));
				coordinates.push_back(spCoord3);
				std::tr1::shared_ptr<Coordinate> spCoord4(new Coordinate(x + 1, y + 1, true));
				coordinates.push_back(spCoord4);
			}
			if(kind == LINE)
			{
				std::tr1::shared_ptr<Coordinate> spCoord5(new Coordinate(x, y, true));
				coordinates.push_back(spCoord5);
				std::tr1::shared_ptr<Coordinate> spCoord6(new Coordinate(x, y + 1, true));
				coordinates.push_back(spCoord6);
				std::tr1::shared_ptr<Coordinate> spCoord7(new Coordinate(x, y + 2, true));
				coordinates.push_back(spCoord7);
				std::tr1::shared_ptr<Coordinate> spCoord8(new Coordinate(x, y + 3, true));
				coordinates.push_back(spCoord8);
				std::tr1::shared_ptr<Coordinate> spCoord9(new Coordinate(x, y + 4, true));
				coordinates.push_back(spCoord9);
				std::tr1::shared_ptr<Coordinate> spCoord10(new Coordinate(x, y + 5, true));
				coordinates.push_back(spCoord10);
				std::tr1::shared_ptr<Coordinate> spCoord11(new Coordinate(x, y + 6, true));
				coordinates.push_back(spCoord11);
			}

			m_input.m_board.UpdateCoordinates(coordinates);
		}
	}

	Input& m_input;
};


Input::Input(Board& _board)
	: m_board(_board)
{
}


void Input::Start()
{
	std::tr1::shared_ptr<IRunnable> spInputRunnable(new InputTask(*this));
	std::tr1::shared_ptr<Thread> threadPtr(new Thread(spInputRunnable));
	m_threadPtr = threadPtr;
}


void Input::WaitForUserQuit()
{
	m_threadPtr->Join();
}






















///////////////////////////////////////////////////////////////////////////////////////////////
			// std::cout << "\n\nPlease insert your choice: \n\n"
			// "1. Inhabitate a CROSS colony \n"
			// "2. Inhabitate a SINGLE LINE colony \n"
			// "3. exit\n\n"
			// << '\n';
			// int choice;
			// std::cin >> choice;
			// int x, y;
			// enum Shapes kind;

			// switch(choice)
			// {
			// 	case 1 :
			// 		std::cout << "insert x coordinate:" << '\n';
			// 		std::cin >> x;
			// 		std::cout << "insert y coordinate:" << '\n';
			// 		std::cin >> y;
			// 		kind = CROSS;
			// 	break;
			// 	case 2 :
			// 		std::cout << "insert x coordinate:" << '\n';
			// 		std::cin >> x;
			// 		std::cout << "insert y coordinate:" << '\n';
			// 		std::cin >> y;
			// 		kind = LINE;
			// 	break;
			// }



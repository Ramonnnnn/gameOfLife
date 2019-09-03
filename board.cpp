#include "board.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

Board::Board()
	: m_semProduce(1), m_semConsume(0)
{
	m_board = new char*[BOARDSIZE];
	for(size_t i = 0; i < BOARDSIZE; ++i)
	{
		m_board[i] = new char[BOARDSIZE];
	}

	for(size_t i = 0; i < BOARDSIZE; ++i)
	{
		for(size_t j = 0; j < BOARDSIZE; ++j)
		{
			m_board[i][j] = 'O';
		}
	}
}


Board::~Board()
{
	for(size_t i = 0; i < BOARDSIZE; ++i)
	{
		delete [] m_board[i];
	}

	delete [] m_board;
}


void Board::UpdateCoordinates(const BoardUpdater& _boardUpdater)
{
	m_semProduce.Wait();
	m_mutex.Lock();

	std::list<std::tr1::shared_ptr<Coordinate> > newCoordinates = _boardUpdater.CalculateNewCoordinates(const_cast<const char**>(m_board), BOARDSIZE);
	MarkCoordsOnBoard(newCoordinates);

	m_mutex.Unlock();
	m_semConsume.Post();
}


void Board::UpdateCoordinates(const std::list<std::tr1::shared_ptr<Coordinate> >& _coordinates)
{
	m_semProduce.Wait();
	m_mutex.Lock();

	MarkCoordsOnBoard(_coordinates);

	m_mutex.Unlock();
	m_semConsume.Post();
}


void Board::MarkCoordsOnBoard(const std::list<std::tr1::shared_ptr<Coordinate> >& _coordinates)
{
	for(std::list<std::tr1::shared_ptr<Coordinate> >::const_iterator it = _coordinates.begin(); it != _coordinates.end(); ++it)
	{
		size_t x = (*it)->m_x;
		size_t y = (*it)->m_y;
		if((x >= 0) && (x < BOARDSIZE) && (y >= 0) && (y < BOARDSIZE))
		{
			if((*it)->m_mark == true)
			{
				m_board[x][y] = 'X';
			}
			else //if((*it)->m_mark == false)
			{
				m_board[x][y] = 'O';
			}
		}
	}
}


void Board::DrawUpdatedBoard()
{
	m_semConsume.Wait();
	m_mutex.Lock();
	system("clear");
	for(size_t i = 0; i < BOARDSIZE; ++i)
	{
		for(size_t j = 0; j < BOARDSIZE; ++j)
		{
			if(m_board[i][j] == 'X')
			{
				printf(ANSI_COLOR_RED     "%c"     ANSI_COLOR_RESET, m_board[i][j]);
			}
			else
			{
				printf(ANSI_COLOR_CYAN     "%c"     ANSI_COLOR_RESET, m_board[i][j]);	
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n\n\n";
	static int i = 0;
	std::cout << i << '\n';
	++i;

	m_mutex.Unlock();
	m_semProduce.Post();
}
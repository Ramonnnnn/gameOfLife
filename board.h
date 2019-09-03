#ifndef __BOARD_H__
#define __BOARD_H__
#include "thread.h"
#include "coordinate.h"
#include <list>
#include <cstddef>


struct BoardUpdater
{
	virtual std::list<std::tr1::shared_ptr<Coordinate> > CalculateNewCoordinates(const char** _currentBoard, size_t _boardSize) const = 0;
};


class Board
{
	static const size_t BOARDSIZE = 30;

public:
	Board();
	~Board();
	void UpdateCoordinates(const BoardUpdater& _boardUpdater);
	void UpdateCoordinates(const std::list<std::tr1::shared_ptr<Coordinate> >& _coordinates);
	void DrawUpdatedBoard();

private:
	void MarkCoordsOnBoard(const std::list<std::tr1::shared_ptr<Coordinate> >& _coordinates);

	advcpp::Semaphore m_semProduce;
	advcpp::Semaphore m_semConsume;
	advcpp::Mutex m_mutex;
	//std::list<std::tr1::shared_ptr<Coordinate> > m_coordinates;
	char** m_board;
};

#endif//__BOARD_H__
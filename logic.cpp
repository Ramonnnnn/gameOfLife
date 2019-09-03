#include "logic.h"
#include <unistd.h>

using namespace advcpp;


struct NewGenerationUpdater : public BoardUpdater
{
	virtual std::list<std::tr1::shared_ptr<Coordinate> > CalculateNewCoordinates(const char** _currentBoard, size_t _boardSize) const
	{
		std::list<std::tr1::shared_ptr<Coordinate> > newCoordinates;
		CalculateBoard(_currentBoard, _boardSize, newCoordinates);
		return newCoordinates;
	}

	void CalculateBoard(const char** _board, size_t _boardSize, std::list<std::tr1::shared_ptr<Coordinate> >& _coordsList) const
	{
		for(size_t i = 0; i < _boardSize; ++i)
		{
			for(size_t j = 0; j < _boardSize; ++j)
			{
				size_t numOfNeighbors = CountNeighbors(_board, i, j, _boardSize);
				if(_board[i][j] == 'X')
				{
					if(numOfNeighbors < 2)
					{
						std::tr1::shared_ptr<Coordinate> spCoord(new Coordinate(i, j, false));
						_coordsList.push_back(spCoord);
					}
					if(numOfNeighbors > 3)
					{
						std::tr1::shared_ptr<Coordinate> spCoord(new Coordinate(i, j, false));
						_coordsList.push_back(spCoord);
					}
				}
				if(_board[i][j] == 'O')
				{
					if(numOfNeighbors == 3)
					{
						std::tr1::shared_ptr<Coordinate> spCoord(new Coordinate(i, j, true));
						_coordsList.push_back(spCoord);
					}	
				}
			}
		}
	}

	size_t CountNeighbors(const char** _board, int _i, int _j, int _sizeOfMatrix) const
	{
		int r = _i - 1;
		int c = _j - 1;
		size_t counter = 0;
		int rowLimit = r + 2;
		int colLimit = c + 2;
		for(; r <= (rowLimit); ++r)
		{
			for(; c <= (colLimit); ++c)
			{
				if((r == _i) && (c == _j))
				{
					continue;
				}
				if((r >= 0) && (r < _sizeOfMatrix) && (c >= 0) && (c < _sizeOfMatrix))
				{
					if(_board[r][c] == 'X')
					{
						++counter;
					}
				}
			}
			c = _j - 1;
		}

		return counter;
	}

};


struct LogicTask : public IRunnable
{
	LogicTask(Logic& _logic)
		: m_logic(_logic) { }

	void Run()
	{
		NewGenerationUpdater genUpdater;

		while(1)
		{
			sleep(1);
			m_logic.m_board.UpdateCoordinates(genUpdater);
		}
	}

	Logic& m_logic;
};


Logic::Logic(Board& _board)
	: m_board(_board)
{
}


void Logic::Start()
{
	std::tr1::shared_ptr<IRunnable> spLogicRunnable(new LogicTask(*this));
	std::tr1::shared_ptr<Thread> threadPtr(new Thread(spLogicRunnable));
	m_threadPtr = threadPtr;
}

#ifndef __INPUT_H__
#define __INPUT_H__

#include "board.h"
#include <list>
#include <cstddef>
#include <tr1/memory>


class Input
{
	friend struct InputTask;

public:
	Input(Board& _board);
	void Start();
	void WaitForUserQuit();

	// std::list<std::tr1::shared_ptr<Coordinate> >& GetCoordinateSet() {return m_coordinates;}
	// void LockMutex() {m_mutex.Lock();}
	// void UnlockMutex() {m_mutex.Unlock();}

private:
	std::tr1::shared_ptr<advcpp::Thread> m_threadPtr;
	// advcpp::Mutex m_mutex;
	Board& m_board;
};


#endif//__INPUT_H__
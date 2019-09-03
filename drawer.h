#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "board.h"
#include <tr1/memory>


class Drawer
{
	friend struct DrawerTask;

public:
	Drawer(Board& _board);
	// ~Drawer();
	void Start();

	// void ProducerWait() {m_semProduce.Wait();}
	// void ConsumerPost() {m_semConsume.Post();}
	// void LockMutex() {m_mutex.Lock();}
	// void UnlockMutex() {m_mutex.Unlock();}
	// const char** GetBoard() {return (const char**)m_board;}
	// size_t GetBoardSize() {return N;}
	// std::list<std::tr1::shared_ptr<Coordinate> >& GetCoordinateSet() {return m_coordinates;}

private:
	//void DrawGeneration();
	Board& m_board;
	std::tr1::shared_ptr<advcpp::Thread> m_threadPtr;
};


#endif//__DRAWER_H__
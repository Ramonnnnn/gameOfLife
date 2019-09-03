#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "board.h"
#include <tr1/memory>

class Logic
{
	friend struct LogicTask;

public:
	Logic(Board& _board);
	void Start();

private:
	Board& m_board;
	std::tr1::shared_ptr<advcpp::Thread> m_threadPtr;
};

#endif//__LOGIC_H__
#include "drawer.h"

using namespace advcpp;

struct DrawerTask : public IRunnable
{
	DrawerTask(Drawer& _drawer)
		: m_drawer(_drawer) { }
	void Run()
	{
		while(1)
		{
			m_drawer.m_board.DrawUpdatedBoard();
		}
	}
	Drawer& m_drawer;
};


Drawer::Drawer(Board& _board)
	: m_board(_board)
{
}


void Drawer::Start()
{
	std::tr1::shared_ptr<IRunnable> spDrawerRunnable(new DrawerTask(*this));
	std::tr1::shared_ptr<advcpp::Thread> threadPtr(new Thread(spDrawerRunnable));
	m_threadPtr = threadPtr;
}


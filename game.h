#ifndef __GAME_H__
#define __GAME_H__

#include "logic.h"
#include "input.h"
#include "drawer.h"

class GameOfLife
{
public:
	GameOfLife();
	void Start();
	
private:
	Board m_board;
	Input m_input;
	Drawer m_drawer;
	Logic m_logic;
};


#endif//__GAME_H__
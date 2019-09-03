#include "game.h"


GameOfLife::GameOfLife()
	: m_input(m_board), m_drawer(m_board), m_logic(m_board)
{
}


void GameOfLife::Start()
{
	m_drawer.Start();
	m_logic.Start();
	m_input.Start();

	m_input.WaitForUserQuit();
}
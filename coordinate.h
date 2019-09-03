#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <cstddef>

struct Coordinate
{
	Coordinate(size_t _x, size_t _y, bool _mark = false)
		: m_x(_x), m_y(_y), m_mark(_mark) { }
	size_t m_x;
	size_t m_y;
	bool m_mark;
};

#endif//__COORDINATE_H__
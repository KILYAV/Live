#pragma once
#include <vector>
#include "point.h"
#include "setting.h"

class Board :
	virtual Setting,
	std::vector<Cell>
{
protected:
	explicit Board();
	Cell Fill(const Cell cell);
	Cell Set(const Point point, const Cell cell);
	Cell Reset(const Point point, const Cell cell);
	Cell Get(const Point point) const;

	void Fill(const std::vector<Cell>& board);
	bool Empty(const std::vector<Cell>& board);
	bool Equal(const std::vector<Cell>& board);
	std::vector<Cell> Next();
private:
	unsigned Test(const Point point);
};
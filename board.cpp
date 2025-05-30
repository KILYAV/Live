#include "board.h"
#include <numeric>

Board::Board() :
	Setting{},
	std::vector<Cell>{ Setting::size * Setting::size, Cell::dead }
{}
Cell Board::Fill(const Cell cell) {
	for (auto& cell_ : *this) {
		cell_ = cell;
	}
	return cell;
}
Cell Board::Set(const Point point, const Cell cell) {
	return (*this)[point.Y() * Setting::size + point.X()] = cell;
}
Cell Board::Reset(const Point point, const Cell cell) {
	if (Cell::dead == cell) {
		return Set(point, Cell::live);
	}
	else {
		return Set(point, Cell::dead);
	}
}
Cell Board::Get(const Point point) const {
	return (*this)[point.Y() * Setting::size + point.X()];
}
void Board::Fill(const std::vector<Cell>& board) {
	static_cast<std::vector<Cell>&>(*this) = board;
}
bool Board::Empty(const std::vector<Cell>& board) {
	for (const auto cell : board) {
		if (Cell::live == cell)
			return false;
	}
	return true;
}
bool Board::Equal(const std::vector<Cell>& board) {
	return static_cast<std::vector<Cell>&>(*this) == board;
}
std::vector<Cell> Board::Next() {
	std::vector<Cell> next{ Setting::size * Setting::size, Cell::dead };
	for (unsigned x = 0; x < Setting::size; ++x) {
		for (unsigned y = 0; y < Setting::size; ++y) {
			const Point point{ x, y };
			unsigned count{
				Test(point.Up()) + Test(point.Up().Right()) +
				Test(point.Right()) + Test(point.Right().Down()) +
				Test(point.Down()) + Test(point.Down().Left()) +
				Test(point.Left()) + Test(point.Left().Up())
			};
			if (Cell::dead == Get(point)) {
				if (3 == count) {
					next[y * Setting::size + x] = Cell::live;
				}
			}
			else {
				if (1 < count && count < 4) {
					next[y * Setting::size + x] = Cell::live;
				}
			}
		}
	}
	return next;
}
unsigned Board::Test(const Point point) {
	if (point.IsNotNan(Setting::size)) {
		if (Cell::live == Get(point))
			return 1;
	}
	return 0;
}

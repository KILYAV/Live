#include "Point.h"

unsigned Point::X() const {
	return x;
};
unsigned Point::Y() const {
	return y;
};
bool Point::IsNan() const {
	return -1 == x || -1 == y;
}
bool Point::IsNan(const unsigned max) const {
	return x >= max || y >= max;
}
bool Point::IsNotNan() const {
	return false == IsNan();
}
bool Point::IsNotNan(const unsigned max) const {
	return false == IsNan(max);
}
Point& Point::Up() {
	if (this->IsNan() || (y - 1 == -1))
		x = -1, y = -1;
	else
		y -= 1;
	return *this;
}
Point& Point::Down() {
	if (this->IsNan() || (y + 1 == -1))
		x = -1, y = -1;
	else
		y += 1;
	return *this;
}
Point& Point::Left() {
	if (this->IsNan() || (x - 1 == -1))
		x = -1, y = -1;
	else
		x -= 1;
	return *this;
}
Point& Point::Right() {
	if (this->IsNan() || (x + 1 == -1))
		x = -1, y = -1;
	else
		x += 1;
	return *this;
}
Point Point::Up() const {
	if (this->IsNan() || (y - 1 == -1))
		return Point{};
	else
		return Point{ x, y - 1 };
}
Point Point::Down() const {
	if (this->IsNan() || (y + 1 == -1))
		return Point{};
	else
		return Point{ x, y + 1 };
}
Point Point::Left() const {
	if (this->IsNan() || (x - 1 == -1))
		return Point{};
	else
		return Point{ x - 1, y };
}
Point Point::Right() const {
	if (this->IsNan() || (x + 1 == -1))
		return Point{};
	else
		return Point{ x + 1, y };
}
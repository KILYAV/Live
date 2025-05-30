#pragma once

enum class Cell {
	dead,
	live
};
class Point {
private:
	unsigned x;
	unsigned y;

public:
	explicit Point(
		unsigned new_x = -1,
		unsigned new_y = -1
	) :
		x{ new_x },
		y{ new_y }
	{}

	unsigned X() const;
	unsigned Y() const;

	bool IsNan() const;
	bool IsNan(const unsigned max) const;

	bool IsNotNan() const;
	bool IsNotNan(const unsigned max) const;

	Point& Up();
	Point& Down();
	Point& Left();
	Point& Right();

	Point Up() const;
	Point Down() const;
	Point Left() const;
	Point Right() const;
};
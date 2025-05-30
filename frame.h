#pragma once
#include <SDL.h>
#include <vector>
#include "point.h"
#include "setting.h"
#include <memory>

class BMP {
public:
	const std::unique_ptr<char[]> ptr;
	const int size;
private:
	struct Size {
		const int size;
		const int width;
		const unsigned image;
		const int bmp;
	};
public:
	BMP(const Size size);
	BMP& Invert();
	char* get() { return ptr.get(); };
	static Size Init(const int size);
};
class Frame :
	virtual Setting
{
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture* live;
	SDL_Texture* dead;
protected:
	Frame(BMP bmp);
	Frame& Fill();
	Frame& Fill(const std::vector<Cell>& board);
	Frame& Title(const char* title);

	Cell Set(const Point point, const Cell cell);
	Cell Reset(const Point point, const Cell cell);

	int Exit();
};
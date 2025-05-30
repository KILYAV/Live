#include <Windows.h>
#include "frame.h"

constexpr int biPlanes = 1;
constexpr int biBitCount = 8 * sizeof(RGBTRIPLE);
BMP::BMP(const Size size) :
	ptr{ std::invoke([&]() {
		char* ptr{ new char[size.bmp] };
		BITMAPFILEHEADER header{ 0x4d42, size.bmp, NULL, NULL, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) };
		std::memcpy(ptr, &header, sizeof(BITMAPFILEHEADER));

		BITMAPINFO info{ BITMAPINFOHEADER{ sizeof(BITMAPINFO), size.size, size.size, biPlanes,
			biBitCount, BI_RGB, size.image, NULL, NULL, NULL, NULL }, NULL };
		std::memcpy(ptr + sizeof(BITMAPFILEHEADER), &info, sizeof(BITMAPINFO));

		std::memset(ptr + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO), 0, size.image);
		const int sizeX = (size.size - 2) * sizeof(RGBTRIPLE);
		const int sizeY = size.size - 1;
		for (int y = 1; y < sizeY; ++y) {
			std::memset(ptr + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + y * size.width + sizeof(RGBTRIPLE),
				~0, sizeX);
		}
		return ptr;
		}) },
	size{ size.bmp }
{}
BMP& BMP::Invert() {
	for (int index = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO); index < size; ++index) {
		ptr[index] = ~ptr[index];
	}
	return *this;
}
BMP::Size BMP::Init(const int size) {
	const int y = size;
	const int x = (size * sizeof(RGBTRIPLE) + sizeof(RGBTRIPLE)) >> 2 << 2;
	const int bmp = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + x * y;
	return { y, x, static_cast<unsigned>(y) * x, bmp };
}

Frame::Frame(BMP bmp) :
	Setting{},
	win{ SDL_CreateWindow(
		"LCM-LIFE/DEAD | RCM-START/STOP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size * scale, size * scale, SDL_WINDOW_SHOWN) },
	ren{ SDL_CreateRenderer(win, NULL, SDL_RENDERER_ACCELERATED) },
	live{ SDL_CreateTextureFromSurface(ren, SDL_LoadBMP_RW(SDL_RWFromMem(bmp.get(), bmp.size), 1))},
	dead{ SDL_CreateTextureFromSurface(ren, SDL_LoadBMP_RW(SDL_RWFromMem(bmp.Invert().get(), bmp.size), 1))}
{
	Fill();
}
Frame& Frame::Fill() {
	SDL_RenderClear(ren);
	for (auto x = 0; x < size; ++x) {
		for (auto y = 0; y < size; ++y) {
			SDL_Rect rect{ x * scale, y * scale, scale, scale };
			SDL_RenderCopy(ren, dead, NULL, &rect);
		}
	}
	SDL_RenderPresent(ren);
	return *this;
}
Frame& Frame::Fill(const std::vector<Cell>& board) {
	SDL_RenderClear(ren);
	for (unsigned x = 0; x < size; ++x) {
		for (unsigned y = 0; y < size; ++y) {
			SDL_Rect rect{ x * scale, y * scale, scale, scale };
			if (Cell::dead == board[x + y * size]) {
				SDL_RenderCopy(ren, dead, NULL, &rect);
			}
			else {
				SDL_RenderCopy(ren, live, NULL, &rect);
			}
		}
	}
	SDL_RenderPresent(ren);
	return *this;
}
Frame& Frame::Title(const char* title) {
	SDL_SetWindowTitle(win, title);
	return *this;
}
Cell Frame::Set(const Point point, const Cell cell) {
	SDL_Rect rect{ point.X() * scale, point.Y() * scale, scale, scale };
	if (Cell::dead == cell) {
		SDL_RenderCopy(ren, dead, NULL, &rect);
	}
	else {
		SDL_RenderCopy(ren, live, NULL, &rect);
	}
	SDL_RenderPresent(ren);
	return cell;
}
Cell Frame::Reset(const Point point, const Cell cell) {
	if (Cell::dead == cell) {
		return Set(point, Cell::live);
	}
	else {
		return Set(point, Cell::dead);
	}
}
int Frame::Exit() {
	SDL_DestroyTexture(dead);
	SDL_DestroyTexture(live);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
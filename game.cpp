#include "game.h"

Game::Game(Setting::Data data) :
	Setting{ data },
	Board{},
	Frame{ BMP{ BMP::Init(data.scale) } },
	timer{ 0 },
	status{ Status::play }
{}
Game::Chain Game::Play() {
	SDL_Event event;
	while (true) {
		if (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type) {
				break;
			}
			if (SDL_MOUSEBUTTONDOWN == event.type) {
				if (Status::over == status) {
					Board::Fill(Cell::dead);
					Frame::Fill();
					Title("LCM-LIFE/DEAD RCM-START/STOP");
					status = Status::play;
					continue;
				}
				if (SDL_BUTTON_LEFT == event.button.button) {
					Point point{ event.button.x / scale, event.button.y / scale };
					Board::Set(point,Frame::Reset(point,Get(point)));
				}
				if (SDL_BUTTON_RIGHT == event.button.button) {
					if (timer) {
						RemoveTimer();
					}
					else {
						timer = SDL_AddTimer(delay, StaticTimeBack, this);
					}
				}
			}
		}
	}
	return *this;
}
unsigned Game::StaticTimeBack(unsigned period, void* game) {
	static_cast<Game*>(game)->TimeBack();
	return period;
}
void Game::TimeBack() {
	auto board{ Next() };
	Frame::Fill(board);
	if (Empty(board) || Equal(board)) {
		RemoveTimer();
		Title("GAME OVER | LCM/RCM - START");
		status = Status::over;
	}
	Board::Fill(board);
}
void Game::RemoveTimer() {
	SDL_RemoveTimer(timer);
	timer = 0;
}
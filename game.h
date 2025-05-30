#pragma once
#include "point.h"
#include "setting.h"
#include "board.h"
#include "frame.h"

class Game :
	virtual Setting,
	Board,
	Frame
{
private:
	SDL_TimerID timer;
	enum class Status {
		play,
		over
	};
	Status status;
	static unsigned StaticTimeBack(unsigned,void*);
	class Chain {
	private:
		Game& game;
	public:
		Chain(Game& game) :
			game{ game }
		{}
		int Exit() {
			return game.Exit();
		}
	};
private:
	void TimeBack();
	void RemoveTimer();
public:
	Game(Setting::Data data);
	Chain Play();
};
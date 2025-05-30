#include <iostream>
#include "game.h"

int main(int argc, char* argv[])
{
	return Game{ Setting::Init(argc, argv) }.Play().Exit();
}
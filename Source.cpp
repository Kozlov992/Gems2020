#include "Game.hpp"
#include <iostream>
int main() {
	std::shared_ptr<Game> Sesion = std::make_shared<Game>();
	Sesion->Launch();
	return 0;
}
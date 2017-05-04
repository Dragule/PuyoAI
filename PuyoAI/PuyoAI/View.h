#pragma once

#include "Couple.h"
#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

struct ASCII_View
{
	void draw(const Game& t);
};

struct Graphical_View
{
	sf::RenderWindow window;
	sf::Font font;
	static const sf::Color BACKGROUND;
	Graphical_View();
	void draw(const Game& g);
};
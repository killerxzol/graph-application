#ifndef DRAW_H
#define DRAW_H

#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include <vector>
#include <string>

class Draw
{
public:

	void virtual show(sf::RenderWindow& window) = 0;

};

#endif
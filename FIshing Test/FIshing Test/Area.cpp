
#include "Area.h"
#include <iostream>

Area::Area()
{
}

Area::~Area()
{
}

void Area::setupArea(sf::Vector2f t_pos)
{
	// Fishing Area
	m_body.setFillColor(sf::Color::Blue);
	m_body.setPosition(t_pos);
	m_body.setSize(m_size);
}
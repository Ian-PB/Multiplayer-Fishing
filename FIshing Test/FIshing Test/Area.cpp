
#include "Area.h"
#include <iostream>

Area::Area()
{
}

Area::~Area()
{
}

void Area::setupArea()
{
	// Fishing Area
	m_body.setFillColor(sf::Color::Blue);
	m_body.setPosition(m_location);
	m_body.setSize(m_size);
}
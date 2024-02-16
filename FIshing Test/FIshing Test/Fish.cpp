
#include "Fish.h"
#include <iostream>

Fish::Fish()
{
}

Fish::~Fish()
{
}

// Object (Fish) Functions
void Fish::setupFish()
{
	// Fish
	m_body.setFillColor(sf::Color::Red);
	m_body.setPosition(m_location);
	m_body.setSize(m_size);
}
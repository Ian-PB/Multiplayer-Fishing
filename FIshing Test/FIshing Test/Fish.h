/// <summary>
/// author Ian Perez Bunuel Febuary 2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef FISH_HPP
#define FISH_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>



class Fish
{
public:

	Fish();
	~Fish();

	void setupFish();
	sf::RectangleShape getBody() { return m_body; }
	sf::Vector2f getPos() { return m_location; }

private:

	// Fish
	sf::RectangleShape m_body;
	sf::Vector2f m_location = { 60.0f, 300.0f };
	sf::Vector2f m_size = { 40.0f, 70.0f };

};

#endif // !GAME_HPP


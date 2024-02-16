/// <summary>
/// author Ian Perez Bunuel Febuary 2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef AREA_HPP
#define AREA_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>


class Area
{
public:

	Area();
	~Area();
	
	// Variables
	const float WIDTH = 60.0f; 
	const float GAP = 100.0f; 

	// Functions
	void setupArea(sf::Vector2f t_pos);

	sf::RectangleShape getBody() { return m_body; }
	sf::Vector2f getPos() { return m_location; }

private:

	// Variables
	const float HIGHT = 400.0f;

	// Area
	sf::RectangleShape m_body;
	sf::Vector2f m_location = { 50.0f, 150.0f }; // Position of first player
	sf::Vector2f m_size = { WIDTH, HIGHT };

};

#endif // !GAME_HPP


/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef PLAYER_HPP
#define PLAYER_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>




class Player
{
public:

	Player();
	~Player();

	// Player Functions
	void setupPlayer(sf::Vector2f t_pos);
	void move();
	void gravity();

	// Collision Functions
	void areaBoundries();
	void catchingCheck(bool t_colliding);

	// Get Variables
	sf::RectangleShape getBody() { return m_body; }
	sf::Vector2f getPos() { return m_location; }
	int getCatchingMeter() { return m_catchingMeter; }

	// Public Variables
	bool m_reeling = false;

private:


	// Player
	sf::RectangleShape m_body;
	sf::Vector2f m_location = { 55.0f, 155.0f };
	sf::Vector2f m_size = { 50.0f, 100.0f };

	// Catching
	const int WIN_CONDITION = 5 * 60; // Seconds needed on fish * Framerate
	int m_catchingMeter = 0;

	// Gravity
	sf::Vector2f m_gravity = { 0.0f, 2.0f };

};

#endif // !GAME_HPP


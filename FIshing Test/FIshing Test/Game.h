/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Fish.h"
#include "Player.h"
#include "Area.h"


const int MAX_PLAYERS = 5;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	// Objects (Fish)
	Fish fish1;
	Fish fish2;
	Fish fish3;
	Fish fish4;
	Fish fish5;
	Fish fishs[MAX_PLAYERS];
	// Objects (Player)
	Player player1;
	Player player2;
	Player player3;
	Player player4;
	Player player5;
	Player players[MAX_PLAYERS];
	// Objects (Area)
	Area area1;
	Area area2;
	Area area3;
	Area area4;
	Area area5;
	Area areas[MAX_PLAYERS];

	// Events
	void update(sf::Time t_deltaTime);
	void render();
	void processEvents();
	// Keys and Mouse
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);

	// Setups
	void setupFontAndText();
	void setupAmountOfPlayers();
	void setupArrays();

	// Collisions
	bool fishColliding();

	// Variables
	bool m_colliding = false;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_catchingText; // text used for message on screen
	bool m_exitGame; // control exiting game

	// Multiple people
	int playersPlaying = 5; // 1 will always be playing at least

	// Gravity
	sf::Vector2f m_gravity = {0.0f, 2.0f};

};

#endif // !GAME_HPP


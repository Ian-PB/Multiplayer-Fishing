/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupAmountOfPlayers(); // setup multiple players
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}

	// Mouse
	if (sf::Event::MouseButtonPressed == newEvent.type)
	{
		processMouseDown(newEvent);
	}

	if (sf::Event::MouseButtonReleased == newEvent.type)
	{
		processMouseUp(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouseDown(sf::Event t_event)
{
	player1.m_reeling = true;
}

void Game::processMouseUp(sf::Event t_event)
{
	player1.m_reeling = false;
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{

	// Collisions
	fishColliding();
	player1.areaBoundries();
	player1.catchingCheck(m_colliding);

	// Check if moving
	if (player1.m_reeling)
	{
		player1.move();
	}

	// Gravity
	player1.gravity();

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_catchingText);

	
	// Checks how many players are in the game and draws that amount
	switch (playersPlaying)
	{
	case 1:
		// Draw Areas
		m_window.draw(area1.getBody());
		// Draw Players
		m_window.draw(player1.getBody());

		break;

	case 2:
		// Draw Areas
		m_window.draw(area1.getBody());
		m_window.draw(area2.getBody());
		// Draw Players
		m_window.draw(player1.getBody());
		m_window.draw(player2.getBody());

		break;

	case 3:
		// Draw Areas
		m_window.draw(area1.getBody());
		m_window.draw(area2.getBody());
		m_window.draw(area3.getBody());
		// Draw Players
		m_window.draw(player1.getBody());
		m_window.draw(player2.getBody());
		m_window.draw(player3.getBody());

		break;

	case 4:
		// Draw Areas
		m_window.draw(area1.getBody());
		m_window.draw(area2.getBody());
		m_window.draw(area3.getBody());
		m_window.draw(area4.getBody());
		// Draw Players
		m_window.draw(player1.getBody());
		m_window.draw(player2.getBody());
		m_window.draw(player3.getBody());
		m_window.draw(player4.getBody());

		break;

	case 5:
		// Draw Areas
		m_window.draw(area1.getBody());
		m_window.draw(area2.getBody());
		m_window.draw(area3.getBody());
		m_window.draw(area4.getBody());
		m_window.draw(area5.getBody());
		// Draw Players
		m_window.draw(player1.getBody());
		m_window.draw(player2.getBody());
		m_window.draw(player3.getBody());
		m_window.draw(player4.getBody());
		m_window.draw(player5.getBody());

		break;
	}

	// Currently doesnt work
	//for (int i = 0; i < playersPlaying; i++)
	//{
	//	m_window.draw(players[i].getBody());
	//	m_window.draw(areas[i].getBody());
	//	m_window.draw(fishs[i].getBody());
	//}

	m_window.draw(fish1.getBody());

	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_catchingText.setFont(m_ArialBlackfont);
	m_catchingText.setString("Fish %: 0");
	m_catchingText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_catchingText.setPosition(250.0f, 40.0f);
	m_catchingText.setCharacterSize(80U);
	m_catchingText.setOutlineColor(sf::Color::Blue);
	m_catchingText.setFillColor(sf::Color::White);
	m_catchingText.setOutlineThickness(3.0f);

}

// Sets up each player in the game
void Game::setupAmountOfPlayers()
{
	// Variables needed
	sf::Vector2f pos1 = area1.getPos();
	sf::Vector2f pos2 = area2.getPos();
	sf::Vector2f pos3 = area3.getPos();
	sf::Vector2f pos4 = area4.getPos();
	sf::Vector2f pos5 = area5.getPos();
	
	// Currently doesnt work
	//for (int i = 0; i < playersPlaying; i++)
	//{
	//	// Players
	//	sf::Vector2f pos = {areas[i].getPos()};
	//	pos.x += (areas[i].GAP + areas[i].WIDTH) * i;  // Move the area over
	//	areas[i].setupArea(pos);
	//	players[i].setupPlayer(pos);
	//}

	switch (playersPlaying)
	{
	case 1:
		// First Player
		pos1.x += (area1.GAP + area1.WIDTH) * 0;  // Move the area over
		area1.setupArea(pos1);
		player1.setupPlayer(pos1);

		break;

	case 2:
		// First Player
		pos1.x += (area1.GAP + area1.WIDTH) * 0;  // Move the area over
		area1.setupArea(pos1);
		player1.setupPlayer(pos1);

		// Second Player
		pos2.x += (area2.GAP + area2.WIDTH) * 1;  // Move the area over
		area2.setupArea(pos2);
		player2.setupPlayer(pos2 += {5.0f, 5.0f});

		break;

	case 3:
		// First Player
		pos1.x += (area1.GAP + area1.WIDTH) * 0;  // Move the area over
		area1.setupArea(pos1);
		player1.setupPlayer(pos1);

		// Second Player
		pos2.x += (area2.GAP + area2.WIDTH) * 1;  // Move the area over
		area2.setupArea(pos2);
		player2.setupPlayer(pos2 += {5.0f, 5.0f});

		// Third Player
		pos3.x += (area3.GAP + area3.WIDTH) * 2;  // Move the area over
		area3.setupArea(pos3);
		player3.setupPlayer(pos3 += {5.0f, 5.0f});

		break;

	case 4:
		// First Player
		pos1.x += (area1.GAP + area1.WIDTH) * 0;  // Move the area over
		area1.setupArea(pos1);
		player1.setupPlayer(pos1);

		// Second Player
		pos2.x += (area2.GAP + area2.WIDTH) * 1;  // Move the area over
		area2.setupArea(pos2);
		player2.setupPlayer(pos2 += {5.0f, 5.0f});

		// Third Player
		pos3.x += (area3.GAP + area3.WIDTH) * 2;  // Move the area over
		area3.setupArea(pos3);
		player3.setupPlayer(pos3 += {5.0f, 5.0f});

		// Forth Player
		pos4.x += (area4.GAP + area4.WIDTH) * 3;  // Move the area over
		area4.setupArea(pos4);
		player4.setupPlayer(pos4 += {5.0f, 5.0f});

		break;

	case 5:
		// First Player
		pos1.x += (area1.GAP + area1.WIDTH) * 0;  // Move the area over
		area1.setupArea(pos1);
		player1.setupPlayer(pos1);

		// Second Player
		pos2.x += (area2.GAP + area2.WIDTH) * 1;  // Move the area over
		area2.setupArea(pos2);
		player2.setupPlayer(pos2 += {5.0f, 5.0f});

		// Third Player
		pos3.x += (area3.GAP + area3.WIDTH) * 2;  // Move the area over
		area3.setupArea(pos3);
		player3.setupPlayer(pos3 += {5.0f, 5.0f});

		// Forth Player
		pos4.x += (area4.GAP + area4.WIDTH) * 3;  // Move the area over
		area4.setupArea(pos4);
		player4.setupPlayer(pos4 += {5.0f, 5.0f});

		// Fifth Player
		pos5.x += (area5.GAP + area5.WIDTH) * 4;  // Move the area over
		area5.setupArea(pos5);
		player5.setupPlayer(pos5 += {5.0f, 5.0f});

		break;

	}
}

// Function that should change the corresponding player's Fish%
bool Game::fishColliding()
{
	sf::RectangleShape fishBody1 = fish1.getBody();

	// Player 1 Collisions
	if (player1.getBody().getGlobalBounds().intersects(fishBody1.getGlobalBounds()))
	{
		m_colliding = true;
	}
	else
	{
		m_colliding = false;
	}
	
	// Change text
	m_catchingText.setString("Fish %: " + (std::to_string(player1.getCatchingMeter() / 3)));

	return m_colliding;
}
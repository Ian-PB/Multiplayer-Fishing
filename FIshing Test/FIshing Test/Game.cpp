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
	setupArrays(); // sets up arrays with values
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

	if (sf::Keyboard::W == t_event.key.code)
	{
		player2.m_reeling = true;
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
	player1.catchingCheck(m_colliding);

	// Check if player1 is moving
	if (player1.m_reeling)
	{
		player1.move();
	}


	for (int i = 0; i < playersPlaying; i++)
	{
		players[i].areaBoundries();



		// Gravity
		players[i].gravity();
	}


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

	// Draws each player
	for (int i = 0; i < playersPlaying; i++)
	{
		m_window.draw(areas[i].getBody());
		m_window.draw(players[i].getBody());
		m_window.draw(fishs[i].getBody());
	}

	
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
	// Currently doesnt work
	for (int i = 0; i < playersPlaying; i++)
	{
		// Players
		sf::Vector2f pos = { areas[i].getPos() };

		pos.x += (GAP + WIDTH) * i;  // Move the area over
		// Give new location
		areas[i].setPos(pos);
		players[i].setPos(pos += {5.0f, 5.0f});
		fishs[i].setPos(pos += {5.0f, 300.0f});

		// Setup
		areas[i].setupArea();
		players[i].setupPlayer();
		fishs[i].setupFish();
	}
}

void Game::setupArrays()
{
	// Fish Array
	fishs[0] = fish1;
	fishs[1] = fish2;
	fishs[2] = fish3;
	fishs[3] = fish4;
	fishs[4] = fish5;

	// Players Array
	players[0] = player1;
	players[1] = player2;
	players[2] = player3;
	players[3] = player4;
	players[4] = player5;

	// Areas Array
	areas[0] = area1;
	areas[1] = area2;
	areas[2] = area3;
	areas[3] = area4;
	areas[4] = area5;
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